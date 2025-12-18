#ifndef SPARSEINDICES_H
#define SPARSEINDICES_H

#include "gltfobject.h"
#include "indexhelper.h"
#include "gltftypes.h"

#include <memory>
#include <optional>

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
          const std::optional<int>& byte_offset,
          int component_type);
};

}

#endif // SPARSEINDICES_H
