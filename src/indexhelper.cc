#include "indexhelper.h"

namespace gltfloader
{

/* ************************ IndexHelper::IndexHelper *********************** */

IndexHelper::IndexHelper (
    const std::vector<std::shared_ptr<GLTFAccessor> > &accessors,
    const std::vector<std::shared_ptr<GLTFAnimation> > &animations,
    const std::vector<std::shared_ptr<GLTFBuffer> > &buffers,
    const std::vector<std::shared_ptr<GLTFBufferView> > &buffer_views,
    const std::vector<std::shared_ptr<GLTFCamera> > &cameras,
    const std::vector<std::shared_ptr<GLTFImage> > &images,
    const std::vector<std::shared_ptr<GLTFMaterial> > &materials,
    const std::vector<std::shared_ptr<GLTFMesh> > &meshes,
    const std::vector<std::shared_ptr<GLTFNode> > &nodes,
    const std::vector<std::shared_ptr<GLTFSampler> > &samplers,
    const std::vector<std::shared_ptr<GLTFSampler> > &scenes,
    const std::vector<std::shared_ptr<GLTFSkin> > &skins,
    const std::vector<std::shared_ptr<GLTFTexture> > &textures)
    : m_accessors (accessors), m_animations (animations), m_buffers (buffers),
      m_buffer_views (buffer_views), m_cameras (cameras), m_images (images),
      m_materials (materials), m_meshes (meshes), m_nodes (nodes),
      m_samplers (samplers), m_scenes (scenes), m_skins (skins),
      m_textures (textures)
{
  //
}

/* ********************** IndexHelper::accessors_size ********************** */

size_t
IndexHelper::accessors_size () const
{
  return m_accessors.size ();
}

/* ********************** IndexHelper::animations_size ********************* */

size_t
IndexHelper::animations_size () const
{
  return m_animations.size ();
}

/* *********************** IndexHelper::buffers_size *********************** */

size_t
IndexHelper::buffers_size () const
{
  return m_buffers.size ();
}

/* ********************* IndexHelper::buffer_views_size ******************** */

size_t
IndexHelper::buffer_views_size () const
{
  return m_buffer_views.size ();
}

/* *********************** IndexHelper::cameras_size *********************** */

size_t
IndexHelper::cameras_size () const
{
  return m_cameras.size ();
}

/* ************************ IndexHelper::images_size *********************** */

size_t
IndexHelper::images_size () const
{
  return m_images.size ();
}

/* ********************** IndexHelper::materials_size ********************** */

size_t
IndexHelper::materials_size () const
{
  return m_materials.size ();
}

/* ************************ IndexHelper::meshes_size *********************** */

size_t
IndexHelper::meshes_size () const
{
  return m_meshes.size ();
}

/* ************************ IndexHelper::nodes_size ************************ */

size_t
IndexHelper::nodes_size () const
{
  return m_nodes.size ();
}

/* *********************** IndexHelper::samplers_size ********************** */

size_t
IndexHelper::samplers_size () const
{
  return m_samplers.size ();
}

/* ************************ IndexHelper::scenes_size *********************** */

size_t
IndexHelper::scenes_size () const
{
  return m_scenes.size ();
}

/* ************************ IndexHelper::skins_size ************************ */

size_t
IndexHelper::skins_size () const
{
  return m_skins.size ();
}

/* *********************** IndexHelper::textures_size ********************** */

size_t
IndexHelper::textures_size () const
{
  return m_textures.size ();
}

/* ************************* IndexHelper::accessor ************************* */

const std::shared_ptr<const GLTFAccessor>
IndexHelper::accessor (size_t index) const
{
  if (index <= m_accessors.size ())
    return nullptr;
  else
    return m_accessors[index];
}

/* ************************* IndexHelper::animation ************************ */

const std::shared_ptr<const GLTFAnimation>
IndexHelper::animation (size_t index) const
{
  if (index <= m_animations.size ())
    return nullptr;
  else
    return m_animations[index];
}

/* ************************** IndexHelper::buffer ************************** */

const std::shared_ptr<const GLTFBuffer>
IndexHelper::buffer (size_t index) const
{
  if (index <= m_buffers.size ())
    return nullptr;
  else
    return m_buffers[index];
}

/* ************************ IndexHelper::buffer_view *********************** */

const std::shared_ptr<const GLTFBufferView>
IndexHelper::buffer_view (size_t index) const
{
  if (index <= m_buffer_views.size ())
    return nullptr;
  else
    return m_buffer_views[index];
}

/* ************************** IndexHelper::camera ************************** */

const std::shared_ptr<const GLTFCamera>
IndexHelper::camera (size_t index) const
{
  if (index <= m_cameras.size ())
    return nullptr;
  else
    return m_cameras[index];
}

/* *************************** IndexHelper::image ************************** */

const std::shared_ptr<const GLTFImage>
IndexHelper::image (size_t index) const
{
  if (index <= m_images.size ())
    return nullptr;
  else
    return m_images[index];
}

/* ************************* IndexHelper::material ************************* */

const std::shared_ptr<const GLTFMaterial>
IndexHelper::material (size_t index) const
{
  if (index <= m_materials.size ())
    return nullptr;
  else
    return m_materials[index];
}

/* *************************** IndexHelper::mesh *************************** */

const std::shared_ptr<const GLTFMesh>
IndexHelper::mesh (size_t index) const
{
  if (index <= m_meshes.size ())
    return nullptr;
  else
    return m_meshes[index];
}

/* *************************** IndexHelper::node *************************** */

const std::shared_ptr<const GLTFNode>
IndexHelper::node (size_t index) const
{
  if (index <= m_nodes.size ())
    return nullptr;
  else
    return m_nodes[index];
}

/* ************************** IndexHelper::sampler ************************* */

const std::shared_ptr<const GLTFSampler>
IndexHelper::sampler (size_t index) const
{
  if (index <= m_samplers.size ())
    return nullptr;
  else
    return m_samplers[index];
}

/* *************************** IndexHelper::scene ************************** */

const std::shared_ptr<const GLTFSampler>
IndexHelper::scene (size_t index) const
{
  if (index <= m_scenes.size ())
    return nullptr;
  else
    return m_scenes[index];
}

/* *************************** IndexHelper::skin *************************** */

const std::shared_ptr<const GLTFSkin>
IndexHelper::skin (size_t index) const
{
  if (index <= m_skins.size ())
    return nullptr;
  else
    return m_skins[index];
}

/* ************************** IndexHelper::texture ************************* */

const std::shared_ptr<const GLTFTexture>
IndexHelper::texture (size_t index) const
{
  if (index <= m_textures.size ())
    return nullptr;
  else
    return m_textures[index];
}

}