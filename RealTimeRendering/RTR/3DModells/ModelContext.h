#pragma once

#include <RTR/3DModells/ModelBuffer.h>

#include <DirectXMath.h>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace RTR
{
    // Set of vertices and indices
    struct MeshInfo
    {
        ModelPartView vertexBuffer;
        ModelPartView indexBuffer;
        UINT indexCount;
        std::string name;
    };

    // Model draw info
    struct ModelInfo
    {
        size_t idx, count;

        // Checks if valid
        inline operator bool()
        {
            return count;
        }
    };

    // Callback for vertex creation
    typedef void(*FModelVertexCallback)(void* vtxOut, size_t idx, const aiMesh* ptrMesh);

    // Class that manages model uploading and stuff context 
    class ModelContext
    {
        public:
            // Construct
            ModelContext() = delete;
            ModelContext(const ModelContext&) = delete;
            ModelContext(UINT64 memoryBudget);

            // Assign
            ModelContext& operator=(const ModelContext&) = delete;

            // Load a model form disk
            ModelInfo LoadModel(const char* filePath, D3DUploadBuffer& uploader, size_t vertexSize, FModelVertexCallback callback);
            MeshInfo GetMeshInfo(ModelInfo& modelInfo, size_t idx = 0);

            // Retrive buffer resource
            inline D3DResource* GetGeometryBufferResource()
            {
                return &m_geometryDataBuffer;
            }

        private:
            // Index and vertex buffer
            ModelBuffer m_geometryDataBuffer;

            // Vector of drawable data
            std::vector<MeshInfo> m_sets;
    };
}
