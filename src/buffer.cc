#include "buffer.h"
#include "base64.h"
#include "gltfnamedobject.h"

#include <fstream>
#include <iostream>
#include <iterator>

namespace gltfloader
{

/* ************************* GLTFBuffer::GLTFBuffer ************************ */

GLTFBuffer::GLTFBuffer (const std::string &name) : GLTFNamedObject (name)
{
  //
}

/* **************************** GLTFBuffer::set **************************** */

void
GLTFBuffer::set (const uint8_t *data, size_t sz)
{
  m_data.assign (data, data + sz);
}

/* **************************** GLTFBuffer::path *************************** */

const std::string &
GLTFBuffer::path () const
{
  return m_path;
}

/* **************************** GLTFBuffer::data *************************** */

const std::vector<uint8_t> &
GLTFBuffer::data () const
{
  return m_data;
}

/* **************************** GLTFBuffer::size *************************** */

size_t
GLTFBuffer::size () const
{
  return m_data.size ();
}

/* *************************** GLTFBuffer::create ************************** */

std::shared_ptr<GLTFBuffer>
GLTFBuffer::create (const std::string &name, const std::string &uri,
                    size_t length)
{
  std::shared_ptr<GLTFBuffer> tmp (new GLTFBuffer (name));

  const std::string prefix_str1 = "data:application/octet-stream;base64,";
  const std::string prefix_str2 = "data:application/gltf-buffer;base64,";

  // TODO : Correct URI parsing

  if (uri.empty ())
    {
      // TODO : What we are going to do if URI is empty?
      std::cout << "[W] Empty URI detected" << std::endl;
      std::cout << "[I] glTF 2.0 5.10.1 allows empty URIs but define no "
                   "actions in this case"
                << std::endl;
      return nullptr;
    }
  else
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
              std::cout << "[W] glTF 2.0 5.10.1: Expect base64 string"
                        << std::endl;
              return nullptr;
            }
        }
      else
        {
          std::ifstream file (uri);

          if (!file)
            {
              std::cout << "[W] glTF 2.0 5.10.1: The file \"" << uri
                        << "\" can not be read" << std::endl;
              return nullptr;
            }

          file.seekg (0, std::ios_base::end);
          size_t sz = file.tellg ();
          file.seekg (0, std::ios_base::beg);

          if (sz == 0)
            {
              std::cout << "[W] glTF 2.0 5.10.1: The file \"" << uri
                        << "\" is empty" << std::endl;
              return nullptr;
            }
          if (sz < length)
            {
              std::cout << "[W] glTF 2.0 3.6.1.1: The file \"" << uri
                        << " can not be shorter than buffer" << std::endl;
              return nullptr;
            }
          tmp->m_data.assign (std::istreambuf_iterator<char> (file),
                              std::istreambuf_iterator<char> ());
          tmp->m_data.resize (length);
        }

      return (tmp->m_data.empty () ? nullptr : tmp);
    }
}

}