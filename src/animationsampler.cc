#include "animationsampler.h"
#include "indexhelper.h"

#include <iostream>

namespace gltfloader
{

/* *************** GLTFAnimationSampler::GLTFAnimationSampler ************** */

GLTFAnimationSampler::GLTFAnimationSampler () : GLTFObject ()
{
  //
}

/* ********************** GLTFAnimationSampler::input ********************** */

size_t
GLTFAnimationSampler::input () const
{
  return m_input;
}

/* ********************** GLTFAnimationSampler::output ********************* */

size_t
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
GLTFAnimationSampler::create (const IndexHelper &helper, int input, int output,
                              const std::string &interpolation)
{
  std::shared_ptr<GLTFAnimationSampler> tmp (new GLTFAnimationSampler ());

  if (input < 0)
    {
      std::cout << "[W] glTF 2.0 5.8.1: animation.samplers[n].input >= 0"
                << std::endl;
      return nullptr;
    }
  size_t shifted_accessor = input + helper.accessor_defaults_size();
  if (shifted_accessor >= helper.accessors_size ())
    {
      std::cout
          << "[W] glTF 2.0 5.8.1: animation.samplers[n].input is out of range"
          << std::endl;
      return nullptr;
    }
  // TODO : Check for input strictly increasing
  tmp->m_input = shifted_accessor;

  if (output < 0)
    {
      std::cout << "[W] glTF 2.0 5.8.3: animation.samplers[n].output >= 0"
                << std::endl;
      return nullptr;
    }
  shifted_accessor = output + helper.accessor_defaults_size();
  if (shifted_accessor >= helper.accessors_size ())
    {
      std::cout
          << "[W] glTF 2.0 5.8.3: animation.samplers[n].output is out of range"
          << std::endl;
      return nullptr;
    }
  tmp->m_output = shifted_accessor;

  if (interpolation.empty ())
    tmp->m_interpolation = GLTFInterpolationMethod::linear;
  else if (interpolation == "STEP")
    tmp->m_interpolation = GLTFInterpolationMethod::step;
  else if (interpolation == "LINEAR")
    tmp->m_interpolation = GLTFInterpolationMethod::linear;
  else if (interpolation == "CUBICSPLINE")
    tmp->m_interpolation = GLTFInterpolationMethod::cubic;
  else
    {
      std::cout
          << "[W] glTF 2.0 5.8.2: animation.samplers[n].interpolation can "
             "only be \"STEP\", \"LINEAR\", \"CUBICSPLINE\" or be empty"
          << std::endl;
      return nullptr;
    }

  // TODO : Check for sampler accessor size for appropriate interpolation

  return tmp;
}

}