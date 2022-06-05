#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

   
    class LightningComponent : public Component {

      public:
        
          int type=1;
        
        glm::vec4 color={1,0,0,0};
        glm::vec2 cone_angles={10.0f, 1.0f};
        glm::vec3 attenuation={1, 0, 0};
        glm::vec3 diffuse= {1, 0.9, 0.7};
        glm::vec3 specular={1, 0.9, 0.7};
           
        
       
       static std::string getID() { return "lighting"; }

       
        void deserialize(const nlohmann::json& data) override;

    
    };

}