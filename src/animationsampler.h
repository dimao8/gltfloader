#ifndef ANIMATIONSAMPLER_H
#define ANIMATIONSAMPLER_H

#include "gltfobject.h"

#include <memory>
#include <string>

namespace gltfloader
{

class GLTFAccessor;

enum GLTFInterpolationMethod
{
  none,
  step,
  linear,
  cubic
};

class GLTFAnimationSampler : public GLTFObject
{
private:
  std::shared_ptr<GLTFAccessor> m_input;
  GLTFInterpolationMethod m_interpolation;
  std::shared_ptr<GLTFAccessor> m_output;

  GLTFAnimationSampler ();

public:
  GLTFAnimationSampler (const GLTFAnimationSampler &) = delete;
  virtual ~GLTFAnimationSampler () {}

  const std::shared_ptr<GLTFAccessor> &input () const;
  const std::shared_ptr<GLTFAccessor> &output () const;
  GLTFInterpolationMethod interpolation () const;

  static std::shared_ptr<GLTFAnimationSampler>
  create (const std::shared_ptr<GLTFAccessor> &input,
          const std::shared_ptr<GLTFAccessor> &output,
          const std::string &interpolation = "LINEAR");
};

}

#endif // ANIMATIONSAMPLER_H
