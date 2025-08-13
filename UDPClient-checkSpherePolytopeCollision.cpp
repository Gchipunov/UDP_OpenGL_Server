#include <vector>
#include <glm/glm.hpp>

// A Polytope can be defined as a set of planes
struct Polytope {
    std::vector<Plane> faces;
};

bool checkSpherePolytopeCollision(const Sphere& sphere, const Polytope& polytope) {
    // If the sphere is outside of ANY face, there is no collision
    for (const auto& face : polytope.faces) {
        glm::vec3 normalizedNormal = glm::normalize(face.normal);
        float signedDistance = glm::dot(normalizedNormal, sphere.center) + face.distance;

        // Check if the sphere's center is on the "outside" of the plane
        // A negative signedDistance means the point is "inside" the face, assuming the normals point outwards.
        if (signedDistance > sphere.radius) {
            // The sphere is completely outside this face, so no collision.
            return false;
        }
    }
    // If the sphere's center is "inside" or "colliding" with all faces, there is a collision.
    return true;
}
