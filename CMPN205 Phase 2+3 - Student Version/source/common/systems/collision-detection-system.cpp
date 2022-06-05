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
        return distance < radius_sum / 2;
    }

    void collisionDetectionSystem::preventCollision(CollisionComponent* comp1, CollisionComponent* comp2)
    {
        Entity* owner1 = comp1->getOwner();
        Entity* owner2 = comp2->getOwner();
        glm::vec3 comp1Center = owner1->getLocalToWorldMatrix() * glm::vec4(comp1->boundingBoxCenter, 1);
        glm::vec3 comp2Center = owner2->getLocalToWorldMatrix() * glm::vec4(comp2->boundingBoxCenter, 1);
        FreeCameraControllerComponent* ent1 = owner1->getComponent<FreeCameraControllerComponent>();
        FreeCameraControllerComponent* ent2 = owner2->getComponent<FreeCameraControllerComponent>();
        if(ent1)
        {
            glm::vec3 preventDirection = comp2Center - comp1Center;
            preventDirection[0] = preventDirection[0] > 0 ? 1 : preventDirection[0] == 0 ? 0 : -1;
            preventDirection[1] = preventDirection[1] > 0 ? 1 : preventDirection[1] == 0 ? 0 : -1;
            preventDirection[2] = preventDirection[2] > 0 ? 1 : preventDirection[2] == 0 ? 0 : -1;
            owner1->localTransform.position += preventDirection * ent1->positionSensitivity;
        }
        if(ent2)
        {
            glm::vec3 preventDirection = comp1Center - comp2Center;
            preventDirection[0] = preventDirection[0] > 0 ? 1 : preventDirection[0] == 0 ? 0 : -1;
            preventDirection[1] = preventDirection[1] > 0 ? 1 : preventDirection[1] == 0 ? 0 : -1;
            preventDirection[2] = preventDirection[2] > 0 ? 1 : preventDirection[2] == 0 ? 0 : -1;
            owner2->localTransform.position += preventDirection * ent2->positionSensitivity;
        }
    }

    void collisionDetectionSystem::exit()
    {

    }
}
