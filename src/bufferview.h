#ifndef BUFFERVIEW_H
#define BUFFERVIEW_H

#include "gltfnamedobject.h"
#include "gltftypes.h"
#include "indexhelper.h"

#include <memory>
#include <optional>
#include <string>

namespace gltfloader
{

class GLTFBuffer;

class GLTFBufferView : public GLTFNamedObject
{
private:
  size_t m_buffer;
  std::optional<GLTFBufferViewTarget> m_target;
  size_t m_byte_offset;
  size_t m_byte_length;
  std::optional<size_t> m_byte_stride;

  GLTFBufferView (const std::string &name);

public:
  GLTFBufferView () = delete;
  GLTFBufferView (const GLTFBufferView &) = delete;

  virtual ~GLTFBufferView () {}

  size_t buffer () const;
  const std::optional<GLTFBufferViewTarget> &target () const;
  size_t byte_offset () const;
  size_t byte_length () const;
  const std::optional<size_t> &byte_stride () const;

  static std::shared_ptr<GLTFBufferView>
  create (const IndexHelper &helper, const std::string &name, int buffer,
          const std::optional<int> &target, int byte_offset = 0,
          int byte_length = 1,
          const std::optional<int> &byte_stride = std::nullopt);
};

}

#endif // BUFFERVIEW_H
