#ifndef BUFFERVIEW_H
#define BUFFERVIEW_H

#include "gltfnamedobject.h"

#include <memory>
#include <string>

namespace gltfloader
{

class GLTFBuffer;

enum GLTFBufferViewTarget
{
  unknown = -1,
  array_buffer = 34962,
  element_array_buffer = 34963
};

class GLTFBufferView : public GLTFNamedObject
{
private:
  std::shared_ptr<GLTFBuffer> m_buffer;
  GLTFBufferViewTarget m_target;
  int m_byte_offset;
  int m_byte_length;
  int m_byte_stride;

  GLTFBufferView (const std::string &name);

public:
  GLTFBufferView () = delete;
  GLTFBufferView (const GLTFBufferView &) = delete;

  virtual ~GLTFBufferView () {}

  const std::shared_ptr<GLTFBuffer> &buffer () const;
  GLTFBufferViewTarget target () const;
  bool is_bad () const;

  static std::shared_ptr<GLTFBufferView>
  create (const std::string &name, const std::shared_ptr<GLTFBuffer> &buffer,
          GLTFBufferViewTarget target = GLTFBufferViewTarget::unknown,
          int byte_offset = 0, int byte_length = 1, int byte_stride = 4);
};

}

#endif // BUFFERVIEW_H
