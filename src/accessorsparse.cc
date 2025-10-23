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
    const IndexHelper &helper, int count,
    const std::shared_ptr<GLTFAccessorSparseIndices> &indices,
    const std::shared_ptr<GLTFAccessorSparseValues> &values)
{
  std::shared_ptr<GLTFAccessorSparse> tmp (new GLTFAccessorSparse ());

  if (count < 1)
    {
      std::cout << "[W] glTF 2.0 5.2.1: accessor.sparse.count >= 1"
                << std::endl;
      return nullptr;
    }
  tmp->m_count = count;

  if (indices == nullptr)
    {
      std::cout
          << "[W] glTF 2.0 5.2.2: accessor.sparse.indices must be present"
          << std::endl;
      return nullptr;
    }
  // TODO : Check for buffer size
  tmp->m_indices = indices;

  if (values == nullptr)
    {
      std::cout << "[W] glTF 2.0 5.2.3: accessor.sparse.values must be present"
                << std::endl;
      return nullptr;
    }
  tmp->m_values = values;

  return tmp;
}

}