#ifndef __BACKROOMS_MESH_COMPONENT_HPP
#define __BACKROOMS_MESH_COMPONENT_HPP

/**
 * In the ideal world, this class would not hold the OpenGL
 * buffer objects, holding only a reference to an abstract
 * AssetID instead. The `MeshRenderer` would be the one concerned
 * with loading and unloading the GPU buffers, caching and reusing
 * then whenever possible.
 *
 * However, for now, I'll handle everything manually here.
 *
 * ...or will I?
 */
class MeshComponent {
};

#endif
