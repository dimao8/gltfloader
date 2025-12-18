#include "indexhelper.h"

namespace gltfloader
{

/* ************************ IndexHelper::IndexHelper *********************** */

IndexHelper::IndexHelper (
    const size_t &accessor_defaults_size,
    const std::vector<std::shared_ptr<GLTFAccessor> > &accessors,
    const size_t &animation_defaults_size,
    const std::vector<std::shared_ptr<GLTFAnimation> > &animations,
    const size_t &buffer_defaults_size,
    const std::vector<std::shared_ptr<GLTFBuffer> > &buffers,
    const size_t &buffer_view_defaults_size,
    const std::vector<std::shared_ptr<GLTFBufferView> > &buffer_views,
    const size_t &camera_defaults_size,
    const std::vector<std::shared_ptr<GLTFCamera> > &cameras,
    const size_t &image_defaults_size,
    const std::vector<std::shared_ptr<GLTFImage> > &images,
    const size_t &material_defaults_size,
    const std::vector<std::shared_ptr<GLTFMaterial> > &materials,
    const size_t &mesh_defaults_size,
    const std::vector<std::shared_ptr<GLTFMesh> > &meshes,
    const size_t &node_defaults_size,
    const std::vector<std::shared_ptr<GLTFNode> > &nodes,
    const size_t &sampler_defaults_size,
    const std::vector<std::shared_ptr<GLTFSampler> > &samplers,
    const size_t &scene_defaults_size,
    const std::vector<std::shared_ptr<GLTFSampler> > &scenes,
    const size_t &skin_defaults_size,
    const std::vector<std::shared_ptr<GLTFSkin> > &skins,
    const size_t &texture_defaults_size,
    const std::vector<std::shared_ptr<GLTFTexture> > &textures,
    const size_t &texture_info_defaults_size,
    const std::vector<std::shared_ptr<GLTFTextureInfo> > &texture_infos)
    : m_accessor_defaults_size (accessor_defaults_size),
      m_accessors (accessors),
      m_animation_defaults_size (animation_defaults_size),
      m_animations (animations), m_buffer_defaults_size (buffer_defaults_size),
      m_buffers (buffers),
      m_buffer_view_defaults_size (buffer_view_defaults_size),
      m_buffer_views (buffer_views),
      m_camera_defaults_size (camera_defaults_size), m_cameras (cameras),
      m_image_defaults_size (image_defaults_size), m_images (images),
      m_material_defaults_size (material_defaults_size),
      m_materials (materials), m_mesh_defaults_size (mesh_defaults_size),
      m_meshes (meshes), m_node_defaults_size (node_defaults_size),
      m_nodes (nodes), m_sampler_defaults_size (sampler_defaults_size),
      m_samplers (samplers), m_scene_defaults_size (scene_defaults_size),
      m_scenes (scenes), m_skin_defaults_size (skin_defaults_size),
      m_skins (skins), m_texture_defaults_size (texture_defaults_size),
      m_textures (textures),
      m_texture_info_defaults_size (texture_info_defaults_size),
      m_texture_infos (texture_infos)
{
  //
}

/* ********************** IndexHelper::accessors_size ********************** */

size_t
IndexHelper::accessors_size () const
{
  return m_accessors.size ();
}

/* ****************** IndexHelper::accessor_defaults_size ****************** */

size_t
IndexHelper::accessor_defaults_size () const
{
  return m_accessor_defaults_size;
}

/* ********************** IndexHelper::animations_size ********************* */

size_t
IndexHelper::animations_size () const
{
  return m_animations.size ();
}

/* ****************** IndexHelper::animation_defaults_size ***************** */

size_t
IndexHelper::animation_defaults_size () const
{
  return m_animation_defaults_size;
}

/* *********************** IndexHelper::buffers_size *********************** */

size_t
IndexHelper::buffers_size () const
{
  return m_buffers.size ();
}

/* ******************* IndexHelper::buffer_defaults_size ******************* */

size_t
IndexHelper::buffer_defaults_size () const
{
  return m_buffer_defaults_size;
}

/* ********************* IndexHelper::buffer_views_size ******************** */

size_t
IndexHelper::buffer_views_size () const
{
  return m_buffer_views.size ();
}

/* ***************** IndexHelper::buffer_view_defaults_size **************** */

size_t
IndexHelper::buffer_view_defaults_size () const
{
  return m_buffer_view_defaults_size;
}

/* *********************** IndexHelper::cameras_size *********************** */

size_t
IndexHelper::cameras_size () const
{
  return m_cameras.size ();
}

/* ******************* IndexHelper::camera_defaults_size ******************* */

size_t
IndexHelper::camera_defaults_size () const
{
  return m_camera_defaults_size;
}

/* ************************ IndexHelper::images_size *********************** */

size_t
IndexHelper::images_size () const
{
  return m_images.size ();
}

/* ******************** IndexHelper::image_defaults_size ******************* */

size_t
IndexHelper::image_defaults_size () const
{
  return m_image_defaults_size;
}

/* ********************** IndexHelper::materials_size ********************** */

size_t
IndexHelper::materials_size () const
{
  return m_materials.size ();
}

/* ****************** IndexHelper::material_defaults_size ****************** */

size_t
IndexHelper::material_defaults_size () const
{
  return m_material_defaults_size;
}

/* ************************ IndexHelper::meshes_size *********************** */

size_t
IndexHelper::meshes_size () const
{
  return m_meshes.size ();
}

/* ******************** IndexHelper::mesh_defaults_size ******************** */

size_t
IndexHelper::mesh_defaults_size () const
{
  return m_mesh_defaults_size;
}

/* ************************ IndexHelper::nodes_size ************************ */

size_t
IndexHelper::nodes_size () const
{
  return m_nodes.size ();
}

/* ******************** IndexHelper::node_defaults_size ******************** */

size_t
IndexHelper::node_defaults_size () const
{
  return m_node_defaults_size;
}

/* ******************* IndexHelper::defalt_sampler_index ******************* */

size_t
IndexHelper::default_texture_sampler_index () const
{
  // TODO : What if there are no default samplers?
  return 0;
}

/* *********************** IndexHelper::samplers_size ********************** */

size_t
IndexHelper::samplers_size () const
{
  return m_samplers.size ();
}

/* ******************* IndexHelper::sampler_defaults_size ****************** */

size_t
IndexHelper::sampler_defaults_size () const
{
  return m_sampler_defaults_size;
}

/* ************************ IndexHelper::scenes_size *********************** */

size_t
IndexHelper::scenes_size () const
{
  return m_scenes.size ();
}

/* ******************** IndexHelper::scene_defaults_size ******************* */

size_t
IndexHelper::scene_defaults_size () const
{
  return m_scene_defaults_size;
}

/* ************************ IndexHelper::skins_size ************************ */

size_t
IndexHelper::skins_size () const
{
  return m_skins.size ();
}

/* ******************** IndexHelper::skin_defaults_size ******************** */

size_t
IndexHelper::skin_defaults_size () const
{
  return m_skin_defaults_size;
}

/* *********************** IndexHelper::textures_size ********************** */

size_t
IndexHelper::textures_size () const
{
  return m_textures.size ();
}

/* ******************* IndexHelper::texture_defaults_size ****************** */

size_t
IndexHelper::texture_defaults_size () const
{
  return m_texture_defaults_size;
}

/* ******************** IndexHelper::texture_infos_size ******************** */

size_t
IndexHelper::texture_infos_size () const
{
  return m_texture_infos.size ();
}

/* **************** IndexHelper::texture_info_defaults_size **************** */

size_t
IndexHelper::texture_info_defaults_size () const
{
  return m_texture_info_defaults_size;
}

/* ********** IndexHelper::default_material_emissive_texture_info ********** */

size_t
IndexHelper::default_material_emissive_texture_info () const
{
  // TODO : What if there are no default texture infos?
  return 0;
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
  if (index >= m_animations.size ())
    return nullptr;
  else
    return m_animations[index];
}

/* ************************** IndexHelper::buffer ************************** */

const std::shared_ptr<const GLTFBuffer>
IndexHelper::buffer (size_t index) const
{
  if (index >= m_buffers.size ())
    return nullptr;
  else
    return m_buffers[index];
}

/* ************************ IndexHelper::buffer_view *********************** */

const std::shared_ptr<const GLTFBufferView>
IndexHelper::buffer_view (size_t index) const
{
  if (index >= m_buffer_views.size ())
    return nullptr;
  else
    return m_buffer_views[index];
}

/* ************************** IndexHelper::camera ************************** */

const std::shared_ptr<const GLTFCamera>
IndexHelper::camera (size_t index) const
{
  if (index >= m_cameras.size ())
    return nullptr;
  else
    return m_cameras[index];
}

/* *************************** IndexHelper::image ************************** */

const std::shared_ptr<const GLTFImage>
IndexHelper::image (size_t index) const
{
  if (index >= m_images.size ())
    return nullptr;
  else
    return m_images[index];
}

/* ************************* IndexHelper::material ************************* */

const std::shared_ptr<const GLTFMaterial>
IndexHelper::material (size_t index) const
{
  if (index >= m_materials.size ())
    return nullptr;
  else
    return m_materials[index];
}

/* *************************** IndexHelper::mesh *************************** */

const std::shared_ptr<const GLTFMesh>
IndexHelper::mesh (size_t index) const
{
  if (index >= m_meshes.size ())
    return nullptr;
  else
    return m_meshes[index];
}

/* *************************** IndexHelper::node *************************** */

const std::shared_ptr<const GLTFNode>
IndexHelper::node (size_t index) const
{
  if (index >= m_nodes.size ())
    return nullptr;
  else
    return m_nodes[index];
}

/* ************************** IndexHelper::sampler ************************* */

const std::shared_ptr<const GLTFSampler>
IndexHelper::sampler (size_t index) const
{
  if (index >= m_samplers.size ())
    return nullptr;
  else
    return m_samplers[index];
}

/* *************************** IndexHelper::scene ************************** */

const std::shared_ptr<const GLTFSampler>
IndexHelper::scene (size_t index) const
{
  if (index >= m_scenes.size ())
    return nullptr;
  else
    return m_scenes[index];
}

/* *************************** IndexHelper::skin *************************** */

const std::shared_ptr<const GLTFSkin>
IndexHelper::skin (size_t index) const
{
  if (index >= m_skins.size ())
    return nullptr;
  else
    return m_skins[index];
}

/* ************************** IndexHelper::texture ************************* */

const std::shared_ptr<const GLTFTexture>
IndexHelper::texture (size_t index) const
{
  if (index >= m_textures.size ())
    return nullptr;
  else
    return m_textures[index];
}

/* *********************** IndexHelper::texture_info *********************** */

const std::shared_ptr<const GLTFTextureInfo>
IndexHelper::texture_info (size_t index) const
{
  if (index >= m_texture_infos.size ())
    return nullptr;
  else
    return m_texture_infos[index];
}

}