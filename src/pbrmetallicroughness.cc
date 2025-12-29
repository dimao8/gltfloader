#include "pbrmetallicroughness.h"
#include "gltfobject.h"

#include <iostream>

namespace gltfloader
{

/* *********** GLTFPBRMetallicRoughness::GLTFPBRMetallicRoughness ********** */

GLTFPBRMetallicRoughness::GLTFPBRMetallicRoughness ()
    : GLTFObject (), m_base_color_factor ({ 1.0, 1.0, 1.0, 1.0 }),
      m_metallic_factor (1.0), m_roughness_factor (1.0),
      m_base_color_texture (nullptr), m_metallic_roughness_texture (nullptr)
{
  //
}

/* ********** GLTFPBRMetallicRoughness::~GLTFPBRMetallicRoughness ********** */

GLTFPBRMetallicRoughness::~GLTFPBRMetallicRoughness ()
{
  //
}

/* ************** GLTFPBRMetallicRoughness::base_color_factor ************** */

const std::array<float, 4> &
GLTFPBRMetallicRoughness::base_color_factor () const
{
  return m_base_color_factor;
}

/* ************** GLTFPBRMetallicRoughness::base_color_texture ************* */

const std::shared_ptr<GLTFTextureInfo> &
GLTFPBRMetallicRoughness::base_color_texture () const
{
  return m_base_color_texture;
}

/* *************** GLTFPBRMetallicRoughness::metallic_factor *************** */

float
GLTFPBRMetallicRoughness::metallic_factor () const
{
  return m_metallic_factor;
}

/* *************** GLTFPBRMetallicRoughness::roughness_factor ************** */

float
GLTFPBRMetallicRoughness::roughness_factor () const
{
  return m_roughness_factor;
}

/* ********** GLTFPBRMetallicRoughness::metallic_roughness_texture ********* */

const std::shared_ptr<GLTFTextureInfo> &
GLTFPBRMetallicRoughness::metallic_roughness_texture () const
{
  return m_metallic_roughness_texture;
}

/* ******************** GLTFPBRMetallicRoughness::create ******************* */

std::shared_ptr<GLTFPBRMetallicRoughness>
GLTFPBRMetallicRoughness::create (
    IndexHelper &helper, const std::optional<GLTFVector4f> &base_color_factor,
    const std::shared_ptr<GLTFTextureInfo> &base_color_texture,
    const std::optional<float> &metallic_factor,
    const std::optional<float> &roughness_factor,
    const std::shared_ptr<GLTFTextureInfo> &metallic_roughness_texture)
{
  std::shared_ptr<GLTFPBRMetallicRoughness> tmp (
      new GLTFPBRMetallicRoughness ());

  if (base_color_factor == std::nullopt)
    tmp->m_base_color_factor = { 1.0f, 1.0f, 1.0f, 1.0f };
  else if ((base_color_factor.value ()[0] < 0.0f)
           || (base_color_factor.value ()[0] > 1.0f)
           || (base_color_factor.value ()[1] < 0.0f)
           || (base_color_factor.value ()[1] > 1.0f)
           || (base_color_factor.value ()[2] < 0.0f)
           || (base_color_factor.value ()[2] > 1.0f)
           || (base_color_factor.value ()[3] < 0.0f)
           || (base_color_factor.value ()[3] > 1.0f))
    {
      std::cout << "[W] glTF 2.0: The base color factor components in PBR "
                   "object MUST fit into [0.0, 1.0] range"
                << std::endl;
      return nullptr;
    }
  else
    tmp->m_base_color_factor = base_color_factor.value ();

  if (base_color_texture != nullptr)
    tmp->m_base_color_texture = base_color_texture;
  else
    tmp->m_base_color_texture = helper.texture_info (
        helper.default_pbr_metallic_roughness_texture_info ());

  if (metallic_factor == std::nullopt)
    tmp->m_metallic_factor = 1.0f;
  else if (metallic_factor < 0.0f || metallic_factor > 1.0f)
    {
      std::cout << "[W] glTF 2.0: The metallic factor in PBR object MUST fit "
                   "into [0.0, 1.0] range"
                << std::endl;
      return nullptr;
    }
  else
    tmp->m_metallic_factor = metallic_factor.value ();

  if (roughness_factor == std::nullopt)
    tmp->m_roughness_factor = 1.0f;
  else if (roughness_factor < 0.0f || roughness_factor > 1.0f)
    {
      std::cout << "[W] glTF 2.0: The roughness factor in PBR object MUST fit "
                   "into [0.0, 1.0] range"
                << std::endl;
      return nullptr;
    }
  else
    tmp->m_roughness_factor = roughness_factor.value ();

  if (metallic_roughness_texture != nullptr)
    tmp->m_metallic_roughness_texture = metallic_roughness_texture;
  else
    tmp->m_metallic_roughness_texture = helper.texture_info (
        helper.default_pbr_metallic_roughness_texture_info ());

  return tmp;
}

}