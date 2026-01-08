/** GLM (OpenGL Mathematics): cross product
 * 
 */
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SWIZZLE

#include <glm/vec3.hpp>
#include <glm/gtx/string_cast.hpp>

/*
Cross product returns a vector perpendicular to the plane formed by vectors a and b.

Important:
    - Order matters!
    - Follows the RIGHT-HAND RULE
*/


int main()
{
	{
        glm::vec3 a(0.0f, 4.0f, 0.0f);
		glm::vec3 b(4.0f, 0.0f, 0.0f);

        glm::vec3 c = glm::cross( a, b );
                      //          ^~~~
                      //   The order of the product matters
        std::cout << "cross product (a, b): " << glm::to_string(c) << std::endl;             // cross product (a, b): vec3(0.000000, 0.000000, -16.000000)
        glm::vec3 d = glm::cross( b, a );
                      //          ^~~~
                      //   The order of the product matters
        std::cout << "cross product (b, a): " << glm::to_string(d) << std::endl;             // cross product (b, a): vec3(0.000000, 0.000000, 16.000000) 
    }

	return 0;
}


