#include "textureinfo.h"
#include "gltfobject.h"

#include <cstddef>
#include <iostream>

namespace gltfloader
{

/* ******************** GLTFTextureInfo::GLTFTextureInfo ******************* */

GLTFTextureInfo::GLTFTextureInfo ()
    : GLTFObject (), m_index (0), m_tex_coord (0)
{
  //
}

/* ******************* GLTFTextureInfo::~GLTFTextureInfo ******************* */

GLTFTextureInfo::~GLTFTextureInfo ()
{
  //
}

/* ************************* GLTFTextureInfo::index ************************ */

size_t
GLTFTextureInfo::index () const
{
  return m_index;
}

/* *********************** GLTFTextureInfo::tex_coord ********************** */

size_t
GLTFTextureInfo::tex_coord () const
{
  return m_tex_coord;
}

/* ************************ GLTFTextureInfo::create ************************ */

std::shared_ptr<GLTFTextureInfo>
GLTFTextureInfo::create (const IndexHelper &helper, int index,
                         const std::optional<int> &tex_coord)
{
  std::shared_ptr<GLTFTextureInfo> tmp (new GLTFTextureInfo ());

  // Check index boundaries
  if (index < 0)
    {
      std::cout << "[W] glTF 2.0 5.30.1 index can not be negative"
                << std::endl;
      return nullptr;
    }

  size_t shifted_index = index + helper.textures_size ();
  if (shifted_index >= helper.textures_size ())
    {
      std::cout << "[W] glTF 2.0 5.30.1 index is out of range" << std::endl;
      return nullptr;
    }

  tmp->m_index = shifted_index;

  // Check texCoord value
  if (tex_coord.has_value ())
    {
      if (tex_coord.value () < 0)
        {
          std::cout << "[W] glTF 2.0 5.30.2 texCoord can not be negative"
                    << std::endl;
          return nullptr;
        }
    }
  tmp->m_tex_coord = tex_coord.value_or (0);

  // NOTE : Check for texture coordinates index in the mesh object
  return tmp;
}

}