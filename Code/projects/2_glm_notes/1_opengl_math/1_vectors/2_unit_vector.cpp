/** // GLM (OpenGL Mathematics): Unit vector
 */
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/gtx/string_cast.hpp>

int main()
{
    // UNIT VECTORS (NORMALIZATION)
    //
    // A unit vector:
    // - Has length = 1
    // - Keeps the same direction
    //
    // Used for:
    // - Directions
    // - Lighting
    // - Camera movement
    //

    {
        /*
              y
              ^
              |
          3 - |        *
              |       /
          2 - |      /   â (a-hat)
              |     /
          1 - |    *
              |
              *----------------------> x
        */

        glm::vec3 a(3.0f, 4.0f, 0.0f);
        glm::vec3 a_hat = glm::normalize(a);

        std::cout << "vector a     : " << glm::to_string(a) << std::endl;
        std::cout << "length a     : " << glm::length(a) << std::endl;

        std::cout << "unit vector â: " << glm::to_string(a_hat) << std::endl;
        std::cout << "length â    : " << glm::length(a_hat) << std::endl; // 1
    }

    return 0;
}
