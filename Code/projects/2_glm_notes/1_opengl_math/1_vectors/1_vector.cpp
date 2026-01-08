/** GLM (OpenGL Mathematics)
 */
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/gtx/string_cast.hpp>

//
// Coordinate System (OpenGL default)
//
//          y
//          ^
//          |
//          |
//          |
//          *------------------------> x
//         /
//        /
//       z
//
// Right-handed coordinate system
//

int main()
{
    // VECTORS
    //   A vector represents a DIRECTION and a MAGNITUDE (length).
    // It does NOT represent a position by itself.
    //
    // Length formula:
    // |v| = sqrt(x² + y² + z²)
    //

    {
        /*
              y
              ^
              |
          4 - |        B (0,4,0)
              |
          3 - |   A (3,0,0)
              |
              *----------------------> x
        */

        glm::vec3 a(3.0f, 0.0f, 0.0f);
        glm::vec3 b(0.0f, 4.0f, 0.0f);

        std::cout << "vector a: " << glm::to_string(a) << std::endl;
        std::cout << "vector b: " << glm::to_string(b) << std::endl;

        std::cout << "length a: " << glm::length(a) << std::endl; // 3
        std::cout << "length b: " << glm::length(b) << std::endl; // 4
    }

    {
        /*
              y
              ^
          4 - |        *
              |       /
          3 - |      /  A (3,4,0)
              |     /
          2 - |    /
              |   /
          1 - |  /
              | /
              *----------------------> x

        length = sqrt(3² + 4²) = 5
        */

        glm::vec3 a(3.0f, 4.0f, 0.0f);
        std::cout << "vector a: " << glm::to_string(a) << std::endl;
        std::cout << "length a: " << glm::length(a) << std::endl; // 5
    }

    return 0;
}
