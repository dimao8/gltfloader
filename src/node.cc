#include "node.h"
#include "gltffunc.h"

#include <iostream>

namespace gltfloader
{

/* *************************** GLTFNode::GLTFNode ************************** */

GLTFNode::GLTFNode (const std::string &name)
    : GLTFNamedObject (name), m_camera (std::nullopt), m_children (),
      m_skin (std::nullopt),
      m_matrix ({ 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0, 1.0 }),
      m_mesh (std::nullopt), m_rotation ({ 0.0, 0.0, 0.0, 1.0 }),
      m_scale ({ 1.0, 1.0, 1.0 }), m_translation ({ 0.0, 0.0, 0.0 }),
      m_weights ()
{
  //
}

/* ************************** GLTFNode::~GLTFNode ************************** */

GLTFNode::~GLTFNode ()
{
  //
}

/* **************************** GLTFNode::camera *************************** */

const std::optional<size_t> &
GLTFNode::camera () const
{
  return m_camera;
}

/* *************************** GLTFNode::children ************************** */

const std::vector<size_t> &
GLTFNode::children () const
{
  return m_children;
}

/* ***************************** GLTFNode::skin **************************** */

const std::optional<size_t> &
GLTFNode::skin () const
{
  return m_skin;
}

/* **************************** GLTFNode::matrix *************************** */

const std::array<float, 16> &
GLTFNode::matrix () const
{
  return m_matrix;
}

/* ***************************** GLTFNode::mesh **************************** */

const std::optional<size_t> &
GLTFNode::mesh () const
{
  return m_mesh;
}

/* *************************** GLTFNode::rotation ************************** */

const std::array<float, 4> &
GLTFNode::rotation () const
{
  return m_rotation;
}

/* **************************** GLTFNode::scale **************************** */

const std::array<float, 3> &
GLTFNode::scale () const
{
  return m_scale;
}

/* ************************* GLTFNode::translation ************************* */

const std::array<float, 3> &
GLTFNode::translation () const
{
  return m_translation;
}

/* *************************** GLTFNode::weights *************************** */

const std::vector<float> &
GLTFNode::weights () const
{
  return m_weights;
}

/* **************************** GLTFNode::create *************************** */

std::shared_ptr<GLTFNode>
GLTFNode::create (IndexHelper &helper, const std::string &name,
                  const std::optional<int> &camera,
                  const std::vector<int> &children,
                  const std::optional<int> &skin,
                  const std::optional<std::array<float, 16> > &matrix,
                  const std::optional<int> &mesh,
                  const std::optional<std::array<float, 4> > &rotation,
                  const std::optional<std::array<float, 3> > &scale,
                  const std::optional<std::array<float, 3> > &translation,
                  const std::vector<float> &weights)
{
  std::shared_ptr<GLTFNode> tmp (new GLTFNode (name));

  size_t shifted_index;

  if (camera == std::nullopt)
    tmp->m_camera = std::nullopt;
  else
    {
      shifted_index = camera.value () + helper.camera_defaults_size ();
      if (camera.value () < 0)
        {
          std::cout << "[W] glTF 2.0 5.25.1: node.camera >= 0" << std::endl;
          return nullptr;
        }
      else if (shifted_index >= helper.cameras_size ())
        {
          std::cout << "[W] glTF 2.0 5.25.1: node.camera is out of bounds"
                    << std::endl;
          return nullptr;
        }

      tmp->m_camera = shifted_index;
    }

  if (!children.empty ())
    {
      for (size_t i = 0; i < children.size (); i++)
        {
          if (children[i] < 0)
            {
              std::cout << "[W] glTF 2.0 5.25.2: node.children >= 0"
                        << std::endl;
              return nullptr;
            }
          shifted_index = children[i] + helper.node_defaults_size ();
          if (shifted_index >= helper.nodes_size ())
            {
              if (i == 0)
                {
                  std::cout << "[W] glTF 2.0 5.25.2: node.children is out of "
                               "bounds"
                            << std::endl;
                  return nullptr;
                }
            }
          if (!is_unique (children, i))
            {
              std::cout << "[W] glTF 2.0 5.25.2: node.children must be "
                           "unique"
                        << std::endl;
              return nullptr;
            }

          tmp->m_children.push_back (shifted_index);
        }
    }

  if (skin == std::nullopt)
    tmp->m_skin = std::nullopt;
  else
    {
      shifted_index = skin.value () + helper.skin_defaults_size ();
      if (skin.value () < 0)
        {
          std::cout << "[W] glTF 2.0 5.25.3: node.skin >= 0" << std::endl;
          return nullptr;
        }
      else if (shifted_index >= helper.skins_size ())
        {
          std::cout << "[W] glTF 2.0 5.25.3: node.skin is out of bounds"
                    << std::endl;
          return nullptr;
        }

      if (tmp->m_mesh == std::nullopt)
        {
          std::cout << "[W] glTF 2.0 5.25.3: node.skin is not supported for "
                       "meshless nodes"
                    << std::endl;
          return nullptr;
        }

      tmp->m_skin = shifted_index;
    }

  tmp->m_matrix = matrix.value_or (
      std::array<float, 16> ({ 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
                               0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 }));

  if (mesh == std::nullopt)
    tmp->m_mesh = std::nullopt;
  else
    {
      shifted_index = mesh.value () + helper.mesh_defaults_size ();
      if (mesh.value () < 0)
        {
          std::cout << "[W] glTF 2.0 5.25.5: node.mesh >= 0" << std::endl;
          return nullptr;
        }
      else if (shifted_index >= helper.meshes_size ())
        {
          std::cout << "[W] glTF 2.0 5.25.1: node.mesh is out of bounds"
                    << std::endl;
          return nullptr;
        }

      tmp->m_mesh = shifted_index;
    }

  tmp->m_rotation
      = rotation.value_or (std::array<float, 4> ({ 0.0, 0.0, 0.0, 1.0 }));

  tmp->m_scale = scale.value_or (std::array<float, 3> ({ 1.0, 1.0, 1.0 }));

  tmp->m_translation
      = translation.value_or (std::array<float, 3> ({ 0.0, 0.0, 0.0 }));

  if (!weights.empty ())
    {
      // TODO : Check for morph targets
      if (tmp->m_mesh == std::nullopt)
        {
          std::cout << "[W] glTF 2.0 5.25.9: node.weights is not supported "
                       "for meshless nodes"
                    << std::endl;
          return nullptr;
        }

      tmp->m_weights.assign (weights.begin (), weights.end ());
    }

  return tmp;
}
}