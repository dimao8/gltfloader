#include "occlusiontextureinfo.h"

#include <iostream>

namespace gltfloader
{

/* *********** GLTFOcclusionTextureInfo::GLTFOcclusionTextureInfo ********** */

GLTFOcclusionTextureInfo::GLTFOcclusionTextureInfo ()
    : GLTFObject (), m_index (0), m_texcoord (0), m_strength (1.0)
{
  //
}

/* ********** GLTFOcclusionTextureInfo::~GLTFOcclusionTextureInfo ********** */

GLTFOcclusionTextureInfo::~GLTFOcclusionTextureInfo ()
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
                                  const std::optional<int> &texcoord,
                                  const std::optional<float> &strength)
{
  std::shared_ptr<GLTFOcclusionTextureInfo> tmp (
      new GLTFOcclusionTextureInfo ());

  size_t shifted_index = index + helper.texture_defaults_size ();

  if (index < 0)
    {
      std::cout
          << "[W] glTF 2.0 5.21.1: material.occlusionTextureInfo.index >= 0"
          << std::endl;
      return nullptr;
    }
  else if (shifted_index >= helper.textures_size ())
    {
      std::cout << "[W] glTF 2.0 5.21.1: material.occlusionTextureInfo.index "
                   "is out of range"
                << std::endl;
      return nullptr;
    }
  tmp->m_index = shifted_index;

  tmp->m_texcoord = texcoord.value_or (0);
  if (texcoord < 0)
    {
      std::cout << "[W] glTF 2.0 5.21.2: material.normalTexture.texCoord >= 0"
                << std::endl;
      return nullptr;
    }

  tmp->m_strength = strength.value_or (1.0);

  return tmp;
}

}