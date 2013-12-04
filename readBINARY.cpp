#include "readBINARY.h"

// -------------------------------------------------------------------------------------------------------------------
// this function opens the STL file specified by the user and reads the contents

int read_binary_STL_file(std::string STL_filename,std::vector<triangle> & facet,
                         double & x_min, double & x_max, double & y_min, double & y_max, double & z_min, double & z_max)
{
    // specify the location of STL files on this computer
    std::string STL_files_path = "../stl/";   

    // declare an (input) file object
    std::ifstream binaryInputFile;

    // open the STL file by using the full path and the name
    // specify that the file is opened in "read-only" mode
    // specify that the file is opened in binary format
    binaryInputFile.open((STL_files_path + STL_filename).c_str(), std::ifstream::in | std::ifstream::binary);

    // check whether the file was opened successfully
    // if yes then continue otherwise terminate program execution
    if(binaryInputFile.fail())
    {
        std::cout << "ERROR: Input STL file could not be opened!" << std::endl;
        return (1);
    }

    // position the pointer to byte number 80
    binaryInputFile.seekg(80);

    // read the number of facets (triangles) in the STL geometry
    int numberOfTriangles;
    binaryInputFile.read((char*) &numberOfTriangles, sizeof(int));

    // declare an object "tri" of type triangle (see main.h for the definition of the triangle class)
    triangle tri;

    // storage space for the "unused bytes" 
    char unused_bytes[2];

    // initialize parameters that will be used to store the minimum and maximum extents of the geometry
    // described by the STL file
    x_min = 1e+30, x_max = -1e+30;
    y_min = 1e+30, y_max = -1e+30;
    z_min = 1e+30, z_max = -1e+30;

    // temporary floating point variable
    float temp_float_var;

    for(int count=0;count<numberOfTriangles;count++)
    {
        // read the three components of the normal vector
        binaryInputFile.read((char*)&temp_float_var,4); tri.normal.x = (double) temp_float_var;
        binaryInputFile.read((char*)&temp_float_var,4); tri.normal.y = (double) temp_float_var;
        binaryInputFile.read((char*)&temp_float_var,4); tri.normal.z = (double) temp_float_var;

        // read the three coordinates of vertex 1 
        binaryInputFile.read((char*)&temp_float_var,4); tri.point[0].x = (double) temp_float_var;
        binaryInputFile.read((char*)&temp_float_var,4); tri.point[0].y = (double) temp_float_var;
        binaryInputFile.read((char*)&temp_float_var,4); tri.point[0].z = (double) temp_float_var;

        // read the three coordinates of vertex 2 
        binaryInputFile.read((char*)&temp_float_var,4); tri.point[1].x = (double) temp_float_var;
        binaryInputFile.read((char*)&temp_float_var,4); tri.point[1].y = (double) temp_float_var;
        binaryInputFile.read((char*)&temp_float_var,4); tri.point[1].z = (double) temp_float_var;

        // read the three coordinates of vertex 3
        binaryInputFile.read((char*)&temp_float_var,4); tri.point[2].x = (double) temp_float_var;
        binaryInputFile.read((char*)&temp_float_var,4); tri.point[2].y = (double) temp_float_var;
        binaryInputFile.read((char*)&temp_float_var,4); tri.point[2].z = (double) temp_float_var;

        // read the 2 unused bytes
        binaryInputFile.read(unused_bytes,2);

        // update geometry extents along X, Y and Z based on vertex 1 of this triangle
        if (tri.point[0].x < x_min) x_min = tri.point[0].x;
        if (tri.point[0].x > x_max) x_max = tri.point[0].x;
        if (tri.point[0].y < y_min) y_min = tri.point[0].y;
        if (tri.point[0].y > y_max) y_max = tri.point[0].y;
        if (tri.point[0].z < z_min) z_min = tri.point[0].z;
        if (tri.point[0].z > z_max) z_max = tri.point[0].z;

        // update geometry extents along X, Y and Z based on vertex 2 of this triangle
        if (tri.point[1].x < x_min) x_min = tri.point[1].x;
        if (tri.point[1].x > x_max) x_max = tri.point[1].x;
        if (tri.point[1].y < y_min) y_min = tri.point[1].y;
        if (tri.point[1].y > y_max) y_max = tri.point[1].y;
        if (tri.point[1].z < z_min) z_min = tri.point[1].z;
        if (tri.point[1].z > z_max) z_max = tri.point[1].z;

        // update geometry extents along X, Y and Z based on vertex 3 of this triangle
        if (tri.point[2].x < x_min) x_min = tri.point[2].x;
        if (tri.point[2].x > x_max) x_max = tri.point[2].x;
        if (tri.point[2].y < y_min) y_min = tri.point[2].y;
        if (tri.point[2].y > y_max) y_max = tri.point[2].y;
        if (tri.point[2].z < z_min) z_min = tri.point[2].z;
        if (tri.point[2].z > z_max) z_max = tri.point[2].z;

        // add data for this triangle to the "facet" vector
        facet.push_back(tri);
    }

    // explicitly close the connection to the input STL file
    binaryInputFile.close();

    return (0);  // all is well
}
