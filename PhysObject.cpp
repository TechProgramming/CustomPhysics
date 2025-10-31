#include "PhysObject.h"
#include "raylib-cpp.hpp"

PhysObject::PhysObject() : Position({ 0,0 }), Velocity({ 0,0 }), Forces({ 0,0 })
{
}

void PhysObject::TickPhys(float Delta)
{
	Velocity += Forces * Delta;
	Forces = {};
	Position += Velocity * Delta;
}

void PhysObject::DrawPhysicsCircle() const
{
	DrawCircle(Position.x, Position.y, 30, raylib::Color::Red());
}

void PhysObject::AddAcceleration(const glm::vec2& Acceleration)
{
	Forces += Acceleration;
}

void PhysObject::AddVelocity(const glm::vec2& Velocity)
{
}

void PhysObject::AddForces(const glm::vec2& Force)
{
}

void PhysObject::AddImpulses(const glm::vec2& Impulse)
{
}
