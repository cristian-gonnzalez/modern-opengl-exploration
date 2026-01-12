/** 
 */
/*
Camera space / View space:

                                                                  World space
           Local space                                               Y
        (local coordinates)                                          ^
                                                                     |
                y                                                    ^ y         ┐
                ^                                                    |           |  Each object has its own local axes
                |                                                *---|---*       |  which are transformed into world space
            *---|---*                                            |   |   |       |
            |   |   |               =======>                     *---|---*       | 
            *---|---*               translate                --------+-------->  |   
        --------+--------> x                                        /|        x  ┘
               /                                                   / |
             /                                                    z  +-----------------------> X
             z                                                      /
                                                                   /
                                                                  /
                                                                  Z

    Local space --------> World space --------> Camera space
                  Model                View
                  matrix               matrix
                                         

Camera space (View space):

    Camera space represents the world as seen from the camera. Imagine you are a 
photographer, and you are movig your camera for ex: rotating it, so this is the 
view direction in my world.

    Conceptually:
    - We can think of moving the camera through the world.
    - Or equivalently, moving the entire world so that the camera
      is positioned at the origin and looks down a fixed direction

    In practice, the camera itself does not move in OpenGL.
    Instead, the View matrix transforms world-space coordinates
    into camera-space coordinates.


                                                        World space
                                                        Y
                                                        ^
                   ┌─────┐                              |
                   |     |_|                          ^ y'         ┐
                   └─────┘                              |/ |        |  The view matrix re-expresses
                    Camera                              /  *        |  world coordinates relative
                                                       /| /         |  to the camera's position
                                                      * /           |  and orientation.
                                                      |/+-------->  |
                                                      */|       z'  ┘
                                                      / |
                                                    -x' +-----------------------> X
                                                      /
                                                     /
                                                    /
                                                    
                                               Again we can think the quad hasnt move but our camera has where our
                                            eye is viewing the scene    

IMPORTANT:
  The View matrix does NOT rotate or move the world itself.
  It transforms world-space coordinates into the camera's
  local coordinate system.


In GLM, we commonly construct the View matrix using glm::lookAt():

    glm::mat4 view = glm::lookAt(
        eye,     // Camera position in world space
        center,  // Point the camera is looking at
        up       // Camera's up direction (usually (0, 1, 0))
    );

- eye:
    Position of the camera in world space

- center:
    Target point the camera is looking at
    (defines the view direction)

- up:
    Normalized vector indicating the camera's upward direction
    (typically (0, 1, 0) in OpenGL)
*/

