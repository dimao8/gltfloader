#include "orthographiccamera.h"

#include <iostream>

namespace gltfloader
{

/* ************* GLTFOrthographicCamera::GLTFOrthographicCamera ************ */

GLTFOrthographicCamera::GLTFOrthographicCamera () : GLTFObject ()
{
  //
}

/* ********************** GLTFOrthographicCamera::xmag ********************* */

float
GLTFOrthographicCamera::xmag () const
{
  return m_xmag;
}

/* ********************** GLTFOrthographicCamera::ymag ********************* */

float
GLTFOrthographicCamera::ymag () const
{
  return m_ymag;
}

/* ********************** GLTFOrthographicCamera::zfar ********************* */

float
GLTFOrthographicCamera::zfar () const
{
  return m_zfar;
}

/* ********************* GLTFOrthographicCamera::znear ********************* */

float
GLTFOrthographicCamera::znear () const
{
  return m_znear;
}

/* ********************* GLTFOrthographicCamera::create ******************** */

std::shared_ptr<GLTFOrthographicCamera>
GLTFOrthographicCamera::create (float xmag, float ymag, float zfar,
                                float znear)
{
  std::shared_ptr<GLTFOrthographicCamera> tmp (new GLTFOrthographicCamera ());

  if (xmag == 0)
    {
      std::cout << "[W] glTF 2.0: xmag field in camera.orthographic can not "
                   "be equal to zero"
                << std::endl;
      return nullptr;
    }
  else
    {
      if (xmag < 0.0f)
        std::cout << "[I] glTF 2.0: xmag field in camera.orthographic should "
                     "not be negative"
                  << std::endl;
      tmp->m_xmag = xmag;
    }

  if (ymag == 0)
    {
      std::cout << "[W] glTF 2.0: ymag field in camera.orthographic can not "
                   "be equal to zero"
                << std::endl;
      return nullptr;
    }
  else
    {
      if (ymag < 0.0f)
        std::cout << "[W] glTF 2.0: ymag field in camera.orthographic should "
                     "not be negative"
                  << std::endl;
      tmp->m_ymag = ymag;
    }

  if (znear < 0.0f)
    {
      std::cout << "[W] glTF 2.0: znear field in camera.orthographic can not "
                   "be negative"
                << std::endl;
      return nullptr;
    }
  tmp->m_znear = znear;

  if (zfar <= 0.0f)
    {
      std::cout
          << "[W] glTF 2.0: zfar field in camera.orthographic must be positive"
          << std::endl;
      return nullptr;
    }
  if (zfar < znear)
    {
      std::cout << "[W] glTF 2.0: zfar field in camera.orthographic must be "
                   "greater than znear"
                << std::endl;
      return nullptr;
    }
  tmp->m_zfar = zfar;

  return tmp;
}

}