#ifndef SKIN_H
#define SKIN_H

#include "gltfnamedobject.h"
#include "indexhelper.h"

#include <memory>
#include <optional>
#include <vector>

namespace gltfloader
{

class GLTFSkin : public GLTFNamedObject
{
private:
  std::optional<size_t> m_inverse_bind_matrices;
  std::optional<size_t> m_skeleton;
  std::vector<size_t> m_joints;
  GLTFSkin (const std::string &name);

public:
  GLTFSkin () = delete;
  GLTFSkin (const GLTFSkin &) = delete;
  virtual ~GLTFSkin ();

  const std::optional<size_t> &inverse_bind_matrices () const;
  const std::optional<size_t> &skeleton () const;
  const std::vector<size_t> &joints () const;

  static std::shared_ptr<GLTFSkin>
  create (const IndexHelper &helper, const std::string &name,
          const std::optional<int> &inverse_bind_matrices,
          const std::optional<int> &skeleton, const std::vector<int> &joints);
};

}

#endif // SKIN_H