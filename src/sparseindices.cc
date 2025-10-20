#include "sparseindices.h"

#include <iostream>

namespace gltfloader
{

/* ********** GLTFAccessorSparseIndices::GLTFAccessorSparseIndices ********* */

GLTFAccessorSparseIndices::GLTFAccessorSparseIndices () : GLTFObject ()
{
  //
}

/* ***************** GLTFAccessorSparseIndices::buffer_view **************** */

const std::shared_ptr<GLTFBufferView> &
GLTFAccessorSparseIndices::buffer_view () const
{
  return m_buffer_view;
}

/* ***************** GLTFAccessorSparseIndices::byte_offset **************** */

int
GLTFAccessorSparseIndices::byte_offset () const
{
  return m_byte_offset;
}

/* *************** GLTFAccessorSparseIndices::component_type *************** */

GLTFSparseIndicesComponentType
GLTFAccessorSparseIndices::component_type () const
{
  return m_component_type;
}

/* ******************* GLTFAccessorSparseIndices::create ******************* */

std::shared_ptr<GLTFAccessorSparseIndices>
GLTFAccessorSparseIndices::create (
    const std::shared_ptr<GLTFBufferView> &buffer_view,
    GLTFSparseIndicesComponentType component_type, int byte_offset)
{
  std::shared_ptr<GLTFAccessorSparseIndices> tmp (
      new GLTFAccessorSparseIndices ());

  // TODO : Check bufferView content

  if (buffer_view == nullptr)
    {
      std::cout << "[W] glTF 2.0: The bufferView object must be present in "
                   "accessor.sparse.sparseIndices field"
                << std::endl;
      return nullptr;
    }
  tmp->m_buffer_view = buffer_view;

  tmp->m_component_type = component_type;

  if (byte_offset < 0)
    {
      std::cout << "[W] glTF 2.0: The byteOffset can not be less than 0 in "
                   "accessor.sparse.sparseIndices field"
                << std::endl;
      return nullptr;
    }
  tmp->m_byte_offset = byte_offset;

  return tmp;
}

}