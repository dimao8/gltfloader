#ifndef ANIMATIONSAMPLER_H
#define ANIMATIONSAMPLER_H

#include "gltfobject.h"
#include "indexhelper.h"

#include <memory>
#include <string>

namespace gltfloader
{

class GLTFAccessor;

enum class GLTFInterpolationMethod
{
  none,
  step,
  linear,
  cubic
};

class GLTFAnimationSampler : public GLTFObject
{
private:
  size_t m_input;
  GLTFInterpolationMethod m_interpolation;
  size_t m_output;

  GLTFAnimationSampler ();

public:
  GLTFAnimationSampler (const GLTFAnimationSampler &) = delete;
  virtual ~GLTFAnimationSampler () {}

  size_t input () const;
  size_t output () const;
  GLTFInterpolationMethod interpolation () const;

  static std::shared_ptr<GLTFAnimationSampler>
  create (const IndexHelper &helper, int input, int output,
          const std::string &interpolation = "LINEAR");
};

}

#endif // ANIMATIONSAMPLER_H
