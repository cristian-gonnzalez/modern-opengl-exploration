/** 
 * 
 */

/*
OpenGL Mathematics: 

This file intends to check if GLM library works.

Download GLM library https://glm.g-truc.net/0.9.9/ 

*/


#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_SWIZZLE

// GL Math
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtx/string_cast.hpp>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

int main()
{
	/*
	
	- dot()

			GLM_FUNC_DECL T glm::dot	(	vec< L, T, Q > const & 	x,
											vec< L, T, Q > const & 	y )		

	  Returns the dot product of x and y, i.e., result = x * y.

	Template Parameters
		L	An integer between 1 and 4 included that qualify the dimension of the vector.
		T	Floating-point scalar types.
	
	*/


	glm::vec3 a(2.0f);
	glm::vec3 b(1.5f);

	float f = glm::dot(a, b);
    
	std::cout << "a * b = " << f << std::endl; 

	/*
	
	- normalize()

			GLM_FUNC_DECL vec<L, T, Q> glm::normalize	(	vec< L, T, Q > const & 	x	)	

	  Returns a vector in the same direction as x but with length of 1.

  	  According to issue 10 GLSL 1.10 specification, if length(x) == 0 then result is undefined and generate an error.

	Template Parameters
		L	An integer between 1 and 4 included that qualify the dimension of the vector.
		T	Floating-point scalar types.
	*/

	
	f = glm::dot( glm::normalize(a), glm::normalize(b) );
    
	std::cout << "x * y = " << f << std::endl; 

	std::cout << "a: " << glm::to_string( a ) << " "
	          << "normalize(a): " << glm::to_string( glm::normalize(a) ) << std::endl
	          << "b: " << glm::to_string( b ) << " " 
	          << "normalize(b): " << glm::to_string( glm::normalize(b) ) << std::endl; 	

	glm::mat4 mat(1.0f);
	std::cout << "mat: " << glm::to_string( mat ) << std::endl; 	

	std::cout << glm::to_string( a.yz() ) << std::endl;
	//                             ^~
	//                          SWIZZLE
	std::cout << glm::to_string( b.xyz() ) << std::endl;
	std::cout << glm::to_string( b.zyx() ) << std::endl;

	glm::vec3 c = glm::cross( a,b );
	std::cout << glm::to_string( c ) << std::endl;

	return 0;
}