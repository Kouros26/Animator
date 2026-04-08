#include "Resources/model.hpp"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "assimp/material.h"

Model::Model()
    : IResource("resources/models/cube.obj")
{
}

Model::Model(const std::string& pPath)
	: IResource(pPath)
{
	LoadModel();
}

Model::Model(const std::string& pPath, const std::string& pTexturePath)
    : IResource(pPath)
{
    LoadModel();
    LoadTexture(pTexturePath);
}

void Model::Draw(const unsigned shaderProgram) const
{
    for (const auto& mesh : meshes)
    {
	    mesh.Draw(shaderProgram);
    }
}

void Model::AddMesh(const std::string& pPath)
{
    resourcePath = pPath;

    LoadModel();
}

void Model::AddMesh(const std::string& pPath, const std::string& pTexturePath)
{
    resourcePath = pPath;

    LoadModel(pTexturePath);
}

std::vector<Mesh>& Model::GetMeshes()
{
    return meshes;
}

void Model::LoadModel(const std::string& pTexturePath)
{
    Assimp::Importer import;
    const aiScene * scene = import.ReadFile(PROJECT_PATH + resourcePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
	    std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    ProcessNode(scene->mRootNode, scene, pTexturePath);
}

void Model::ProcessNode(const aiNode* node, const aiScene* scene, const std::string& pPath)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
	    const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene, pPath));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene, pPath);
    }
}

Mesh Model::ProcessMesh(const aiMesh* mesh, const aiScene* scene, const std::string& pPath)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.BiTangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    Texture texture(pPath == "" ? "resources/textures/container.jpg" : pPath);

    if (texture.GetValidity())
    {
        textures.push_back(texture);
    }

    return { vertices, indices, textures };
}

std::vector<Texture> Model::LoadMaterialTextures(const aiMaterial* mat, const aiTextureType type, const std::string& name) const
{
    std::vector<Texture> textures;
    const std::string path = resourcePath +  "/../textures/" + name;
    const Texture texture(path);

    if (texture.GetValidity())
    {
        textures.push_back(texture);
    }

    return textures;
}

void Model::LoadTexture(const std::string& path)
{
    Texture texture(path);

    if (!texture.GetValidity())
        return;

    std::vector<Texture> textures;
    textures.push_back(texture);

    for (auto& mesh : meshes)
    {
        mesh.SetTextures(textures);
    }
}
