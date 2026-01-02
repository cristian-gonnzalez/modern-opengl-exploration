/** How Shaders are used in the pipeline
 *  Modern OpenGL
 */
/*

  Modern OpenGL uses a programmable graphics pipeline. Shaders are small programs that run on the GPU and control
specific stages of this pipeline.

Pipeline overview (simplified):

                        ┌───────────────────────┐   
                        │  Vertex Specificaton  │   VAO's and VBO's  
                        │      (CPU side)       │ 
                        └───────────────────────┘ 
                                    ↓
                        ┌── ── ── ── ── ── ── ──┐   
                        │     Vertex Shader     │    Executes once per vertex and will be in charge of the final position of the vertex
                        └── ── ── ── ── ── ── ──┘ 
                                    ↓               
                                   ...
                                    ↓          
                        ┌----------------------┐    After determining which pixels are rasterized in the rasterization stage
                        |    Fragment Shader   |    The fragment shader executes once per fragment (i.e. roughly for every pixel that will be rasterized), 
                        └----------------------┘   and in part determines the final color that will be sent to the screen
                                ↓
                        ┌──────────────────────┐
                        | Per-sample operation |
                        └──────────────────────┘

    Shaders allow us to program how vertices are transformed and how fragments are colored.

    Vertex and fragment shaders are compiled with OpenGL commands and uploaded to the GPU.

*/


int main()
{
    return 0;
}