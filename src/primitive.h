#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "gltfobject.h"
#include "gltftypes.h"
#include "indexhelper.h"

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

// TODO : Redo indexed objects

namespace gltfloader
{

class GLTFAccessor;

class GLTFPrimitive : public GLTFObject
{
private:
  std::optional<size_t> m_position; /// Index of the position accessor
  std::optional<size_t> m_normal;   /// Index of the normal accessor
  std::optional<size_t> m_tangent;  /// Index of the tangent accessor
  std::vector<size_t> m_texcoords;  /// Array of the texcoord accessor indices
  std::vector<size_t> m_colors;     /// Array of the color accessor indices
  std::vector<size_t> m_joints;     /// Array of the joint accessor indices
  std::vector<size_t> m_weights;    /// Array of the weight accessor indices
  std::optional<size_t> m_indices;    /// Index of the index accessor
  std::optional<size_t> m_material; /// Index of the material
  GLTFDrawMode m_mode;              /// Draw mode
  std::optional<size_t>
      m_position_target;                 /// Index of the morph position target
  std::optional<size_t> m_normal_target; /// Index of the morph normal target
  std::optional<size_t> m_tangent_target; /// Index of the morph tangent target
  std::vector<size_t>
      m_texcoord_targets;               /// Array of the morph texcoord targets
  std::vector<size_t> m_color_targets;  /// Array of the morph color targets
  std::vector<size_t> m_joint_targets;  /// Array of the morph joint targets
  std::vector<size_t> m_weight_targets; /// Array of the morph weight targets

  GLTFPrimitive ();

public:
  using GLTFAttributeList = std::map<std::string, int>;

  GLTFPrimitive (const GLTFPrimitive &) = delete;
  virtual ~GLTFPrimitive () {}

  static std::shared_ptr<GLTFPrimitive>
  create (IndexHelper &helper, const GLTFAttributeList &attributes,
          const std::optional<int> &indices, const std::optional<int> &material,
          const std::optional<int> &mode, const GLTFAttributeList &targets);
};

}

#endif // PRIMITIVE_H
