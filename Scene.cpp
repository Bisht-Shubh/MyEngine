#include "pch.h"
#include "Scene.h"

#include "ResourceManager.h"
#include "MeshRenderer.h"
#include "Shader.h"
#include "Skybox.h"
#include "Terrain.h"
#include "Cube.h"
#include "Model.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "Window.h"

#include<chrono>

// LIGHTING
DirectionalLight* directionalLight;   // a directional light source, like sunlight, that illuminates all objects in the scene from a specific direction

// MODELS
Model* modelCar;           // load a model (e.g. .obj file) and render it in the scene
Model* modelTree;          // load a model (e.g. .obj file) and render it in the scene

Skybox* skybox;              // a cube that surrounds the entire scene and is textured with a skybox texture to create the illusion of distant surroundings


Scene::Scene(unsigned int width, unsigned int height, Input& input)
	: Width(width), Height(height), Keys(), input(input)  
{

}

Scene::~Scene()
{
    glfwTerminate();
}

//-------------------------------------------------------------------------------------------//
//------------------------------INITIALIZATION AND GAME LOOP----------------------------------//
//-------------------------------------------------------------------------------------------//

void Scene::Init()
{
	camera = new Camera(Width, Height, 45.0f);

    // Load time of shaders
    auto start = std::chrono::high_resolution_clock::now();

    //-------------------------------------------------------------------------------------------//
	//---------------------LOAD SHADERS AND PRINT LOAD TIME TO CONSOLE---------------------------//
	//-------------------------------------------------------------------------------------------//
	ResourceManager::LoadShader("D:/OpenGL/MyEngine/Mesh_vs.txt", "D:/OpenGL/MyEngine/Mesh_fs.txt", nullptr, "cube");
    ResourceManager::LoadShader("D:/OpenGL/MyEngine/SkyBox_vs.txt", "D:/OpenGL/MyEngine/SkyBox_fs.txt", nullptr, "skybox");
    ResourceManager::LoadShader("D:/OpenGL/MyEngine/Depth_vs.txt", "D:/OpenGL/MyEngine/Depth_fs.txt", nullptr, "depth");

    auto end = std::chrono::high_resolution_clock::now();       // END LOAD TIME

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\nDEBUG::Loaded shaders in::" << duration.count() << "ms";

    // List loaded shaders
    std::stringstream ss;

    ss << "\n============================================\n";
    ss << "DEBUG::Shader loading complete";
    ss << "\nLOADED_SHADERS::(" << ResourceManager::Shaders.size() << ")\n";    // print total shaders loaded
    ss << "\n--------------------------------------------\n";

    for (const auto& [name, shader] : ResourceManager::Shaders)
        ss << name << "\n";                         // print all shaders name

    ss << "============================================\n";

    std::cout << ss.str();
	//-------------------------------------------------------------------------------------------//
    //-------------------------------------------------------------------------------------------//
    
    //------------------------------------------------------------------------------------------//
    //----------------------------------------LOAD TEXTURE--------------------------------------//
	//------------------------------------------------------------------------------------------//


    // Load models
	modelCar = new Model("D:/Assets/Blender Files/Table.obj");
	modelTree = new Model("D:/Assets/Blender Files/Tree.obj");
    std::cout << "DEBUG::ModelCar meshes: " << modelCar->meshes.size() << "\n";
    std::cout << "DEBUG::ModelTree meshes: " << modelTree->meshes.size() << "\n";

    // Generate depth map framebuffer/texture for shadow mapping
    genDepthMap(depthMapFBO, depthMap, SHADOW_WIDTH, SHADOW_HEIGHT);

    // Ensure the cube shader samples the shadow map from texture unit 2
    ResourceManager::GetShader("cube").Use().SetInteger("shadowMap", 2, true);

	skybox = new Skybox("D:/Assets/Textures/CubeMaps/skybox");

    // Set properties of light
    glm::vec3 direction = glm::normalize(glm::vec3(1.3f, -1.0f, 2.5f));
    glm::vec3 diffuse = glm::vec3(2.0f, 1.9f, 1.98f);
    glm::vec3 specular = glm::vec3(0.9, 0.7f, 0.5f);
    glm::vec3 ambient = glm::vec3(0.25f, 0.25f, 0.22f);

    // Set directional light properties and add to scene
    DirectionalLight* directionalLight = new DirectionalLight(direction, ambient, diffuse, specular);
    SetDirectionalLight(direction, ambient, diffuse, specular);
}

//-------------------------------------------------------------------------------------------//
//------------------------------INPUT, UPDATE AND RENDERING----------------------------------//
//-------------------------------------------------------------------------------------------//


void Scene::Update(float dt)
{
    if (updateCallback)
        updateCallback(*this, dt);

    
}

void Scene::Render()
{
    // Screen details
    glViewport(0, 0, Width, Height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //--------------------------------------------------------------------------------------------------//
    //-----------------------------------------RENDER MODE----------------------------------------------//
	//--------------------------------------------------------------------------------------------------//

    // 2 render passes are required to render shadows in the scene. 
    // The first pass renders the scene from the light's perspective and creates a depth map (shadow map) 
    // that stores the distance of each fragment from the light source. The second pass renders the scene 
    // from the camera's perspective, using the depth map to determine whether each fragment is in shadow or not.
    
    //---------------------------------------------------------------------------------------------------//
	//--------------------------SHADOW PASS : RENDER FROM LIGHTS PERSPECTIVE-----------------------------//
	//---------------------------------------------------------------------------------------------------//

    glEnable(GL_CULL_FACE);
    // Use back-face culling for the depth pass (standard for shadow mapping)
    glCullFace(GL_BACK);
    // Enable polygon offset to help prevent shadow acne
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2.0f, 4.0f);


    // Shadow mapping properties
    glm::mat4 lightSpaceMatrix;
    glm::mat4 lightProjection;
    glm::mat4 lightView;
    // Shadow camera extents and precision
    float nearPlane = 1.0f;
    float farPlane = 100.0f;

    // Tighten orthographic box to scene extents to improve shadow quality
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);

    glm::vec3 lightTarget = glm::vec3(0.0f); // center of the scene
    // Place the directional 'camera' sufficiently far along the light direction so the ortho projection covers the scene
    float lightDistance = 30.0f; // tune this value if shadows appear offset or clipped
    glm::vec3 lightPosDir = lightTarget - directionalLight->GetDirection() * lightDistance;
    lightView = glm::lookAt(lightPosDir, lightTarget, glm::vec3(0.0f, 1.0f, 0.0f)); // Create the light's view matrix

    lightSpaceMatrix = lightProjection * lightView;
    // Pass the light space matrix to the shader for shadow mapping
	ResourceManager::GetShader("depth").Use().SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    // Use distinct model matrices per object and keep them consistent between passes
    glm::mat4 modelCarModel = glm::mat4(1.0f);
    modelCarModel = glm::translate(modelCarModel, glm::vec3(-2.0f, -0.775f, -3.0f)); // Move the car back and down the z-axis
	modelCarModel = glm::rotate(modelCarModel, glm::radians(-75.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate the car to face forward
    modelCarModel = glm::scale(modelCarModel, glm::vec3(0.25f)); // Scale down if needed

    ResourceManager::GetShader("depth").Use().SetMatrix4("model", modelCarModel);

    glm::mat4 modelTreeModel = glm::mat4(1.0f);
    modelTreeModel = glm::translate(modelTreeModel, glm::vec3(0.0f, 0.0f, -3.0f)); // Move the tree back on z-axis
    ResourceManager::GetShader("depth").Use().SetMatrix4("model", modelTreeModel);
    modelTree->Draw(ResourceManager::GetShader("depth"));
    // Disable polygon offset after depth pass
    glDisable(GL_POLYGON_OFFSET_FILL);

	//---------------------------------------------------------------------------------------------------//
	//--------------------------RENDER PASS : RENDER FROM CAMERAS PERSPECTIVE-----------------------------//
	//---------------------------------------------------------------------------------------------------//

	glCullFace(GL_BACK); // Restore default culling
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, Width, Height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ResourceManager::GetShader("cube").Use().SetVector3f("viewPos", camera->GetCameraPos());
    directionalLight->ApplyLight(ResourceManager::GetShader("cube").Use());
    ResourceManager::GetShader("cube").Use().SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);
    // Pass camera matrices to the shader
    ResourceManager::GetShader("cube").Use().SetMatrix4("view", camera->GetView());
    ResourceManager::GetShader("cube").Use().SetMatrix4("projection", camera->GetProjection());
    glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, depthMap);

    // Render from camera using the exact same model matrices used for the depth pass
    ResourceManager::GetShader("cube").Use().SetMatrix4("model", modelCarModel);
    //modelCar->Draw(ResourceManager::GetShader("cube"));

    ResourceManager::GetShader("cube").Use().SetMatrix4("model", modelTreeModel);
    modelTree->Draw(ResourceManager::GetShader("cube"));

	// Render skybox last with depth function set to less or equal so it renders behind all other objects
	glDepthFunc(GL_LEQUAL);
	skybox->Draw(ResourceManager::GetShader("skybox"), camera->GetView(), camera->GetProjection());
	glDepthFunc(GL_LESS);
    
}

void Scene::SetUpdateCallback(UpdateCallback callback)
{
    updateCallback = std::move(callback);
}

//--------------------------------------------------------------------------------------------//
//-----------------------------WINDOW INITIALIZATION AND INPUT CALLBACKS----------------------//
//-------------------------------------------------------------------------------------------//

void Scene::SetCamera(Camera* cam)
{
	camera = cam;
}

Camera& Scene::GetCamera()
{
    return *camera;
}

//---------------------------------------------------------------------------------------------------------------//
//-------------------------------------LIGHTING SETUP AND CALLBACKS----------------------------------------------//
//---------------------------------------------------------------------------------------------------------------//

void Scene::SetDirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
{
	directionalLight = new DirectionalLight(direction, ambient, diffuse, specular);
	//directionalLight->ApplyLight(ResourceManager::GetShader("cube"));
}

// Generate depth map for shadow mapping
void Scene::genDepthMap(unsigned int& depthMapFBO, unsigned int& depthMap, unsigned int SHADOW_WIDTH, unsigned int SHADOW_HEIGHT)
{
    glGenFramebuffers(1, &depthMapFBO);
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Check FBO completeness
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Depth framebuffer not complete: " << status << "\n";
    else
        std::cout << "DEBUG::FRAMEBUFFER:: Depth framebuffer created and complete. FBO=" << depthMapFBO << " tex=" << depthMap << "\n";
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

