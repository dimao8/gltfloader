#ifndef NORMALTEXTUREINFO_H
#define NORMALTEXTUREINFO_H

#include "gltfobject.h"
#include "indexhelper.h"

#include <memory>
#include <optional>

namespace gltfloader
{

class GLTFNormalTextureInfo : public GLTFObject
{
private:
  size_t m_index;
  size_t m_texcoord;
  float m_scale;

  GLTFNormalTextureInfo ();

public:
  GLTFNormalTextureInfo (const GLTFNormalTextureInfo &) = delete;
  virtual ~GLTFNormalTextureInfo ();

  size_t index () const;
  size_t texcoord () const;
  float scale () const;

  static std::shared_ptr<GLTFNormalTextureInfo>
  create (const IndexHelper &helper, int index,
          const std::optional<int> &texcoord,
          const std::optional<float> &scale);
};

}

#endif // NORMALTEXTUREINFO_H
