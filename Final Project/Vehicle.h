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

// stdlib
#include <string>

class Vehicle
{
public:
    Vehicle(const std::string& obj, float scale);

    std::string objPath;
    float objScale;
    GLObjectObj* object;
    GLAppearance* appearance;
};
