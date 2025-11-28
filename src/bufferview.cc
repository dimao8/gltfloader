#include "bufferview.h"
#include "buffer.h"
#include "gltfnamedobject.h"

#include <iostream>
#include <optional>

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

const std::optional<GLTFBufferViewTarget> &
GLTFBufferView::target () const
{
  return m_target;
}

/* ********************** GLTFBufferView::byte_offset ********************** */

size_t
GLTFBufferView::byte_offset () const
{
  return m_byte_offset;
}

/* ********************** GLTFBufferView::byte_length ********************** */

size_t
GLTFBufferView::byte_length () const
{
  return m_byte_length;
}

/* ********************** GLTFBufferView::byte_stride ********************** */

const std::optional<size_t> &
GLTFBufferView::byte_stride () const
{
  return m_byte_stride;
}

/* ************************* GLTFBufferView::create ************************ */

std::shared_ptr<GLTFBufferView>
GLTFBufferView::create (const IndexHelper &helper, const std::string &name,
                        int buffer, const std::optional<int> &target,
                        int byte_offset, int byte_length,
                        const std::optional<int> &byte_stride)
{
  std::shared_ptr<GLTFBufferView> tmp (new GLTFBufferView (name));

  if (buffer < 0)
    {
      std::cout << "[W] glTF 2.0 5.11.1: bufferView.buffer >= 0" << std::endl;
      return nullptr;
    }
  if (buffer + helper.buffer_defaults_size () >= helper.buffers_size ())
    {
      std::cout << "[W] glTF 2.0 5.11.1: bufferView.buffer is out of range"
                << std::endl;
      return nullptr;
    }
  tmp->m_buffer = buffer + helper.buffer_defaults_size ();

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

  if (byte_stride == std::nullopt)
    tmp->m_byte_stride = std::nullopt;
  else if (byte_stride < 4 || byte_stride > 252)
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

  if (target.has_value ())
    {
      switch (target.value ())
        {
        case static_cast<int> (GLTFBufferViewTarget::array_buffer):
          tmp->m_target = GLTFBufferViewTarget::array_buffer;
          break;

        case static_cast<int> (GLTFBufferViewTarget::element_array_buffer):
          tmp->m_target = GLTFBufferViewTarget::element_array_buffer;
          break;
        }
    }
  else
    tmp->m_target = std::nullopt;

  return tmp;
}

}