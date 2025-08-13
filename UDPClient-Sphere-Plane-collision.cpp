#include <glm/glm.hpp>

struct Plane {
    glm::vec3 normal;
    float distance; // Distance from origin
};

struct Sphere {
    glm::vec3 center;
    float radius;
};

bool checkSpherePlaneCollision(const Sphere& sphere, const Plane& plane) {
    // Normalize the plane's normal to ensure correct distance calculation
    glm::vec3 normalizedNormal = glm::normalize(plane.normal);
    
    // Calculate the signed distance from the sphere's center to the plane
    float signedDistance = glm::dot(normalizedNormal, sphere.center) + plane.distance;

    // Check for collision
    // If the absolute distance is less than or equal to the sphere's radius, they are colliding.
    return std::abs(signedDistance) <= sphere.radius;
}
