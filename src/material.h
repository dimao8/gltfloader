#ifndef MATERIAL_H
#define MATERIAL_H

#include "gltfnamedobject.h"
#include "gltftypes.h"
#include "indexhelper.h"

#include <array>
#include <memory>
#include <optional>
#include <string>

namespace gltfloader
{

class GLTFPBRMetallicRoughness;
class GLTFNormalTextureInfo;
class GLTFOcclusionTextureInfo;
class GLTFTextureInfo;

class GLTFMaterial : public GLTFNamedObject
{
private:
  std::shared_ptr<GLTFPBRMetallicRoughness> m_pbr_metallic_roughness;
  std::shared_ptr<GLTFNormalTextureInfo> m_normal_texture;
  std::shared_ptr<GLTFOcclusionTextureInfo> m_occlusion_texture;
  size_t m_emissive_texture;
  std::array<float, 3> m_emissive_factor;
  GLTFAlphaMode m_alpha_mode;
  float m_alpha_cutoff;
  bool m_double_sided;

  GLTFMaterial (const std::string &name);

public:
  GLTFMaterial () = delete;
  GLTFMaterial (const GLTFMaterial &) = delete;
  virtual ~GLTFMaterial () {}

  const std::shared_ptr<GLTFPBRMetallicRoughness> &
  pbr_metallic_roughness () const;
  const std::shared_ptr<GLTFNormalTextureInfo> &normal_texture () const;
  const std::shared_ptr<GLTFOcclusionTextureInfo> &occlusion_texture () const;
  size_t emissive_texture () const;
  const std::array<float, 3> &emissive_factor () const;
  GLTFAlphaMode alpha_mode () const;
  float alpha_cutoff () const;
  bool double_sided () const;

  static std::shared_ptr<GLTFMaterial> create (
      const std::string &name, const IndexHelper &helper,
      const std::shared_ptr<GLTFPBRMetallicRoughness> &pbr_metallic_roughness
      = nullptr,
      const std::shared_ptr<GLTFNormalTextureInfo> &normal_texture = nullptr,
      const std::shared_ptr<GLTFOcclusionTextureInfo> &occlusion_texture
      = nullptr,
      const std::optional<int> &emissive_texture = std::nullopt,
      std::array<float, 3> emissive_factor = { 0.0f, 0.0f, 0.0f },
      const std::string &alpha_mode = "OPAQUE", float alpha_cutoff = 0.5f,
      bool double_sided = false);
};

}

#endif // MATERIAL_H
