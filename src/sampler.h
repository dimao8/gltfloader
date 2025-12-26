#ifndef SAMPLER_H
#define SAMPLER_H

#include "gltfnamedobject.h"
#include "gltftypes.h"
#include "indexhelper.h"

#include <memory>
#include <optional>

namespace gltfloader
{

class GLTFSampler : public GLTFNamedObject
{
private:
  std::optional<GLTFTextureFilter> m_mag_filter;
  std::optional<GLTFTextureFilter> m_min_filter;
  GLTFTextureWrap m_wrap_s;
  GLTFTextureWrap m_wrap_t;
  GLTFSampler (const std::string &name);

public:
  GLTFSampler () = delete;
  GLTFSampler (const GLTFSampler &) = delete;
  virtual ~GLTFSampler ();

  const std::optional<GLTFTextureFilter> &mag_filter () const;
  const std::optional<GLTFTextureFilter> &min_filter () const;
  GLTFTextureWrap wrap_s () const;
  GLTFTextureWrap wrap_t () const;

  static std::shared_ptr<GLTFSampler>
  create (IndexHelper &helper, const std::string &name,
          std::optional<int> mag_filter, std::optional<int> min_filter,
          std::optional<int> wrap_s, std::optional<int> wrap_t);
};

}

#endif // SAMPLER_H