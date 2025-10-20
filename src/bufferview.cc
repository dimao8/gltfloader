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

const std::shared_ptr<GLTFBuffer> &
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

/* ************************* GLTFBufferView::is_bad ************************ */

bool
GLTFBufferView::is_bad () const
{
  return m_buffer == nullptr;
}

/* ************************* GLTFBufferView::create ************************ */

std::shared_ptr<GLTFBufferView>
GLTFBufferView::create (const std::string &name,
                        const std::shared_ptr<GLTFBuffer> &buffer,
                        GLTFBufferViewTarget target, int byte_offset,
                        int byte_length, int byte_stride)
{
  std::shared_ptr<GLTFBufferView> tmp (new GLTFBufferView (name));

  if (byte_offset < 0)
    {
      std::cout << "[W] glTF 2.0: Byte offset of the bufferView \""
                << tmp->name () << "\" can not be negative" << std::endl;
      return nullptr;
    }
  else
    tmp->m_byte_offset = byte_offset;

  if (byte_length < 1)
    {
      std::cout << "[W] glTF 2.0: The size of the bufferView \""
                << tmp->name () << "\" can not be less than 1" << std::endl;
      return nullptr;
    }
  else
    tmp->m_byte_length = byte_length;

  if (byte_stride < 4 || byte_stride > 252)
    {
      std::cout << "[W] glTF 2.0: The stride of the bufferView \""
                << tmp->name () << "\" must fit [4,252] range" << std::endl;
      return nullptr;
    }
  else
    tmp->m_byte_stride = byte_stride;

  if (tmp->m_buffer->data ().size () < byte_length)
    {
      std::cout << "[W] glTF 2.0: The size of the bufferView \""
                << tmp->name ()
                << "\" can not be greater than buffer size" << std::endl;
      return nullptr;
    }

  return tmp;
}

}