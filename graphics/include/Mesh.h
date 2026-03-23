//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    Vertex()
    : position(glm::vec3(0.0f))
    , normal(glm::vec3(0.0f))
    , texCoords(glm::vec2(0.0f)){}
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
    public:
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);
        void draw(Shader &shader);
    private:
        // render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};

#endif