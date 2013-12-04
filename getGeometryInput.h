#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>

#include "structs_and_classes.h"

extern int read_binary_STL_file (std::string STL_filename,std::vector<triangle> & facet,
                                 double & x_min, double & x_max, double & y_min, double & y_max, double & z_min, double & z_max);

extern int read_ascii_STL_file  (std::string STL_filename, std::vector<triangle> & facet,
                                 double & x_min, double & x_max, double & y_min, double & y_max, double & z_min, double & z_max);
