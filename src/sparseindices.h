#ifndef SPARSEINDICES_H
#define SPARSEINDICES_H

#include "gltfobject.h"
#include "indexhelper.h"

#include <memory>

namespace gltfloader
{

class GLTFBufferView;

// FIXME : Can be moved into separate file
enum class GLTFSparseIndicesComponentType
{
  unsigned_byte = 5121,
  unsigned_short = 5123,
  unsigned_int = 5125
};

class GLTFAccessorSparseIndices : public GLTFObject
{
private:
  size_t m_buffer_view;
  int m_byte_offset;
  GLTFSparseIndicesComponentType m_component_type;

  GLTFAccessorSparseIndices ();

public:
  GLTFAccessorSparseIndices (const GLTFAccessorSparseIndices &) = delete;
  virtual ~GLTFAccessorSparseIndices () {}

  size_t buffer_view () const;
  int byte_offset () const;
  GLTFSparseIndicesComponentType component_type () const;

  static std::shared_ptr<GLTFAccessorSparseIndices>
  create (const IndexHelper &helper, int buffer_view,
          int component_type, int byte_offset = 0);
};

}

#endif // SPARSEINDICES_H
