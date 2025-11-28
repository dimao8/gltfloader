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

size_t
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

GLTFComponentType
GLTFAccessorSparseIndices::component_type () const
{
  return m_component_type;
}

/* ******************* GLTFAccessorSparseIndices::create ******************* */

std::shared_ptr<GLTFAccessorSparseIndices>
GLTFAccessorSparseIndices::create (const IndexHelper &helper, int buffer_view,
                                   int component_type, int byte_offset)
{
  std::shared_ptr<GLTFAccessorSparseIndices> tmp (
      new GLTFAccessorSparseIndices ());

  // TODO : Check bufferView content

  if (buffer_view < 0)
    {
      std::cout
          << "[W] glTF 2.0 5.3.1: accessor.sparse.indices.bufferView >= 0"
          << std::endl;
      return nullptr;
    }
  if (buffer_view >= helper.buffer_views_size ())
    {
      std::cout << "[W] glTF 2.0 5.3.1: accessor.sparse.indices.bufferView is "
                   "out of range"
                << std::endl;
      return nullptr;
    }
  tmp->m_buffer_view = buffer_view;

  switch (component_type)
    {
    case static_cast<int> (GLTFComponentType::unsigned_byte):
      tmp->m_component_type = GLTFComponentType::unsigned_byte;
      break;

    case static_cast<int> (GLTFComponentType::unsigned_short):
      tmp->m_component_type = GLTFComponentType::unsigned_short;
      break;

    case static_cast<int> (GLTFComponentType::unsigned_int):
      tmp->m_component_type = GLTFComponentType::unsigned_short;
      break;

    default:
      std::cout << "[W] glTF 2.0 5.3.3: accessor.componentType can be only "
                   " 5121, 5123 or 5125"
                << std::endl;
      return nullptr;
    }

  if (byte_offset < 0)
    {
      std::cout
          << "[W] glTF 2.0 5.3.2: accessor.sparse.indices.byteOffset >= 0"
          << std::endl;
      return nullptr;
    }
  tmp->m_byte_offset = byte_offset;

  return tmp;
}

}