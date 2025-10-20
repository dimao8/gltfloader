#include "perspectivecamera.h"

#include <iostream>
#include <optional>

namespace gltfloader
{

template <typename T> const T pi = T (3.1415926535897932384626434);

/* ************** GLTFPerspectiveCamera::GLTFPerspectiveCamera ************* */

GLTFPerspectiveCamera::GLTFPerspectiveCamera () : GLTFObject ()
{
  //
}

/* ****************** GLTFPerspectiveCamera::aspect_ratio ****************** */

std::optional<float>
GLTFPerspectiveCamera::aspect_ratio () const
{
  return m_aspect_ratio;
}

/* ********************** GLTFPerspectiveCamera::yfov ********************** */

float
GLTFPerspectiveCamera::yfov () const
{
  return m_yfov;
}

/* ********************** GLTFPerspectiveCamera::zfar ********************** */

float
GLTFPerspectiveCamera::zfar () const
{
  return m_zfar;
}

/* ********************** GLTFPerspectiveCamera::znear ********************* */

float
GLTFPerspectiveCamera::znear () const
{
  return m_znear;
}

/* ********************* GLTFPerspectiveCamera::create ********************* */

std::shared_ptr<GLTFPerspectiveCamera>
GLTFPerspectiveCamera::create (float yfov, float zfar, float znear,
                               std::optional<float> aspect_ratio)
{
  std::shared_ptr<GLTFPerspectiveCamera> tmp (new GLTFPerspectiveCamera ());

  if (aspect_ratio.has_value ())
    {
      if (aspect_ratio.value () <= 0)
        {
          std::cout << "[W] glTF 2.0: aspectRatio field in camera.perspective "
                       "must be positive"
                    << std::endl;
          return nullptr;
        }
    }
  tmp->m_aspect_ratio = aspect_ratio;

  if (yfov <= 0)
    {
      std::cout
          << "[W] glTF 2.0: yfov field in camera.perspective must be positive"
          << std::endl;
      return nullptr;
    }
  else
    {
      if (yfov > pi<float>)
        std::cout << "[I] glTF 2.0: yfov field in camera.perspective should "
                     "be less than Pi"
                  << std::endl;
      tmp->m_yfov = yfov;
    }

  if (znear <= 0.0f)
    {
      std::cout << "[W] glTF 2.0: znear field in camera.perspective can not "
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