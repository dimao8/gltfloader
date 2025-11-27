#include "indexhelper.h"
#include "texture.h"

#include <iostream>
#include <optional>

namespace gltfloader
{

/* ************************ GLTFTexture::GLTFTexture *********************** */

GLTFTexture::GLTFTexture (const std::string &name) : GLTFNamedObject (name)
{
  //
}

/* ************************** GLTFTexture::sampler ************************* */

const std::optional<size_t> &
GLTFTexture::sampler () const
{
  return m_sampler;
}

/* ************************** GLTFTexture::source ************************** */

const std::optional<size_t> &
GLTFTexture::source () const
{
  return m_source;
}

/* ************************** GLTFTexture::create ************************** */

std::shared_ptr<GLTFTexture>
GLTFTexture::create (const IndexHelper &helper, const std::string &name,
                     std::optional<int> sampler, std::optional<int> source)
{
  std::shared_ptr<GLTFTexture> texture = std::make_shared<GLTFTexture> (name);

  if (sampler == std::nullopt)
    {
      // TODO : Make default sampler
    }
  else if (sampler < 0)
    {
      std::cout << "[W] glTF 2.0 5.29.1: texture.sampler >= 0" << std::endl;
      return nullptr;
    }
  else if (sampler >= helper.samplers_size ())
    {
      texture->m_sampler = sampler;
    }

  if (source == std::nullopt)
    {
      // TODO : Special mechanism from extensions (glTF 2.0 5.29.2)
    }
  else if (source < 0)
    {
      std::cout << "[W] glTF 2.0 5.29.2: texture.source >= 0" << std::endl;
      return nullptr;
    }

  return texture;
}

}