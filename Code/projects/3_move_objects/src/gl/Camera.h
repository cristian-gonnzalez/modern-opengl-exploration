#pragma once

#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/mat4x4.hpp> 
#include <glm/gtx/rotate_vector.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp> // lookAt

struct Projection
{
    public:
      explicit Projection( int width, int height )
      : _fovy{45.0f}, 
        _aspect{static_cast<float>(width) / static_cast<float>(height)},
        _near_plane{0.1f},
        _far_plane{10.0f}
      {
      }

      glm::mat4 get_projection_matrix() const
      {           
          return glm::perspective( glm::radians(_fovy),
                                   _aspect,
                                   _near_plane,
                                   _far_plane );
      }

    private:
      // Projection     
      float _fovy;          // View angle in the y direction. Expressed in radians
                            // This is how wide we seen in our screen      
      float _aspect;        // The aspect ratio is the ratio of x (width) to y (height).
      float _near_plane;    // distance from the viewer to the near clipping plane
      float _far_plane;     // distance from the viewer to the far clipping plane
};

/** Camera
 *
 * Pure CPU-side abstraction.
 * Produces View and Projection matrices.
 *
 * OpenGL has no camera — this class only computes matrices
 * that are later uploaded as uniforms by the Renderer.
 */
struct Camera
{
    public:
      Camera(int width, int height);
      glm::mat4 get_view_matrix() const;
      glm::mat4 get_projection_matrix() const;

      void move_forward(float speed);
      void move_backward(float speed);
      void move_right(float speed);
      void move_left(float speed);

      void mouse_look(float dx, float dy);

      int get_width() const
      {
        return _width;
      }
      int get_height() const
      {
        return _height;
      }

    private:
        // Projection
        Projection  _perspective;
        
        // Camera state
        glm::vec3 _eye{};                // Point: uses as location in space
        glm::vec3 _view_direction{};     // Direction vector: uses to see where it looks
        glm::vec3 _up_vector{};          // Direction vector: uses to orientation reference

        // Settings
        int _width{0}, _height{0};
        glm::vec2 _mouse{0.0f, 0.0f};
};


