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

/* ************************ GLTFAnimation::channels ************************ */

const std::vector<std::shared_ptr<GLTFAnimationChannel> > &
GLTFAnimation::channels () const
{
  return m_channels;
}

/* ************************* GLTFAnimation::create ************************* */

std::shared_ptr<GLTFAnimation>
GLTFAnimation::create (
    const std::string &name,
    const std::vector<std::shared_ptr<GLTFAnimationChannel> > &channels,
    const std::vector<std::shared_ptr<GLTFAnimationSampler> > &samplers)
{
  std::shared_ptr<GLTFAnimation> tmp (new GLTFAnimation (name));

  if (channels.empty ())
    {
      std::cout << "[W] glTF 2.0: The Animation field of the file \"" << name
                << "\" can not contain empty channels list" << std::endl;
      return nullptr;
    }
  // TODO : Check for the equal targets in channels
  tmp->m_channels = channels;

  if (samplers.empty ())
    {
      std::cout << "[W] glTF 2.0: The Animation field of the file \"" << name
                << "\" can not contain empty samplers list" << std::endl;
      return nullptr;
    }
  tmp->m_samplers = samplers;

  return tmp;
}

}
