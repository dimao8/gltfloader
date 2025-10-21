#ifndef PBRMETALLICROUGHNESS_H
#define PBRMETALLICROUGHNESS_H

#include "gltfobject.h"

#include <array>
#include <memory>

namespace gltfloader
{

class GLTFTextureInfo;

class GLTFPBRMetallicRoughness : public GLTFObject
{
private:
  std::array<float, 4> m_base_color_factor;
  std::shared_ptr<GLTFTextureInfo> m_base_color_texture;
  float m_metallic_factor;
  float m_roughness_factor;
  std::shared_ptr<GLTFTextureInfo> m_metallic_roughness_texture;

  GLTFPBRMetallicRoughness ();

public:
  GLTFPBRMetallicRoughness (const GLTFPBRMetallicRoughness &) = delete;
  virtual ~GLTFPBRMetallicRoughness () {}

  const std::array<float, 4> &base_color_factor () const;
  const std::shared_ptr<GLTFTextureInfo> &base_color_texture () const;
  float metallic_factor () const;
  float roughness_factor () const;
  const std::shared_ptr<GLTFTextureInfo> &metallic_roughness_texture () const;

  static std::shared_ptr<GLTFPBRMetallicRoughness>
  create (const std::array<float, 4> &base_color_factor
          = { 1.0f, 1.0f, 1.0f, 1.0f },
          const std::shared_ptr<GLTFTextureInfo> &base_color_texture = nullptr,
          float metallic_factor = 1.0f, float roughness_factor = 1.0f,
          const std::shared_ptr<GLTFTextureInfo> &metallic_roughness_texture
          = nullptr);
};

}

#endif // PBRMETALLICROUGHNESS_H
