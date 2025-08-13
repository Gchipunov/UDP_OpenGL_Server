#include <vector>
#include <glm/glm.hpp>
#include "UDPClient_update-AABB-Cubes.h"

// Assuming glm::vec3 is used for vectors
using namespace glm;


// Check for AABB collision
bool checkAABBCollision(const Cube& a, const Cube& b) {
    return (abs(a.position.x - b.position.x) < (a.halfSize + b.halfSize)) &&
        (abs(a.position.y - b.position.y) < (a.halfSize + b.halfSize)) &&
        (abs(a.position.z - b.position.z) < (a.halfSize + b.halfSize));
}

// Resolve AABB collision
void resolveAABBCollision(Cube& a, Cube& b) {
    vec3 normal = normalize(a.position - b.position);
    float overlap = (a.halfSize + b.halfSize) - length(a.position - b.position);

    if (overlap > 0) {
        // Separate the cubes
        vec3 separation = normal * (overlap / 2.0f);
        a.position += separation;
        b.position -= separation;

        // Simple impulse-based resolution
        float relativeVelocity = dot(a.velocity - b.velocity, normal);
        if (relativeVelocity < 0) {
            vec3 impulse = (a.velocity - b.velocity) - normal * relativeVelocity;
            a.velocity -= impulse;
            b.velocity += impulse;
        }
    }
}

// Update all cubes
void updateCubes(std::vector<Cube>& cubes, float deltaTime) {
    const float gravity = -9.8f;
    const float restitution = 0.5f; // Bounciness
    const float floorZ = 0.0f;

    // Apply gravity
    for (auto& cube : cubes) {
        cube.velocity.z += gravity * deltaTime;
        cube.position += cube.velocity * deltaTime;
    }

    // Floor collision
    for (auto& cube : cubes) {
        if (cube.position.z - cube.halfSize <= floorZ) {
            cube.position.z = floorZ + cube.halfSize;
            cube.velocity.z *= -restitution; // Reverse velocity with restitution
            if (abs(cube.velocity.z) < 0.1f) {
                cube.velocity.z = 0.0f; // Stop small bounces
            }
        }
    }

    // Cube-to-cube collision
    for (size_t i = 0; i < cubes.size(); ++i) {
        for (size_t j = i + 1; j < cubes.size(); ++j) {
            if (checkAABBCollision(cubes[i], cubes[j])) {
                resolveAABBCollision(cubes[i], cubes[j]);
            }
        }
    }
}
