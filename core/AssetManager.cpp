
#include "AssetManager.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include <direct.h>
#define GetCurrentDir _getcwd

#include "stb_image.h"

AssetManager *AssetManager::instance = nullptr;

AssetManager::AssetManager() {}

AssetManager* AssetManager::getInstance()
{
    if(!instance)
        instance = new AssetManager();
    return instance;
}

Shader AssetManager::loadShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath, std::string name)
{
    if(shaders.count(name))
        return shaders[name];

    shaders[name] = loadShaderFromFile(vertexShaderPath, fragmentShaderPath, geometryShaderPath);
    return shaders[name];
}

Shader AssetManager::getShader(std::string name)
{
    return shaders[name];
}

Texture2D AssetManager::loadTexture(const char* path, bool alpha, std::string name)
{
    if(textures.count(name))
        return textures[name];

    textures[name] = loadTextureFromFile(path, alpha);
    return textures[name];
}

Texture2D AssetManager::getTexture(std::string name)
{
    return textures[name];
}

AudioClip AssetManager::loadAudioClip(const char* path, AudioFileFormat fileFormat, std::string name)
{
    if(audioClips.count(name))
        return audioClips[name];

    audioClips[name] = loadAudioClipFromFile(path, fileFormat);
    return audioClips[name];
}

AudioClip AssetManager::getAudioClip(std::string name)
{
    return audioClips[name];
}

TextFont AssetManager::loadTextFont(const char *path, std::string name, int size)
{
    if(textFonts.count(name))
        return textFonts[name];

    textFonts[name] = loadTextFontFromFile(path, size);
    return textFonts[name];
}

TextFont AssetManager::getTextFont(std::string name)
{
    return textFonts[name];
}

void AssetManager::clear()
{
    for(auto iter : shaders)
        glDeleteProgram(iter.second.id);
    for(auto iter : textures)
        glDeleteTextures(1, &iter.second.id);
}

Shader AssetManager::loadShaderFromFile(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath)
{
    std::string vertexCode, fragmentCode, geometryCode;
    std::ifstream vertexFile, fragmentFile, geometryFile;

    // Ensure ifstream objects can throw exceptions:
    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    geometryFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        char vert_buff[200]; //create string buffer to hold path
        char frag_buff[200];
        GetCurrentDir( vert_buff, 200 );
        GetCurrentDir( frag_buff, 200 );
        strcat(vert_buff, "\\");
        strcat(vert_buff, vertexShaderPath);

        strcat(frag_buff, "\\");
        strcat(frag_buff, fragmentShaderPath);

        // Open files
        vertexFile.open(vert_buff);
        fragmentFile.open(frag_buff);
        std::stringstream vertexStream, fragmentStream;

        // Read file's buffer contents in to streams
        vertexStream << vertexFile.rdbuf();
        vertexFile.close();
        vertexCode   = vertexStream.str();

        fragmentStream << fragmentFile.rdbuf();
        fragmentFile.close();
        fragmentCode = fragmentStream.str();

        // if geometry shader path is present, also load a geometry shader
        if (geometryShaderPath)
        {
            std::ifstream geometryFile(geometryShaderPath);
            std::stringstream geometryStream;
            geometryStream << geometryFile.rdbuf();
            geometryFile.close();
            geometryCode = geometryStream.str();
        }
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    Shader shader;
    shader.compile(vertexCode, fragmentCode, geometryCode);
    return shader;
}

Texture2D AssetManager::loadTextureFromFile(const char* path, bool alpha)
{
    Texture2D texture;
    if(alpha)
    {
        texture.internalFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    }

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    texture.generate(width, height, data);

    stbi_image_free(data);
    return texture;
}

AudioClip AssetManager::loadAudioClipFromFile(const char* file, AudioFileFormat fileFormat)
{
    AudioClip audioClip;

    audioClip.load(file, fileFormat);

    return audioClip;
}

TextFont AssetManager::loadTextFontFromFile(const char *file, int size)
{
    TextFont textFont;

    textFont.load(file, size);

    return textFont;
}