#include "camera.h"

#include <iostream>

namespace gltfloader
{

/* ************************* GLTFCamera::GLTFCamera ************************ */

GLTFCamera::GLTFCamera (const std::string &name) : GLTFNamedObject (name)
{
  //
}

/* **************************** GLTFCamera::type *************************** */

GLTFCameraType
GLTFCamera::type () const
{
  return m_type;
}

/* ************************ GLTFCamera::orthographic *********************** */

const std::shared_ptr<GLTFOrthographicCamera> &
GLTFCamera::orthographic () const
{
  return m_orthographic;
}

/* ************************ GLTFCamera::perspective ************************ */

const std::shared_ptr<GLTFPerspectiveCamera> &
GLTFCamera::perspective () const
{
  return m_perspective;
}

/* *************************** GLTFCamera::create ************************** */

std::shared_ptr<GLTFCamera>
GLTFCamera::create (
    const std::string &name, const std::string &type,
    const std::shared_ptr<GLTFOrthographicCamera> &orthographic,
    const std::shared_ptr<GLTFPerspectiveCamera> &perspective)
{
  std::shared_ptr<GLTFCamera> tmp (new GLTFCamera (name));

  if (type == "perspective")
    {
      if (!perspective)
        {
          std::cout << "[W] glTF 2.0: The perspective field in \"" << name
                    << "\" is missing, but type is set to \"perspective\""
                    << std::endl;
          return nullptr;
        }
      if (orthographic)
        {
          std::cout << "[W] glTF 2.0: The orthographic field in \"" << name
                    << "\" is present, but type is set to \"perspective\""
                    << std::endl;
          return nullptr;
        }

      tmp->m_perspective = perspective;
    }
  else if (type == "orthographic")
    {
      if (!orthographic)
        {
          std::cout << "[W] glTF 2.0: The orthographic field in \"" << name
                    << "\" is missing, but type is set to \"orthographic\""
                    << std::endl;
          return nullptr;
        }
      if (perspective)
        {
          std::cout << "[W] glTF 2.0: The perspective field in \"" << name
                    << "\" is present, but type is set to \"orthographic\""
                    << std::endl;
          return nullptr;
        }

      tmp->m_orthographic = orthographic;
    }

  return tmp;
}

}
