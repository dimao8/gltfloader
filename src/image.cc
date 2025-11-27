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

/* ************************** GLTFImage::data_size ************************* */

size_t
GLTFImage::data_size () const
{
  return m_data.size ();
}

/* ************************* GLTFImage::buffer_view ************************ */

size_t
GLTFImage::buffer_view () const
{
  return m_buffer_view;
}

/* *************************** GLTFImage::create *************************** */

// FIXME : Boilerplate. See buffer.cc:85
const std::shared_ptr<GLTFImage>
GLTFImage::create (const IndexHelper &helper, const std::string &name,
                   int buffer_view, const std::string &mime_type,
                   const std::string &uri)
{
  std::shared_ptr<GLTFImage> tmp (new GLTFImage (name));

  const std::string prefix_str1 = "data:application/octet-stream;base64,";
  const std::string prefix_str2 = "data:application/gltf-buffer;base64,";

  // TODO : Correct URI parsing

  if (uri.empty ()) // Only bufferView
    {
      if (buffer_view < 0)
        {
          std::cout << "[W] glTF 2.0 5.18.3: image.bufferView >= 0"
                    << std::endl;
          return nullptr;
        }
      if (buffer_view >= helper.buffer_views_size ())
        {
          std::cout << "[W] glTF 2.0 5.18.3: image.bufferView is out of range"
                    << std::endl;
          return nullptr;
        }
      tmp->m_buffer_view = buffer_view;

      if (mime_type == "image/jpeg")
        tmp->m_mime_type = GLTFImageMIMEType::jpeg;
      else if (mime_type == "image/png")
        tmp->m_mime_type = GLTFImageMIMEType::png;
      else
        {
          std::cout << "[W] glTF 2.0 5.18.2: image.mimeType must present and "
                       "can be \"image/jpeg\" or \"image/png\""
                    << std::endl;
          return nullptr;
        }
    }
  else // Data in file or uri (Base64)
    {
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
              std::cout
                  << "[W] glTF 2.0 5.18.1: Can not decode Base64 in image.uri"
                  << std::endl;
              return nullptr;
            }
        }
      else
        {
          std::ifstream file (uri);

          if (!file)
            {
              std::cout << "[W] glTF 2.0 5.18.1: The file \"" << uri
                        << "\" can not be read" << std::endl;
              return nullptr;
            }

          file.seekg (0, std::ios_base::end);
          size_t sz = file.tellg ();
          file.seekg (0, std::ios_base::beg);

          if (sz == 0)
            {
              std::cout << "[W] glTF 2.0 5.18.1: The file \"" << uri
                        << "\" is empty" << std::endl;
              return nullptr;
            }

          tmp->m_data.reserve (sz);
          tmp->m_data.assign (std::istreambuf_iterator<char> (file),
                              std::istreambuf_iterator<char> ());
        }
    }

  return tmp;
}

}