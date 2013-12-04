#ifndef STRUCTS_AND_CLASSES_H
#define STRUCTS_AND_CLASSES_H

// define the vec3d struct (a 3D vector with three components)
struct vec3d
{
    /// x-component of the 3D vector
    double x;  

    /// y-component of the 3D vector
    double y;  

    /// z-component of the 3D vector
    double z;  
};

// A triangular element is defined using the three vertices and a normal vector defining the orientation
// of the element in relation to the surface of the solid object. The normal vector usually points outwards
// for each surface element.

class triangle
{
public:

    /// 3 components of the normal vector to the triangle
    vec3d normal;

    /// 3 coordinates of the three vertices of the triangle
    vec3d point[3];
};
#endif
