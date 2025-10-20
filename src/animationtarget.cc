#include "animationtarget.h"
#include "gltfobject.h"

#include <iostream>

namespace gltfloader
{

/* **************** GLTFAnimationTarget::GLTFAnimationTarget *************** */

GLTFAnimationTarget::GLTFAnimationTarget () : GLTFObject ()
{
  //
}

/* ********************** GLTFAnimationTarget::create ********************** */

std::shared_ptr<GLTFAnimationTarget>
GLTFAnimationTarget::create (const std::shared_ptr<GLTFNode> &node,
                             const std::string &path)
{
  std::shared_ptr<GLTFAnimationTarget> tmp (new GLTFAnimationTarget ());

  if (!node)
    {
      std::cout
          << "[W] glTF 2.0: The Animation target field must contain valid node"
          << std::endl;
      return nullptr;
    }
  tmp->m_node = node;

  if (path == "translation")
    tmp->m_path = GLTFAnimationPath::translation;
  else if (path == "rotation")
    tmp->m_path = GLTFAnimationPath::rotation;
  else if (path == "scale")
    tmp->m_path = GLTFAnimationPath::scale;
  else if (path == "weights")
    tmp->m_path = GLTFAnimationPath::weights;
  else
    {
      std::cout << "[W] glTF 2.0: The Path field in animation targets must "
                   "contain one of the following values: \"translation\", "
                   "\"rotation\", \"scale\" or \"weights\""
                << std::endl;
      return nullptr;
    }

  return tmp;
}

}