#include "Shapes.h"

#include <cassert>

#include <glm/glm.hpp>

bool CheckCircleCircle(const glm::vec2& Circle1Position, const Circle& Circle1Shape, const glm::vec2& Circle2Position, const Circle& Circle2Shape)
{
    //Determines distance between circles
    glm::vec2 offset = Circle1Position - Circle2Position;
    float distance = glm::length(offset);

    //Determines the sum of the radii
    float sum = Circle1Shape.Radius + Circle2Shape.Radius;

    //If distance is less than sum, then collision has occured
    return distance < sum;
}

bool CheckAABBAABB(const glm::vec2& AABB1Position, const AABB& AABB1Shape, const glm::vec2& AABB2Position, const AABB& AABB2Shape)
{
    return AABB1Position.x - AABB1Shape.HalfExtents.x < AABB2Position.x + AABB2Shape.HalfExtents.x && //left within right collision
           AABB1Position.x + AABB1Shape.HalfExtents.x > AABB2Position.x - AABB2Shape.HalfExtents.x && //right within left collision
           AABB1Position.y - AABB1Shape.HalfExtents.y < AABB2Position.y + AABB2Shape.HalfExtents.y && //top within bottom collision
           AABB1Position.y + AABB1Shape.HalfExtents.y > AABB2Position.y - AABB2Shape.HalfExtents.y; //right within top collision
}

bool CheckCircleCircle(const glm::vec2& Shape1Position, const Shape& Shape1, const glm::vec2& Shape2Position, const Shape& Shape2)
{
    assert(Shape1.Type == ShapeType::CIRCLE && "Called CheckCircleCircle but a circle wasn't provided.");
    assert(Shape2.Type == ShapeType::CIRCLE && "Called CheckCircleCircle but a circle wasn't provided.");

    return CheckCircleCircle(Shape1Position, Shape1.CircleData, Shape2Position, Shape2.CircleData);
}

bool CheckAABBAABB(const glm::vec2& Shape1Position, const Shape& Shape1, const glm::vec2& Shape2Position, const Shape& Shape2)
{
    assert(Shape1.Type == ShapeType::AABB && "Called CheckAABBAABB but an AABB wasn't provided.");
    assert(Shape2.Type == ShapeType::AABB && "Called CheckAABBAABB but an AABB wasn't provided.");

    return CheckAABBAABB(Shape1Position, Shape1.AABBData, Shape2Position, Shape2.AABBData);
}
