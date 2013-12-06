#include "drawGeometry.h"

void drawGeometry(GLFWwindow *window, float scale, int time,
                  float *vertices, int NUM_VERTICES,
                  float move_x, float move_y, float move_z)
{
        // select background color to be black
        float R = 0, G = 0, B = 0, alpha = 0;
        glClearColor(R, G, B, alpha);
/*
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
*/
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
        float x_min = -scale, x_max = scale;
        float y_min = -scale, y_max = scale;
        float z_min = -20*scale, z_max = 20*scale;
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
