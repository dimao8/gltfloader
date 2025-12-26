#ifndef NODE_H
#define NODE_H

#include "gltfnamedobject.h"
#include "indexhelper.h"

#include <array>
#include <memory>
#include <optional>
#include <vector>

namespace gltfloader
{

class GLTFNode : public GLTFNamedObject
{
private:
  std::optional<size_t> m_camera;
  std::vector<size_t> m_children;
  std::optional<size_t> m_skin;
  std::array<float, 16> m_matrix;
  std::optional<size_t> m_mesh;
  std::array<float, 4> m_rotation;
  std::array<float, 3> m_scale;
  std::array<float, 3> m_translation;
  std::vector<float> m_weights;

  GLTFNode (const std::string &name);

public:
  GLTFNode () = delete;
  GLTFNode (const GLTFNode &) = delete;
  virtual ~GLTFNode ();

  const std::optional<size_t> &camera () const;
  const std::vector<size_t> &children () const;
  const std::optional<size_t> &skin () const;
  const std::array<float, 16> &matrix () const;
  const std::optional<size_t> &mesh () const;
  const std::array<float, 4> &rotation () const;
  const std::array<float, 3> &scale () const;
  const std::array<float, 3> &translation () const;
  const std::vector<float> &weights () const;

  static std::shared_ptr<GLTFNode>
  create (IndexHelper &helper, const std::string &name,
          const std::optional<int> &camera, const std::vector<int> &children,
          const std::optional<int> &skin,
          const std::optional<std::array<float, 16> > &matrix,
          const std::optional<int> &mesh,
          const std::optional<std::array<float, 4> > &rotation,
          const std::optional<std::array<float, 3> > &scale,
          const std::optional<std::array<float, 3> > &translation,
          const std::vector<float> &weights);
};

}

#endif // NODE_H