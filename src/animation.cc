#include "animation.h"
#include "animationchannel.h"

#include <iostream>

namespace gltfloader
{

/* ********************** GLTFAnimation::GLTFAnimation ********************* */

GLTFAnimation::GLTFAnimation (const std::string &name) : GLTFNamedObject (name)
{
  //
}

/* *********************** GLTFAnimation::find_target ********************** */

bool
GLTFAnimation::is_exist_twice (
    const std::shared_ptr<GLTFAnimationChannel> &target,
    const GLTFChannelList &list)
{
  if (target == nullptr)
    return false;

  size_t n = 0;

  for (auto it : list)
    {
      if (target->target () == it->target ())
        n++;
    }

  return n > 1;
}

/* ************************ GLTFAnimation::channels ************************ */

const GLTFAnimation::GLTFChannelList &
GLTFAnimation::channels () const
{
  return m_channels;
}

/* ************************ GLTFAnimation::samplers ************************ */

const GLTFAnimation::GLTFSamplerList &
GLTFAnimation::samplers () const
{
  return m_samplers;
}

/* ************************* GLTFAnimation::create ************************* */

std::shared_ptr<GLTFAnimation>
GLTFAnimation::create (const IndexHelper &helper, const std::string &name,
                       const GLTFChannelList &channels,
                       const GLTFSamplerList &samplers)
{
  std::shared_ptr<GLTFAnimation> tmp (new GLTFAnimation (name));

  // TODO : Check for the number of points for CUBIC interpolation

  if (channels.empty ())
    {
      std::cout << "[W] glTF 2.0 5.5.1: animation.channels must have at least "
                   "one entry"
                << std::endl;
      return nullptr;
    }
  for (auto it : channels) // Search for two equal targets
    {
      if (is_exist_twice (it, channels))
        {
          std::cout << "[W] glTF 2.0 5.5.1: animation.channels must not have "
                       "same targets"
                    << std::endl;
          return nullptr;
        }
      if (it->sampler () >= samplers.size ())
        {
          std::cout << "[W] glTF 2.0 5.6.1: animation.channels[n].sampler is "
                       "out of range"
                    << std::endl;
          return nullptr;
        }
    }
  tmp->m_channels = channels;

  if (samplers.empty ())
    {
      std::cout << "[W] glTF 2.0 5.5.1: animation.samplers must have at least "
                   "one entry"
                << std::endl;
      return nullptr;
    }
  tmp->m_samplers = samplers;

  return tmp;
}

}
