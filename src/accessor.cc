#include "accessor.h"
#include "accessorsparse.h"
#include "gltfnamedobject.h"

#include <iostream>

// TODO : Check accessor fields for glTF 2.0 spec

namespace gltfloader
{

/* *********************** GLTFAccessor::GLTFAccessor ********************** */

GLTFAccessor::GLTFAccessor (const std::string &name) : GLTFNamedObject (name)
{
  //
}

/* ************************** GLTFAccessor::is_bad ************************* */

bool
GLTFAccessor::is_bad () const
{
  return (m_component_type == GLTFAccessorComponentType::unknown)
         || (m_count < 1);
}

/* ************************** GLTFAccessor::create ************************* */

std::shared_ptr<GLTFAccessor>
GLTFAccessor::create (
    const std::string &name, GLTFAccessorComponentType component_type,
    int count, GLTFAccessorType type,
    const std::shared_ptr<GLTFBufferView> &buffer_view, int byte_offset,
    bool normalize, const std::vector<float> &min,
    const std::vector<float> &max,
    const std::vector<std::shared_ptr<GLTFAccessorSparse> > &sparse)
{
  std::shared_ptr<GLTFAccessor> tmp (new GLTFAccessor (name));

  if (buffer_view == nullptr)
    {
      return nullptr;
    }
  else
    {
      if (byte_offset < 0)
        {
          std::cout << "[E] The byte offset in the \"" << name
                    << "\" object can not be negative" << std::endl;
          return nullptr;
        }
      tmp->m_byte_offset = byte_offset;

      if (component_type == GLTFAccessorComponentType::unknown)
        {
          std::cout << "[E] The component type in the \"" << name
                    << "\" object can not be unknown" << std::endl;
          return nullptr;
        }
      tmp->m_component_type = component_type;

      int sz;

      switch (type)
        {
        case gltfloader::GLTFAccessorType::vec2:
          sz = 2;
          break;

        case gltfloader::GLTFAccessorType::vec3:
          sz = 3;
          break;

        case gltfloader::GLTFAccessorType::vec4:
        case gltfloader::GLTFAccessorType::mat2:
          sz = 4;
          break;

        case gltfloader::GLTFAccessorType::mat3:
          sz = 9;
          break;

        case gltfloader::GLTFAccessorType::mat4:
          sz = 16;
          break;

        default:
          sz = 1;
        }

      if (!min.empty ())
        {
          if (min.size () != sz)
            {
              std::cout << "[E] The size of the \"min\" array in the \""
                        << name << "\" must conform accessor type"
                        << std::endl;
              return nullptr;
            }
        }
      else
        tmp->m_min = min;

      if (!max.empty ())
        {
          if (max.size () != sz)
            {
              std::cout << "[E] The size of the \"max\" array in the \""
                        << name << "\" must conform accessor type"
                        << std::endl;
              return nullptr;
            }
        }
      else
        tmp->m_max = max;

      tmp->m_sparse = sparse;
    }

  return tmp;
}

}