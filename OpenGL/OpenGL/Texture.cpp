#include "Texture.h"

unsigned int Texture::num_textures = 0;

/* Default constructor */
Texture::Texture()
{
	num_textures++;
}

/* De-constructor */
Texture::~Texture()
{
	num_textures--;
}

/* Private function: Bind a texture file to an specified ID */
bool Texture::bindTexture(char const * path, unsigned int &id)
{
	glGenTextures(1, &id);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
		return true;
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
		return false;
	}
}

/* Add a texture file to this texture object. Specify filepath and the texture type, ex. 'TXT_NORMAL' */
bool Texture::addTexture(const std::string path, const TEXTURE_TYPE type)
{
	if (type == TXT_DIFFUSE)
	{
		return addDiffuse(path.c_str());
	}
	else if (type == TXT_SPECULAR)
	{
		return addSpecular(path.c_str());
	}
	else if (type == TXT_NORMAL)
	{
		return addNormal(path.c_str());
	}
	else if (type == TXT_DISPLACEMENT)
	{
		return addDisplacement(path.c_str());
	}
	else if (type == TXT_AO)
	{
		return addAO(path.c_str());
	}
	else return false;
}

/* Add a diffuse texture file to this texture object. Specify filepath */
bool Texture::addDiffuse(const std::string path)
{
	diffuseBound = bindTexture(path.c_str(), diffuse_id);
	return diffuseBound;		
}

/* Add a specular texture file to this texture object. Specify filepath */
bool Texture::addSpecular(const std::string path)
{
	specularBound = bindTexture(path.c_str(), specular_id);
	return specularBound;
}

/* Add a normal texture file to this texture object. Specify filepath */
bool Texture::addNormal(const std::string path)
{
	normalBound = bindTexture(path.c_str(), normal_id);
	return normalBound;
}

/* Add a displacement texture file to this texture object. Specify filepath */
bool Texture::addDisplacement(const std::string path)
{
	displacementBound = bindTexture(path.c_str(), displacement_id);
	return displacementBound;
}

/* Add a ambient oclusion texture file to this texture object. Specify filepath */
bool Texture::addAO(const std::string path)
{
	AOBound = bindTexture(path.c_str(), ao_id);
	return AOBound;
}

/* Returns a bool whether this texture object has a diffuse texture file bound or not */
bool Texture::hasDiffuse() {
	return diffuseBound;
}

/* Returns a bool whether this texture object has a specular texture file bound or not */
bool Texture::hasSpecular()
{
	return specularBound;
}

/* Returns a bool whether this texture object has a normal texture file bound or not */
bool Texture::hasNormal()
{
	return normalBound;
}

/* Returns a bool whether this texture object has a displacement texture file bound or not */
bool Texture::hasDisplacement()
{
	return displacementBound;
}

/* Returns a bool whether this texture object has a ambient oclusion texture file bound or not */
bool Texture::hasAO()
{
	return AOBound;
}

/* Get the unique diffuse texture ID generated by glGenTextures */
unsigned int Texture::getDiffuse()
{
	return diffuse_id;
}

/* Get the unique specular texture ID generated by glGenTextures */
unsigned int Texture::getSpecular()
{
	return specular_id;
}

/* Get the unique normal texture ID generated by glGenTextures */
unsigned int Texture::getNormal()
{
	return normal_id;
}

/* Get the unique dispalcement texture ID generated by glGenTextures */
unsigned int Texture::getDisplacement()
{
	return displacement_id;
}

/* Get the unique ambient oclusion texture ID generated by glGenTextures */
unsigned int Texture::getAO() {
	return ao_id;
}

/* Return the number of textures created on this stack */
unsigned int Texture::getNumTextures()
{
	return num_textures;
}