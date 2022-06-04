#include "collision.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {

    CollisionComponent::CollisionComponent(){
        auto entity = getOwner();
        MeshRendererComponent *meshRenderer = entity->getComponent<MeshRendererComponent>();
        if(!meshRenderer)
        {
            std::cerr << "There is no mesh rendered attached to this entity" << std::endl;
            std::exit(-1);
        }
        int maxX = meshRenderer->mesh->maxX;
        int minX = meshRenderer->mesh->minX;
        int maxY = meshRenderer->mesh->maxY;
        int minY = meshRenderer->mesh->minY;
        int maxZ = meshRenderer->mesh->maxZ;
        int minZ = meshRenderer->mesh->minZ;
        boundingBoxCenter = entity->getLocalToWorldMatrix() * glm::vec4(calculateCenter(minX, maxX, minY, maxY, minZ, maxZ), 1);
        highestBoundingBoxVertex = entity->getLocalToWorldMatrix() * glm::vec4(calculateHighestVertex(minX, maxX, minY, maxY, minZ, maxZ), 1);
        radius = calculateRadius(boundingBoxCenter, highestBoundingBoxVertex);
    }
    glm::vec3 CollisionComponent::calculateCenter(int mnX, int mxX, int mnY, int mxY, int mnZ, int mxZ)
    {
        int cX = (mnX + mxX) / 2;
        int cY = (mnY + mxY) / 2;
        int cZ = (mnZ + mxZ) / 2;
        return glm::vec3(cX, cY, cZ);
    }

    glm::vec3 CollisionComponent::calculateHighestVertex(int mnX, int mxX, int mnY, int mxY, int mnZ, int mxZ)
    {
        int maxX = glm::max(glm::abs(mnX), glm::abs(mxX));
        int maxY = glm::max(glm::abs(mnY), glm::abs(mxY));
        int maxZ = glm::max(glm::abs(mnZ), glm::abs(mxZ));
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