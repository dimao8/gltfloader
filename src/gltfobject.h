#ifndef GLTFOBJECT_H
#define GLTFOBJECT_H

// TODO : extras and extensions

namespace gltfloader
{
class GLTFObject
{
public:
  GLTFObject () = default;
  GLTFObject (const GLTFObject &) = delete;
  virtual ~GLTFObject () {}
};

}

#endif // GLTFOBJECT_H
