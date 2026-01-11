/**  Modern OpenGL
 */

/*
  OpenGL is a series of graphics commands: it is a C-programming based API that allows
us to interact with the GPU -- upload data onto the GPU and then instruct it to render or draw 
efficiently, much faster than using the CPU.

  OpenGL itselfs is a specification (not an implementation) defining what a graphic API 
should look like where Hardware vendors (NVIDIA, AMD, Intel) implement his own version. 
*/

/*
The programmable Graphics-pipeline:

  Also known as the rendering pipeline, it is the sequence of steps OpenGL uses to transform 
3D data into a 2D image on the screen.

  It represents a vertex / line / triangle’s journey from 3D space to the final pixels on 
your screen.

Note: Shader
  This is a new term in the modern OpenGL pipline. 

  A shader is a small program that runs on the GPU. Shaders are the
programmable parts of the modern OpenGL pipeline.

  They allow developers to control how vertices are transformed and how
fragments (potential pixels) are colored, giving full control over how
geometry is rendered.

  Shaders are not optional in modern OpenGL (core profile requires them)

Note: 
  In OpenGL, a primitive is a basic geometric object formed by grouping one or more vertices, 
which the GPU can process and render.
*/
//For ex:

struct Point3D            //                  Z
{                         //                  |    
    float x, y, z;        //                  O──X
};                        //                 /
                          //                Y
Point3D point(1.0, 0.0, -5.0);   
//      ^~~~~
//  We define a point in 3D coordinates. We kwnow that this means a point in a 3D-space.
//  (Geometry-data)

/*                          
- But what does this mean in a 2D-screen?

  We want to make sure that this point show up the same way we are specifying in 3D 
coordinates. 

  So, the process that it goes throught is:

                        ┌───────────────────────┐   We define (specify) a vertex or a series
                        │  Vertex Specificaton  │ of vertices that represent geometry data (cube,   
                        │      (CPU side)       │ triangle, ...).
                        └───────────────────────┘ 
                                    |             Point3D point(1.0f, 0.0f, -5.0f);
                                    |                       
                                    |               We might also have other attributes such as 
                                    |             color and texture.
                                    | 
                                    |               So, vertex specification is where we setup on
                                    |             the CPU our geometry.
                                    |
                                    |               This data will be stored in buffers (VBOs) 
                                    |             on the GPU
                                    ↓
                        ┌── ── ── ── ── ── ── ──┐   The Vertex Shader executes on each vertex,
                        │     Vertex Shader     │ positioning that vertex.   
                        └── ── ── ── ── ── ── ──┘ 
                                    |               So, this will position our point in the space. 
                                    ↓               
                        ┌-----------------------┐   This allows to give more detail in my scene by 
              Optional  |      Tessellation     | subdividing my geometry-data further into smaller primitives  
                        └-----------------------┘ by adding more traingles using a tessellation shader.
                                    ↓ 
                        ┌-----------------------┐    Runs per primitive (point, line, triangle).  
              Optional  |     Geometry Shader   |  We can generate new geometry or discard existing geometry. 
                        └-----------------------┘  For ex: if I define only one point. I can generate on the GPU
                                    |              from this point more points.
                                    |
                                    ↓                Useful for effects like explosions or particle expansion.
                        ┌────────────────────────┐
                        | Vertex Post-Processing |   I can modify the goemtry data if needed
                        └────────────────────────┘
                                    ↓
                        ┌────────────────────────┐   Now we have our geometry data, we assemble those
                        |   Primitive Assembly   | going to be lines, triangles, etc getting the final
                        └────────────────────────┘ geometry
                                    |
                                    |                Assembles vertices into primitives (points, lines, triangles)
                                    ↓
                        ┌────────────────────────┐   Converts primitives into fragments (potential pixels).
                        |    Rasterization       |   This determinates which pixels get filled in to draw our object  
                        └────────────────────────┘  
                                    ↓                Important: fragments are not pixels yet
                        ┌----------------------┐
             Optional   |    Fragment Shader   |   executes on each fragment ('pixel') to Computes the final color, 
                        └----------------------┘ depth, and other attributes.
                                ↓
                        ┌──────────────────────┐
                        | Per-sample operation |
                        └──────────────────────┘

  Everytime we do a draw call has to go thorugh this pipeline.

*/

int main()
{ 
  return 0;
}