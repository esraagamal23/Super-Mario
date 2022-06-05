#include "collision.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {

    void CollisionComponent::init()
    {
        Entity* entity = getOwner();
        if(!entity)
        std::cerr << "error" << std::endl;
        MeshRendererComponent *meshRenderer = entity->getComponent<MeshRendererComponent>();
        if(!meshRenderer)
        {
            std::cerr << "There is no mesh rendered attached to this entity" << std::endl;
            std::exit(-1);
        }
        float maxX = meshRenderer->mesh->maxX;
        float minX = meshRenderer->mesh->minX;
        float maxY = meshRenderer->mesh->maxY;
        float minY = meshRenderer->mesh->minY;
        float maxZ = meshRenderer->mesh->maxZ;
        float minZ = meshRenderer->mesh->minZ;
        boundingBoxCenter = glm::vec4(calculateCenter(minX, maxX, minY, maxY, minZ, maxZ), 1);
        highestBoundingBoxVertex = glm::vec4(calculateHighestVertex(minX, maxX, minY, maxY, minZ, maxZ), 1);
        radius = calculateRadius(boundingBoxCenter, highestBoundingBoxVertex);
    }

    glm::vec3 CollisionComponent::calculateCenter(float mnX, float mxX, float mnY, float mxY, float mnZ, float mxZ)
    {
        float cX = (mnX + mxX) / 2;
        float cY = (mnY + mxY) / 2;
        float cZ = (mnZ + mxZ) / 2;
        return glm::vec3(cX, cY, cZ);
    }

    glm::vec3 CollisionComponent::calculateHighestVertex(float mnX, float mxX, float mnY, float mxY, float mnZ, float mxZ)
    {
        float maxX = glm::max(glm::abs(mnX), glm::abs(mxX));
        float maxY = glm::max(glm::abs(mnY), glm::abs(mxY));
        float maxZ = glm::max(glm::abs(mnZ), glm::abs(mxZ));
        return glm::vec3(maxX, maxY, maxZ);
    }

    float CollisionComponent::calculateRadius(glm::vec3 point1, glm::vec3 point2)
    {
        return glm::sqrt(glm::pow(point1[0] - point2[0], 2) + glm::pow(point1[1] - point2[1], 2) + glm::pow(point1[2] - point2[2], 2));
    }

    // Reads linearVelocity & angularVelocity from the given json object
    void CollisionComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        boundingBoxCenter = data.value("boundingBoxCenter", boundingBoxCenter);
        highestBoundingBoxVertex = data.value("boundingBoxRadius", highestBoundingBoxVertex);
    }
}