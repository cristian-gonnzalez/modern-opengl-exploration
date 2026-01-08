/** GLM (OpenGL Mathematics): dot product
 */
#include <iostream>
#include <cmath>

#include <glm/vec3.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtx/string_cast.hpp>

/*
Dot product:
  Dot product measures how aligned two vectors are (how similar 2 vectors are).

  Formula: a · b = |a||b|cos(theta)
  If vectors are normalized: dot(a, b) = cos(theta)

*/

int main()
{
	{
        glm::vec3 a(3.0f, 4.0f, 0.0f);
        glm::vec3 b(0.0f, 7.0f, 0.0f);

        //                 Ax*Bx + Ay*By + Az*Bz
        //                      ^~~~~~~
        float raw_dot = glm::dot(a, b);
        
        // The result is hard to understand, so we need to normalized to get a better rusult
        std::cout << "raw dot(a, b): " << raw_dot << std::endl;          // raw dot(a, b): 28

        float dot_product = glm::dot(glm::normalize(a), glm::normalize(b));
        float angle = std::acos(dot_product) * 180.0f / glm::pi<float>(); 

        std::cout << "normalized dot(a, b): " << dot_product << std::endl; // normalized dot(a, b): 0.8 
        std::cout << "angle: " << angle << " degrees\n" << std::endl;      // angle: 36.8699 degrees       
	}
  {	
        
    /*
            ^
            |        0 = 90
          B |0   A
            *---->
		*/

    // Perpendicular vectors (90°)
		glm::vec3 a(1.0f, 0.0f, 0.0f);
		glm::vec3 b(0.0f, 1.0f, 0.0f);

    
    float dot_product = glm::dot(a, b);
    float angle = std::acos(dot_product) * 180.0f / glm::pi<float>();
                                                                        //   This means that a and b are perpendicular 
                                                                        //                      ^
    std::cout << "dot (perpendicular): " << dot_product << std::endl;   // dot (perpendicular): 0
    std::cout << "angle: " << angle << " degrees\n" << std::endl;       // angle: 90 degrees
	}
  {	        
    /*
                0 = 0
         
            *----------> AB
		*/

    // Same direction (0°)
		glm::vec3 a(1.0f, 0.0f, 0.0f);
		glm::vec3 b(1.0f, 0.0f, 0.0f);

    float dot_product = glm::dot(a, b);
    float angle = std::acos(dot_product) * 180.0f / glm::pi<float>();

                                                                             //   This means that a and b are paralel and moving the same directions
                                                                             //                       ^
    std::cout << "dot (same direction): " << dot_product << std::endl;       // dot (same direction): 1
    std::cout << "angle: " << angle << " degrees\n" << std::endl;            // angle: 0 degrees
	}  
  {	     
    /*        
          B  0   A
     <-------*-------->
            
		*/
     // Opposite direction (180°)
		glm::vec3 a(1.0f, 0.0f, 0.0f);
		glm::vec3 b(-1.0f, 0.0f, 0.0f);

    
    float dot_product = glm::dot(a, b);
    float angle = std::acos(dot_product) * 180.0f / glm::pi<float>();

                                                                             // This means that a and b are paralel and moving oposite directions
                                                                             //                            ^
    std::cout << "dot (opposite direction): " << dot_product << std::endl;   // dot (opposite direction): -1
    std::cout << "angle: " << angle << " degrees\n" << std::endl;            // angle: 180 degrees
	}

	return 0;
}



