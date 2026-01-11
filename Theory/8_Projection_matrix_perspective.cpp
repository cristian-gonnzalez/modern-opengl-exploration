
/*
The OpenGL perspective projection matrix

Perspective:
  Perspective is the way we perceive depth in the real world.

  Objects appear smaller as they move farther away and larger as they
get closer to the viewer. This effect is called perspective projection.

  A common intuition is “divide by distance”:
      position ≈ (x / z, y / z)

  However, in OpenGL this is implemented using homogeneous coordinates
and a perspective divide, not an explicit division in user code.


- What does projection represent?

  Projection answers a global question:

      How is the 3D world mapped onto a 2D screen?

  Projection is a camera concern, not a per-object (renderable) concern.
In a game or engine, zooming in/out or changing the field of view is
done by modifying the camera’s projection matrix.


- Conceptual coordinate-space pipeline:

      Object space  --(Model)-->  World space
      World space   --(View)-->   Camera / View space
      View space    --(Projection)--> Clip space


- Canonical matrix responsibilities:

        Matrix        Responsibility           Scope
        ------------------------------------------------
        Model         Object transform          Per object
        View          Camera position/orient.  Per frame
        Projection    Camera lens / frustum    Per frame


- How the matrices are used:

  1. Model matrix
        Transforms vertices from local (object) space into world space.

                  local space -> world space

  2. View matrix (Camera)
       Transforms world-space coordinates into camera (view / eye) space.

                  world space -> view space

  3. Projection matrix (Camera lens)
       Transforms view-space coordinates into clip space, defining the visible frustum.

                view space -> Clip space


Visual intuition (camera frustum):

               /   \
              /     \     Perspective frustum
             /       \    (zoom in / zoom out
            /         \    changes the angle)
*/
