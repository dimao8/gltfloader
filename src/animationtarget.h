#ifndef ANIMATIONTARGET_H
#define ANIMATIONTARGET_H

#include "gltfobject.h"

#include <memory>
#include <string>

namespace gltfloader
{

class GLTFNode;

enum GLTFAnimationPath
{
  translation,
  rotation,
  scale,
  weights
};

class GLTFAnimationTarget : public GLTFObject
{
private:
  std::shared_ptr<GLTFNode> m_node;
  GLTFAnimationPath m_path;

  GLTFAnimationTarget ();

public:
  GLTFAnimationTarget (const GLTFAnimationTarget &) = delete;
  virtual ~GLTFAnimationTarget () {}

  static std::shared_ptr<GLTFAnimationTarget>
  create (const std::shared_ptr<GLTFNode> &node, const std::string &path);
};

}

#endif // ANIMATIONTARGET_H
