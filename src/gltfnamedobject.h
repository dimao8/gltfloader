#ifndef GLTFNAMEDOBJECT_H
#define GLTFNAMEDOBJECT_H

#include "gltfobject.h"

#include <string>

namespace gltfloader
{

class GLTFNamedObject : public GLTFObject
{
private:
  std::string m_name;

  void generate_name ();

public:
  GLTFNamedObject ();
  GLTFNamedObject (const std::string &name);
  virtual ~GLTFNamedObject () {}

  const std::string &name () const;
};

}

#endif // GLTFNAMEDOBJECT_H
