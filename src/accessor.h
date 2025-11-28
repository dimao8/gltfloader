#ifndef ACCESSOR_H
#define ACCESSOR_H

#include "gltfnamedobject.h"
#include "indexhelper.h"
#include "gltftypes.h"

#include <memory>
#include <optional>
#include <vector>

namespace gltfloader
{

class GLTFBufferView;
class GLTFAccessorSparse;

class GLTFAccessor : public GLTFNamedObject
{
private:
  std::optional<size_t> m_buffer_view;
  size_t m_byte_offset;
  GLTFComponentType m_component_type;
  GLTFAccessorType m_type;
  bool m_normalize;
  size_t m_count;
  std::vector<float> m_min;
  std::vector<float> m_max;
  std::shared_ptr<GLTFAccessorSparse> m_sparse;

  GLTFAccessor (const std::string &name);

public:
  GLTFAccessor () = delete;
  GLTFAccessor (const GLTFAccessor &) = delete;

  virtual ~GLTFAccessor () {}

  const std::optional<size_t> &buffer_view () const;
  size_t byte_offset () const;
  GLTFComponentType component_type () const;
  GLTFAccessorType type () const;
  bool normalize () const;
  size_t count () const;
  const std::vector<float> &min () const;
  const std::vector<float> &max () const;
  const std::shared_ptr<GLTFAccessorSparse> &sparse () const;

  static std::shared_ptr<GLTFAccessor>
  create (const IndexHelper &helper, const std::string &name,
          int component_type, int count, const std::string &type,
          const std::optional<int> &buffer_view, int byte_offset = 0,
          bool normalize = false, const std::vector<float> &min = {},
          const std::vector<float> &max = {},
          const std::shared_ptr<GLTFAccessorSparse> &sparse = nullptr);

  static std::shared_ptr<GLTFAccessor> create (const IndexHelper &helper,
                                               const std::string &name);
};

/**
 * \brief Returns the number of components for the given accessor type
 */
size_t accessor_size (GLTFAccessorType type);

}

#endif // ACCESSOR_H
