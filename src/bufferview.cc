#include "bufferview.h"
#include "buffer.h"
#include "gltfnamedobject.h"

#include <iostream>

namespace gltfloader
{

/* ********************* GLTFBufferView::GLTFBufferView ******************** */

GLTFBufferView::GLTFBufferView (const std::string &name)
    : GLTFNamedObject (name)
{
  //
}

/* ************************* GLTFBufferView::buffer ************************ */

size_t
GLTFBufferView::buffer () const
{
  return m_buffer;
}

/* ************************* GLTFBufferView::target ************************ */

GLTFBufferViewTarget
GLTFBufferView::target () const
{
  return m_target;
}

/* ************************* GLTFBufferView::create ************************ */

std::shared_ptr<GLTFBufferView>
GLTFBufferView::create (const IndexHelper &helper, const std::string &name,
                        int buffer, int target, int byte_offset,
                        int byte_length, int byte_stride)
{
  std::shared_ptr<GLTFBufferView> tmp (new GLTFBufferView (name));

  if (buffer < 0)
    {
      std::cout << "[W] glTF 2.0 5.11.1: bufferView.buffer >= 0" << std::endl;
      return nullptr;
    }
  if (buffer >= helper.buffers_size ())
    {
      std::cout << "[W] glTF 2.0 5.11.1: bufferView.buffer is out of range"
                << std::endl;
      return nullptr;
    }
  tmp->m_buffer = buffer;

  if (byte_offset < 0)
    {
      std::cout << "[W] glTF 2.0 5.11.2: bufferView.byteOffset >= 0"
                << std::endl;
      return nullptr;
    }
  else
    tmp->m_byte_offset = byte_offset;

  if (byte_length < 1)
    {
      std::cout << "[W] glTF 2.0 5.11.3: bufferView.byteLength > 0"
                << std::endl;
      return nullptr;
    }
  else
    tmp->m_byte_length = byte_length;

  if (byte_stride < 4 || byte_stride > 252)
    {
      std::cout
          << "[W] glTF 2.0 5.11.4: bufferView.byteStride in range [4, 252]"
          << std::endl;
      return nullptr;
    }
  else
    tmp->m_byte_stride = byte_stride;

  if (byte_length > helper.buffer (buffer)->size ())
    {
      std::cout << "[W] glTF 2.0: buffer is smaller than bufferView.byteLength"
                << std::endl;
      return nullptr;
    }

  return tmp;
}

}