#include "collision-detection-system.hpp"
#include "../components/collision.hpp"
namespace our{

    void collisionDetectionSystem::enter(Application * app)
    {
        this->app = app;
    }

    void collisionDetectionSystem::update(World* world, float deltaTime)
    {
        CollisionComponent* comp1 = nullptr;
        CollisionComponent* comp2 = nullptr;
        auto entities = world->getEntities();
        for(auto entity1 = entities.begin(); entity1 != entities.end(); entity1++)
        {
            for(auto entity2 = entity1++; entity2 != entities.end(); entity2++)
            {
                comp1 = (*entity1)->getComponent<CollisionComponent>();
                comp2 = (*entity2)->getComponent<CollisionComponent>();
                if(comp1 && comp2 && comp1 != comp2)
                {
                    comp1->init();
                    comp2->init();
                    if(isCollidable(comp1, comp2))
                    {
                        std::cout << "collision" << std::endl;
                        preventCollision(comp1, comp2);
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
        return distance < radius_sum;
    }

    void collisionDetectionSystem::preventCollision(CollisionComponent* comp1, CollisionComponent* comp2)
    {
        Entity* owner1 = comp1->getRootOwner(comp1->getOwner());
        Entity* owner2 = comp2->getRootOwner(comp2->getOwner());
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
        // glm::vec3 preventDirection = comp2->boundingBoxCenter - comp1->boundingBoxCenter;
        // preventDirection[0] = preventDirection[0] > 0 ? 1 : preventDirection[0] == 0 ? 0 : -1;
        // preventDirection[1] = preventDirection[1] > 0 ? 1 : preventDirection[1] == 0 ? 0 : -1;
        // preventDirection[2] = preventDirection[2] > 0 ? 1 : preventDirection[2] == 0 ? 0 : -1;
        // owner->localTransform.position = owner->localTransform.toMat4() * glm::vec4(preventDirection, 1.0);
    }

    void collisionDetectionSystem::exit()
    {

    }
}
