#include "image.h"

#include <fstream>

namespace gltfloader
{

/* ************************** GLTFImage::GLTFImage ************************* */

GLTFImage::GLTFImage (const std::string &name, GLTFImageMIMEType mime_type,
                      const std::string &path)
    : GLTFNamedObject (name), m_mime_type (mime_type)
{
  std::ifstream file (path);

  if (!file)
    return;

  file.seekg (0, std::ios_base::end);
  size_t sz = file.tellg ();
  file.seekg (0, std::ios_base::beg);

  uint8_t *ptr = new uint8_t[sz];
  file.read (reinterpret_cast<char *> (ptr), sz);
  set (ptr, sz);
  delete[] ptr;
}

/* ************************** GLTFImage::GLTFImage ************************* */

GLTFImage::GLTFImage (const std::string &name, GLTFImageMIMEType mime_type,
                      const std::shared_ptr<GLTFBufferView> buffer_view)
    : GLTFNamedObject (name), m_mime_type (mime_type),
      m_buffer_view (buffer_view)
{
  //
}

/* ***************************** GLTFImage::set **************************** */

void
GLTFImage::set (const uint8_t *data, size_t sz)
{
  m_data.assign (data, data + sz);
}

/* *************************** GLTFImage::is_bad *************************** */

bool
GLTFImage::is_bad () const
{
  return (m_data.empty ()) && (m_buffer_view == nullptr);
}

/* ************************** GLTFImage::mime_type ************************* */

GLTFImageMIMEType
GLTFImage::mime_type () const
{
  return m_mime_type;
}

/* **************************** GLTFImage::path **************************** */

const std::string &
GLTFImage::path () const
{
  return m_path;
}

/* **************************** GLTFImage::data **************************** */

const std::vector<uint8_t> &
GLTFImage::data () const
{
  return m_data;
}

/* ************************* GLTFImage::buffer_view ************************ */

const std::shared_ptr<GLTFBufferView>
GLTFImage::buffer_view () const
{
  return m_buffer_view;
}

}