#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "gltfobject.h"
#include "gltftypes.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

// TODO : Redo indexed objects

namespace gltfloader
{

class GLTFAccessor;

class GLTFPrimitive : public GLTFObject
{
private:
  std::shared_ptr<GLTFAccessor> m_position;
  std::shared_ptr<GLTFAccessor> m_normal;
  std::shared_ptr<GLTFAccessor> m_tangent;
  std::vector<std::shared_ptr<GLTFAccessor> > m_texcoords;
  std::vector<std::shared_ptr<GLTFAccessor> > m_colors;
  std::vector<std::shared_ptr<GLTFAccessor> > m_joints;
  std::vector<std::shared_ptr<GLTFAccessor> > m_weights;
  int m_index;
  int m_material;
  GLTFDrawMode m_mode;
  std::shared_ptr<GLTFAccessor> m_position_target;
  std::shared_ptr<GLTFAccessor> m_normal_target;
  std::shared_ptr<GLTFAccessor> m_tangent_target;
  std::vector<std::shared_ptr<GLTFAccessor> > m_texcoord_targets;
  std::vector<std::shared_ptr<GLTFAccessor> > m_color_targets;
  std::vector<std::shared_ptr<GLTFAccessor> > m_joint_targets;
  std::vector<std::shared_ptr<GLTFAccessor> > m_weight_targets;

  GLTFPrimitive ();

public:
  using GLTFAttributeList = std::map<std::string, int>;

  GLTFPrimitive (const GLTFPrimitive &) = delete;
  virtual ~GLTFPrimitive () {}

  static std::shared_ptr<GLTFPrimitive>
  create (const GLTFAttributeList &attributes, int index, int material,
          const std::string &mode, const GLTFAttributeList &targets);
};

}

#endif // PRIMITIVE_H
