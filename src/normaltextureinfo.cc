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

const std::shared_ptr<GLTFTexture> &
GLTFNormalTextureInfo::index () const
{
  return m_index;
}

/* ***************** GLTFNormalTextureInfo::attribute_index **************** */

const std::shared_ptr<GLTFPrimitiveAttribute> &
GLTFNormalTextureInfo::attribute_index () const
{
  return m_attribute_index;
}

/* ********************** GLTFNormalTextureInfo::scale ********************* */

float
GLTFNormalTextureInfo::scale () const
{
  return m_scale;
}

/* ********************* GLTFNormalTextureInfo::create ********************* */

std::shared_ptr<GLTFNormalTextureInfo>
GLTFNormalTextureInfo::create (
    const std::shared_ptr<GLTFTexture> &index,
    const std::shared_ptr<GLTFPrimitiveAttribute> &attribute_index,
    float scale)
{
  std::shared_ptr<GLTFNormalTextureInfo> tmp (new GLTFNormalTextureInfo ());

  if (index == nullptr)
    {
      std::cout << "[W] glTF 2.0: The index value in normal texture info "
                   "object MUST link to valid texture"
                << std::endl;
      return nullptr;
    }
  tmp->m_index = index;

  // FIXME : Delete this after migration to the index-based arguments
  if (attribute_index == nullptr)
    {
      std::cout
          << "[W] glTF 2.0: The attribute index value in normal texture info "
             "object MUST link to valid primitive attribute (TEXCOORD)"
          << std::endl;
      return nullptr;
    }
  tmp->m_attribute_index = attribute_index;

  tmp->m_scale = scale;
  return tmp;
}

}