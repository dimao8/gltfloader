#ifndef ANIMATION_H
#define ANIMATION_H

#include "gltfnamedobject.h"

#include <memory>
#include <string>
#include <vector>

namespace gltfloader
{

class GLTFAnimationChannel;
class GLTFAnimationSampler;

class GLTFAnimation : public GLTFNamedObject
{
private:
  std::vector<std::shared_ptr<GLTFAnimationChannel> > m_channels;
  std::vector<std::shared_ptr<GLTFAnimationSampler> > m_samplers;

  GLTFAnimation (const std::string &name);

public:
  GLTFAnimation () = delete;
  GLTFAnimation (const GLTFAnimation &) = delete;

  virtual ~GLTFAnimation () {}

  const std::vector<std::shared_ptr<GLTFAnimationChannel> > &channels () const;

  static std::shared_ptr<GLTFAnimation>
  create (const std::string &name,
          const std::vector<std::shared_ptr<GLTFAnimationChannel> > &channels,
          const std::vector<std::shared_ptr<GLTFAnimationSampler> > &samplers);
};

}

#endif // ANIMATION_H
