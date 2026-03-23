//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 6/8/2022.
//

#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Shader.h"
#include "Texture2D.h"
#include "AudioClip.h"
#include "TextFont.h"

class AssetManager
{
    static AssetManager* instance;

    std::map<std::string, Shader>   shaders;
    std::map<std::string, Texture2D>  textures;
    std::map<std::string, AudioClip>  audioClips;
    std::map<std::string, TextFont> textFonts;

//    FT_Library ft;

    // This is a singleton so the constructor is private
    AssetManager();

public:
    static AssetManager *getInstance();

    Shader loadShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath, std::string name);
    Shader getShader(std::string name);

    Texture2D loadTexture(const char* path, bool alpha, std::string name);
    Texture2D getTexture(std::string name);

    AudioClip loadAudioClip(const char* path, AudioFileFormat fileFormat, std::string name);
    AudioClip getAudioClip(std::string name);

    TextFont loadTextFont(const char* path, std::string name, int size);
    TextFont getTextFont(std::string name);

    void clear();

private:
    Shader loadShaderFromFile(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath);
    Texture2D loadTextureFromFile(const char* file, bool alpha);
    AudioClip loadAudioClipFromFile(const char* file, AudioFileFormat fileFormat);
    TextFont loadTextFontFromFile(const char* file, int size);
};

#endif //ASSET_MANAGER_H
