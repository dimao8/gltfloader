#ifndef SPARSEINDICES_H
#define SPARSEINDICES_H

#include "gltfobject.h"

#include <memory>

namespace gltfloader
{

class GLTFBufferView;

enum GLTFSparseIndicesComponentType
{
  unknown = -1,
  unsigned_byte = 5121,
  unsigned_short = 5123,
  unsigned_int = 5125
};

class GLTFAccessorSparseIndices : public GLTFObject
{
private:
  std::shared_ptr<GLTFBufferView> m_buffer_view;
  int m_byte_offset;
  GLTFSparseIndicesComponentType m_component_type;

  GLTFAccessorSparseIndices ();

public:
  GLTFAccessorSparseIndices (const GLTFAccessorSparseIndices &) = delete;
  virtual ~GLTFAccessorSparseIndices () {}

  const std::shared_ptr<GLTFBufferView>& buffer_view () const;
  int byte_offset () const;
  GLTFSparseIndicesComponentType component_type () const;

  static std::shared_ptr<GLTFAccessorSparseIndices>
  create (const std::shared_ptr<GLTFBufferView> &buffer_view,
          GLTFSparseIndicesComponentType component_type, int byte_offset = 0);
};

}

#endif // SPARSEINDICES_H
