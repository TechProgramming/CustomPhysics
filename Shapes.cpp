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

bool CheckCircleAABB(const glm::vec2& PositionA, const Circle& CircleA, const glm::vec2& PositionB, const AABB& AABB)
{
    //Finds the nearest point in the AABB in the direction of the circle
    float DistanceX = PositionA.x - glm::clamp(PositionA.x, PositionB.x - AABB.HalfExtents.x, PositionB.x + AABB.HalfExtents.x);
    float DistanceY = PositionA.y - glm::clamp(PositionA.x, PositionB.x - AABB.HalfExtents.x, PositionB.x + AABB.HalfExtents.x);

    //Is considered to be in collision if the distance to that point is less than the circle's radius
    return (DistanceX * DistanceX + DistanceY * DistanceY) < CircleA.Radius * CircleA.Radius;
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

bool CheckCircleAABB(const glm::vec2& Shape1Position, const Shape& Shape1, const glm::vec2& Shape2Position, const Shape& Shape2)
{
    assert(Shape1.Type == ShapeType::CIRCLE && "Called CheckCircleAABB but a Circle wasn't provided for shape 1.");
    assert(Shape2.Type == ShapeType::AABB && "Called CheckCircleAABB but an AABB wasn't provided for shape 2.");

    return CheckCircleAABB(Shape1Position, Shape1.CircleData, Shape2Position, Shape2.AABBData);
}

glm::vec2 DepenetrateCircleCircle(const glm::vec2& PositionA, const Circle& CircleA, const glm::vec2& PositionB, const Circle& CircleB, float& Penetration)
{
    //Gets the distance between the two circles
    float distance = glm::length(PositionB - PositionA);

    //Adds the sum of the two radii
    float radii = CircleA.Radius + CircleB.Radius;

    //Finds the difference and places it into the Penetration parameter
    Penetration = radii - distance;

    //Returns the direction to correct along
    return glm::normalize(PositionB - PositionA);
}

glm::vec2 DepenetrateCircleCircle(const glm::vec2& PositionA, const Shape& ShapeA, const glm::vec2& PositionB, const Shape& ShapeB, float& Penetration)
{
    return DepenetrateCircleCircle(PositionA, ShapeA, PositionB, ShapeB, Penetration);
}


glm::vec2 DepenetrateAABBAABB(const glm::vec2& PositionA, const Shape& AABB1, const glm::vec2& PositionB, const Shape& AABB2, float& Penetration)
{
    //Gets the distance between the two circles
    float distance = glm::length(PositionB - PositionA);

    //Adds the sum of the two half extents
    float halfExtents = AABB1.AABBData.HalfExtents.x + AABB2.AABBData.HalfExtents.x;

    //Finds the difference and places it into the Penetration parameter
    Penetration = halfExtents - distance;

    //Returns the direction to correct along
    return glm::normalize(PositionB - PositionA);
}

//glm::vec2 DepenetrateAABBAABB(const glm::vec2& PositionA, const Shape& ShapeA, const glm::vec2& PositionB, const Shape& ShapeB, float& Penetration)
//{
//    return DepenetrateAABBAABB(PositionA, ShapeA, PositionB, ShapeB, Penetration);
//}

