#pragma once

#include <glm/mat4x4.hpp> 
#include <glm/ext/matrix_clip_space.hpp>


struct Camera
{
    explicit Camera( int width, int height )
    : _fovy{45.0f}, 
      _aspect{static_cast<float>(width) / static_cast<float>(height)},
      _near_plane{0.1f},
      _far_plane{10.0f}
    {
    }

    float _fovy{60.0f};           // View angle in the y direction. Expressed in radians
                                                                     // This is how wide we seen in our screen      
    float _aspect{16.0f / 9.0f};  // The aspect ratio is the ratio of x (width) to y (height).
    float _near_plane{0.1f};      // distance from the viewer to the near clipping plane
    float _far_plane{100.0f};     // distance from the viewer to the far clipping plane

    glm::mat4 get_projection_matrix() const
    {           
        return glm::perspective( glm::radians(_fovy),
                                 _aspect,
                                 _near_plane,
                                 _far_plane );
    }
};
