#include "animationchannel.h"

#include <iostream>

namespace gltfloader
{

/* *************** GLTFAnimationChannel::GLTFAnimationChannel ************** */

GLTFAnimationChannel::GLTFAnimationChannel () : GLTFObject ()
{
  //
}

/* ********************* GLTFAnimationChannel::sampler ********************* */

const std::shared_ptr<GLTFAnimationSampler> &
GLTFAnimationChannel::sampler () const
{
  return m_sampler;
}

/* ********************** GLTFAnimationChannel::target ********************* */

const std::shared_ptr<GLTFAnimationTarget> &
GLTFAnimationChannel::target () const
{
  return m_target;
}

/* ********************** GLTFAnimationChannel::create ********************* */

std::shared_ptr<GLTFAnimationChannel>
GLTFAnimationChannel::create (
    const std::shared_ptr<GLTFAnimationSampler> &sampler,
    const std::shared_ptr<GLTFAnimationTarget> &target)
{
  std::shared_ptr<GLTFAnimationChannel> tmp (new GLTFAnimationChannel ());

  if (sampler == nullptr)
    {
      std::cout << "[W] glTF 2.0: Animation channel must contain valid sampler"
                << std::endl;
      return nullptr;
    }
  tmp->m_sampler = sampler;

  if (target == nullptr)
    {
      std::cout << "[W] glTF 2.0: Animation channel must contain valid target"
                << std::endl;
      return nullptr;
    }
  tmp->m_target = target;

  return tmp;
}

}