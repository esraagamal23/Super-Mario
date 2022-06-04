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
    }

    // Reads linearVelocity & angularVelocity from the given json object
    void CollisionComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        boundingBoxCenter = data.value("boundingBoxCenter", boundingBoxCenter);
        boundingBoxRadius = data.value("boundingBoxRadius", boundingBoxRadius);
    }
}