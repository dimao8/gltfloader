#ifndef ANIMATIONCHANNEL_H
#define ANIMATIONCHANNEL_H

#include "gltfobject.h"

#include <memory>

namespace gltfloader
{

class GLTFAnimationSampler;
class GLTFAnimationTarget;

class GLTFAnimationChannel : GLTFObject
{
private:
  std::shared_ptr<GLTFAnimationSampler> m_sampler;
  std::shared_ptr<GLTFAnimationTarget> m_target;

  GLTFAnimationChannel ();

public:
  GLTFAnimationChannel (const GLTFAnimationChannel &) = delete;

  virtual ~GLTFAnimationChannel () {}

  const std::shared_ptr<GLTFAnimationSampler> &sampler () const;
  const std::shared_ptr<GLTFAnimationTarget> &target () const;

  static std::shared_ptr<GLTFAnimationChannel>
  create (const std::shared_ptr<GLTFAnimationSampler> &sampler,
          const std::shared_ptr<GLTFAnimationTarget> &target);
};

}

#endif // ANIMATIONCHANNEL_H
