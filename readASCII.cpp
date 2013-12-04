#include "readASCII.h"

// -------------------------------------------------------------------------------------------------------------------
// this function opens the STL file specified by the user and reads the contents

int read_ascii_STL_file(std::string STL_filename, std::vector<triangle> & facet,
                        double & x_min, double & x_max, double & y_min, double & y_max, double & z_min, double & z_max)
{
    // specify the location of STL files on this computer
    std::string STL_files_path = "../stl/";   

    // declare a (input) file object
    std::ifstream asciiInputFile;

    // open the STL file by using the full path and the name
    // specify that the file is opened in "read-only" mode
    asciiInputFile.open((STL_files_path + STL_filename).c_str(), std::ifstream::in);

    // check whether the file was opened successfully
    // if yes then continue otherwise terminate program execution
    if(asciiInputFile.fail())
    {
        std::cout << "ERROR: Input STL file could not be opened!" << std::endl;
        return(1); // error
    }

    // read in the contents line by line until the file ends

    // initialize counter for counting the number of lines in this file
    int triangle_number = 0;  

    // declare an object "tri" of type triangle (see above for the definition of the triangle struct)
    triangle tri;

    // declare some string objects
    std::string junk;
    std::string string1,string2;

    // read in the first line (until the /n delimiter) and store it in the string object "line"
    getline(asciiInputFile,junk);

    // initialize parameters that will be used to store the minimum and maximum extents of the geometry
    // described by the STL file
    x_min = 1e+30, x_max = -1e+30;
    y_min = 1e+30, y_max = -1e+30;
    z_min = 1e+30, z_max = -1e+30;

    // begin loop to read the rest of the file until the file ends
    while(true)
    {
        // read the components of the normal vector
        asciiInputFile >> string1 >> string2 >> tri.normal.x >> tri.normal.y >> tri.normal.z;        //  1
        // continue reading this line until the \n delimiter
        getline(asciiInputFile,junk);                                                                //  1

        // read the next line until the \n delimiter
        getline(asciiInputFile,junk);                                                                //  2

        // read the (x,y,z) coordinates of vertex 1            
        asciiInputFile >> string1 >> tri.point[0].x >> tri.point[0].y >> tri.point[0].z;             //  3
        getline(asciiInputFile,junk);                                                                //  3

        // read the (x,y,z) coordinates of vertex 2            
        asciiInputFile >> string1 >> tri.point[1].x >> tri.point[1].y >> tri.point[1].z;             //  4
        getline(asciiInputFile,junk);                                                                //  4

        // read the (x,y,z) coordinates of vertex 3            
        asciiInputFile >> string1 >> tri.point[2].x >> tri.point[2].y >> tri.point[2].z;             //  5
        getline(asciiInputFile,junk);                                                                //  5

        // read some more junk
        getline(asciiInputFile,junk);                                                                //  6
        getline(asciiInputFile,junk);                                                                //  7

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

        // break out of the while loop if "end-of-file" becomes true
        if (asciiInputFile.eof()) break;

        // increment the triangle number
        triangle_number++;

        // add data for this triangle to the "facet" vector
        facet.push_back(tri);
    }
    // end while loop

    // explicitly close the output file
    asciiInputFile.close();

    return (0);   // all is well
}
