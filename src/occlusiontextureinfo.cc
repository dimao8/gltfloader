#include "occlusiontextureinfo.h"

#include <iostream>

namespace gltfloader
{

/* *********** GLTFOcclusionTextureInfo::GLTFOcclusionTextureInfo ********** */

GLTFOcclusionTextureInfo::GLTFOcclusionTextureInfo () : GLTFObject ()
{
  //
}

/* ******************** GLTFOcclusionTextureInfo::index ******************** */

size_t
GLTFOcclusionTextureInfo::index () const
{
  return m_index;
}

/* ******************* GLTFOcclusionTextureInfo::texcoord ****************** */

size_t
GLTFOcclusionTextureInfo::texcoord () const
{
  return m_texcoord;
}

/* ******************** GLTFOcclusionTextureInfo::scale ******************** */

float
GLTFOcclusionTextureInfo::strength () const
{
  return m_strength;
}

/* ******************** GLTFOcclusionTextureInfo::create ******************* */

std::shared_ptr<GLTFOcclusionTextureInfo>
GLTFOcclusionTextureInfo::create (const IndexHelper &helper, int index,
                                  int texcoord, float strength)
{
  std::shared_ptr<GLTFOcclusionTextureInfo> tmp (
      new GLTFOcclusionTextureInfo ());

  if (index < 0)
    {
      std::cout
          << "[W] glTF 2.0 5.21.1: material.occlusionTextureInfo.index >= 0"
          << std::endl;
      return nullptr;
    }
  if (index >= helper.textures_size ())
    {
      std::cout << "[W] glTF 2.0 5.21.1: material.occlusionTextureInfo.index "
                   "is out of range"
                << std::endl;
      return nullptr;
    }
  tmp->m_index = index;

  if (texcoord < 0)
    {
      std::cout << "[W] glTF 2.0 5.21.2: material.normalTexture.texCoord >= 0"
                << std::endl;
      return nullptr;
    }
  tmp->m_texcoord = texcoord;

  tmp->m_strength = strength;

  return tmp;
}

}