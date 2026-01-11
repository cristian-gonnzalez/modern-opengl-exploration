/*
Vertex Winding Order and Face Orientation

  When drawing geometry in OpenGL, primitives (such as triangles) are defined by a sequence of vertices. 
The order in which vertices are specified determines the triangle's 'winding order'.

Triangle Example (CCW):

                     y                                    
                     ^
            3        |                         Direction: 1 → 2 → 3  (Counter-Clockwise) 
            *        |                         VBO order: [ Vertex 1, Vertex 2, Vertex 3 ]          
            | \      |                         
            |   \    |                           The winding order is the direction that our vertices are laid out     
            |     \  |                         It can be:        
            |       \|                                        
  ──────────|────────|──────────────────> x              - CCW (counter clockwise) 
            |        |\                                  - CW (clockwise) 
            |        |  \                                 
            |        |    \   ^                                          
            |        |      \  \                       
            *--------|--------*                                   
            1        |        2                                    
                --->   


   OpenGL uses the winding order to determine which side of a triangle is the 'front face' and which is the 'back face'.

   By default:
     - Front face  → Counter-Clockwise (CCW)
     - Back face   → Clockwise (CW)
 
   This matters for:
     - Face culling (GL_CULL_FACE)
     - Correct orientation in 3D space
  

  By default, OpenGL uses a 'right-handed coordinate system':
  
     - Thumb        → +X axis
     - Index finger → +Y axis
     - Middle finger→ +Z axis
  
   If the vertices are specified in CCW order when viewed from the camera, the triangle is considered a 'front face'. 
This means that the triangle is facing 'toward the viewer' (positive Z direction).


 Quad (Rectangle) Using Two Triangles
 
   A quad is drawn as 'two triangles'. Each triangle must respect CCW order.
 
                       3        |        4
                       *-----------------*                    VBO order: [
                       | \      |        |                                  Vertex 1, Vertex 2, Vertex 3,   // First triangle
                       |   \    |        |                                  Vertex 2, Vertex 4, Vertex 3    // Second triangle
                       |     \  |        |                               ]
                       |       \|        |                            
   --------------------|--------|--------|------------> x
                       |        |\       |
                       |        |  \     |
                       |        |    \   |
                       |        |      \ |
                       *--------|--------*
                       1        |        2
 
  Each triangle is specified independently, but both must follow CCW winding order to be front-facing.

*/