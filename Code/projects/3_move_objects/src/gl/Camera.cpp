#include "Camera.h"
#include <algorithm>


Camera::Camera(int width, int height)
: _perspective{width, height},
  _width{width},
  _height{height},
  _mouse{width/2, height/2}
{
    // Asume we are placed at the origin
    // NOTE: If you are modeling a game, the eye position might be a little bit elevated since 
    // your characteer has height 
    _eye = glm::vec3(0.0f,0.0f,0.0f);
 // ^~~~
 // eye is a Point (not a vector)
 //
    
    // Assume we are looking out into the world
    // NOTE: This is aling '-z', because otherwise, we'd be looking behind us.
    _view_direction =glm::vec3(0.0f, 0.0f, -1.0f);
    //                                     ^~~~~
    // If we use the right-hand rule, the figure is +z towards us, so we are viewing -z towards the figure
    //
    //                        World space
    //                               Y
    //                               ^
    //                               |
    //                               ^ y'        ┐
    //                               |/ |        |  
    //                              /   *        |  Figure local coordinates  
    //                             / |/          |  (In this image is rotated over y-axis)
    //                            * /            |  
    //                            |/ |           |
    //                            *  +-------->  |
    //                             / |       z'  ┘
    //                            /  |
    //                          -x'  +-----------------------> X
    //                             /
    //                            /
    //                           /
    //                    Y     Z 
    //                    ^
    //                    |                   ┌─────┐  
    //                    | /-Z               |     |_|
    //                    |/                  └─────┘
    //        ------------+ ------------->   Camera view 
    //                   /               X 
    //                  /
    //                +Z  

    // Asume we start on a perfect plane
    _up_vector =glm::vec3(0.0f, 1.0f, 0.0f);
    //                          ^~~~
    //              Our up-orientation (y axis) is aligned witu the Y axis of the World space

    // NOTE: 
    //   '_view_direction' and '_up_vector' must be vectors, They are used as 'direction vector'
    // :
    //      - Must not translate
    //      - Only rotate
    //      - Represent orientation, not location.
    //
    // That’s why they are:
    //      - Normalized
    //      - Used in cross products
    //      - Treated as basis vectors

    // IMPORTANT: Why this matters that _eye is a 'POINT' and _view and _up are 'DIRECTION VECTORS':
    //
    //      - Translation matrix affects points
    //      - Translation matrix does not affect vectors.

    // Conceptually:
    //    We define a 'eye' point and uses normailized vectors (view/up) as orientation as shown:
    //
    //                          World space
    //                               Y
    //                               ^
    //                               |
    //                               ^ y'        ┐
    //                               |/ |        |  
    //                              /   *        |  Figure local coordinates  
    //                             / |/          |  (In this image is rotated over y-axis)
    //                            * /            |  
    //                            |/ |           |
    //                            *  +-------->  |
    //                             / |       z'  ┘
    //                           -x  |
    //                               |
    //                   _up (0,1,0) ^ ^ _view (0,0,-1)
    //                               |/
    //                               +-----------------------> X
    //                    *         /
    //                 _eye        /
    //                 (Point)    /
    //                          Z 
    //                     
    //                  
}


glm::mat4 Camera::get_view_matrix() const
{
    return glm::lookAt( _eye,                   // position of the camera
                     // point + vector         = point
                     // ^~~~~   ^~~~~~~~~~~~~~
                        _eye + _view_direction, // center = eye + direction
                        //     ^~~~~~~~~~~~~~~     ^~~~~~
                        //     front              Position where the camera is looking up   
                        _up_vector);
}
glm::mat4 Camera::get_projection_matrix() const
{
    return _perspective.get_projection_matrix();
}


// Movement
void Camera::move_forward(float speed)
{
    // _eye.z is the position of our eyes so it is where our camera is based in the view direction

    // Point + Vector = Point
    _eye += _view_direction * speed;
        //  ^~~~~~~~~~~~~~~
        // This is our front. So we want to update x,y,z based in our front
        //
        // For ex:
        //      _eye (point)           _view (vector)        speed
        //      ^~~~~~~~~~~~~~~~~      ^~~~~~~~~~~~~~~~~~    ^~~~~~~~~~~~~~~~~~
        //      [1.0f, 2.0f, 3.0f] + ( [1.0f, 0.0f, 0.0f]  * [0.5f, 0.5f, 0.5f] ) 
        //                              ^~~~ 
        //                          Our direction is +x
        //      [1.0f, 2.0f, 3.0f] + ( 0.5f, 0.0f, 0.0f] )
        //
        //      [1.5f, 2.0f, 3.0f]
        //       ^~~~
        //   _eye only was moved in the _view direction 
        //
}

void Camera::move_backward(float speed)
{
    _eye -= _view_direction * speed;  
}


void Camera::move_right(float speed)
{
    //   The cross product of two vectors, the result is always a vector that points in a 
    // direction perpendicular (or 90 degrees) to both of the original vectors
    //
    //                                            C 
    //        ^ A                                 ^   ^ A
    //       /                     A * B  ->      |  /
    //      /                                     | /
    //     +----------> B                         +----------> B   
    //    

    //   With this concept, we can know where the right side is in our camera since we have Y (up)
    // and Z (view) vectors.
    //
    //   If two vectors lie in the Z-Y plane, their cross-product results in a vector along the 
    // X-axis, perpendicular to the ZY plane.
    //                                             front             up    
    //        x-axis                               z-axis          y- axis
    //        ^~~~~                             ^~~~~~~~~~~~~~~  ^~~~~~~~~~
    glm::vec3 right = glm::normalize(glm::cross(_view_direction, _up_vector));
    //        ^~~~~
    //    This vector tell us where the rigth side is. That's why we named it 'rigth'
    //
    //   If we use the rigth hand rule, our thumb finger always point to our rigth side (+x)
    // 
    //                               ^ y       
    //                               |
    //                               *   
    //                              /| \     
    //                             / |  \   
    //                           *---|---*    
    //                               |           
    //                               +--------> x  
    //                             /          
    //                           z  
    //
    _eye += right * speed;
}

void Camera::move_left(float speed)
{
    glm::vec3 right = glm::normalize(glm::cross(_view_direction, _up_vector));
    _eye -= right * speed;
}

// Mouse look
void Camera::mouse_look(float dx, float dy)
{
    glm::vec2 _old = _mouse;

    // current position
    _mouse.x += dx;
    _mouse.y += dy;

    glm::vec2 delta = _old - _mouse;
        
    // Using glm::rotate from rotate_vector
    _view_direction = glm::rotate( _view_direction, 
                                    glm::radians(delta.x), 
                                    _up_vector );
                                 // ^~~~~~~~~~
                                 // we rotate over our y-axis       
}


