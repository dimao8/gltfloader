#ifndef GLTFLOADER_H
#define GLTFLOADER_H

#include <vector>
#include <memory>

namespace gltfloader
{

class GLTFBuffer;

class GLTFLoader
{
private:
  // Buffers section
  std::vector<std::shared_ptr<GLTFBuffer>> m_buffers;
};

}

#endif // GLTFLOADER_H
