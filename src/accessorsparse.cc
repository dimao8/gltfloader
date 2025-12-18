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

  if (count <= 0)
    {
      std::cout << "[W] glTF 2.0 5.2.1: accessor.sparse.count >= 1"
                << std::endl;
      return nullptr;
    }
  tmp->m_count = count;

  // NOTE : Presents is checked in GLTFAccessor::create
  tmp->m_indices = indices;

  // TODO : Check for buffer size
  tmp->m_values = values;

  return tmp;
}

}