#pragma once

#include "iostream"
#include "../ecs/component.hpp"
#include "mesh-renderer.hpp"
#include <glm/glm.hpp>

namespace our {

    // This component denotes that the MovementSystem will move the owning entity by a certain linear and angular velocity.
    // This component is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/systems/movement.hpp"
    // For a more complex example of how to use the ECS framework, see "free-camera-controller.hpp"
    class CollisionComponent : public Component {
    public:
        glm::vec3 boundingBoxCenter = {0, 0, 0}; // Each frame, the entity should move as follows: position += linearVelocity * deltaTime 
        glm::vec3 highestBoundingBoxVertex = {0, 0, 0}; // Each frame, the entity should rotate as follows: rotation += angularVelocity * deltaTime
        float radius = 0.0;
        // constructor of the collision component
        CollisionComponent();
        // Calculate center
        glm::vec3 calculateCenter(int, int, int, int, int, int);
        // Calculate HighestVertex
        glm::vec3 calculateHighestVertex(int, int, int, int, int, int);
        // Calculate Radius
        float calculateRadius(glm::vec3, glm::vec3);
        // The ID of this component type is "Movement"
        static std::string getID() { return "Collision"; }

        // Reads linearVelocity & angularVelocity from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}