#ifndef SPARSEVALUES_H
#define SPARSEVALUES_H

#include "gltfobject.h"
#include "indexhelper.h"

#include <memory>

namespace gltfloader
{

class GLTFBufferView;

class GLTFAccessorSparseValues : public GLTFObject
{
private:
  size_t m_buffer_view;
  int m_byte_offset;

  GLTFAccessorSparseValues ();

public:
  GLTFAccessorSparseValues (const GLTFAccessorSparseValues &) = delete;
  virtual ~GLTFAccessorSparseValues () {}

  size_t buffer_view () const;
  int byte_offset () const;

  static std::shared_ptr<GLTFAccessorSparseValues>
  create (const IndexHelper &helper, int buffer_view, int byte_offset = 0);
};

}

#endif // SPARSEVALUES_H
