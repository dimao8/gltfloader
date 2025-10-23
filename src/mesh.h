#ifndef MESH_H
#define MESH_H

#include "gltfnamedobject.h"

#include <memory>
#include <vector>

namespace gltfloader
{

class GLTFPrimitive;

class GLTFMesh : public GLTFNamedObject
{
private:
  std::vector<std::shared_ptr<GLTFPrimitive> > m_primitives;
  std::vector<float> m_weights;

  GLTFMesh (const std::string &name);

public:
  GLTFMesh () = delete;
  GLTFMesh (const GLTFMesh &) = delete;
  virtual ~GLTFMesh () {}

  const std::vector<std::shared_ptr<GLTFPrimitive> > &primitives () const;
  const std::vector<float> &weights () const;

  static std::shared_ptr<GLTFMesh>
  create (const std::string &name,
          const std::vector<std::shared_ptr<GLTFPrimitive> > &primitives,
          const std::vector<float> &weights);
};

}

#endif // MESH_H
