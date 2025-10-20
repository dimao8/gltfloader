#include "image.h"
#include "base64.h"
#include "gltfnamedobject.h"

#include <cstddef>
#include <fstream>
#include <iostream>

namespace gltfloader
{

/* ************************** GLTFImage::GLTFImage ************************* */

GLTFImage::GLTFImage (const std::string &name) : GLTFNamedObject (name)
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

/* *************************** GLTFImage::create *************************** */

// FIXME : Boilerplate. See buffer.cc:85
const std::shared_ptr<GLTFImage>
GLTFImage::create (const std::string &name, GLTFImageMIMEType mime_type,
                   const std::string &uri)
{
  std::shared_ptr<GLTFImage> tmp (new GLTFImage (name));

  const std::string prefix_str1 = "data:application/octet-stream;base64,";
  const std::string prefix_str2 = "data:application/gltf-buffer;base64,";

  // TODO : Correct URI parsing

  // Check for base64
  size_t prefix = std::string::npos;

  if (uri.find (prefix_str1) == 0)
    prefix = prefix_str1.size ();
  else if (uri.find (prefix_str2) == 0)
    prefix = prefix_str2.size ();

  if (prefix != std::string::npos)
    {
      if (!base64_import (tmp->m_data, uri.substr (prefix)))
        {
          std::cout << "[W] glTF 2.0: Expect base64 string in \"" << uri
                    << "\"" << std::endl;
          return nullptr;
        }
    }
  else
    {
      std::ifstream file (uri);

      if (!file)
        {
          std::cout << "[W] glTF 2.0: The file \"" << uri
                    << "\" can not be read" << std::endl;
          return nullptr;
        }

      file.seekg (0, std::ios_base::end);
      size_t sz = file.tellg ();
      file.seekg (0, std::ios_base::beg);

      if (sz == 0)
        {
          std::cout << "[W] glTF 2.0: The file \"" << uri << "\" is empty"
                    << std::endl;
          return nullptr;
        }

      tmp->m_data.reserve (sz);
      tmp->m_data.assign (std::istreambuf_iterator<char> (file),
                          std::istreambuf_iterator<char> ());
    }

  if (tmp->is_bad ())
    return nullptr;
  else
    return tmp;
}

/* *************************** GLTFImage::create *************************** */

const std::shared_ptr<GLTFImage>
GLTFImage::create (const std::string &name, GLTFImageMIMEType mime_type,
                   const std::shared_ptr<GLTFBufferView> buffer_view)
{
  std::shared_ptr<GLTFImage> tmp (new GLTFImage (name));

  tmp->m_buffer_view = buffer_view;
  if (mime_type == GLTFImageMIMEType::unknown)
    {
      std::cout << "[W] glTF 2.0: The image object \"" << tmp->name ()
                << "\" can not have unknown type when bufferView is defined"
                << std::endl;
      return nullptr;
    }

  if (tmp->is_bad ())
    return nullptr;
  else
    return tmp;
}

}