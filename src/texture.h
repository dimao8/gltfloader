#ifndef TEXTURE_H
#define TEXTURE_H

#include "gltfnamedobject.h"

#include <memory>
#include <optional>
#include <string>

namespace gltfloader
{

class IndexHelper;

/**
 * \brief GLTFTexture class
 */
class GLTFTexture : public GLTFNamedObject
{
private:
  std::optional<size_t> m_sampler; /// glTF 2.0 texture.sampler
  std::optional<size_t> m_source;  /// glTF 2.0 texture.source

  GLTFTexture (const std::string &name);

public:
  GLTFTexture (const GLTFTexture &) = delete;
  virtual ~GLTFTexture () {}

  const std::optional<size_t> &sampler () const;
  const std::optional<size_t> &source () const;

  static std::shared_ptr<GLTFTexture>
  create (const IndexHelper &helper, const std::string &name,
          const std::optional<int> &sampler, const std::optional<int> &source);
};

}

#endif // TEXTURE_H
