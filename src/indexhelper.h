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

class IndexHelper
{
private:
  const std::vector<std::shared_ptr<GLTFAccessor> > &m_accessors;
  const std::vector<std::shared_ptr<GLTFAnimation> > &m_animations;
  const std::vector<std::shared_ptr<GLTFBuffer> > &m_buffers;
  const std::vector<std::shared_ptr<GLTFBufferView> > &m_buffer_views;
  const std::vector<std::shared_ptr<GLTFCamera> > &m_cameras;
  const std::vector<std::shared_ptr<GLTFImage> > &m_images;
  const std::vector<std::shared_ptr<GLTFMaterial> > &m_materials;
  const std::vector<std::shared_ptr<GLTFMesh> > &m_meshes;
  const std::vector<std::shared_ptr<GLTFNode> > &m_nodes;
  const std::vector<std::shared_ptr<GLTFSampler> > &m_samplers;
  const std::vector<std::shared_ptr<GLTFSampler> > &m_scenes;
  const std::vector<std::shared_ptr<GLTFSkin> > &m_skins;
  const std::vector<std::shared_ptr<GLTFTexture> > &m_textures;

public:
  IndexHelper () = delete;
  IndexHelper (const IndexHelper &) = delete;
  IndexHelper (
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
