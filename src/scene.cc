#include "scene.h"
#include "gltfnamedobject.h"

#include <iostream>

namespace gltfloader
{

/* ************************** GLTFScene::GLTFScene ************************* */

GLTFScene::GLTFScene (const std::string &name)
    : GLTFNamedObject (name), m_nodes ()
{
  //
}

/* ************************* GLTFScene::~GLTFScene ************************* */

GLTFScene::~GLTFScene ()
{
  //
}

/* ************************* GLTFScene::has_unique ************************* */

bool
GLTFScene::is_unique (const std::vector<int> &nodes, size_t i)
{
  if (i >= nodes.size ())
    return true;

  size_t count = 0;

  for (auto it : nodes)
    {
      if (nodes[i] == it)
        {
          count++;
        }
    }

  return count <= 1;
}

/* **************************** GLTFScene::nodes *************************** */

const std::vector<size_t> &
GLTFScene::nodes () const
{
  return m_nodes;
}

/* *************************** GLTFScene::create *************************** */

std::shared_ptr<GLTFScene>
GLTFScene::create (IndexHelper &helper, const std::string &name,
                   const std::vector<int> &nodes)
{
  std::shared_ptr<GLTFScene> tmp (new GLTFScene (name));

  if (nodes.empty ())
    {
      std::cout << "[W] glTF 2.0 5.27.1 scene must contain at least one node"
                << std::endl;
      return nullptr;
    }

  size_t shifted_node_index;

  for (size_t i = 0; i < nodes.size (); i++)
    {
      shifted_node_index = nodes[i] + helper.node_defaults_size ();
      if (nodes[i] < 0)
        {
          std::cout << "[W] glTF 2.0 5.27.1 scene must contain only positive "
                       "node indices"
                    << std::endl;
          return nullptr;
        }
      else if (shifted_node_index >= helper.nodes_size ())
        {
          std::cout << "[W] glTF 2.0 5.27.1 scene.node is out of bounds"
                    << std::endl;
          return nullptr;
        }

      if (!GLTFScene::is_unique (nodes, i))
        {
          std::cout
              << "[W] glTF 2.0 5.27.1 scene must contain only unique nodes"
              << std::endl;
          return nullptr;
        }

      tmp->m_nodes.push_back (shifted_node_index);
    }

  return tmp;
}

}