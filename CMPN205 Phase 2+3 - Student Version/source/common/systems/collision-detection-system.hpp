#pragma once

#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include "../components/free-camera-controller.hpp"
#include "../components/collision.hpp"
#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{
    class collisionDetectionSystem {
        Application* app; // The application in which the state runs

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application* app);

        // This should be called every frame to update all entities containing a FreeCameraControllerComponent 
        void update(World* world, float deltaTime);

        bool isCollidable(CollisionComponent*, CollisionComponent*);

        void preventCollision(CollisionComponent*, CollisionComponent*);

        // When the state exits, it should call this function to ensure the mouse is unlocked
        void exit();

    };

}
