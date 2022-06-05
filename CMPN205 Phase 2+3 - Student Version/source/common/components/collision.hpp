#pragma once

#include "iostream"
#include "../ecs/component.hpp"
#include "mesh-renderer.hpp"
#include <glm/glm.hpp>

namespace our {

    /**
     * Collision component is responsible for add the collision property its entity
     * and it's based on the bounding box surrounding the entity, and use it to detect if it collides or not
     * here we use bounding ball and store its center and farest point of the shape and use them 
     * to form the ball
    */
    class CollisionComponent : public Component {
    public:
        glm::vec3 boundingBoxCenter = {0, 0, 0}; 
        glm::vec3 highestBoundingBoxVertex = {0, 0, 0};
        float radius = 0.0;
        //initilize the component with its center and radius
        void init();
        /**
         * Calculate the center of the ball using the min, max x, y, z for 
         * the shape by calculating their average
         * @param minX
         * @param maxX
         * @param minY
         * @param maxY
         * @param minZ
         * @param maxZ
        */
        glm::vec3 calculateCenter(float, float, float, float, float, float);
        // Calculate HighestVertex by getting max point in the shape
        glm::vec3 calculateHighestVertex(float, float, float, float, float, float);
        // Calculate Radius
        float calculateRadius(glm::vec3, glm::vec3);
        // The ID of this component type is "Collision"
        static std::string getID() { return "Collision"; }
        // Reads ball center & highest point from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}