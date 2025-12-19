#include "texture.h"
#include "indexhelper.h"

#include <iostream>
#include <optional>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAS_CONFIG_H

namespace gltfloader
{

/* ************************ GLTFTexture::GLTFTexture *********************** */

GLTFTexture::GLTFTexture (const std::string &name)
    : GLTFNamedObject (name), m_sampler (std::nullopt), m_source (std::nullopt)
{
  //
}

/* *********************** GLTFTexture::~GLTFTexture *********************** */

GLTFTexture::~GLTFTexture ()
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
                     const std::optional<int> &sampler,
                     const std::optional<int> &source)
{
  std::shared_ptr<GLTFTexture> tmp (new GLTFTexture (name));

  size_t shifted_sampler_index;

  // NOTE : We are do not use default sampler from default samplers storage in
  // IndexHelper. Instead we just save std::nullopt to the appropriate field
  // and wait for upper layer to fill it instead.
  if (sampler == std::nullopt)
    {
      tmp->m_sampler = sampler;
    }
  else
    {
      shifted_sampler_index
          = sampler.value () + helper.sampler_defaults_size ();
      if (sampler < 0)
        {
          std::cout << "[W] glTF 2.0 5.29.1: texture.sampler >= 0"
                    << std::endl;
          return nullptr;
        }
      else if (shifted_sampler_index >= helper.samplers_size ())
        {
          tmp->m_sampler = shifted_sampler_index;
        }
    }

  if (source == std::nullopt)
    {
      // TODO : Special mechanism from extensions (glTF 2.0 5.29.2)
      std::cout << "[W] glTF 2.0 5.29.2: missing texture.source is valid but "
                   "not supported by "
                << PACKAGE << " " << VERSION << std::endl;
      return nullptr;
    }
  else if (source < 0)
    {
      std::cout << "[W] glTF 2.0 5.29.2: texture.source >= 0" << std::endl;
      return nullptr;
    }

  return tmp;
}

}