#include "animationtarget.h"
#include "gltfobject.h"

#include <iostream>
#include <optional>

namespace gltfloader
{

/* **************** GLTFAnimationTarget::GLTFAnimationTarget *************** */

GLTFAnimationTarget::GLTFAnimationTarget () : GLTFObject ()
{
  //
}

/* ********************** GLTFAnimationTarget::create ********************** */

std::shared_ptr<GLTFAnimationTarget>
GLTFAnimationTarget::create (const IndexHelper &helper,
                             const std::optional<int> &node,
                             const std::string &path)
{
  std::shared_ptr<GLTFAnimationTarget> tmp (new GLTFAnimationTarget ());

  if (node == std::nullopt)
    {
      // glTF 2.0 5.7.1 Extension must be used
      // TODO : Check for extension
    }
  else if (node < 0)
    {
      std::cout << "[W] glTF 2.0 5.7.1: animation.channel[n].target.node >= 0"
                << std::endl;
      return nullptr;
    }
  else if (node.value() + helper.node_defaults_size() >= helper.nodes_size ())
    {
      std::cout << "[W] glTF 2.0 5.7.1: animation.channel[n].target.node is "
                   "out of range"
                << std::endl;
      return nullptr;
    }
  tmp->m_node = node.value () + helper.node_defaults_size ();

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
      std::cout
          << "[W] glTF 2.0 5.7.2: animation.channels[n].target.path can only "
             "be \"translation\", \"rotation\", \"scale\" or \"weights\""
          << std::endl;
      return nullptr;
    }

  return tmp;
}

/* *********************** GLTFAnimationTarget::node *********************** */

const std::optional<size_t> &
GLTFAnimationTarget::node () const
{
  return m_node;
}

/* *********************** GLTFAnimationTarget::path *********************** */

GLTFAnimationPath
GLTFAnimationTarget::path () const
{
  return m_path;
}

/* ******************************* operator== ****************************** */

bool
operator== (const GLTFAnimationTarget &t1, const GLTFAnimationTarget &t2)
{
  return (t1.node () == t2.node ()) && (t1.path () == t2.path ());
}

/* ******************************* operator!= ****************************** */

bool
operator!= (const GLTFAnimationTarget &t1, const GLTFAnimationTarget &t2)
{
  return (t1.node () != t2.node ()) || (t1.path () != t2.path ());
}

}