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

const std::shared_ptr<GLTFTexture> &
GLTFOcclusionTextureInfo::index () const
{
  return m_index;
}

/* *************** GLTFOcclusionTextureInfo::attribute_index *************** */

const std::shared_ptr<GLTFPrimitiveAttribute> &
GLTFOcclusionTextureInfo::attribute_index () const
{
  return m_attribute_index;
}

/* ******************** GLTFOcclusionTextureInfo::scale ******************** */

float
GLTFOcclusionTextureInfo::strength () const
{
  return m_strength;
}

/* ******************** GLTFOcclusionTextureInfo::create ******************* */

std::shared_ptr<GLTFOcclusionTextureInfo>
GLTFOcclusionTextureInfo::create (
    const std::shared_ptr<GLTFTexture> &index,
    const std::shared_ptr<GLTFPrimitiveAttribute> &attribute_index,
    float strength)
{
  std::shared_ptr<GLTFOcclusionTextureInfo> tmp (
      new GLTFOcclusionTextureInfo ());

  if (index == nullptr)
    {
      std::cout << "[W] glTF 2.0: The index value in occlusion texture info "
                   "object MUST link to valid texture"
                << std::endl;
      return nullptr;
    }
  tmp->m_index = index;

  // FIXME : Delete this after migration to the index-based arguments
  if (attribute_index == nullptr)
    {
      std::cout << "[W] glTF 2.0: The attribute index value in occlusion "
                   "texture info object MUST link to valid primitive "
                   "attribute (TEXCOORD)"
                << std::endl;
      return nullptr;
    }
  tmp->m_attribute_index = attribute_index;

  if ((strength < 0.0f) || (strength > 1.0f))
    {
      std::cout << "[W] glTF 2.0: The strength value in occlusion texture "
                   "info object MUST fit into [0.0, 1.0] range"
                << std::endl;
      return nullptr;
    }
  tmp->m_strength = strength;

  return tmp;
}

}