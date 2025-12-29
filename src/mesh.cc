#include "mesh.h"
#include "primitive.h"

#include <iostream>

namespace gltfloader
{

/* *************************** GLTFMesh::GLTFMesh ************************** */

GLTFMesh::GLTFMesh (const std::string &name)
    : GLTFNamedObject (name), m_primitives (), m_weights ()
{
  //
}

/* ************************** GLTFMesh::~GLTFMesh ************************** */

GLTFMesh::~GLTFMesh ()
{
  //
}

/* ************************** GLTFMesh::primitives ************************* */

const std::vector<std::shared_ptr<GLTFPrimitive> > &
GLTFMesh::primitives () const
{
  return m_primitives;
}

/* *************************** GLTFMesh::weights *************************** */

const std::vector<float> &
GLTFMesh::weights () const
{
  return m_weights;
}

/* **************************** GLTFMesh::create *************************** */

std::shared_ptr<GLTFMesh>
GLTFMesh::create (
    IndexHelper &helper, const std::string &name,
    const std::vector<std::shared_ptr<GLTFPrimitive> > &primitives,
    const std::vector<float> &weights)
{
  std::shared_ptr<GLTFMesh> tmp (new GLTFMesh (name));

  if (primitives.empty ())
    {
      std::cout << "[W] glTF 2.0: Mesh object can not be empty" << std::endl;
      return nullptr;
    }
  tmp->m_primitives = primitives;

  if (!weights.empty ())
    {
      for (auto it : primitives)
        {
          if (it->targets ().size () != weights.size ())
            {
              std::cout << "[W] glTF 2.0: Mesh object weights size "
                           "does not match the number of targets"
                        << std::endl;
              return nullptr;
            }
        }

      tmp->m_weights = weights;
    }

  return tmp;
}

}