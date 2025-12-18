#ifndef NORMALTEXTUREINFO_H
#define NORMALTEXTUREINFO_H

#include "gltfobject.h"
#include "indexhelper.h"

#include <memory>

// TODO : Set indices as integers. Check for existence

namespace gltfloader
{

class GLTFTexture;
class GLTFPrimitiveAttribute;

class GLTFNormalTextureInfo : public GLTFObject
{
private:
  size_t m_index;
  size_t m_texcoord;
  float m_scale;

  GLTFNormalTextureInfo ();

public:
  GLTFNormalTextureInfo (const GLTFNormalTextureInfo &) = delete;
  virtual ~GLTFNormalTextureInfo () {}

  size_t index () const;
  size_t texcoord () const;
  float scale () const;

  static std::shared_ptr<GLTFNormalTextureInfo>
  create (const IndexHelper &helper, int index, int texcoord = 0,
          float scale = 1.0f);
};

}

#endif // NORMALTEXTUREINFO_H
