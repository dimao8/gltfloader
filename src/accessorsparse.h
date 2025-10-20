#ifndef ACCESSORSPARSE_H
#define ACCESSORSPARSE_H

#include "gltfobject.h"

#include <memory>

namespace gltfloader
{

class GLTFBufferView;
class GLTFAccessorSparseIndices;
class GLTFAccessorSparseValues;

class GLTFAccessorSparse : public GLTFObject
{
protected:
  int m_count;
  std::shared_ptr<GLTFAccessorSparseIndices> m_indices;
  std::shared_ptr<GLTFAccessorSparseValues> m_values;

  GLTFAccessorSparse ();

public:
  GLTFAccessorSparse (const GLTFAccessorSparse &) = delete;

  virtual ~GLTFAccessorSparse () {}

  int count () const;
  const std::shared_ptr<GLTFAccessorSparseValues> &values () const;
  const std::shared_ptr<GLTFAccessorSparseIndices> &indices () const;

  static std::shared_ptr<GLTFAccessorSparse>
  create (int count, const std::shared_ptr<GLTFAccessorSparseIndices> &indices,
          const std::shared_ptr<GLTFAccessorSparseValues> &values);
};

}

#endif // ACCESSORSPARSE_H
