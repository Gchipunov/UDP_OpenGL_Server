
#ifndef CUBESUPDATE_H
#define CUBESUPDATE_H


#ifdef WIN32
#pragma once

#endif



// AABB Cube struct
struct Cube {
    vec3 position;
    vec3 velocity;
    float halfSize;
};

bool checkAABBCollision(const Cube& a, const Cube& b);
void resolveAABBCollision(Cube& a, Cube& b);
void updateCubes(std::vector<Cube>& cubes, float deltaTime);




#endif
