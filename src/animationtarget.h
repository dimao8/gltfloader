#ifndef ANIMATIONTARGET_H
#define ANIMATIONTARGET_H

#include "gltfobject.h"
#include "indexhelper.h"

#include <memory>
#include <string>

namespace gltfloader
{

class GLTFNode;

enum class GLTFAnimationPath
{
  translation,
  rotation,
  scale,
  weights
};

class GLTFAnimationTarget : public GLTFObject
{
private:
  size_t m_node;
  GLTFAnimationPath m_path;

  GLTFAnimationTarget ();

public:
  GLTFAnimationTarget (const GLTFAnimationTarget &) = delete;
  virtual ~GLTFAnimationTarget () {}

  size_t node () const;
  GLTFAnimationPath path () const;

  static std::shared_ptr<GLTFAnimationTarget>
  create (const IndexHelper &helper, int node, const std::string &path);
};

bool operator== (const GLTFAnimationTarget &t1, const GLTFAnimationTarget &t2);

}

#endif // ANIMATIONTARGET_H
