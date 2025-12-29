#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "gltfobject.h"
#include "gltftypes.h"
#include "indexhelper.h"
#include "primitivetarget.h"

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
public:
  using GLTFPrimitiveTargetList
      = std::vector<std::shared_ptr<GLTFPrimitiveTarget> >;

private:
  std::optional<size_t> m_position;  /// Index of the position accessor
  std::optional<size_t> m_normal;    /// Index of the normal accessor
  std::optional<size_t> m_tangent;   /// Index of the tangent accessor
  std::vector<size_t> m_texcoords;   /// Array of the texcoord accessor indices
  std::vector<size_t> m_colors;      /// Array of the color accessor indices
  std::vector<size_t> m_joints;      /// Array of the joint accessor indices
  std::vector<size_t> m_weights;     /// Array of the weight accessor indices
  std::optional<size_t> m_indices;   /// Index of the index accessor
  std::optional<size_t> m_material;  /// Index of the material
  GLTFDrawMode m_mode;               /// Draw mode
  GLTFPrimitiveTargetList m_targets; /// Array of the targets

  GLTFPrimitive ();

public:
  using GLTFAttributeList = std::map<std::string, int>;

  GLTFPrimitive (const GLTFPrimitive &) = delete;
  virtual ~GLTFPrimitive ();

  const std::optional<size_t> &position () const;
  const std::optional<size_t> &normal () const;
  const std::optional<size_t> &tangent () const;
  const std::vector<size_t> &texcoords () const;
  const std::vector<size_t> &colors () const;
  const std::vector<size_t> &joints () const;
  const std::vector<size_t> &weights () const;
  const std::optional<size_t> &indices () const;
  const std::optional<size_t> &material () const;
  GLTFDrawMode mode () const;
  const GLTFPrimitiveTargetList &targets () const;

  static std::shared_ptr<GLTFPrimitive>
  create (IndexHelper &helper, const GLTFAttributeList &attributes,
          const std::optional<int> &indices,
          const std::optional<int> &material, const std::optional<int> &mode,
          const GLTFPrimitiveTargetList &targets);
};

}

#endif // PRIMITIVE_H
