#include "collision-detection-system.hpp"
#include "../components/collision.hpp"
namespace our{

    void collisionDetectionSystem::enter(Application * app)
    {
        this->app = app;
    }

    void collisionDetectionSystem::update(World* world, float deltaTime)
    {
        CollisionComponent* player_collision = nullptr;
        for(auto entity : world->getEntities()){
                FreeCameraControllerComponent* player = entity->getComponent<FreeCameraControllerComponent>();
                if(player)
                {
                    player_collision = entity->getComponent<CollisionComponent>();
                    break;
                }
            }
        if(player_collision)
        {
            for(auto entity : world->getEntities())
            {
                CollisionComponent * component = entity->getComponent<CollisionComponent>();
                FreeCameraControllerComponent * player = entity->getComponent<FreeCameraControllerComponent>();
                if(component && !player && isCollidable(component, player_collision))
                {
                    preventCollision(player_collision, component);
                }

            }
        }
        else
        {
            std::cerr << "There is no player in the game" << std::endl;
        }
        
    }

    bool collisionDetectionSystem::isCollidable(CollisionComponent* comp1, CollisionComponent* comp2)
    {
        glm::vec3 comp1Center = comp1->boundingBoxCenter;
        float comp1Radius = comp1->radius;
        glm::vec3 comp2Center = comp2->boundingBoxCenter;
        float comp2Radius = comp2->radius;

        float distance = comp1->calculateRadius(comp1Center, comp2Center);
        float radius_sum = comp1Radius + comp2Radius;
        return distance < radius_sum;
    }

    void collisionDetectionSystem::preventCollision(CollisionComponent* comp1, CollisionComponent* comp2)
    {
        glm::vec3 preventDirection = comp2->boundingBoxCenter - comp1->boundingBoxCenter;
        preventDirection[0] = preventDirection[0] > 0 ? 1 : preventDirection[0] == 0 ? 0 : -1;
        preventDirection[1] = preventDirection[1] > 0 ? 1 : preventDirection[1] == 0 ? 0 : -1;
        preventDirection[2] = preventDirection[2] > 0 ? 1 : preventDirection[2] == 0 ? 0 : -1;
        comp1->getOwner()->localTransform.position += preventDirection;
    }

    void collisionDetectionSystem::exit()
    {

    }
}
