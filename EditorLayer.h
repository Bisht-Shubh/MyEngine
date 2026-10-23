#pragma once

#include <optional>

class Game;
class DebugLayer;
class imGuiLayer;
class Input;

class EditorLayer
{
public:

    enum class Mode
    {
        Editor,
        Game
    };

    EditorLayer(
        Game& game,
        Input& input,
        DebugLayer& debugLayer,
        imGuiLayer& imguiLayer
    );

    void Update(float deltaTime);
    void CheckInput();

    void SwitchToEditorMode();
    void SwitchToGameMode();

    bool IsEditorMode() const;
    bool IsGameMode() const;

private:

    Game& m_game;
    Input& m_input;
    DebugLayer& m_debugLayer;
    imGuiLayer& m_imguiLayer;
    std::optional<unsigned int> m_selectedEntityID;

    Mode m_mode{ Mode::Editor };

    // Temporary
    float m_temperature{ 0.0f };
    float GetTemperature()
    {
        return m_temperature;
    }
};