/**
 * \file
 * \brief IndexHelper class declaration
 *
 * \note Indices of all glTF object lists are started from offset. The offset
 * value depends on the number of default objects. All indices are shifted by
 * this offset at the initialization.
 */

#ifndef INDEXHELPER_H
#define INDEXHELPER_H

#include <memory>
#include <vector>

namespace gltfloader
{

class GLTFAccessor;
class GLTFAnimation;
class GLTFBuffer;
class GLTFBufferView;
class GLTFCamera;
class GLTFImage;
class GLTFMaterial;
class GLTFMesh;
class GLTFNode;
class GLTFSampler;
class GLTFScene;
class GLTFSkin;
class GLTFTexture;

/**
 * \brief Helper class for accessing glTF objects by index
 */
class IndexHelper
{
private:
  size_t &m_accessor_defaults_size;
  const std::vector<std::shared_ptr<GLTFAccessor> > &m_accessors;
  size_t &m_animation_defaults_size;
  const std::vector<std::shared_ptr<GLTFAnimation> > &m_animations;
  size_t &m_buffer_defaults_size;
  const std::vector<std::shared_ptr<GLTFBuffer> > &m_buffers;
  size_t &m_buffer_view_defaults_size;
  const std::vector<std::shared_ptr<GLTFBufferView> > &m_buffer_views;
  size_t &m_camera_defaults_size;
  const std::vector<std::shared_ptr<GLTFCamera> > &m_cameras;
  size_t &m_image_defaults_size;
  const std::vector<std::shared_ptr<GLTFImage> > &m_images;
  size_t &m_material_defaults_size;
  const std::vector<std::shared_ptr<GLTFMaterial> > &m_materials;
  size_t &m_mesh_defaults_size;
  const std::vector<std::shared_ptr<GLTFMesh> > &m_meshes;
  size_t &m_node_defaults_size;
  const std::vector<std::shared_ptr<GLTFNode> > &m_nodes;
  size_t &m_sampler_defaults_size;
  const std::vector<std::shared_ptr<GLTFSampler> > &m_samplers;
  size_t &m_scene_defaults_size;
  const std::vector<std::shared_ptr<GLTFSampler> > &m_scenes;
  size_t &m_skin_defaults_size;
  const std::vector<std::shared_ptr<GLTFSkin> > &m_skins;
  size_t &m_texture_defaults_size;
  const std::vector<std::shared_ptr<GLTFTexture> > &m_textures;

public:
  IndexHelper () = delete;
  IndexHelper (const IndexHelper &) = delete;
  IndexHelper (
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
      const std::vector<std::shared_ptr<GLTFTexture> > &textures);
  ~IndexHelper () {}

  size_t accessors_size () const;
  size_t animations_size () const;
  size_t buffers_size () const;
  size_t buffer_views_size () const;
  size_t cameras_size () const;
  size_t images_size () const;
  size_t materials_size () const;
  size_t meshes_size () const;
  size_t nodes_size () const;
  size_t samplers_size () const;
  size_t scenes_size () const;
  size_t skins_size () const;
  size_t textures_size () const;

  const std::shared_ptr<const GLTFAccessor> accessor (size_t index) const;
  const std::shared_ptr<const GLTFAnimation> animation (size_t index) const;
  const std::shared_ptr<const GLTFBuffer> buffer (size_t index) const;
  const std::shared_ptr<const GLTFBufferView> buffer_view (size_t index) const;
  const std::shared_ptr<const GLTFCamera> camera (size_t index) const;
  const std::shared_ptr<const GLTFImage> image (size_t index) const;
  const std::shared_ptr<const GLTFMaterial> material (size_t index) const;
  const std::shared_ptr<const GLTFMesh> mesh (size_t index) const;
  const std::shared_ptr<const GLTFNode> node (size_t index) const;
  const std::shared_ptr<const GLTFSampler> sampler (size_t index) const;
  const std::shared_ptr<const GLTFSampler> scene (size_t index) const;
  const std::shared_ptr<const GLTFSkin> skin (size_t index) const;
  const std::shared_ptr<const GLTFTexture> texture (size_t index) const;
};

}

#endif // INDEXHELPER_H
