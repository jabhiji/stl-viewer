// include the header file

#include "getGeometryInput.h"

// this function handles the task of reading in input geometry files in STL format 
// and finding out the required size of the environmental box

int getGeometryInput(char* argv[],
                     std::vector<triangle> & facet, 
                     double & x_min, double & x_max, 
                     double & y_min, double & y_max, 
                     double & z_min, double & z_max)
{
    // open the STL file and read its contents

    // get the name of the STL file (command line input)
    std::string STL_filename = argv[1];

    // specify the location of STL files on this computer
    std::string STL_files_path = "../stl/";

    // BEGIN algorithm from ParaView to detect whether the STL file is ASCII or BINARY

    // open the STL file specified by the user as "read-only" and in "binary" mode
    // and store the pointer to the file buffer in "fp"

    FILE *fp = fopen((STL_files_path+STL_filename).c_str(),"rb");

    // specify how many bytes of the file will be read to calculate the percentage of characters
    // that are non-ASCII
    unsigned long length = 256;

    // dynamically allocate a buffer for storing the contents of the file
    // based on the length specified above
    unsigned char *buffer = new unsigned char[length];

    // read an array of "length" elements from the STL file, where each element is 1 byte in size
    // store the result in the buffer defined above
    // fread returns the number of bytes successfully read and this is stored in "read_length" 
    size_t read_length = fread(buffer,1,length,fp);

    // close the STL file
    fclose(fp);

    // loop over contents and count

    size_t text_count = 0;

    const unsigned char *ptr = buffer;
    const unsigned char *buffer_end = buffer + read_length;

    // loop over the entire buffer, starting at the memory location pointed to by "ptr"
    while(ptr != buffer_end)
    {
        if ( (*ptr >= 0x20 && *ptr <=0x7F) || *ptr == '\n' || *ptr == '\r' || *ptr == '\t')
        {
            text_count++;  // Yay! we have an ASCII character!
        }
        ptr++;    // move on to the next "byte"
    }

    // free memory
    delete [] buffer;

    // calculate the fraction of characters(bytes) in part of the STL file that are BINARY
    double current_percent_bin = (static_cast<double> (read_length - text_count) / static_cast<double> (read_length));

    // anything above the cut-off value below means that this STL file is of type BINARY
    double percent_bin = 0.05;

    std::string STL_filetype;

    if(current_percent_bin >= percent_bin)
    {
        STL_filetype = "binary";
    }
    else
    {
        STL_filetype = "ascii";
    }

    // END algorithm from ParaView to detect whether the STL file is ASCII or BINARY

    std::cout << "Input Geometry File = " << STL_filename << " (" << STL_filetype << ")" << std::endl;
 
    // function call to open the ascii file and read the content
    if (STL_filetype == "ascii")
    {
        // call the function to read the ASCII file
        // if all goes well, this function will return a value of 0
        int error = read_ascii_STL_file(STL_filename,facet,x_min,x_max,y_min,y_max,z_min,z_max);

        // if something goes wrong, the above function will return a value of 1
        if (error == 1) 
        {
            return(1);       // exit returning an error
        }
    }

    // function call to open the binary file and read the content
    if (STL_filetype == "binary") 
    {
        // call the function to read the BINARY file
        // if all goes well, this function will return a value of 0
        int error = read_binary_STL_file (STL_filename,facet,x_min,x_max,y_min,y_max,z_min,z_max);

        // if something goes wrong, the above function will return a value of 1
        if (error == 1) 
        {
            return(1);       // exit returning an error
        }
    }

    if (STL_filetype != "ascii" && STL_filetype != "binary") 
    {
        std::cout << "ERROR: Unable to find out whether the STL file is ascii or binary" << std::endl;
        return(1);
    }
 
    // print the number of triangles
    std::cout << "The number of triangles in the STL file = " << facet.size() << std::endl;

    // print the domain extent along X, Y and Z
    std::cout << std::endl;
    std::cout << "X range : " << x_min << " to " << x_max << " (delta = " << x_max - x_min << ")" << std::endl;
    std::cout << "Y range : " << y_min << " to " << y_max << " (delta = " << y_max - y_min << ")" << std::endl;
    std::cout << "Z range : " << z_min << " to " << z_max << " (delta = " << z_max - z_min << ")" << std::endl;
    std::cout << std::endl;

    return (0);  // all is well
}
