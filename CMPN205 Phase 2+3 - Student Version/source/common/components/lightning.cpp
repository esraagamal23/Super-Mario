#include "light.hpp"
#include "../asset-loader.hpp"

namespace our {
    // Receives the mesh & material from the AssetLoader by the names given in the json object
    void LightningComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        // Notice how we just get a string from the json file and pass it to the AssetLoader to get us the actual asset
     
    
          int type_light=data.value("type_light", type);
           color=data.value("color", color);
          cone_angles=glm::radians(data.value("cone_angles", cone_angles)[0]), glm::radians(data.value("cone_angles", cone_angles)[1])
    }
}