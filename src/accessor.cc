#include "accessor.h"
#include "accessorsparse.h"
#include "buffer.h"
#include "bufferview.h"
#include "gltfnamedobject.h"
#include "indexhelper.h"
#include "sparseindices.h"
#include "sparsevalues.h"

#include <iostream>
#include <memory>
#include <optional>

// TODO : Check accessor fields for glTF 2.0 spec

namespace gltfloader
{

/* *********************** GLTFAccessor::GLTFAccessor ********************** */

GLTFAccessor::GLTFAccessor (const std::string &name) : GLTFNamedObject (name)
{
  //
}

/* *********************** GLTFAccessor::buffer_view *********************** */

const std::optional<size_t> &
GLTFAccessor::buffer_view () const
{
  return m_buffer_view;
}

/* *********************** GLTFAccessor::byte_offset *********************** */

size_t
GLTFAccessor::byte_offset () const
{
  return m_byte_offset;
}

/* ********************** GLTFAccessor::component_type ********************* */

GLTFComponentType
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
GLTFAccessor::normalized () const
{
  return m_normalized;
}

/* ************************** GLTFAccessor::count ************************** */

size_t
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
GLTFAccessor::create (const IndexHelper &helper, const std::string &name,
                      const std::optional<int> &buffer_view,
                      const std::optional<int> &byte_offset,
                      int component_type,
                      const std::optional<bool> &normalized, int count,
                      const std::string &type, const std::vector<float> &min,
                      const std::vector<float> &max,
                      const std::shared_ptr<GLTFAccessorSparse> &sparse)
{
  std::shared_ptr<GLTFAccessor> tmp (new GLTFAccessor (name));
  size_t shifted_buffer_view;

  if (buffer_view == std::nullopt)
    {
      // glTF 2.0 5.1.1 No bufferView. Zeroing the fields of the accessor
      tmp->m_buffer_view = std::nullopt;
      tmp->m_byte_offset = 0;
      tmp->m_component_type = GLTFComponentType::unsigned_byte;
      tmp->m_type = GLTFAccessorType::scalar;
      tmp->m_normalized = false;
      tmp->m_count = 0;
      tmp->m_min.clear ();
      tmp->m_max.clear ();
      tmp->m_sparse = nullptr;
      return tmp;
    }
  else
    {
      if (buffer_view < 0)
        {
          std::cout << "[W] glTF 2.0 5.1.1: accessor.bufferView >= 0"
                    << std::endl;
          return nullptr;
        }

      shifted_buffer_view
          = buffer_view.value () + helper.buffer_view_defaults_size ();

      if (shifted_buffer_view >= helper.buffer_views_size ())
        {
          std::cout
              << "[W] glTF 2.0 5.1.1: accessor.bufferView is out of range"
              << std::endl;
          return nullptr;
        }
      tmp->m_buffer_view = shifted_buffer_view;

      // glTF 2.0 5.1.2 byteOffset has default value 0
      if (byte_offset < 0)
        {
          std::cout << "[W] glTF 2.0 5.1.2: accessor.byteOffset >= 0"
                    << std::endl;
          return nullptr;
        }
      tmp->m_byte_offset = byte_offset.value_or (0);

      size_t val_sz;

      // glTF 2.0 5.1.3 componentType is required field
      switch (component_type)
        {
        case static_cast<int> (GLTFComponentType::unsigned_byte):
          tmp->m_component_type = GLTFComponentType::unsigned_byte;
          val_sz = 1;
          break;

        case static_cast<int> (GLTFComponentType::byte):
          tmp->m_component_type = GLTFComponentType::byte;
          val_sz = 1;
          break;

        case static_cast<int> (GLTFComponentType::unsigned_short):
          tmp->m_component_type = GLTFComponentType::unsigned_short;
          val_sz = 2;
          break;

        case static_cast<int> (GLTFComponentType::sshort):
          tmp->m_component_type = GLTFComponentType::sshort;
          val_sz = 2;
          break;

        case static_cast<int> (GLTFComponentType::unsigned_int):
          tmp->m_component_type = GLTFComponentType::unsigned_int;
          val_sz = 4;
          break;

        case static_cast<int> (GLTFComponentType::ffloat):
          tmp->m_component_type = GLTFComponentType::ffloat;
          val_sz = 4;
          break;

        default:
          std::cout
              << "[W] glTF 2.0 5.1.3: accessor.componentType can be only "
                 "5120, 5121, 5122, 5123, 5125 or 5126"
              << std::endl;
          return nullptr;
        }

      // glTF 2.0 5.1.6 type is required field
      if (type == "SCALAR")
        tmp->m_type = GLTFAccessorType::scalar;
      else if (type == "VEC2")
        tmp->m_type = GLTFAccessorType::vec2;
      else if (type == "VEC3")
        tmp->m_type = GLTFAccessorType::vec3;
      else if (type == "VEC4")
        tmp->m_type = GLTFAccessorType::vec4;
      else if (type == "MAT2")
        tmp->m_type = GLTFAccessorType::mat2;
      else if (type == "MAT3")
        tmp->m_type = GLTFAccessorType::mat3;
      else if (type == "MAT4")
        tmp->m_type = GLTFAccessorType::mat4;
      else
        {
          std::cout
              << "[W] glTF 2.0 5.1.6: accessor.type can only be one of the "
                 "follows: \"SCALAR\", \"VEC2\", \"VEC3\", \"VEC4\", "
                 "\"MAT2\", \"MAT3\" or \"MAT4\""
              << std::endl;
          return nullptr;
        }

      tmp->m_normalized = normalized.value_or (false);

      if (count <= 0)
        {
          std::cout << "[W] glTF 2.0 5.1.5: accessor.count > 0" << std::endl;
          return nullptr;
        }
      else
        tmp->m_count = count;

      size_t sz = accessor_size (tmp->m_type);

      // NOTE : According to glTF 2.0 3.7.2 Only position actually must have
      // min value in accessor. Check it at mesh loading
      if (min.size () != 0)
        {
          if (min.size () != sz)
            {
              std::cout << "[W] glTF 2.0 5.1.8: accessor.min must conforms "
                           "accessor.type"
                        << std::endl;
              return nullptr;
            }
          else
            tmp->m_min = min;
        }

      // NOTE : According to glTF 2.0 3.7.2 Only position actually must have
      // max value in accessor. Check it at mesh loading
      if (max.size () != 0)
        {
          if (max.size () != sz)
            {
              std::cout << "[W] glTF 2.0 5.1.8: accessor.max must conforms "
                           "accessor.type"
                        << std::endl;
              return nullptr;
            }
          else
            tmp->m_max = max;
        }

      if (sparse != nullptr)
        {
          // Check indices presents
          if (sparse->indices () == nullptr)
            {
              std::cout << "[W] glTF 2.0 5.2.2: accessor.sparse.indices must "
                           "be present"
                        << std::endl;
              return nullptr;
            }

          // Check values presents
          if (sparse->values () == nullptr)
            {
              std::cout << "[W] glTF 2.0 5.2.3: accessor.sparse.values must "
                           "be present"
                        << std::endl;
              return nullptr;
            }

          // Check indices bufferView index boundaries
          size_t shifted_buffer_view = helper.buffer_view_defaults_size ()
                                       + sparse->indices ()->buffer_view ();
          if (shifted_buffer_view >= helper.buffer_views_size ())
            {
              std::cout << "[W] glTF 2.0 5.3.1: "
                           "accessor.sparse.indices.bufferView is "
                           "out of range"
                        << std::endl;
              return nullptr;
            }

          // Check indices bufferView target and stride missing
          if (helper.buffer_view (shifted_buffer_view)->target ().has_value ()
              || helper.buffer_view (shifted_buffer_view)
                     ->byte_stride ()
                     .has_value ())
            {
              std::cout
                  << "[W] glTF 2.0 5.3.1: accessor.sparse.indices.bufferView "
                     "must not have its target or byteStride properties "
                     "defined"
                  << std::endl;
              return nullptr;
            }

          // Check indices bufferView and sparse alignment
          if (((helper.buffer_view (shifted_buffer_view)->byte_offset ()
                % (sz * val_sz))
               != 0)
              || ((tmp->m_sparse->indices ()->byte_offset () % (sz * val_sz))
                  != 0))
            {
              std::cout
                  << "[W] glTF 2.0 5.3.1: accessor.sparse.indices.bufferView "
                     "and sparse must be aligned to the componentType"
                  << std::endl;
            }

          // TODO : Check index sequence

          // Check indices bufferView index boundaries
          shifted_buffer_view = helper.buffer_view_defaults_size ()
                                + sparse->values ()->buffer_view ();
          if (shifted_buffer_view >= helper.buffer_views_size ())
            {
              std::cout << "[W] glTF 2.0 5.3.1: "
                           "accessor.sparse.indices.bufferView is "
                           "out of range"
                        << std::endl;
              return nullptr;
            }
        }
      tmp->m_sparse = sparse;

      return tmp;
    }
}

/* ***************************** accessor_size ***************************** */

size_t
accessor_size (GLTFAccessorType type)
{
  switch (type)
    {
    case GLTFAccessorType::scalar:
      return 1;

    case GLTFAccessorType::vec2:
      return 2;

    case GLTFAccessorType::vec3:
      return 3;

    case GLTFAccessorType::vec4:
    case GLTFAccessorType::mat2:
      return 4;

    case GLTFAccessorType::mat3:
      return 9;

    case GLTFAccessorType::mat4:
      return 16;
    }
}

}