#pragma once
#include <glm/vec2.hpp>

class PhysObject
{
public:
	//Known as Location in UE
	glm::vec2 Position;

	glm::vec2 Velocity;

	glm::vec2 Forces;

	//Determines whether an object is effected by gravity or not
	bool physicsEnabled;

	PhysObject();

	void TickPhys(float Delta);
	void DrawPhysicsCircle() const;

	//Applies continuous forces on objects of any mass equally like gravity
	void AddAcceleration(const glm::vec2 & Acceleration);

	//Applies instantaneous forces on objects of any mass equally to emulate platform movement
	void AddVelocity(const glm::vec2& Velocity);

	//Applies continuous forces that consider objects' mass
	void AddForces(const glm::vec2& Force);

	//Applies instantaneous forces that consider objects' mass
	void AddImpulses(const glm::vec2& Impulse);
};