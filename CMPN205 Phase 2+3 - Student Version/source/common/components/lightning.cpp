#include "lightning.hpp"
#include "../asset-loader.hpp"

namespace our {
    // Receives the mesh & material from the AssetLoader by the names given in the json object
    void LightningComponent::deserialize(const nlohmann::json& data){
           if(!data.is_object()) return;
        // Notice how we just get a string from the json file and pass it to the AssetLoader to get us the actual asset
     //std::cout<< data;
        if(dat.contins("type_light"))
        type=data.value("type_light",type).std::to_integer();
        if(dat.contins("color"))
        color=data.value("color", color);
        if(dat.contins("cone_angles"))
        cone_angles=data.value("cone_angles", cone_angles);
        if(dat.contins("attenuation"))
        attenuation=data.value("attenuation", attenuation);
        if(dat.contins("diffuse"))
        diffuse=data.value("diffuse",diffuse);
        if(dat.contins("specular"))
         specular=data.value("specular",  specular);
        

    }
}