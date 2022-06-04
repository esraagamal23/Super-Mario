#pragma once

#include "../ecs/component.hpp"
#include "../mesh/mesh.hpp"
#include "../material/material.hpp"
#include "../asset-loader.hpp"

namespace our {

    // This component denotes that any renderer should draw the given mesh using the given material at the transformation of the owning entity.
    class LightningComponent : public Component {

      public:
        
       
          int type_light;
          glm::vec4 color;
         glm::ec2 cone_angles; // x: inner_angle, y: outer_angle  
        // The ID of this component type is "Mesh Renderer"
       static std::string getID() { return "lighting"; }

        // Receives the mesh & material from the AssetLoader by the names given in the json object
        void deserialize(const nlohmann::json& data) override;

    
    };

}