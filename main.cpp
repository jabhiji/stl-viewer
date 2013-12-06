#include "main.h"

static void key_callback(GLFWwindow* window, int key, int scancode,
                         int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char *argv[])  
{
    //--------------------------------------------------
    // read STL geometry (triangle vertices and normals)
    //--------------------------------------------------
    int error = getGeometryInput(argv, facet, 
                                 x_min, x_max, 
                                 y_min, y_max, 
                                 z_min, z_max);

    if (error == 1) return(1);       // exit main returning an error

    //-------------------------------------------------------
    // calculate translation parameters to move the center of 
    // the geometry approximately to the origin
    //-------------------------------------------------------
    float x_center = (x_min + x_max) / 2.0;
    float y_center = (y_min + y_max) / 2.0;
    float z_center = (z_min + z_max) / 2.0;

    float move_x = 0.0 - x_center;   // translation along X
    float move_y = 0.0 - y_center;   // translation along Y
    float move_z = 0.0 - z_center;   // translation along Z

    std::cout << "Need to translate the geometry by: " << move_x
                                                << " " << move_y
                                                << " " << move_z << std::endl;

    // calculate scaling factors along X, Y and Z
    float scale_x = (x_max - x_min)/2.0;
    float scale_y = (y_max - y_min)/2.0;
    float scale_z = (z_max - z_min)/2.0;

    float scale = scale_x;
    if (scale_y > scale) scale = scale_y;
    if (scale_z > scale) scale = scale_z;

    scale = 1.5*scale;

    //------------------------------------------
    // create a vertex array based on facet data
    //------------------------------------------
    float* vertices = new float[facet.size()*30];

    createVertexArray(facet, vertices);

    //--------------------------------
    //   Create a WINDOW using GLFW
    //--------------------------------
    GLFWwindow *window;

    // initialize the library
    if(!glfwInit())
    {
        return -1;
    }

    // window size for displaying graphics
    int WIDTH  = 600; //atoi(argv[1]);
    int HEIGHT = 600; //atoi(argv[2]);

    // set the window's display mode
    window = glfwCreateWindow(WIDTH, HEIGHT, "STL viewer", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
	    return -1;
    }

    // make the windows context current
    glfwMakeContextCurrent(window);

    // enable quitting the graphics by pressing ESC
    glfwSetKeyCallback(window, key_callback);

    // render things in the window

    float delta = 0.01;  // change in scale
    int time = 0;
    while(!glfwWindowShouldClose(window))
    {
        drawGeometry(window, scale, time,
                     vertices, 3*facet.size(),
                     move_x, move_y, move_z);

//      // adjust scale
//      scale += delta;
//      if ( (scale > 10) || (scale < 1) ) delta = -delta;

        // increment time
        time++;
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;    // main program is successful
}
