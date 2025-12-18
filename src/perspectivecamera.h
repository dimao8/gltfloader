#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "gltfobject.h"

#include <limits>
#include <memory>
#include <optional>

namespace gltfloader
{

class GLTFPerspectiveCamera : public GLTFObject
{
private:
  std::optional<float> m_aspect_ratio;
  float m_yfov;
  float m_zfar;
  float m_znear;

  GLTFPerspectiveCamera ();

public:
  GLTFPerspectiveCamera (const GLTFPerspectiveCamera &) = delete;
  virtual ~GLTFPerspectiveCamera () {}

  std::optional<float> aspect_ratio () const;
  float yfov () const;
  float zfar () const;
  float znear () const;

  static std::shared_ptr<GLTFPerspectiveCamera>
  create (float yfov, float zfar,
          float znear = std::numeric_limits<float>::infinity (),
          std::optional<float> aspect_ratio = std::nullopt);
};

}

#endif // PERSPECTIVECAMERA_H
