#ifndef OCCLUSIONTEXTUREINFO_H
#define OCCLUSIONTEXTUREINFO_H

#include "gltfobject.h"

#include <memory>

namespace gltfloader
{

class GLTFTexture;
class GLTFPrimitiveAttribute;

class GLTFOcclusionTextureInfo : public GLTFObject
{
private:
  std::shared_ptr<GLTFTexture> m_index;
  std::shared_ptr<GLTFPrimitiveAttribute> m_attribute_index;
  float m_strength;

  GLTFOcclusionTextureInfo ();

public:
  GLTFOcclusionTextureInfo (const GLTFOcclusionTextureInfo &) = delete;
  virtual ~GLTFOcclusionTextureInfo () {}

  const std::shared_ptr<GLTFTexture> &index () const;
  const std::shared_ptr<GLTFPrimitiveAttribute> &attribute_index () const;
  float strength () const;

  static std::shared_ptr<GLTFOcclusionTextureInfo>
  create (const std::shared_ptr<GLTFTexture> &index,
          const std::shared_ptr<GLTFPrimitiveAttribute> &attribute_index,
          float strength = 1.0f);
};

}

#endif // OCCLUSIONTEXTUREINFO_H
