#include "Physics.h"
#include "PhysObject.h"

float ResolveCollisions(const glm::vec2& PositionA, const glm::vec2& VelocityA, float MassA,
    const glm::vec2& PositionB, const glm::vec2& VelocityB, float MassB,
    float Elasticity, const glm::vec2& Normal)
{
    //Calculates the relative Velocity
    glm::vec2 relativeVelocity = VelocityB - VelocityA;

    //Calculates the impulse magnitude
    float impulseMagnitude = glm::dot(-(1.0f + Elasticity) * relativeVelocity, Normal) /
        glm::dot(Normal, Normal * (1 / MassA + 1 / MassB));

    //Returns the impulse to apply to both objects
    return impulseMagnitude;
}
