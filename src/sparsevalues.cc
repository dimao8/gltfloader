#include "sparcevalues.h"

#include <iostream>

namespace gltfloader
{

/* *********** GLTFAccessorSparseValues::GLTFAccessorSparseValues ********** */

GLTFAccessorSparseValues::GLTFAccessorSparseValues () : GLTFObject ()
{
  //
}

/* ***************** GLTFAccessorSparseValues::buffer_view ***************** */

size_t
GLTFAccessorSparseValues::buffer_view () const
{
  return m_buffer_view;
}

/* ***************** GLTFAccessorSparseValues::byte_offset ***************** */

int
GLTFAccessorSparseValues::byte_offset () const
{
  return m_byte_offset;
}

/* ******************** GLTFAccessorSparseValues::create ******************* */

std::shared_ptr<GLTFAccessorSparseValues>
GLTFAccessorSparseValues::create (const IndexHelper &helper, int buffer_view,
                                  int byte_offset)
{
  std::shared_ptr<GLTFAccessorSparseValues> tmp (
      new GLTFAccessorSparseValues ());

  if (buffer_view < 0)
    {
      std::cout << "[W] glTF 2.0 5.4.1: accessor.sparse.values.bufferView >= 0"
                << std::endl;
      return nullptr;
    }
  if (buffer_view >= helper.buffer_views_size ())
    {
      std::cout << "[W] glTF 2.0 5.4.1: accessor.sparse.values.bufferView is "
                   "out of range"
                << std::endl;
      return nullptr;
    }
  // TODO : Check for the buffer size
  tmp->m_buffer_view = buffer_view;

  if (byte_offset < 0)
    {
      std::cout << "[W] glTF 2.0 5.4.2: accessor.sparse.values.byteOffset >= 0"
                << std::endl;
      return nullptr;
    }
  tmp->m_byte_offset = byte_offset;

  return nullptr;
}

}