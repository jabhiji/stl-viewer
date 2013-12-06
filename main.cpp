#include "main.h"

// OpenGL specific headers

#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>       // for using gluLookAt( ... )

//#define USE_LIGHTING

static void key_callback(GLFWwindow* window, int key, int scancode,
                         int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void drawGeometry(GLFWwindow *window, float scale, int time,
                  float *vertices, int NUM_VERTICES,
                  float move_x, float move_y, float move_z)
{
        // select background color to be black
        float R = 0, G = 0, B = 0, alpha = 0;
        glClearColor(R, G, B, alpha);

#ifdef USE_LIGHTING
        // light position           x  y   z  w
        GLfloat light_position[] = {0, 0, 15, 0};
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        // light color              R    G    B  alpha
        GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

        // material color          R    G    B  alpha 
        GLfloat mat_ambient[] = { 0.5, 0.87, 0.76, 1.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

        glEnable(GL_LIGHTING);     // lighting ON
        glEnable(GL_LIGHT0);       // light source #0 ON
#endif
        glEnable(GL_DEPTH_TEST);   // hidden surface removal

        // clear all pixels in the window with the color selected above
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //------------------------------------------------------------
        // transformations on the 3D object - Modeling transformations
        //------------------------------------------------------------

        // change the current mode to MODELVIEW
        glMatrixMode(GL_MODELVIEW);

        // current transformation matrix = identity matrix
        glLoadIdentity();

        // rotate object by 90 degrees about the X axis (1,0,0)
        glRotatef(90.0, 1.0, 0.0, 0.0);

        // translate the geometry along X, Y and Z
        // such that it is centered at the origin
        glTranslatef(move_x, move_y, move_z);

        // ----------------------
        // Viewing transformation
        // ----------------------

        // change the current mode to MODELVIEW
        glMatrixMode(GL_PROJECTION);

        // current transformation matrix = identity matrix
        glLoadIdentity();

        // set clipping planes in the X-Y-Z coordinate system
        x_min = -scale, x_max = scale;
        y_min = -scale, y_max = scale;
        z_min = -20*scale, z_max = 20*scale;
        glOrtho(x_min, x_max, y_min, y_max, z_min, z_max);
   
        float angle = 0.002*time;

        gluLookAt (cos(angle), sin(angle), 1.0,    // camera position at (x,y,z)
                          0.0,        0.0, 0.0,    // camera looks towards point (x,y,z)
                          0.0,        0.0, 1.0);   // the "up" vector

        //-----------------------------------------------------------
        // Enable use of vertex data (coordinates, normals and color)
        //-----------------------------------------------------------

        // enable use of vertex coordinate information from the array
        glEnableClientState(GL_VERTEX_ARRAY);

        glVertexPointer(3,                 // number of coordinates per vertex (X,Y,Z)
                        GL_FLOAT,          // type of numbers
                        sizeof(float)*10,  // stride - gap between each set of (X,Y,Z)
                        &vertices[0]);     // offset - location of initial (X,Y,Z)

        // enable use of vertex normal information from the array
        glEnableClientState(GL_NORMAL_ARRAY);
  
        glNormalPointer(GL_FLOAT,         // type of values
                        sizeof(float)*10, // stride - gap between each set of (N_x,N_y,N_z) 
                        &vertices[3]);    // offset - location of initial (N_x,N_y,N_z)

        // enable use of vertex color information from the array
        glEnableClientState(GL_COLOR_ARRAY);
  
        glColorPointer(4,                 // number of color values per vertex (R,G,B,A)
                       GL_FLOAT,          // type of values
                       sizeof(float)*10,  // stride - gap between each set of (R,G,B,A)
                       &vertices[6]);     // offset - location of initial (R,G,B,A)

        //------------------
        // draw the geometry
        //------------------

        // draw command
        glDrawArrays(GL_TRIANGLES,     // type of GL element
                     0,                // starting offset
                     NUM_VERTICES);    // number of vertices to be used for rendering

        // swap front and back buffers
        glfwSwapBuffers(window);

        // poll for and processs events
        glfwPollEvents();

}

void createVertexArray(std::vector<triangle> & facet, float* vertices)
{
    const int NUM_FACETS = facet.size();
    int count = 0;
    for(int facet_index = 0; facet_index < NUM_FACETS; facet_index++)
    {
        // vertex 0
        {
            // x-y-z coordinates of the point
            vertices[count +  0] = facet[facet_index].point[0].x;
            vertices[count +  1] = facet[facet_index].point[0].y;
            vertices[count +  2] = facet[facet_index].point[0].z;
            // x-y-z coordinates of the normal
            vertices[count +  3] = facet[facet_index].normal.x;
            vertices[count +  4] = facet[facet_index].normal.y;
            vertices[count +  5] = facet[facet_index].normal.z;
            // (R,G,B,A) color values 
            vertices[count +  6] = fabs(facet[facet_index].normal.x);
            vertices[count +  7] = fabs(facet[facet_index].normal.y);
            vertices[count +  8] = fabs(facet[facet_index].normal.z);
            vertices[count +  9] = 1.0;
        }

        // vertex 1
        {
            // x-y-z coordinates of the point
            vertices[count + 10] = facet[facet_index].point[1].x;
            vertices[count + 11] = facet[facet_index].point[1].y;
            vertices[count + 12] = facet[facet_index].point[1].z;
            // x-y-z coordinates of the normal
            vertices[count + 13] = facet[facet_index].normal.x;
            vertices[count + 14] = facet[facet_index].normal.y;
            vertices[count + 15] = facet[facet_index].normal.z;
            // (R,G,B,A) color values 
            vertices[count + 16] = fabs(facet[facet_index].normal.x);
            vertices[count + 17] = fabs(facet[facet_index].normal.y);
            vertices[count + 18] = fabs(facet[facet_index].normal.z);
            vertices[count + 19] = 1.0;
        }

        // vertex 2
        {
            // x-y-z coordinates of the point
            vertices[count + 20] = facet[facet_index].point[2].x;
            vertices[count + 21] = facet[facet_index].point[2].y;
            vertices[count + 22] = facet[facet_index].point[2].z;
            // x-y-z coordinates of the normal
            vertices[count + 23] = facet[facet_index].normal.x;
            vertices[count + 24] = facet[facet_index].normal.y;
            vertices[count + 25] = facet[facet_index].normal.z;
            // (R,G,B,A) color values 
            vertices[count + 26] = fabs(facet[facet_index].normal.x);
            vertices[count + 27] = fabs(facet[facet_index].normal.y);
            vertices[count + 28] = fabs(facet[facet_index].normal.z);
            vertices[count + 29] = 1.0;
        }

        count += 30;
    }
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
