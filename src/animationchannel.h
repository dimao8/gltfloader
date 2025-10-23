#ifndef ANIMATIONCHANNEL_H
#define ANIMATIONCHANNEL_H

#include "gltfobject.h"
#include "indexhelper.h"

#include <memory>

namespace gltfloader
{

class GLTFAnimationSampler;
class GLTFAnimationTarget;

class GLTFAnimationChannel : GLTFObject
{
private:
  size_t m_sampler;
  std::shared_ptr<GLTFAnimationTarget> m_target;

  GLTFAnimationChannel ();

public:
  GLTFAnimationChannel (const GLTFAnimationChannel &) = delete;

  virtual ~GLTFAnimationChannel () {}

  size_t sampler () const;
  const std::shared_ptr<GLTFAnimationTarget> &target () const;

  static std::shared_ptr<GLTFAnimationChannel>
  create (const IndexHelper &helper, int sampler,
          const std::shared_ptr<GLTFAnimationTarget> &target);
};

}

#endif // ANIMATIONCHANNEL_H
