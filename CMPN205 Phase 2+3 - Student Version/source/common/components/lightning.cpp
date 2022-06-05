#include "lightning.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Receives the mesh & material from the AssetLoader by the names given in the json object
    void  LightningComponent::deserialize(const nlohmann::json& data){
           if(!data.is_object()) return;
        // Notice how we just get a string from the json file and pass it to the AssetLoader to get us the actual asset
     //std::cout<< data;
         if(data.contains("type_light"))
        type=data.value("type_light",type);
       if(data.contains("color"))
        color=data.value("color", color);
        if(data.contains("cone_angles"))
        cone_angles=data.value("cone_angles", cone_angles);
       if(data.contains("attenuation"))
        attenuation=data.value("attenuation", attenuation);
       if(data.contains("diffuse"))
        diffuse=data.value("diffuse",diffuse);
        if(data.contains("specular"))
         specular=data.value("specular",  specular);
        

    }
}