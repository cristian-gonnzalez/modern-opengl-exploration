/**

WWhen drawing, we use vertices. OpenGl considered the windond order of the vertices


                     y
                     ^
            3        |                                 VBO = [Vertex 1, Vertex 2, Vertex 1]
            *        |                                   
            | \      |        
            |   \    |        
            |     \  |        
            |       \|        
  ──────────|────────|──────────────────> x            Notice the direction, we are going from 1->2->3. It is know as the windding order
            |        |\                               We are going to counter clockwise-direction
            |        |  \                             
            |        |    \   ^                        The winding order is the direction that our vertices are laid out                  
            |        |      \  \                       It can be:
            *--------|--------*                                   - CCW (counter clockwise)   
            1        |        2                                   - CW (clockwise)  
                --->   
                                                       The windows order is which direction is the front of the triangle. This triangle
                                                    is facing out towards us (the user) (z-positve towards us)

                                                       By default, OpenGL follow the right-handed coodinate system

                                                                  The thumb becomes the positive x-axis 
                                                                  The index finger becomes the positive y-axis 
                                                                  The middle finger becomes the z-axis
                                                        
                                                        This is important since when we are drawing we need to do it i CCW order
  
  When drawing a a quad ('rectangle'), we need to specify the order of the vertices in CCW in the VBO


                        3        |         4 
                        *-----------------*                             VBO = [Vertex 1, Vertex 2, Vertex 1,      -> First triangle
                        | \      |        |                                    Vertex 2, Vertex 4, Vertex 3]      -> Second triangle
                        |   \    |        |
                        |     \  |        |
                        |       \|        |
              ──────────|────────|─────────|─────────> x
                        |        |\       |
                        |        |  \     |
                        |        |    \   |
                        |        |      \ |
                        *--------|--------*
                        1        |        2

 */