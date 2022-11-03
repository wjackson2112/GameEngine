//
// Created by Will on 5/31/2022.
//

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <assimp/scene.h>

#include "Mesh.h"

class Model
{
public:
    explicit Model(std::string path);
    void draw(Shader &shader);
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> loadedTextures;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    static unsigned int loadTexture(const std::string& texturePath);
};

#endif //MODEL_H
