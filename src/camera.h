#ifndef CAMERA_H
#define CAMERA_H

#include "gltfnamedobject.h"

#include <memory>
#include <string>

namespace gltfloader
{

class GLTFOrthographicCamera;
class GLTFPerspectiveCamera;

enum GLTFCameraType
{
  orthographic,
  perspective
};

class GLTFCamera : public GLTFNamedObject
{
private:
  std::shared_ptr<GLTFOrthographicCamera> m_orthographic;
  std::shared_ptr<GLTFPerspectiveCamera> m_perspective;
  GLTFCameraType m_type;

  GLTFCamera (const std::string &name);

public:
  GLTFCamera () = delete;
  GLTFCamera (const GLTFCamera &) = delete;
  virtual ~GLTFCamera () {}

  GLTFCameraType type () const;
  const std::shared_ptr<GLTFOrthographicCamera> &orthographic () const;
  const std::shared_ptr<GLTFPerspectiveCamera> &perspective () const;

  static std::shared_ptr<GLTFCamera>
  create (const std::string &name, const std::string &type,
          const std::shared_ptr<GLTFOrthographicCamera> &orthographic,
          const std::shared_ptr<GLTFPerspectiveCamera> &perspective);
};

}

#endif // CAMERA_H
