#ifndef BUFFERVIEW_H
#define BUFFERVIEW_H

#include "gltfnamedobject.h"
#include "indexhelper.h"

#include <memory>
#include <string>

namespace gltfloader
{

class GLTFBuffer;

enum class GLTFBufferViewTarget
{
  array_buffer = 34962,
  element_array_buffer = 34963
};

class GLTFBufferView : public GLTFNamedObject
{
private:
  size_t m_buffer;
  GLTFBufferViewTarget m_target;
  int m_byte_offset;
  int m_byte_length;
  int m_byte_stride;

  GLTFBufferView (const std::string &name);

public:
  GLTFBufferView () = delete;
  GLTFBufferView (const GLTFBufferView &) = delete;

  virtual ~GLTFBufferView () {}

  size_t buffer () const;
  GLTFBufferViewTarget target () const;

  static std::shared_ptr<GLTFBufferView>
  create (const IndexHelper &helper, const std::string &name, int buffer,
          int target, int byte_offset = 0, int byte_length = 1,
          int byte_stride = 4);
};

}

#endif // BUFFERVIEW_H
