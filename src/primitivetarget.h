#ifndef PRIMITIVETARGET_H
#define PRIMITIVETARGET_H

#include <map>
#include <optional>
#include <string>
#include <vector>

#include "indexhelper.h"

namespace gltfloader
{

class GLTFPrimitiveTarget
{
private:
  std::optional<size_t>
      m_position_target;                 /// Index of the morph position target
  std::optional<size_t> m_normal_target; /// Index of the morph normal target
  std::optional<size_t> m_tangent_target; /// Index of the morph tangent target
  std::vector<size_t>
      m_texcoord_targets;              /// Array of the morph texcoord targets
  std::vector<size_t> m_color_targets; /// Array of the morph color targets

  void cleanup ();

public:
  using GLTFTargetAttributeList = std::map<std::string, int>;

  GLTFPrimitiveTarget () = delete;
  GLTFPrimitiveTarget (const GLTFPrimitiveTarget &) = delete;
  GLTFPrimitiveTarget (IndexHelper &helper,
                       const GLTFTargetAttributeList &target_attributes);
  ~GLTFPrimitiveTarget ();

  const std::optional<size_t> &position_target () const;
  const std::optional<size_t> &normal_target () const;
  const std::optional<size_t> &tangent_target () const;
  const std::vector<size_t> &texcoord_targets () const;
  const std::vector<size_t> &color_targets () const;

  bool is_empty () const;
};

}

#endif // PRIMITIVETARGET_H