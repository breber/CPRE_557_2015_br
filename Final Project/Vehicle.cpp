//
//  Vehicle.cpp
//
//  Group:
//  Brian R., breber@iastate.edu
//  Kyle V., vansicek@iastate.edu
//  Shrabya K., shrabya@iastate.edu

#include "Vehicle.h"

Vehicle::Vehicle(
    const std::string& obj,
    float scale,
    const std::string& vs,
    const std::string& fs)
: objPath(obj)
, objScale(scale)
, object()
, appearance(vs, fs)
{
}
