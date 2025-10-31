#include "World.h"
#include "raylib.h"

World::World() : AccumulatedFixedTime(0), TargetFixedStep(1.0f / 30.0f)
{
}

void World::Init()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    OnInit();
}

void World::Tick()
{
    AccumulatedFixedTime += GetFrameTime();

    OnTick();
}

void World::TickFixed()
{
    AccumulatedFixedTime -= TargetFixedStep;

    for (auto& physicsObjectOne : PhysObjects)
    {
        physicsObjectOne.physicsEnabled = true;
        if (physicsObjectOne.physicsEnabled)
        {
            physicsObjectOne.AddAcceleration({ 0,10 });
            physicsObjectOne.TickPhys(TargetFixedStep);
        }
    }

    OnTickFixed();
}

void World::Draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    for (auto& physicsObjectOne : PhysObjects)
    {
        physicsObjectOne.DrawPhysicsCircle();
    }

    EndDrawing();

    OnDraw();
}

void World::Exit()
{
    OnExit();

    CloseWindow();        // Close window and OpenGL context
}

bool World::ShouldClose() const
{
	return WindowShouldClose();
}

bool World::ShouldTickFixed() const
{
    return AccumulatedFixedTime >= TargetFixedStep;
}
