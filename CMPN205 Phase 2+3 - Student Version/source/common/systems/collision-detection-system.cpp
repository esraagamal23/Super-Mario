#include "collision-detection-system.hpp"
#include "../components/collision.hpp"
namespace our{

    void collisionDetectionSystem::enter(Application * app)
    {
        this->app = app;
    }

    void collisionDetectionSystem::update(World* world, float deltaTime)
    {
        FreeCameraControllerComponent* playerCamera = nullptr;
        CollisionComponent* playerCollision = nullptr;
        Entity* playerEntity = nullptr;
        CollisionComponent* comp = nullptr;
        Entity* compEntity = nullptr;
        auto entities = world->getEntities();
        for(auto entity : entities)
        {
            playerCollision = entity->getComponent<CollisionComponent>();
            if(playerCollision)
            {
                playerEntity = playerCollision->getOwner()->parent ? playerCollision->getOwner()->parent : playerCollision->getOwner();
                playerCamera = playerEntity->getComponent<FreeCameraControllerComponent>();
                if(playerCamera)
                break;
            }
        }
        if(!playerCamera) return;
        playerCollision->init();
        for(auto entity : entities)
        {
            comp = entity->getComponent<CollisionComponent>();
            if(comp)
            {
                compEntity = comp->getOwner()->parent ? comp->getOwner()->parent : comp->getOwner();
                if(compEntity != playerEntity)
                {
                    comp->init();
                    if(isCollidable(playerCollision, comp))
                    {
                        std::cout << "collision...." << std::endl;
                        preventCollision(playerCollision, comp);
                    }
                }
            }
            
        }
        
    }

    bool collisionDetectionSystem::isCollidable(CollisionComponent* comp1, CollisionComponent* comp2)
    {
        Entity* ent1 = comp1->getOwner();
        Entity* ent2 = comp2->getOwner();
        glm::vec3 comp1Center = ent1->getLocalToWorldMatrix() * glm::vec4(comp1->boundingBoxCenter, 1);
        glm::vec3 comp2Center = ent2->getLocalToWorldMatrix() * glm::vec4(comp2->boundingBoxCenter, 1);
        glm::vec3 comp1Highest = ent1->getLocalToWorldMatrix() * glm::vec4(comp1->highestBoundingBoxVertex, 1);
        glm::vec3 comp2Highest = ent2->getLocalToWorldMatrix() * glm::vec4(comp2->highestBoundingBoxVertex, 1);
        float comp1Radius = comp1->calculateRadius(comp1Center, comp1Highest);
        float comp2Radius = comp2->calculateRadius(comp2Center, comp2Highest);

        float distance = comp1->calculateRadius(comp1Center, comp2Center);
        float radius_sum = comp1Radius + comp2Radius;
        return distance < radius_sum ;
    }

    void collisionDetectionSystem::preventCollision(CollisionComponent* player, CollisionComponent* comp)
    {
        Entity* owner1 = player->getOwner();
        Entity* owner2 = comp->getOwner();
        Entity* health;
        auto entities = owner2->getWorld()->getEntities();
        for(auto entity : entities)
        {
            if(entity->getComponent<MeshRendererComponent>())
            {
                if(entity->getComponent<MeshRendererComponent>()->mesh->name =="health")
                {  
                    health = entity;
                    break;
                }
            }
        }
        if(owner2)
        {
            owner2->localTransform.position = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
            if(owner2->getComponent<MeshRendererComponent>()->mesh->name == "coin")
            {
                if(health->localTransform.scale.x <2.5)
                    health->localTransform.scale.x += 0.5;
            }
            if(owner2->getComponent<MeshRendererComponent>()->mesh->name == "bomb")
            {
                health->localTransform.scale.x -= 0.5;
            }
        }
        
    }

    void collisionDetectionSystem::exit()
    {

    }
}
