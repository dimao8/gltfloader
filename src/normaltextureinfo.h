#ifndef NORMALTEXTUREINFO_H
#define NORMALTEXTUREINFO_H

#include "gltfobject.h"

#include <memory>

// TODO : Set indices as integers. Check for existence

namespace gltfloader
{

class GLTFTexture;
class GLTFPrimitiveAttribute;

class GLTFNormalTextureInfo : public GLTFObject
{
private:
  std::shared_ptr<GLTFTexture> m_index;
  std::shared_ptr<GLTFPrimitiveAttribute> m_attribute_index;
  float m_scale;

  GLTFNormalTextureInfo ();

public:
  GLTFNormalTextureInfo (const GLTFNormalTextureInfo &) = delete;
  virtual ~GLTFNormalTextureInfo () {}

  const std::shared_ptr<GLTFTexture> &index () const;
  const std::shared_ptr<GLTFPrimitiveAttribute> &attribute_index () const;
  float scale () const;

  static std::shared_ptr<GLTFNormalTextureInfo>
  create (const std::shared_ptr<GLTFTexture> &index,
          const std::shared_ptr<GLTFPrimitiveAttribute> &attribute_index,
          float scale = 1.0f);
};

}

#endif // NORMALTEXTUREINFO_H
