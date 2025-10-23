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

size_t
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
    const IndexHelper &helper, int sampler,
    const std::shared_ptr<GLTFAnimationTarget> &target)
{
  std::shared_ptr<GLTFAnimationChannel> tmp (new GLTFAnimationChannel ());

  if (sampler < 0)
    {
      std::cout << "[W] glTF 2.0 5.6.1: animation.channels[n].sampler can not "
                   "be negative"
                << std::endl;
      return nullptr;
    }
  tmp->m_sampler = sampler;

  if (target == nullptr)
    {
      std::cout
          << "[W] glTF 2.0 5.6.2: animation.channels[n].target must must exist"
          << std::endl;
      return nullptr;
    }
  tmp->m_target = target;

  return tmp;
}

}