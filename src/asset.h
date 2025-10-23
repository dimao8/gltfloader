#ifndef ASSET_H
#define ASSET_H

#include "gltfobject.h"

#include <array>
#include <memory>
#include <string>

namespace gltfloader
{

class GLTFAsset : public GLTFObject
{
private:
  std::string m_copyright;
  std::string m_generator;
  std::string m_version;
  std::string m_min_version;

  std::array<size_t, 2> m_version_int;
  std::array<size_t, 2> m_min_version_int;

  GLTFAsset ();

public:
  GLTFAsset (const GLTFAsset &) = delete;
  virtual ~GLTFAsset () {}

  const std::string &copyright () const;
  const std::string &generator () const;
  const std::string &version () const;
  const std::string &min_version () const;

  static std::shared_ptr<GLTFAsset>
  create (const std::string &version, const std::string &copyright = {},
          const std::string &generator = {},
          const std::string &min_version = {});
};

}

#endif // ASSET_H
