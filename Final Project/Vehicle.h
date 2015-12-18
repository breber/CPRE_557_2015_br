//
//  Vehicle.h
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu
#pragma once

// local files
#include "Scene.h"
#include "VehicleObject.h"

// stdlib
#include <string>

class Vehicle
{
public:
    Vehicle(
        const std::string& obj,
        float scale,
        const std::string& vs,
        const std::string& fs);

    std::string objPath;
    float objScale;
    VehicleObject* object;
    GLAppearance appearance;
};
