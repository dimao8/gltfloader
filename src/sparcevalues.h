#ifndef SPARSEVALUES_H
#define SPARSEVALUES_H

#include "bufferview.h"
#include "gltfobject.h"

#include <memory>

namespace gltfloader
{

class GLTFBufferView;

class GLTFAccessorSparseValues : public GLTFObject
{
private:
  std::shared_ptr<GLTFBufferView> m_buffer_view;
  int m_byte_offset;

  GLTFAccessorSparseValues ();

public:
  GLTFAccessorSparseValues (const GLTFAccessorSparseValues &) = delete;
  virtual ~GLTFAccessorSparseValues () {}

  const std::shared_ptr<GLTFBufferView> &buffer_view () const;
  int byte_offset () const;

  static std::shared_ptr<GLTFAccessorSparseValues>
  create (const std::shared_ptr<GLTFBufferView> &buffer_view,
          int byte_offset = 0);
};

}

#endif // SPARSEVALUES_H
