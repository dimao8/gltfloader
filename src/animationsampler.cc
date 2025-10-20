#include "animationsampler.h"

#include <iostream>

namespace gltfloader
{

/* *************** GLTFAnimationSampler::GLTFAnimationSampler ************** */

GLTFAnimationSampler::GLTFAnimationSampler () : GLTFObject ()
{
  //
}

/* ********************** GLTFAnimationSampler::input ********************** */

const std::shared_ptr<GLTFAccessor> &
GLTFAnimationSampler::input () const
{
  return m_input;
}

/* ********************** GLTFAnimationSampler::output ********************* */

const std::shared_ptr<GLTFAccessor> &
GLTFAnimationSampler::output () const
{
  return m_output;
}

/* ****************** GLTFAnimationSampler::interpolation ****************** */

GLTFInterpolationMethod
GLTFAnimationSampler::interpolation () const
{
  return m_interpolation;
}

/* ********************** GLTFAnimationSampler::create ********************* */

std::shared_ptr<GLTFAnimationSampler>
GLTFAnimationSampler::create (const std::shared_ptr<GLTFAccessor> &input,
                              const std::shared_ptr<GLTFAccessor> &output,
                              const std::string &interpolation)
{
  std::shared_ptr<GLTFAnimationSampler> tmp (new GLTFAnimationSampler ());

  if (!input)
    {
      std::cout << "[W] glTF 2.0: The Animation target field must contain "
                   "valid input accessor"
                << std::endl;
      return nullptr;
    }
  tmp->m_input = input;

  if (!output)
    {
      std::cout << "[W] glTF 2.0: The Animation target field must contain "
                   "valid output accessor"
                << std::endl;
      return nullptr;
    }
  tmp->m_output = output;

  if (interpolation.empty ())
    tmp->m_interpolation = GLTFInterpolationMethod::none;
  else if (interpolation == "STEP")
    tmp->m_interpolation = GLTFInterpolationMethod::step;
  else if (interpolation == "LINEAR")
    tmp->m_interpolation = GLTFInterpolationMethod::linear;
  else if (interpolation == "CUBICSPLINE")
    tmp->m_interpolation = GLTFInterpolationMethod::cubic;
  else
    {
      std::cout << "[W] glTF 2.0: The Path field in animation targets must "
                   "contain one of the following values: \"STEP\", "
                   "\"LINEAR\", \"CUBICSPLINE\" or be empty"
                << std::endl;
      return nullptr;
    }

  return tmp;
}

}