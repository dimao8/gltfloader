#include "material.h"
#include "pbrmetallicroughness.h"

#include <iostream>

namespace gltfloader
{

/* *********************** GLTFMaterial::GLTFMaterial ********************** */

GLTFMaterial::GLTFMaterial (const std::string &name) : GLTFNamedObject (name)
{
  //
}

/* ****************** GLTFMaterial::pbr_metallic_roughness ***************** */

const std::shared_ptr<GLTFPBRMetallicRoughness> &
GLTFMaterial::pbr_metallic_roughness () const
{
  return m_pbr_metallic_roughness;
}

/* ********************** GLTFMaterial::normal_texture ********************* */

const std::shared_ptr<GLTFNormalTextureInfo> &
GLTFMaterial::normal_texture () const
{
  return m_normal_texture;
}

/* ******************** GLTFMaterial::occlusion_texture ******************** */

const std::shared_ptr<GLTFOcclusionTextureInfo> &
GLTFMaterial::occlusion_texture () const
{
  return m_occlusion_texture;
}

/* ********************* GLTFMaterial::emissive_texture ******************** */

const std::shared_ptr<GLTFTextureInfo> &
GLTFMaterial::emissive_texture () const
{
  return m_emissive_texture;
}

/* ********************* GLTFMaterial::emissive_factor ********************* */

const std::array<float, 3> &
GLTFMaterial::emissive_factor () const
{
  return m_emissive_factor;
}

/* ************************ GLTFMaterial::alpha_mode *********************** */

GLTFAlphaMode
GLTFMaterial::alpha_mode () const
{
  return m_alpha_mode;
}

/* *********************** GLTFMaterial::alpha_cutoff ********************** */

float
GLTFMaterial::alpha_cutoff () const
{
  return m_alpha_cutoff;
}

/* *********************** GLTFMaterial::double_sided ********************** */

bool
GLTFMaterial::double_sided () const
{
  return m_double_sided;
}

/* ************************** GLTFMaterial::create ************************* */

std::shared_ptr<GLTFMaterial>
GLTFMaterial::create (
    const std::string &name,
    const std::shared_ptr<GLTFPBRMetallicRoughness> &pbr_metallic_roughness,
    const std::shared_ptr<GLTFNormalTextureInfo> &normal_texture,
    const std::shared_ptr<GLTFOcclusionTextureInfo> &occlusion_texture,
    const std::shared_ptr<GLTFTextureInfo> &emissive_texture,
    std::array<float, 3> emissive_factor, const std::string &alpha_mode,
    float alpha_cutoff, bool double_sided)
{
  std::shared_ptr<GLTFMaterial> tmp (new GLTFMaterial (name));
  if (pbr_metallic_roughness == nullptr)
    {
      // TODO : GLTFPBRMetallicRoughness class
      tmp->m_pbr_metallic_roughness = GLTFPBRMetallicRoughness::create ();
      std::cout << "[I] glTF 2.0: Set Metallic/Roughness texture for \""
                << name << "\" object to default" << std::endl;
    }

  tmp->m_normal_texture = normal_texture;
  tmp->m_occlusion_texture = occlusion_texture;
  tmp->m_emissive_texture = emissive_texture;

  if ((emissive_factor[0] < 0.0f) || (emissive_factor[0] > 1.0f)
      || (emissive_factor[1] < 0.0f) || (emissive_factor[1] > 1.0f)
      || (emissive_factor[2] < 0.0f) || (emissive_factor[2] > 1.0f))
    {
      std::cout << "[W] glTF 2.0: The emissive factor for \"" << name
                << "\" object can have components from [0.0,1.0] range"
                << std::endl;
      return nullptr;
    }
  tmp->m_emissive_factor = emissive_factor;

  if (alpha_mode == "OPAQUE")
    tmp->m_alpha_mode = GLTFAlphaMode::opaque;
  else if (alpha_mode == "MASK")
    tmp->m_alpha_mode = GLTFAlphaMode::mask;
  else if (alpha_mode == "BLEND")
    tmp->m_alpha_mode = GLTFAlphaMode::blend;
  else
    {
      std::cout << "[W] glTF 2.0: The alpha mode for \"" << name
                << "\" object can be \"OPAQUE\", \"MASK\" or \"BLEND\""
                << std::endl;
      return nullptr;
    }

  if (alpha_cutoff < 0.0f)
    {
      std::cout << "[W] glTF 2.0: The alpha cutoff value for \"" << name
                << "\" object can not be less than zero" << std::endl;
      return nullptr;
    }
  tmp->m_alpha_cutoff = alpha_cutoff;

  tmp->m_double_sided = double_sided;

  return tmp;
}

}