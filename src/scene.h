#ifndef SCENE_H
#define SCENE_H

#include "gltfnamedobject.h"
#include "indexhelper.h"

#include <cstddef>
#include <vector>

namespace gltfloader
{

class GLTFScene : public GLTFNamedObject
{
private:
  std::vector<size_t> m_nodes;

  GLTFScene (const std::string &name);
  static bool is_unique (const std::vector<int> &nodes, size_t i);

public:
  GLTFScene () = delete;
  GLTFScene (const GLTFScene &) = delete;
  virtual ~GLTFScene ();

  const std::vector<size_t> &nodes () const;

  static std::shared_ptr<GLTFScene> create (IndexHelper &helper,
                                            const std::string &name,
                                            const std::vector<int> &nodes);
};

}

#endif // SCENE_H