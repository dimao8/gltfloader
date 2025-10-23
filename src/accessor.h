#ifndef ACCESSOR_H
#define ACCESSOR_H

#include "gltfnamedobject.h"
#include "indexhelper.h"

#include <memory>
#include <vector>

namespace gltfloader
{

enum class GLTFAccessorComponentType
{
  byte = 5120,
  unsigned_byte = 5121,
  sshort = 5122,
  unsigned_short = 5123,
  unsigned_int = 5125,
  ffloat = 5126
};

enum class GLTFAccessorType
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
  size_t m_buffer_view;
  int m_byte_offset;
  GLTFAccessorComponentType m_component_type;
  GLTFAccessorType m_type;
  bool m_normalize;
  int m_count;
  std::vector<float> m_min;
  std::vector<float> m_max;
  std::shared_ptr<GLTFAccessorSparse> m_sparse;

  GLTFAccessor (const std::string &name);

public:
  GLTFAccessor () = delete;
  GLTFAccessor (const GLTFAccessor &) = delete;

  virtual ~GLTFAccessor () {}

  size_t buffer_view () const;
  int byte_offset () const;
  GLTFAccessorComponentType component_type () const;
  GLTFAccessorType type () const;
  bool normalize () const;
  int count () const;
  const std::vector<float> &min () const;
  const std::vector<float> &max () const;
  const std::shared_ptr<GLTFAccessorSparse> &sparse () const;

  static std::shared_ptr<GLTFAccessor>
  create (const IndexHelper &helper, const std::string &name,
          int component_type, int count, const std::string &type,
          int buffer_view, int byte_offset = 0, bool normalize = false,
          const std::vector<float> &min = {},
          const std::vector<float> &max = {},
          const std::shared_ptr<GLTFAccessorSparse> &sparse = nullptr);

  static std::shared_ptr<GLTFAccessor> create (const IndexHelper &helper,
                                               const std::string &name);
};

}

#endif // ACCESSOR_H
