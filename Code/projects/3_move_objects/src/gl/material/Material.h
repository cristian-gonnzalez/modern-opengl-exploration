#pragma once

#include "Shader.h"
#include "UniformSet.h"

/** Material
 *
 * Couples a Shader with its uniform state.
 * Responsible for binding the shader and setting uniforms.
 *
 * Does NOT own geometry or perform draw calls.
 */
class Material 
{
    public:
        explicit Material(std::shared_ptr<Shader> shader)
        : _shader(std::move(shader)), _uniforms(*_shader) 
        {
        }

        void bind(const glm::mat4& model) 
        {
            _shader->use();
            _uniforms.set_mat4("u_model_matrix", model);
        }

        void bind(const float y_offset) 
        {
            _shader->use();
            _uniforms.set_float("u_offset", y_offset );
        }

        Shader& shader() { return *_shader; }

    private:
        std::shared_ptr<Shader> _shader;
        UniformSet _uniforms;
};