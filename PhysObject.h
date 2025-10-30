#pragma once
#include <glm/vec2.hpp>

class PhysObject
{
public:
	glm::vec2 Position;
	glm::vec2 Velocity;

	PhysObject();

	void TickPhys(float Delta);
};