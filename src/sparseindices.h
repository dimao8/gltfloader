#ifndef SPARSEINDICES_H
#define SPARSEINDICES_H

#include "gltfobject.h"
#include "indexhelper.h"
#include "gltftypes.h"

#include <memory>

namespace gltfloader
{

class GLTFBufferView;

class GLTFAccessorSparseIndices : public GLTFObject
{
private:
  size_t m_buffer_view;
  int m_byte_offset;
  GLTFComponentType m_component_type;

  GLTFAccessorSparseIndices ();

public:
  GLTFAccessorSparseIndices (const GLTFAccessorSparseIndices &) = delete;
  virtual ~GLTFAccessorSparseIndices () {}

  size_t buffer_view () const;
  int byte_offset () const;
  GLTFComponentType component_type () const;

  static std::shared_ptr<GLTFAccessorSparseIndices>
  create (const IndexHelper &helper, int buffer_view,
          int component_type, int byte_offset = 0);
};

}

#endif // SPARSEINDICES_H
