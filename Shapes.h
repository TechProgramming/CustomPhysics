#pragma once
#include <cstdint>
#include "glm/vec2.hpp"

struct Circle
{
	float Radius = 1.0f;
};

struct AABB
{
	//Represents 2 floats, or 4 bytes * 2, or 8 bytes total
	glm::vec2 HalfExtents;
};

enum class ShapeType : uint8_t
{
	NONE = 0,
	CIRCLE = 1 << 0,
	AABB = 1 << 1
};

struct Shape
{
	ShapeType Type;

	//Anonymous union that holds the data for the shape defined by this object
	//Access to its members aren't done via a name, but through directly referencing its members
	union
	{
		Circle CircleData;
		AABB AABBData;
	};
};

//Tests if two circles at their given locations and shape are in collision
//Returns true if collision occurs, false otherwise
bool CheckCircleCircle(const glm::vec2& Circle1Position, const Circle& Circle1Shape, const glm::vec2& Circle2Position, const Circle& Circle2Shape);

//Tests if two AABBs at their given locations and shape are in collision
//Returns true if collision occurs, false otherwise
bool CheckAABBAABB(const glm::vec2& AABB1Position, const AABB& AABB1Shape, const glm::vec2& AABB2Position, const AABB& AABB2Shape);

//Tests if two shapes (assuming they're circles) at their given locations and shape are in collision
//Returns true if collision occurs, false otherwise
bool CheckCircleCircle(const glm::vec2& Shape1Position, const Shape& Shape1, const glm::vec2& Shape2Position, const Shape& Shape2);

//Tests if two shapes (assuming they're AABBs) at their given locations and shape are in collision
//Returns true if collision occurs, false otherwise
bool CheckAABBAABB(const glm::vec2& Shape1Position, const Shape& Shape1, const glm::vec2& Shape2Position, const Shape& Shape2);

//Determines the minimum translation vector (MTV) to separate two circles
glm::vec2 DepenetrateCircleCircle(const glm::vec2& PositionA, const Circle& CircleA, const glm::vec2& PositionB, const Circle& CircleB, float& Penetration);

//Determines the minimum translation vector (MTV) to separate two shapes (assuming they're circles)
glm::vec2 DepenetrateCircleCircle(const glm::vec2& PositionA, const Shape& ShapeA, const glm::vec2& PoistionB, const Shape& ShapeB, float& Penetration);