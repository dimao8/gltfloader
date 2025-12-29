#include "primitivetarget.h"
#include "accessor.h"

#include <iostream>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

namespace gltfloader
{

/* **************** GLTFPrimitiveTarget::GLTFPrimitiveTarget *************** */

GLTFPrimitiveTarget::GLTFPrimitiveTarget (
    IndexHelper &helper, const GLTFTargetAttributeList &target_attributes)
{
  size_t shifted_index;
  size_t n;

  // FIXME : Boilerplate. Same as attributes extraction.
  // FIXME : Each morph target attribute must have appropriate attribute.
  //         Check it.
  for (auto it : target_attributes)
    {
      shifted_index = it.second + helper.accessor_defaults_size ();
      if (it.second < 0)
        {
          std::cout << "[W] glTF 2.0 5.24.1: mesh.primitive.targets "
                       "accessor index >= 0"
                    << std::endl;
          cleanup ();
          return;
        }
      if (shifted_index >= helper.accessors_size ())
        {
          std::cout << "[W] glTF 2.0 5.24.1: mesh.primitive.targets "
                       "accessor index is out of bounds"
                    << std::endl;
          cleanup ();
          return;
        }

      // FIXME : Boilerplate in multiple indexed target attribute extraction.
      //         It can be fixed with a prefix in the string variable.
      if (it.first == "POSITION")
        {
          if (helper.accessor (shifted_index)->min ().empty ()
              || helper.accessor (shifted_index)->max ().empty ())
            {
              std::cout << "[W] glTF 2.0 3.7.2: mesh.primitive.attributes "
                           "must have min and max values"
                        << std::endl;
              cleanup ();
              return;
            }
          m_position_target = shifted_index;
        }
      else if (it.first == "NORMAL")
        m_normal_target = shifted_index;
      else if (it.first == "TANGENT")
        m_tangent_target = shifted_index;
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
              cleanup ();
              return;
            }
          if (n != m_texcoord_targets.size ())
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: TEXCOORD targets must "
                           "start from 0 and must has consecutive indices"
                        << std::endl;
              cleanup ();
              return;
            }
          m_texcoord_targets.push_back (shifted_index);
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
              cleanup ();
              return;
            }
          if (n != m_color_targets.size ())
            {
              std::cout << "[W] glTF 2.0 3.7.2.1: COLOR targets must "
                           "start from 0 and must has consecutive indices"
                        << std::endl;
              cleanup ();
              return;
            }
          m_color_targets.push_back (shifted_index);
        }
      else
        {
          std::cout << "[W] glTF 2.0 3.7.2.1: user defined targets are not "
                       "supported by "
                    << PACKAGE << " " << VERSION << std::endl;
          cleanup ();
          return;
        }
    }
}

/* ********************** GLTFPrimitiveTarget::cleanup ********************* */

void
GLTFPrimitiveTarget::cleanup ()
{
  m_color_targets.clear ();
  m_texcoord_targets.clear ();
  m_position_target = std::nullopt;
  m_normal_target = std::nullopt;
  m_tangent_target = std::nullopt;
}

/* ********************* GLTFPrimitiveTarget::is_empty ********************* */

bool
GLTFPrimitiveTarget::is_empty () const
{
  return m_color_targets.empty () && m_texcoord_targets.empty ()
         && (m_normal_target == std::nullopt)
         && (m_tangent_target == std::nullopt)
         && (m_position_target == std::nullopt);
}

}