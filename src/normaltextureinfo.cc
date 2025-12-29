#include "normaltextureinfo.h"

#include <iostream>

namespace gltfloader
{

/* ************** GLTFNormalTextureInfo::GLTFNormalTextureInfo ************* */

GLTFNormalTextureInfo::GLTFNormalTextureInfo ()
    : GLTFObject (), m_index (0), m_texcoord (0), m_scale (1.0)
{
  //
}

/* ************* GLTFNormalTextureInfo::~GLTFNormalTextureInfo ************* */

GLTFNormalTextureInfo::~GLTFNormalTextureInfo ()
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
                               const std::optional<int> &texcoord,
                               const std::optional<float> &scale)
{
  std::shared_ptr<GLTFNormalTextureInfo> tmp (new GLTFNormalTextureInfo ());

  size_t shifted_index = index + helper.textures_size ();
  if (index < 0)
    {
      std::cout << "[W] glTF 2.0 5.20.1: material.normalTexture.index >= 0"
                << std::endl;
      return nullptr;
    }
  else if (shifted_index >= helper.textures_size ())
    {
      std::cout << "[W] glTF 2.0 5.20.1: material.normalTexture.index is out "
                   "of range"
                << std::endl;
      return nullptr;
    }
  tmp->m_index = shifted_index;

  tmp->m_texcoord = texcoord.value_or (0);
  if (tmp->m_texcoord < 0)
    {
      std::cout << "[W] glTF 2.0 5.20.2: material.normalTexture.texCoord >= 0"
                << std::endl;
      return nullptr;
    }

  tmp->m_scale = scale.value_or (1.0);
  return tmp;
}

}