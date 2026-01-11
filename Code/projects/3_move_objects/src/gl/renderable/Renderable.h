#pragma once

#include "Mesh.h"
#include "Transform.h"
#include "Material.h"


/** Renderable
 *
 * In engine design, a Renderable is the conceptual object that can be drawn.
 * It doesn’t own the GPU resources; it’s more like a bundle of everything needed to issue a draw call.
 */
struct Renderable 
{
    Renderable(Mesh* mesh_ptr, Material* mat_ptr)
    : mesh{mesh_ptr}, material{mat_ptr}
    {
    }

    Mesh*       mesh{nullptr};
    Material*   material{nullptr};
    Transform   transform{};
};