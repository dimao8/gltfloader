#include "sparcevalues.h"

#include <iostream>

namespace gltfloader
{

/* *********** GLTFAccessorSparseValues::GLTFAccessorSparseValues ********** */

GLTFAccessorSparseValues::GLTFAccessorSparseValues () : GLTFObject ()
{
  //
}

/* ******************** GLTFAccessorSparseValues::create ******************* */

std::shared_ptr<GLTFAccessorSparseValues>
GLTFAccessorSparseValues::create (
    const std::shared_ptr<GLTFBufferView> &buffer_view, int byte_offset)
{
  std::shared_ptr<GLTFAccessorSparseValues> tmp (
      new GLTFAccessorSparseValues ());

  if (buffer_view == nullptr)
    {
      std::cout << "[W] glTF 2.0: The bufferView object must be present in "
                   "accessor.sparse.sparseValues field"
                << std::endl;
      return nullptr;
    }
  tmp->m_buffer_view = buffer_view;

  if (byte_offset < 0)
    {
      std::cout << "[W] glTF 2.0: The byteOffset can not be less than 0 in "
                   "accessor.sparse.sparseValues field"
                << std::endl;
      return nullptr;
    }
  tmp->m_byte_offset = byte_offset;

  return nullptr;
}

/* ***************** GLTFAccessorSparseValues::buffer_view ***************** */

const std::shared_ptr<GLTFBufferView> &
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

}