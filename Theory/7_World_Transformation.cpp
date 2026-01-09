/** World transformation
 */
/*
- model transform matrix:

   We are going to use sth know as a 'model transform matrix' that takes the shape and then transform them so that we can rotate
 scale, translate by moving the object.

 We use what is known as a *model transformation matrix* to manipulate an object in the scene. This matrix allows us to:

    - translate (move)
    - rotate
    - scale

an object relative to the world.


  When drawing in OpenGL, vertex positions are specified in 'local (object) coordinates'. These coordinates describe the shape of the
object around its own origin.

  To place the object into the world, we multiply its local coordinates by a 'model matrix', which transforms them into 'world space'.


                                                                     World space

                                                                            ^ 
                                                                            |
                                                                      3     |   4         ┐
                                                                       *--------*         | 
                                                                       | \  |   |         |
                Local (object) space                                   |  \ |   |         |  Local coordinates
                 Local coordinates                                ─────|────|───|───> x   |  
                         y                                             |    |\  |         |  We can translated in the wordls space
                         ^                                             |    |  \|         | 
                    3    |   4                                         *----|---*         |
                    *--------*                                         1    |   2         ┘
                    | \  |   |       * [ Mat 4x4 ]                          |
                    |  \ |   |                                              | 
               ─────|────|───|───> x   Model Matrix       ──────────────────|─────────────────> x                  
                    |    |\  |                                              | 
                    |    |  \|                                              |
                    *----|---*                                              |
                    1    |   2                                              |

               └─────────────────┘               
          Per Object we can have a model matrix that 
        allows us to manipulate the object by movng it

- The geometry is defined once in local space.
- The model matrix moves the object into world space.
- Each object can have its own model matrix.

 */

/*
- Per-object transformation:
          Each renderable object can have its own model matrix, allowing it to be independently 
        positioned, rotated, and scaled in the scene.
          This avoids modifying vertex data directly and allows efficient per-frame transformations.
*/

/*

- Vertex shader example:

#version 410 core

layout(location=0) in vec3 position;

uniform mat4 u_model_matrix;

void main()
{
    // Transform from local space to world space
    vec4 world_position = u_model_matrix * vec4(position, 1.0);
    gl_Position = world_position;
}

*/

/*
- Important notes:
     - The model matrix is a uniform variable.
     - Uniforms must be set from the CPU before drawing.
     - Uniform values have no default initialization.
     - The shader program must be active (glUseProgram) before updating uniform values.
*/

/*
- Build and run example:

     Code/projects/3_move_objects$ make
     mkdir -p /tmp/gl/shaders
     cp -r src/shaders/uv_mat4/* /tmp/gl/shaders
     g++ -g  -std=c++20 -Weffc++ src/app/*.cpp src/gl/*.cpp src/gl/gl_objects/*.cpp ../../third_party/glad/src/glad.c  -Isrc/app/ -Isrc/gl/ -Isrc/gl/gl_objects/ -I../../third_party/glad/include -I../../third_party/glm-master/ -isystem ../../third_party/glm-master/ -o prog -lSDL2 -ldl
      
     Code/projects/3_move_objects$ ./prog 
  
  */