#include "primitive.h"
#include "gltftypes.h"
#include "indexhelper.h"

#include <cstdlib>
#include <iostream>
#include <optional>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

namespace gltfloader
{

/* ********************** GLTFPrimitive::GLTFPrimitive ********************* */

GLTFPrimitive::GLTFPrimitive () : GLTFObject ()
{
  //
}

/* ************************* GLTFPrimitive::create ************************* */

std::shared_ptr<GLTFPrimitive>
GLTFPrimitive::create (IndexHelper &helper,
                       const GLTFAttributeList &attributes,
                       const std::optional<int> &indices,
                       const std::optional<int> &material,
                       const std::optional<int> &mode,
                       const GLTFAttributeList &targets)
{
  std::shared_ptr<GLTFPrimitive> tmp (new GLTFPrimitive ());

  size_t shifted_index;
  size_t n;

  // TODO : Check for TEXTURE object
  if (attributes.empty ())
    {
      std::cout << "[W] glTF 2.0 3.7.2.1: Mesh object must have at least one "
                   "attribute: \"POSITION\""
                << std::endl;
      return nullptr;
    }
  else if (attributes.find ("POSITION") == attributes.end ())
    {
      std::cout << "[W] glTF 2.0 3.7.2.1: Mesh object must have at least one "
                   "attribute: \"POSITION\""
                << std::endl;
      return nullptr;
    }

  // Attributes
  for (auto it : attributes)
    {
      shifted_index = it.second + helper.accessor_defaults_size ();
      if (it.second < 0)
        {
          std::cout << "[W] glTF 2.0 5.24.1: mesh.primitive.attributes "
                       "accessor index >= 0"
                    << std::endl;
          return nullptr;
        }
      if (shifted_index >= helper.accessors_size ())
        {
          std::cout << "[W] glTF 2.0 5.24.1: mesh.primitive.attributes "
                       "accessor index is out of bounds"
                    << std::endl;
          return nullptr;
        }

      // FIXME : Boilerplate in multiple indexed attribute extraction.
      //         It can be fixed with a prefix in the string variable.
      if (it.first == "POSITION")
        tmp->m_position = shifted_index;
      else if (it.first == "NORMAL")
        tmp->m_normal = shifted_index;
      else if (it.first == "TANGENT")
        tmp->m_tangent = shifted_index;
      else if (it.first.find ("TEXCOORD_") == 0)
        {
          try
            {
              n = std::strtol (it.first.c_str () + 9, nullptr, 10);
            }
          catch (...)
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: semantic of TEXCOORD has to "
                           "be \"TEXCOORD_n\""
                        << std::endl;
              return nullptr;
            }
          if (n != tmp->m_texcoords.size ())
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: TEXCOORD attributes must "
                           "start from 0 and must has consecutive indices"
                        << std::endl;
              return nullptr;
            }
          tmp->m_texcoords.push_back (shifted_index);
        }
      else if (it.first.find ("COLOR_") == 0)
        {
          try
            {
              n = std::strtol (it.first.c_str () + 6, nullptr, 10);
            }
          catch (...)
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: semantic of COLOR has to "
                           "be \"COLOR_n\""
                        << std::endl;
              return nullptr;
            }
          if (n != tmp->m_colors.size ())
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: COLOR attributes must "
                           "start from 0 and must has consecutive indices"
                        << std::endl;
              return nullptr;
            }
          tmp->m_colors.push_back (shifted_index);
        }
      else if (it.first.find ("JOINTS_") == 0)
        {
          try
            {
              n = std::strtol (it.first.c_str () + 7, nullptr, 10);
            }
          catch (...)
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: semantic of JOINTS has to "
                           "be \"JOINTS_n\""
                        << std::endl;
              return nullptr;
            }
          if (n != tmp->m_joints.size ())
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: JOINTS attributes must "
                           "start from 0 and must has consecutive indices"
                        << std::endl;
              return nullptr;
            }
          tmp->m_joints.push_back (shifted_index);
        }
      else if (it.first.find ("WEIGHTS_") == 0)
        {
          try
            {
              n = std::strtol (it.first.c_str () + 8, nullptr, 10);
            }
          catch (...)
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: semantic of WEIGHTS has to "
                           "be \"WEIGHTS_n\""
                        << std::endl;
              return nullptr;
            }
          if (n != tmp->m_weights.size ())
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: WEIGHTS attributes must "
                           "start from 0 and must has consecutive indices"
                        << std::endl;
              return nullptr;
            }
          tmp->m_weights.push_back (shifted_index);
        }
      else
        {
          std::cout << "[W] glTF 2.0 3.7.2.1: user defined attributes are not "
                       "supported by "
                    << PACKAGE << " " << VERSION << std::endl;
          return nullptr;
        }
    }

  if (indices == std::nullopt)
    tmp->m_indices = std::nullopt;
  else
    {
      shifted_index = indices.value () + helper.accessor_defaults_size ();
      if (indices.value () < 0)
        {
          std::cout << "[W] glTF 2.0 5.24.2: mesh.primitives.indices >= 0"
                    << std::endl;
          return nullptr;
        }
      if (shifted_index >= helper.accessor_defaults_size ())
        {
          std::cout << "[W] glTF 2.0 5.24.2: mesh.primitives.indices is out "
                       "of bounds"
                    << std::endl;
          return nullptr;
        }

      tmp->m_indices = shifted_index;
    }

  if (material == std::nullopt)
    tmp->m_material = std::nullopt;
  else
    {
      shifted_index = material.value () + helper.material_defaults_size ();
      if (material.value () < 0)
        {
          std::cout << "[W] glTF 2.0 5.24.3: mesh.primitives.material >= 0"
                    << std::endl;
          return nullptr;
        }
      if (shifted_index >= helper.material_defaults_size ())
        {
          std::cout << "[W] glTF 2.0 5.24.3: mesh.primitives.material is out "
                       "of bounds"
                    << std::endl;
          return nullptr;
        }

      tmp->m_material = shifted_index;
    }

  if (mode == std::nullopt)
    tmp->m_mode = GLTFDrawMode::triangles;
  else
    {
      switch (mode.value ())
        {
        case static_cast<int> (GLTFDrawMode::points):
          tmp->m_mode = GLTFDrawMode::points;
          break;

        case static_cast<int> (GLTFDrawMode::lines):
          tmp->m_mode = GLTFDrawMode::lines;
          break;

        case static_cast<int> (GLTFDrawMode::line_loop):
          tmp->m_mode = GLTFDrawMode::line_loop;
          break;

        case static_cast<int> (GLTFDrawMode::line_strip):
          tmp->m_mode = GLTFDrawMode::line_strip;
          break;

        case static_cast<int> (GLTFDrawMode::triangles):
          tmp->m_mode = GLTFDrawMode::triangles;
          break;

        case static_cast<int> (GLTFDrawMode::triangle_strip):
          tmp->m_mode = GLTFDrawMode::triangle_strip;
          break;

        case static_cast<int> (GLTFDrawMode::triangle_fan):
          tmp->m_mode = GLTFDrawMode::triangle_fan;
          break;

        default:
          std::cout << "[W] glTF 2.0 5.24.4: mesh.primitives.mode can be "
                       "only from 0 to 6"
                    << std::endl;
          return nullptr;
        }
    }

  // Target attributes
  // FIXME : Boilerplate. Same as attributes extraction.
  for (auto it : targets)
    {
      shifted_index = it.second + helper.accessor_defaults_size ();
      if (it.second < 0)
        {
          std::cout << "[W] glTF 2.0 5.24.1: mesh.primitive.targets "
                       "accessor index >= 0"
                    << std::endl;
          return nullptr;
        }
      if (shifted_index >= helper.accessors_size ())
        {
          std::cout << "[W] glTF 2.0 5.24.1: mesh.primitive.targets "
                       "accessor index is out of bounds"
                    << std::endl;
          return nullptr;
        }

      // FIXME : Boilerplate in multiple indexed target attribute extraction.
      //         It can be fixed with a prefix in the string variable.
      if (it.first == "POSITION")
        tmp->m_position_target = shifted_index;
      else if (it.first == "NORMAL")
        tmp->m_normal_target = shifted_index;
      else if (it.first == "TANGENT")
        tmp->m_tangent_target = shifted_index;
      else if (it.first.find ("TEXCOORD_") == 0)
        {
          try
            {
              n = std::strtol (it.first.c_str () + 9, nullptr, 10);
            }
          catch (...)
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: semantic of TEXCOORD has to "
                           "be \"TEXCOORD_n\""
                        << std::endl;
              return nullptr;
            }
          if (n != tmp->m_texcoord_targets.size ())
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: TEXCOORD targets must "
                           "start from 0 and must has consecutive indices"
                        << std::endl;
              return nullptr;
            }
          tmp->m_texcoord_targets.push_back (shifted_index);
        }
      else if (it.first.find ("COLOR_") == 0)
        {
          try
            {
              n = std::strtol (it.first.c_str () + 6, nullptr, 10);
            }
          catch (...)
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: semantic of COLOR has to "
                           "be \"COLOR_n\""
                        << std::endl;
              return nullptr;
            }
          if (n != tmp->m_color_targets.size ())
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: COLOR targets must "
                           "start from 0 and must has consecutive indices"
                        << std::endl;
              return nullptr;
            }
          tmp->m_color_targets.push_back (shifted_index);
        }
      else if (it.first.find ("JOINTS_") == 0)
        {
          try
            {
              n = std::strtol (it.first.c_str () + 7, nullptr, 10);
            }
          catch (...)
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: semantic of JOINTS has to "
                           "be \"JOINTS_n\""
                        << std::endl;
              return nullptr;
            }
          if (n != tmp->m_joint_targets.size ())
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: JOINTS targets must "
                           "start from 0 and must has consecutive indices"
                        << std::endl;
              return nullptr;
            }
          tmp->m_joint_targets.push_back (shifted_index);
        }
      else if (it.first.find ("WEIGHTS_") == 0)
        {
          try
            {
              n = std::strtol (it.first.c_str () + 8, nullptr, 10);
            }
          catch (...)
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: semantic of WEIGHTS has to "
                           "be \"WEIGHTS_n\""
                        << std::endl;
              return nullptr;
            }
          if (n != tmp->m_weight_targets.size ())
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: WEIGHTS targets must "
                           "start from 0 and must has consecutive indices"
                        << std::endl;
              return nullptr;
            }
          tmp->m_weight_targets.push_back (shifted_index);
        }
      else
        {
          std::cout << "[W] glTF 2.0 3.7.2.1: user defined targets are not "
                       "supported by "
                    << PACKAGE << " " << VERSION << std::endl;
          return nullptr;
        }
    }

  return tmp;
}

}
