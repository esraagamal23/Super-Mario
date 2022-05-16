#include "entity.hpp"
#include "../deserialize-utils.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our {

    // This function computes and returns a matrix that represents this transform
    // Remember that the order of transformations is: Scaling, Rotation then Translation
    // HINT: to convert euler angles to a rotation matrix, you can use glm::yawPitchRoll
    glm::mat4 Transform::toMat4() const {
        //TODO: (Req 2) Write this function
     
     //translation matrix
        glm::mat4 translate = glm::mat4(1.0f);
        translate =glm::translate(translate, position);
        //scaling matrix
        glm::mat4  Scale = glm::mat4(1.0f);
        Scale = glm::scale( Scale,scale); 
        //rotation matrix
         glm::mat4  Rotate = glm::mat4(1.0f);
       Rotate =glm::yawPitchRoll(rotation.y,rotation.x,rotation.z);
         glm::mat4 transform =translate*Rotate* Scale;  ///transformation matrix

        return transform;
        
    }

     // Deserializes the entity data and components from a json object
    void Transform::deserialize(const nlohmann::json& data){
        position = data.value("position", position);
        rotation = glm::radians(data.value("rotation", glm::degrees(rotation)));
        scale    = data.value("scale", scale);
    }

}