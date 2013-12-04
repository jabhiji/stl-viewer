#include "main.h"

// OpenGL specific headers

#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>       // for using gluLookAt( ... )

static void key_callback(GLFWwindow* window, int key, int scancode,
                         int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void drawGeometry(GLFWwindow *window, float scale, int time,
                  float *vertices, int NUM_VERTICES,
                  double & x_min, double & x_max,
                  double & y_min, double & y_max,
                  double & z_min, double & z_max)
{
        // select background color to be black
        float R = 0, G = 0, B = 0, alpha = 0;
        glClearColor(R, G, B, alpha);

        // light position           x  y   z  w
        GLfloat light_position[] = {0, 0, 15, 0};
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        // light color              R    G    B  alpha
        GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

        // material color          R    G    B  alpha 
        GLfloat mat_ambient[] = { 1.0, 0.0, 0.0, 1.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

//      glEnable(GL_LIGHTING);     // lighting ON
//      glEnable(GL_LIGHT0);       // light source #0 ON
        glEnable(GL_DEPTH_TEST);   // hidden surface removal

        // clear all pixels in the window with the color selected above
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        // enable use of vertex coordinate information from the array
        glEnableClientState(GL_VERTEX_ARRAY);

        glVertexPointer(3,                 // number of coordinates per vertex (X,Y,Z)
                        GL_FLOAT,         // type of numbers
                        9*sizeof(float),  // stride - gap between each set of (X,Y,Z)
                        &vertices[0]);     // offset - location of initial (X,Y,Z)

//      std::cout << "Rendering " << NUM_VERTICES << " vertices using OpenGL\n";

        // enable use of vertex normal information from the array
        glEnableClientState(GL_NORMAL_ARRAY);
  
        glNormalPointer(GL_FLOAT,         // type of values
                        sizeof(float)*9,  // stride - gap between each set of (R,G,B,A)
                        &vertices[3]);     // offset - location of initial (N_x,N_y,N_z)

        // enable use of vertex color information from the array
        glEnableClientState(GL_COLOR_ARRAY);
  
        glColorPointer(4,                 // number of color values per vertex (R,G,B,A)
                       GL_FLOAT,          // type of values
                       sizeof(float)*9,   // stride - gap between each set of (R,G,B,A)
                       &vertices[3]);     // offset - location of initial (R,G,B,A)

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
        vertices[count +  0] = facet[facet_index].point[0].x;
        vertices[count +  1] = facet[facet_index].point[0].y;
        vertices[count +  2] = facet[facet_index].point[0].z;
        vertices[count +  3] = facet[facet_index].normal.x;
        vertices[count +  4] = facet[facet_index].normal.y;
        vertices[count +  5] = facet[facet_index].normal.z;
        vertices[count +  6] = facet[facet_index].normal.x;
        vertices[count +  7] = facet[facet_index].normal.y;
        vertices[count +  8] = facet[facet_index].normal.z;

        vertices[count +  9] = facet[facet_index].point[1].x;
        vertices[count + 10] = facet[facet_index].point[1].y;
        vertices[count + 11] = facet[facet_index].point[1].z;
        vertices[count + 12] = facet[facet_index].normal.x;
        vertices[count + 13] = facet[facet_index].normal.y;
        vertices[count + 14] = facet[facet_index].normal.z;
        vertices[count + 15] = facet[facet_index].normal.x;
        vertices[count + 16] = facet[facet_index].normal.y;
        vertices[count + 17] = facet[facet_index].normal.z;

        vertices[count + 18] = facet[facet_index].point[2].x;
        vertices[count + 19] = facet[facet_index].point[2].y;
        vertices[count + 20] = facet[facet_index].point[2].z;
        vertices[count + 21] = facet[facet_index].normal.x;
        vertices[count + 22] = facet[facet_index].normal.y;
        vertices[count + 23] = facet[facet_index].normal.z;
        vertices[count + 24] = facet[facet_index].normal.x;
        vertices[count + 25] = facet[facet_index].normal.y;
        vertices[count + 26] = facet[facet_index].normal.z;

        count += 27;
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

    float* vertices = new float[facet.size()*27];

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

    float scale = 3, delta = 0.01;
    int time = 0;
    while(!glfwWindowShouldClose(window))
    {
        drawGeometry(window, scale, time,
                     vertices, 3*facet.size(),
              //     &vert[0], 9,
                     x_min, x_max,
                     y_min, y_max,
                     z_min, z_max);

        // adjust scale
        scale += delta;
        if ( (scale > 10) || (scale < 1) ) delta = -delta;

        // increment time
        time++;
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;    // main program is successful
}
