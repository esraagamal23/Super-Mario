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
    /**
     * This class is responsible for detecting the collision between the cart and any coin or bomb
     * and takes an action by hiding them and animate the action bar to the corresponding action
    */
    class collisionDetectionSystem {
        // The application in which the state runs
        Application* app;
    public:
        /**
         * When a state enters, it should call this function and give it the pointer to the application
         * @param app The application running
        */
        void enter(Application* app);
        /**
         * This should be called every frame to update all entities containing a Collision Component
         * @param world A pointer to the world
         * */
        void update(World* world, float deltaTime);
        /**
         * Checks if the two components are collidable of not
         * @param player The player of the game who has a camera moving with him
         * @param component The colliding component
         * @return true if they're colliding, false otherwise
         * */
        bool isCollidable(CollisionComponent*, CollisionComponent*);
        /**
         * Hide the colliding object and animate the action bar
         * @param player The player of the game who has a camera moving with him
         * @param component The colliding component
         * */
        void preventCollision(CollisionComponent*, CollisionComponent*);
        // When the state exits, it should call this function to ensure the mouse is unlocked
        void exit();

    };

}
