#include "pch.h"
#include "Texture.h"

Texture::Texture()
    : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &this->ID);
}

Texture::~Texture()
{
    if (ID != 0)
    {
        glDeleteTextures(1, &this->ID);
        ID = 0;
    }
}

Texture::Texture(Texture&& other) noexcept
    : ID(other.ID),
      Width(other.Width),
      Height(other.Height),
      Internal_Format(other.Internal_Format),
      Image_Format(other.Image_Format),
      Wrap_S(other.Wrap_S),
      Wrap_T(other.Wrap_T),
      Filter_Min(other.Filter_Min),
	  Filter_Max(other.Filter_Max)
{
	other.ID = 0; // Prevent other from deleting the texture
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	if (this != &other)    
    {
        if (ID != 0)
        {
			glDeleteTextures(1, &this->ID);
        }

		// Transfer ownership of texture data
        ID = other.ID;
		Width = other.Width;
		Height = other.Height;
		Internal_Format = other.Internal_Format;
		Image_Format = other.Image_Format;
		Wrap_S = other.Wrap_S;
		Wrap_T = other.Wrap_T;
		Filter_Min = other.Filter_Min;
		Filter_Max = other.Filter_Max;

        // Reset other
		other.ID = 0; 
    }

    return *this;
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->Width = width;
    this->Height = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}