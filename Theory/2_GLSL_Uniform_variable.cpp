/** Uniform variables: Global GPU variables shared among shaders
 */

/*
Vertex Buffer Object (VBO):

 It is a way to pack information such as position, colors, ... related to vertices in the GPU.

     locations          locations          locations          -> attr information 
    ^~~~~~~~~~^         ^~~~~~~~~^         ^~~~~~~~~^ 
    0         1         0        1         0        1
  ┌─────┐  ┌─────┐   ┌─────┐  ┌─────┐   ┌─────┐  ┌─────┐      
[ (x,y,z), (r,g,b),  (x,y,z), (r,g,b),  (x,y,z), (r,g,b),  ]  -> vertex buffer array
  └──────────────┘    └──────────────┘   └──────────────┘ 
         0                  1                  2              -> indices in the buffer array
      vertex              vertex             vertex   

  In each vertex, we define various locations where we could find these data (position, colors, etc) through the VAO.

  This is the way we can send in information and in our shaders we had specific locations to read this values from.


-- What if I want to send information that is not vertex information?

  For example:
      - object position offset
      - transformation matrices
      - time
      - lighting parameters

  This is where UNIFORM variables are used.

Uniform variable:

  Uniform is essentially a global variable on the GPU. This means this is a varibale available in all the graphics pipeline

    - Shared in the vertex/fragment shader
    - It is a const variable (read-only) in shaders
    - Pass value form the CPU->GPU
    - Stored per shader program (NOT global to the whole GPU). Each shader program has its own uniform storage.




        ┌─────────────────────────┐         ┌─────────────────────────┐           ┌─────────────────────────┐
        |            VBO          |  --->   |      vertex shader      |  --->     |    fragment shader      |  ---> 
        | [x, y, z, r, g, b, ...] |         |                         |           |                         |
        └─────────────────────────┘         └─────────────────────────┘           └─────────────────────────┘  
                                              #version 410 core
        [                                     
       0    (x,y,z), location 0 ---------->   layout(location=0) in vec3 position; ---> This means that we are allcating some memory in the GPU to store
            (r,g,b), location 1 ---------->   layout(location=1) in vec3 color;       this variable or at least referencing memory "take this from the VBO"
            
       1    (x,y,z), location 0               out vec3 v_vertex_color;  
            (r,g,b), location 1         
                                              uniform float u_offset;               ---> Reserve this space to store information taken from the CPU  
       2    (x,y,z), ...
            (r,g,b), ...                      .....
        ] 

                                       
   ┌──────────────┐         ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
   |              |         |                                                   GPU                                                           |
   |    CPU       |         |    ┌─────────────────────────┐         ┌─────────────────────────┐           ┌─────────────────────────┐        |
   |              |         |    |            VBO          |  --->   |      vertex shader      |  --->     |    fragment shader      |  --->  |
   |              |         |    | [x, y, z, r, g, b, ...] |         |                         |           |                         |        |
   |              |<------> |    └─────────────────────────┘         └─────────────────────────┘           └─────────────────────────┘        |
   |              |         |                                                    ^                                     ^                      | 
   |              |         |    ┌─────────────────────────┐                     |                                     |                      | 
   |              |         |    |    Uniform variable     | ----------------------------------------------------------┘                      |  
   |              |         |    |                         |       Uniform variables are shared in the shaders                                | 
   |              |         |    |    u_offset             |                                                                                  | 
   |              |         |    |       ^                 |                                                                                  |
   |              |         |    └───────|─────────────────┘                                                                                  | 
   └──────────────┘         └────────────|────────────────────────────────────────────────────────────────────────────────────────────────────┘
                                         |
                            We need to know which location is this to update
                          this value 

                            
                            float value = <read from keyboard>
                               
                            glUseProgram(_shader_program);   

                            // Returns the location of a uniform variable
                            GLint location = glGetUniformLocation( _shader_program,
                                                                   "u_offset" );
                            if( location < 0)
                            {
                                std::cerr << "location 'u_offset' not found\n";
                                return;
                            }
                            else {
                                glUniform1f(location, value);  
                            }
                            
    Important rules:
        - The shader program must be active
        - Uniform locations are program-specific


Notes:
    - Uniform values are stored inside the shader program object.
    - Once set, they keep their value until changed.
    - glUniform* always affects the currently active program.
    - Forgetting glUseProgram leads to silent failure. -> "location 'u_offset' not found"

  */


  /*
  Code example:


      Code/projects/3_move_objects$ make uv
      make UV_OPTION=uv_only all
      make[1]: Entering directory 'modern-opengl-exploration/Code/projects/3_move_objects'
      mkdir -p /tmp/gl/shaders
      cp -r src/shaders/uv/* /tmp/gl/shaders
      g++ -g -DUV -std=c++20 -Weffc++ src/app/*.cpp src/gl/*.cpp src/gl/gl_objects/*.cpp ../../third_party/glad/src/glad.c  -Isrc/app/ -Isrc/gl/ -Isrc/gl/gl_objects/ -I../../third_party/glad/include -I../../third_party/glm-master/ -isystem ../../third_party/glm-master/ -o prog -lSDL2 -ldl
      make[1]: Leaving directory 'modern-opengl-exploration/Code/projects/3_move_objects'

      Code/projects/3_move_objects$ ./prog 
  
  */