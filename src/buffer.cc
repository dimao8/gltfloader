#include "buffer.h"
#include "gltfnamedobject.h"

#include <fstream>
#include <uuid/uuid.h>

namespace gltfloader
{

/* ************************* GLTFBuffer::GLTFBuffer ************************ */

GLTFBuffer::GLTFBuffer (const std::string &name,
                        const std::vector<uint8_t> &data)
    : GLTFNamedObject (name)
{
  uuid_t uuid;

  set (data.data (), data.size ());
  m_path = GLTFNamedObject::name () + ".bin";
}

/* ************************* GLTFBuffer::GLTFBuffer ************************ */

GLTFBuffer::GLTFBuffer (const std::string &name, const uint8_t *data,
                        size_t sz)
    : GLTFNamedObject (name)
{
  set (data, sz);
}

/* ************************* GLTFBuffer::GLTFBuffer ************************ */

GLTFBuffer::GLTFBuffer (const std::string &name, const std::string &path)
    : GLTFNamedObject (name), m_path (path)
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

/* *************************** GLTFBuffer::is_bad ************************** */

bool
GLTFBuffer::is_bad () const
{
  return m_data.empty ();
}

/* **************************** GLTFBuffer::data *************************** */

const std::vector<uint8_t> &
GLTFBuffer::data () const
{
  return m_data;
}

}