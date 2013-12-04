#ifndef MAIN_H
#define MAIN_H

// include files

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <list>
#include <sstream>
#include <iomanip>
#include <locale>
#include <cstdlib>

#include "structs_and_classes.h"

// function prototypes
// the following functions are used by main(), but defined in other source files (.cpp files)

extern int getGeometryInput(char* argv[],
                            std::vector<triangle> & facet, 
                            double & x_min, double & x_max, 
                            double & y_min, double & y_max, 
                            double & z_min, double & z_max);

// variables and constants used in main.cpp

// input geometry

std::vector<triangle> facet;        // define a vector object (container) called "facet" of type "triangle"
double x_min, x_max, delta_x;       // geometry extents along X
double y_min, y_max, delta_y;       // geometry extents along Y
double z_min, z_max, delta_z;       // geometry extents along Z

#endif
