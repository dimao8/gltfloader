#ifndef TEXTUREINFO_H
#define TEXTUREINFO_H

#include "gltfobject.h"
#include "indexhelper.h"

#include <cstddef>
#include <memory>
#include <optional>

namespace gltfloader
{

class GLTFTextureInfo : public GLTFObject
{
private:
  size_t m_index;
  size_t m_tex_coord;
  GLTFTextureInfo ();

public:
  GLTFTextureInfo (const GLTFTextureInfo &) = delete;
  virtual ~GLTFTextureInfo ();
  size_t index () const;
  size_t tex_coord () const;

  static std::shared_ptr<GLTFTextureInfo>
  create (const IndexHelper &helper, int index,
          const std::optional<int> &tex_coord);
};

}

#endif // TEXTUREINFO_H