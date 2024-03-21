#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <box2D/box2d.h>

#include "Types.h"
#include "Rendering/Texture2D.h"
#include "Rendering/Renderer.h"

#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Entities/Terrain.h"

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1000, 600, "Blobbin a'bout", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(1, 1, 1, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    Renderer renderer;

    b2Vec2 gravity(0.001f, -40.0f);
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    b2World world(gravity);

    Player player(world);
    world.SetContactListener(&player);

    Terrain ground(world, { 0, -10 }, { 32, 10 }, "container.jpg");
    Terrain floor(world, { 0, -5 }, { 32, 1 }, "wall.jpg", true);

    Terrain box(world, { -8, 0 }, { 10, 3 }, "container.jpg");

    while (!glfwWindowShouldClose(window))
    {
        renderer.ClearScreen();

        Entity::UpdateAll(window);
        Entity::DrawAll(renderer);

        world.Step(timeStep, velocityIterations, positionIterations);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}