#include "normaltextureinfo.h"

#include <iostream>

namespace gltfloader
{

/* ************** GLTFNormalTextureInfo::GLTFNormalTextureInfo ************* */

GLTFNormalTextureInfo::GLTFNormalTextureInfo () : GLTFObject ()
{
  //
}

/* ********************** GLTFNormalTextureInfo::index ********************* */

size_t
GLTFNormalTextureInfo::index () const
{
  return m_index;
}

/* ******************** GLTFNormalTextureInfo::texcoord ******************** */

size_t
GLTFNormalTextureInfo::texcoord () const
{
  return m_texcoord;
}

/* ********************** GLTFNormalTextureInfo::scale ********************* */

float
GLTFNormalTextureInfo::scale () const
{
  return m_scale;
}

/* ********************* GLTFNormalTextureInfo::create ********************* */

std::shared_ptr<GLTFNormalTextureInfo>
GLTFNormalTextureInfo::create (const IndexHelper &helper, int index,
                               int texcoord, float scale)
{
  std::shared_ptr<GLTFNormalTextureInfo> tmp (new GLTFNormalTextureInfo ());

  if (index < 0)
    {
      std::cout << "[W] glTF 2.0 5.20.1: material.normalTexture.index >= 0"
                << std::endl;
      return nullptr;
    }
  if (index >= helper.textures_size ())
    {
      std::cout << "[W] glTF 2.0 5.20.1: material.normalTexture.index is out "
                   "of range"
                << std::endl;
      return nullptr;
    }
  tmp->m_index = index;

  if (texcoord < 0)
    {
      std::cout << "[W] glTF 2.0 5.20.2: material.normalTexture.texCoord >= 0"
                << std::endl;
      return nullptr;
    }
  tmp->m_texcoord = texcoord;

  tmp->m_scale = scale;
  return tmp;
}

}