#include "PhysObject.h"
#include "raylib-cpp.hpp"

PhysObject::PhysObject() : Position({ 0,0 }), Velocity({ 0,0 }), PendingAcceleration({ 0,0 }), Collider({ShapeType::NONE})
{
}

void PhysObject::ContinuousTick(float Delta)
{
	Velocity += PendingAcceleration * Delta;
	PendingAcceleration = {};
	Position += Velocity * Delta;
}

void PhysObject::InstantaneousTick(float Delta)
{
	Position += Velocity * Delta;
}

void PhysObject::DrawPhysicsCircle() const
{
	switch (Collider.Type)
	{
	case ShapeType::NONE:
		break;
	case ShapeType::CIRCLE:
		DrawCircleLines(Position.x, Position.y, 30, raylib::Color::Red());
		break;
	case ShapeType::AABB:
		DrawRectangleLines(Position.x - Collider.AABBData.HalfExtents.x, Position.y - Collider.AABBData.HalfExtents.y, Collider.AABBData.HalfExtents.x * 2.0f,
			Collider.AABBData.HalfExtents.y * 2.0f, raylib::Color::Red());
		break;
	}
}

void PhysObject::DrawPhysicsCircleTwo() const
{
	DrawCircle(Position.x+75, Position.y+75, 30, raylib::Color::Blue());
}

//Applies continuous forces on objects of any mass equally like gravity
void PhysObject::AddAcceleration(const glm::vec2& Acceleration)
{
	PendingAcceleration += Acceleration;
}

//Applies instantaneous forces on objects of any mass equally to emulate platform movement
void PhysObject::AddVelocity(const glm::vec2& velocity)
{
	Velocity += velocity;
}

//Applies continuous forces that consider objects' mass
void PhysObject::AddForce(const glm::vec2& Force)
{
	PendingAcceleration += Force / Mass;
}

//Applies instantaneous forces that consider objects' mass
void PhysObject::AddImpulses(const glm::vec2& Impulse)
{
	Velocity += Impulse / Mass;
}

float PhysObject::ResolveCollision(const glm::vec2& PositionA, const glm::vec2& VelocityA, float MassA, 
	const glm::vec2& PositionB, const glm::vec2& VelocityB, float MassB, 
	float Elasticity, const glm::vec2& Normal)
{
	glm::vec2 relativeVelocity = VelocityB - VelocityA;

	//For glm::dot to function, "glm/glm.hpp" must be included
	float impulseMagnitude = glm::dot(-(1.0f + Elasticity) * relativeVelocity, Normal) / glm::dot(Normal, Normal * (1 / MassA + 1 / MassB));

	return impulseMagnitude;
}

void PhysObject::ResolvePhysObjects(PhysObject& LeftHandSide, PhysObject& RightHandSide, float Elasticity, const glm::vec2& Normal, float Penetration)
{
	//Calculates resolution impulse
	//The Normal and Penetration vectors are passed by reference and will get updated
	float impulseMagnitude = ResolveCollision(LeftHandSide.Position, LeftHandSide.Velocity, LeftHandSide.Mass,
		RightHandSide.Position, RightHandSide.Velocity, RightHandSide.Mass, Elasticity, Normal);

	//Depenetrates objects
	glm::vec2 minimumTranslationVector = Normal * Penetration;
	LeftHandSide.Position -= minimumTranslationVector;
	RightHandSide.Position += minimumTranslationVector;

	//Applies impulses to to update velocities after a collision
	//Applies an equal but opposite force to the other
	glm::vec2 impulse = Normal * impulseMagnitude;
	LeftHandSide.AddImpulses(-impulse);
	RightHandSide.AddImpulses(impulse);
}
