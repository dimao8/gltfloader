#ifndef ACCESSOR_H
#define ACCESSOR_H

#include "gltfnamedobject.h"

#include <memory>
#include <vector>

namespace gltfloader
{

enum GLTFAccessorComponentType
{
  unknown = -1,
  byte = 5120,
  unsigned_byte = 5121,
  shrt = 5122,
  unsigned_shrt = 5123,
  unsigned_int = 5125,
  flt = 5126
};

enum GLTFAccessorType
{
  scalar,
  vec2,
  vec3,
  vec4,
  mat2,
  mat3,
  mat4
};

class GLTFBufferView;
class GLTFAccessorSparse;

class GLTFAccessor : public GLTFNamedObject
{
private:
  std::shared_ptr<GLTFBufferView> m_buffer_view;
  int m_byte_offset;
  GLTFAccessorComponentType m_component_type;
  GLTFAccessorType m_type;
  bool m_normalize;
  int m_count;
  std::vector<float> m_min;
  std::vector<float> m_max;
  std::vector<std::shared_ptr<GLTFAccessorSparse> > m_sparse;

  GLTFAccessor (const std::string &name);

  bool is_bad () const;

public:
  GLTFAccessor () = delete;
  GLTFAccessor (const GLTFAccessor &) = delete;

  virtual ~GLTFAccessor () {}

  static std::shared_ptr<GLTFAccessor> create (
      const std::string &name, GLTFAccessorComponentType component_type,
      int count, GLTFAccessorType type,
      const std::shared_ptr<GLTFBufferView> &buffer_view = nullptr,
      int byte_offset = 0, bool normalize = false,
      const std::vector<float> &min = {}, const std::vector<float> &max = {},
      const std::vector<std::shared_ptr<GLTFAccessorSparse> > &sparse = {});
};

}

#endif // ACCESSOR_H
