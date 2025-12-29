#ifndef OCCLUSIONTEXTUREINFO_H
#define OCCLUSIONTEXTUREINFO_H

#include "gltfobject.h"
#include "indexhelper.h"

#include <memory>
#include <optional>

namespace gltfloader
{

class GLTFOcclusionTextureInfo : public GLTFObject
{
private:
  size_t m_index;
  size_t m_texcoord;
  float m_strength;

  GLTFOcclusionTextureInfo ();

public:
  GLTFOcclusionTextureInfo (const GLTFOcclusionTextureInfo &) = delete;
  virtual ~GLTFOcclusionTextureInfo ();

  size_t index () const;
  size_t texcoord () const;
  float strength () const;

  static std::shared_ptr<GLTFOcclusionTextureInfo>
  create (const IndexHelper &helper, int index,
          const std::optional<int> &texcoord,
          const std::optional<float> &strength);
};

}

#endif // OCCLUSIONTEXTUREINFO_H
