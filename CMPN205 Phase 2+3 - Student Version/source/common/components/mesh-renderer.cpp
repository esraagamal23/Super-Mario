#include "mesh-renderer.hpp"
#include "../asset-loader.hpp"
#include <iostream>

namespace our {
    // Receives the mesh & material from the AssetLoader by the names given in the json object
    void MeshRendererComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        // Notice how we just get a string from the json file and pass it to the AssetLoader to get us the actual asset
        mesh = AssetLoader<Mesh>::get(data["mesh"].get<std::string>());
        mesh->name = data.value("mesh","");
        material = AssetLoader<Material>::get(data["material"].get<std::string>());
    }
}