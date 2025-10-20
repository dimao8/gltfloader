#include "accessorsparse.h"

#include <iostream>

namespace gltfloader
{

/* ***************** GLTFAccessorSparse::GLTFAccessorSparse **************** */

GLTFAccessorSparse::GLTFAccessorSparse () : GLTFObject ()
{
  //
}

/* *********************** GLTFAccessorSparse::count *********************** */

int
GLTFAccessorSparse::count () const
{
  return m_count;
}

/* *********************** GLTFAccessorSparse::values ********************** */

const std::shared_ptr<GLTFAccessorSparseValues> &
GLTFAccessorSparse::values () const
{
  return m_values;
}

/* ********************** GLTFAccessorSparse::indices ********************** */

const std::shared_ptr<GLTFAccessorSparseIndices> &
GLTFAccessorSparse::indices () const
{
  return m_indices;
}

/* *********************** GLTFAccessorSparse::create ********************** */

std::shared_ptr<GLTFAccessorSparse>
GLTFAccessorSparse::create (
    int count, const std::shared_ptr<GLTFAccessorSparseIndices> &indices,
    const std::shared_ptr<GLTFAccessorSparseValues> &values)
{
  std::shared_ptr<GLTFAccessorSparse> tmp (new GLTFAccessorSparse ());

  if (count < 1)
    {
      std::cout << "[W] glTF 2.0: The size of the Accessor.sparse can not be "
                   "less than 1"
                << std::endl;
      return nullptr;
    }
  tmp->m_count = count;

  if (indices == nullptr)
    {
      std::cout
          << "[W] glTF 2.0: The indices field of the object can not be null"
          << std::endl;
      return nullptr;
    }
  tmp->m_indices = indices;

  if (values == nullptr)
    {
      std::cout
          << "[W] glTF 2.0: The values field of the object can not be null"
          << std::endl;
      return nullptr;
    }
  tmp->m_values = values;

  return tmp;
}

}