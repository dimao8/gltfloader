#include "gltfnamedobject.h"

#include <uuid/uuid.h>

namespace gltfloader
{

/* ******************** GLTFNamedObject::GLTFNamedObject ******************* */

GLTFNamedObject::GLTFNamedObject () { generate_name (); }

/* ******************** GLTFNamedObject::GLTFNamedObject ******************* */

GLTFNamedObject::GLTFNamedObject (const std::string &name)
{
  if (name.empty ())
    generate_name ();
  else
    m_name = name;
}

/* ********************* GLTFNamedObject::generate_name ******************** */

void
GLTFNamedObject::generate_name ()
{
  uuid_t uuid;

  uuid_generate_time (uuid);
  m_name.resize (37);
  uuid_unparse_lower (uuid, &(m_name[0]));
}

/* ************************* GLTFNamedObject::name ************************* */

const std::string &
GLTFNamedObject::name () const
{
  return m_name;
}

}