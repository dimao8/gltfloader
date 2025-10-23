#include "primitive.h"

#include <iostream>

namespace gltfloader
{

/* ********************** GLTFPrimitive::GLTFPrimitive ********************* */

GLTFPrimitive::GLTFPrimitive () : GLTFObject ()
{
  //
}

/* ************************* GLTFPrimitive::create ************************* */

std::shared_ptr<GLTFPrimitive>
GLTFPrimitive::create (const GLTFAttributeList &attributes, int index,
                       int material, const std::string &mode,
                       const GLTFAttributeList &targets)
{
  std::shared_ptr<GLTFPrimitive> tmp (new GLTFPrimitive ());

  if (attributes.empty ())
    {
      std::cout << "[W] glTF 2.0: Mesh object must have at least one "
                   "attribute: \"POSITION\""
                << std::endl;
      return nullptr;
    }
  for (auto it : attributes)
    {
      if (it.first == "POSITION")
        {
          tmp->m_position
        }
    }

  return tmp;
}

}
