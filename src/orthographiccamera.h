#ifndef ORTHOGRAPHICCAMERA_H
#define ORTHOGRAPHICCAMERA_H

#include "gltfobject.h"

#include <memory>

namespace gltfloader
{

class GLTFOrthographicCamera : public GLTFObject
{
private:
  float m_xmag;
  float m_ymag;
  float m_zfar;
  float m_znear;

  GLTFOrthographicCamera ();

public:
  GLTFOrthographicCamera (const GLTFOrthographicCamera &) = delete;
  virtual ~GLTFOrthographicCamera () {}

  float xmag () const;
  float ymag () const;
  float zfar () const;
  float znear () const;

  static std::shared_ptr<GLTFOrthographicCamera>
  create (float xmag, float ymag, float zfar, float znear);
};

}

#endif // ORTHOGRAPHICCAMERA_H
