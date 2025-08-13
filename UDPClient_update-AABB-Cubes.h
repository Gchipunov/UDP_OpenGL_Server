
#ifndef CUBESUPDATE_H
#define CUBESUPDATE_H


#ifdef WIN32
#pragma once

#endif

extern std::vector <Cube> cubes;

// AABB Cube struct
struct Cube {
    glm::vec3 position;
    glm::vec3 velocity;
    float halfSize;
};

bool checkAABBCollision(const Cube& a, const Cube& b);
void resolveAABBCollision(Cube& a, Cube& b);
void updateCubes(std::vector<Cube>& cubes, float deltaTime);




#endif
