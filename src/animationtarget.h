#ifndef ANIMATIONTARGET_H
#define ANIMATIONTARGET_H

#include "gltfobject.h"
#include "indexhelper.h"
#include "gltftypes.h"

#include <memory>
#include <optional>
#include <string>

namespace gltfloader
{

class GLTFNode;

class GLTFAnimationTarget : public GLTFObject
{
private:
  std::optional<size_t> m_node;
  GLTFAnimationPath m_path;

  GLTFAnimationTarget ();

public:
  GLTFAnimationTarget (const GLTFAnimationTarget &) = delete;
  virtual ~GLTFAnimationTarget () {}

  const std::optional<size_t> &node () const;
  GLTFAnimationPath path () const;

  static std::shared_ptr<GLTFAnimationTarget>
  create (const IndexHelper &helper, const std::optional<int> &node,
          const std::string &path);
};

bool operator== (const GLTFAnimationTarget &t1, const GLTFAnimationTarget &t2);
bool operator!= (const GLTFAnimationTarget &t1, const GLTFAnimationTarget &t2);

}

#endif // ANIMATIONTARGET_H
