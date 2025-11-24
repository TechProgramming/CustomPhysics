#include "World.h"

#include <unordered_map>
#include <iostream>

#include "raylib.h"
#include "EnumUtility.h"
#include "Shapes.h"

using CollisionFunc = bool (*)(const glm::vec2&, const Shape&, const glm::vec2&, const Shape&);
using CollisionMap = std::unordered_map<ShapeType, CollisionFunc>;
using DepenetrationFunc = glm::vec2(*)(const glm::vec2& PositionA, const Shape& ShapeA, const glm::vec2& PositionB, const Shape& ShapeB, float& Penetration);
using DepenetrationMap = std::unordered_map<ShapeType, DepenetrationFunc>;

CollisionMap ColMap;
DepenetrationMap DepenMap;

World::World() : AccumulatedFixedTime(0), TargetFixedStep(1.0f / 30.0f)
{
}

void World::Init()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    ColMap[ShapeType::CIRCLE | ShapeType::CIRCLE] = CheckCircleCircle;
    DepenMap[ShapeType::CIRCLE | ShapeType::CIRCLE] = DepenetrateCircleCircle;

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

    //Integrates forces and velocity
    for (auto& physicsObjectOne : PhysObjects)
    {
        physicsObjectOne.physicsEnabled = true;
        if (physicsObjectOne.physicsEnabled)
        {
            physicsObjectOne.AddAcceleration({ 0,10 });
            physicsObjectOne.ContinuousTick(TargetFixedStep);
        }
    }

    //Performs collision detection and resolution
    for (auto& i : PhysObjects)
    {
        for (auto& j : PhysObjects)
        {
            //Skips if i and j point to the same object
            if (&i == &j) { continue; }

            //Skips if the object has no collider
            if (i.Collider.Type == ShapeType::NONE || j.Collider.Type == ShapeType::NONE) { continue; }

            ShapeType ColKey = i.Collider.Type | j.Collider.Type;
            auto KeyPairIterator = ColMap.find(ColKey);

            bool bHasFunc = KeyPairIterator != ColMap.end();
            if (bHasFunc)
            {
                bool bIsColliding = ColMap[ColKey](i.Position, i.Collider, j.Position, j.Collider);
                if (bIsColliding)
                {
                    std::cout << "Collision detected" << std::endl;
                }
            }
            else
            {
                std::cerr << "Can't test for collision; no collision function defined for this pair." << std::endl;
            }
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

//Runs at the end of Init()

inline void World::OnInit() 
{
    PhysObject newObject;
    newObject.Collider.Type = ShapeType::CIRCLE;
    newObject.Collider.CircleData.Radius = 10.0f;
    newObject.Position = { 100, 100 };
    PhysObjects.push_back(newObject);

    newObject.Position = { 500, 200 };
    PhysObjects.push_back(newObject);

    newObject.Position = { 300, 150 };
    PhysObjects.push_back(newObject);
}

//Runs at the end of Tick()

inline void World::OnTick() 
{
    if (IsMouseButtonPressed(0))
    {
        PhysObject newObject;
        newObject.Collider.Type = ShapeType::CIRCLE;
        newObject.Collider.CircleData.Radius = 10.0f;

        Vector2 currentMousePosition = GetMousePosition();
        newObject.Position.x = currentMousePosition.x;
        newObject.Position.y = currentMousePosition.y;

        PhysObjects.push_back(newObject);
    }
    else if (IsMouseButtonPressed(1))
    {
        PhysObject newObject;
        newObject.Collider.Type = ShapeType::AABB;
        newObject.Collider.AABBData.HalfExtents = { 30.0f, 25.0f };

        Vector2 currentMousePosition = GetMousePosition();
        newObject.Position.x = currentMousePosition.x;
        newObject.Position.y = currentMousePosition.y;

        PhysObjects.push_back(newObject);
    }
}
