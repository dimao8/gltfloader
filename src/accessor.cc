#include "accessor.h"
#include "accessorsparse.h"
#include "gltfnamedobject.h"

#include <iostream>
#include <memory>

// TODO : Check accessor fields for glTF 2.0 spec

namespace gltfloader
{

/* *********************** GLTFAccessor::GLTFAccessor ********************** */

GLTFAccessor::GLTFAccessor (const std::string &name) : GLTFNamedObject (name)
{
  //
}

/* *********************** GLTFAccessor::buffer_view *********************** */

size_t
GLTFAccessor::buffer_view () const
{
  return m_buffer_view;
}

/* *********************** GLTFAccessor::byte_offset *********************** */

int
GLTFAccessor::byte_offset () const
{
  return m_byte_offset;
}

/* ********************** GLTFAccessor::component_type ********************* */

GLTFAccessorComponentType
GLTFAccessor::component_type () const
{
  return m_component_type;
}

/* *************************** GLTFAccessor::type ************************** */

GLTFAccessorType
GLTFAccessor::type () const
{
  return m_type;
}

/* ************************ GLTFAccessor::normalize ************************ */

bool
GLTFAccessor::normalize () const
{
  return m_normalize;
}

/* ************************** GLTFAccessor::count ************************** */

int
GLTFAccessor::count () const
{
  return m_count;
}

/* *************************** GLTFAccessor::min *************************** */

const std::vector<float> &
GLTFAccessor::min () const
{
  return m_min;
}

/* *************************** GLTFAccessor::max *************************** */

const std::vector<float> &
GLTFAccessor::max () const
{
  return m_max;
}

/* ************************** GLTFAccessor::sparse ************************* */

const std::shared_ptr<GLTFAccessorSparse> &
GLTFAccessor::sparse () const
{
  return m_sparse;
}

/* ************************** GLTFAccessor::create ************************* */

std::shared_ptr<GLTFAccessor>
GLTFAccessor::create (
    const IndexHelper &helper, const std::string &name, int component_type,
    int count, const std::string &type, int buffer_view, int byte_offset,
    bool normalize, const std::vector<float> &min,
    const std::vector<float> &max,
    const std::shared_ptr<GLTFAccessorSparse> &sparse)
{
  std::shared_ptr<GLTFAccessor> tmp (new GLTFAccessor (name));

  if (buffer_view <= 0)
    {
      std::cout << "[W] glTF 2.0 5.1.1: accessor.bufferView >= 0" << std::endl;
      return nullptr;
    }

  if (buffer_view >= helper.buffer_views_size ())
    {
      std::cout << "[W] glTF 2.0 5.1.1: accessor.bufferView is out of range"
                << std::endl;
      return nullptr;
    }
  tmp->m_buffer_view = buffer_view;

  if (byte_offset < 0)
    {
      std::cout << "[W] glTF 2.0 5.1.2: accessor.byteOffset >= 0" << std::endl;
      return nullptr;
    }
  tmp->m_byte_offset = byte_offset;

  switch (component_type)
    {
    case static_cast<int> (GLTFAccessorComponentType::unsigned_byte):
      tmp->m_component_type = GLTFAccessorComponentType::unsigned_byte;
      break;

    case static_cast<int> (GLTFAccessorComponentType::byte):
      tmp->m_component_type = GLTFAccessorComponentType::byte;
      break;

    case static_cast<int> (GLTFAccessorComponentType::unsigned_short):
      tmp->m_component_type = GLTFAccessorComponentType::unsigned_short;
      break;

    case static_cast<int> (GLTFAccessorComponentType::sshort):
      tmp->m_component_type = GLTFAccessorComponentType::sshort;
      break;

    case static_cast<int> (GLTFAccessorComponentType::unsigned_int):
      tmp->m_component_type = GLTFAccessorComponentType::unsigned_int;
      break;

    case static_cast<int> (GLTFAccessorComponentType::ffloat):
      tmp->m_component_type = GLTFAccessorComponentType::ffloat;
      break;

    default:
      std::cout << "[W] glTF 2.0 5.1.3: accessor.componentType can be only "
                   "5120, 5121, 5122, 5123, 5125 or 5126"
                << std::endl;
      return nullptr;
    }

  size_t sz;

  if (type == "SCALAR")
    {
      tmp->m_type = GLTFAccessorType::scalar;
      sz = 1;
    }
  else if (type == "VEC2")
    {
      tmp->m_type = GLTFAccessorType::vec2;
      sz = 2;
    }
  else if (type == "VEC3")
    {
      tmp->m_type = GLTFAccessorType::vec3;
      sz = 3;
    }
  else if (type == "VEC4")
    {
      tmp->m_type = GLTFAccessorType::vec4;
      sz = 4;
    }
  else if (type == "MAT2")
    {
      tmp->m_type = GLTFAccessorType::mat2;
      sz = 4;
    }
  else if (type == "MAT3")
    {
      tmp->m_type = GLTFAccessorType::mat3;
      sz = 9;
    }
  else if (type == "MAT4")
    {
      tmp->m_type = GLTFAccessorType::mat4;
      sz = 16;
    }
  else
    {
      std::cout << "[W] glTF 2.0 5.1.6: accessor.type can only be one of the "
                   "follows: \"SCALAR\", \"VEC2\", \"VEC3\", \"VEC4\", "
                   "\"MAT2\", \"MAT3\" or \"MAT4\""
                << std::endl;
      return nullptr;
    }

  if (min.size () != sz)
    {
      std::cout
          << "[W] glTF 2.0 5.1.8: accessor.min must conforms accessor.type"
          << std::endl;
      return nullptr;
    }
  else
    tmp->m_min = min;

  if (max.size () != sz)
    {
      std::cout
          << "[W] glTF 2.0 5.1.8: accessor.max must conforms accessor.type"
          << std::endl;
      return nullptr;
    }
  else
    tmp->m_max = max;

  if (sparse == nullptr)
    return nullptr;
  
  // FIXME : Need to create invalid sparse to separate bad sparse and no sparse
  tmp->m_sparse = sparse;

  return tmp;
}

/* ************************** GLTFAccessor::create ************************* */

std::shared_ptr<GLTFAccessor>
GLTFAccessor::create (const IndexHelper &helper, const std::string &name)
{
  std::shared_ptr<GLTFAccessor> tmp (new GLTFAccessor (name));

  tmp->m_buffer_view = 0;
  tmp->m_component_type = GLTFAccessorComponentType::byte;
  tmp->m_type = GLTFAccessorType::scalar;
  tmp->m_byte_offset = 0;
  tmp->m_count = 0;
  tmp->m_max = { 0 };
  tmp->m_min = { 0 };
  tmp->m_normalize = false;
  tmp->m_sparse = nullptr;

  return tmp;
}

}