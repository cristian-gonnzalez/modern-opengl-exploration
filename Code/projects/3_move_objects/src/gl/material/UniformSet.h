#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include <glad/glad.h> 

#include "Shader.h"

/** UniformSet
 *
 * Caches and updates shader uniform locations.
 * Provides type-safe uniform upload helpers.
 *
 * Always operates on the currently bound shader.
 */
class UniformSet 
{
  public:
    explicit UniformSet(Shader& shader)
    : _shader(shader) 
    {
    }

    void set_mat4(const std::string& name, const glm::mat4& m) 
    {
        _shader.use();
        auto [success, location] = get_location(name);
        if(success)
            glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
    }

    void set_float(const std::string& name, float v) 
    {
        _shader.use();
        auto [success, location] = get_location(name);
        if(success)
            glUniform1f(location, v);
    }

private:
    std::pair<bool, GLint> get_location(const std::string& name) 
    {
        if( auto it = _cache.find(name); 
            it != _cache.end() )
            return {true, it->second};

        // Returns the location of a uniform variable
        auto [success, loc] = _shader.get_uv_location( name );
        if (success)
           _cache[name] = loc;
            
        return {success, loc};  
    }

    Shader&                                 _shader;
    std::unordered_map<std::string, GLint>  _cache{};
};