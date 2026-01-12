/** Transformation: Rotation
 */
 /*

Transfomrmation: https://open.gl/transformations
  
  We define vertices in a space 

  [Vertex specification]    ---->   [Vertex shader]

            *                       
          *   *

  Each individual vertex is processed independently by the vertex shader.
Inside the vertex shader, vertices undergo **transformations** that move
them through different coordinate spaces.

  To apply the transformation, we use a model matrix on the each vertex

  The model matrix is applied to each vertex position.

        Model Matrix          Vertex Position
        [1  0  0  0]               [x]                  This transformation moves vertices from:
        [0  1  0  0]      *        [y]
        [0  0  1  0]               [z]                              Local space → World space
        [0  0  0  1]               [1]
         ^  ^  ^  ^
         x  y  z  w
    
  - Each **column** represents a basis axis (X, Y, Z) and the way we are transformation each of them
  - The last column represents translation
  - The bottom row enables homogeneous coordinates

  This matrix is the **identity matrix**, meaning no transformation is applied. 


NOTE: 
  In OpenGL we use **4D vectors** to represent positions:

    vec4(position, 1.0)

  This allows us to express translation, rotation, and scale using matrix
multiplication.

                    
- Rotation:
    Rotation is performed around one of the principal axes (X, Y, or Z).

  Below is a rotation around the **Y-axis** by an angle θ:

                      Rotation around Y-axis

                [  cosθ   0   sinθ   0 ]   [ x ]
                [   0     1    0     0 ] * [ y ]
                [ -sinθ   0   cosθ   0 ]   [ z ]
                [   0     0    0     1 ]   [ 1 ]

  - The Y-axis remains unchanged (identity)
  - X and Z are rotated in the XZ-plane
  - Positive θ follows the right-hand rule


  Key observations
    - Transformations are applied **per vertex**
    - The vertex shader is responsible for transforming positions
    - The model matrix defines how an object is positioned, rotated, and scaled
      in the world
    - Order matters: matrix multiplication is **not commutative**

Summary
-------
- Vertices start in **local (object) space**
- Model matrix transforms them into **world space**
- Transformations use homogeneous coordinates (vec4)
- Rotation matrices define how axes are rotated around a given axis


Example of rotation:

                                                                  World space
           Local space                                               Y
        (local coordinates)                                          ^
                                                                     |
                y                                                    ^ y         ┐  Local coordinates
                ^                                                    |           |  The shape has its own local axes
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


Rotation:
            World space
              Y
              ^
              |
              ^ y'         ┐
              |/ |         |  When we apply a rotation around the Y axis,
              /  *         |  the object's *local axes* rotate,
             /| /          |  but the *world axes remain fixed*.
            *  /           |
            | /+-------->  |
            * /        z'  ┘
             /|
          -x' +-----------------------> X
             /
            /
           /
          Z


IMPORTANT:
  When we apply a rotation, the object’s local coordinate system rotates,
  but the world coordinate system does NOT rotate.

*/