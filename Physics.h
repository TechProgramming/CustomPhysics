#pragma once
#include "glm/glm.hpp"

float ResolveCollisions(const glm::vec2& PositionA, const glm::vec2& VelocityA, float MassA,
	const glm::vec2& PositionB, const glm::vec2& VelocityB, float MassB,
	float Elasticity, const glm::vec2& Normal);
