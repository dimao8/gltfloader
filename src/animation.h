#ifndef ANIMATION_H
#define ANIMATION_H

#include "gltfnamedobject.h"
#include "indexhelper.h"

#include <memory>
#include <string>
#include <vector>

namespace gltfloader
{

class GLTFAnimationChannel;
class GLTFAnimationSampler;

class GLTFAnimation : public GLTFNamedObject
{
public:
  using GLTFChannelList = std::vector<std::shared_ptr<GLTFAnimationChannel> >;
  using GLTFSamplerList = std::vector<std::shared_ptr<GLTFAnimationChannel> >;

private:
  GLTFChannelList m_channels;
  GLTFSamplerList m_samplers;

  GLTFAnimation (const std::string &name);

  static bool
  is_exist_twice (const std::shared_ptr<GLTFAnimationChannel> &target,
                  const GLTFChannelList &list);

public:
  GLTFAnimation () = delete;
  GLTFAnimation (const GLTFAnimation &) = delete;

  virtual ~GLTFAnimation () {}

  const GLTFChannelList &channels () const;
  const GLTFSamplerList &samplers () const;

  static std::shared_ptr<GLTFAnimation>
  create (const IndexHelper &helper, const std::string &name,
          const GLTFChannelList &channels, const GLTFSamplerList &samplers);
};

}

#endif // ANIMATION_H
