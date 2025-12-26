#include "sampler.h"
#include "gltftypes.h"
#include "indexhelper.h"

#include <iostream>

namespace gltfloader
{

/* ************************ GLTFSampler::GLTFSampler *********************** */

GLTFSampler::GLTFSampler (const std::string &name)
    : GLTFNamedObject (name), m_mag_filter (GLTFTextureFilter::linear),
      m_min_filter (GLTFTextureFilter::linear),
      m_wrap_s (GLTFTextureWrap::repeat), m_wrap_t (GLTFTextureWrap::repeat)
{
  //
}

/* *********************** GLTFSampler::~GLTFSampler *********************** */

GLTFSampler::~GLTFSampler ()
{
  //
}

/* ************************ GLTFSampler::mag_filter ************************ */

const std::optional<GLTFTextureFilter> &
GLTFSampler::mag_filter () const
{
  return m_mag_filter;
}

/* ************************ GLTFSampler::min_filter ************************ */

const std::optional<GLTFTextureFilter> &
GLTFSampler::min_filter () const
{
  return m_min_filter;
}

/* ************************** GLTFSampler::wrap_s ************************** */

GLTFTextureWrap
GLTFSampler::wrap_s () const
{
  return m_wrap_s;
}

/* ************************** GLTFSampler::wrap_t ************************** */

GLTFTextureWrap
GLTFSampler::wrap_t () const
{
  return m_wrap_t;
}

std::shared_ptr<GLTFSampler>
GLTFSampler::create (IndexHelper &helper, const std::string &name,
                     std::optional<int> mag_filter,
                     std::optional<int> min_filter, std::optional<int> wrap_s,
                     std::optional<int> wrap_t)
{
  std::shared_ptr<GLTFSampler> tmp (new GLTFSampler (name));

  if (mag_filter == std::nullopt)
    tmp->m_mag_filter = std::nullopt;
  else
    {
      switch (mag_filter.value ())
        {
        case static_cast<int> (GLTFTextureFilter::nearest):
          tmp->m_mag_filter = GLTFTextureFilter::nearest;
          break;

        case static_cast<int> (GLTFTextureFilter::linear):
          tmp->m_mag_filter = GLTFTextureFilter::linear;
          break;

        default:
          std::cout << "[W] glTF 2.0 5.26.1: sampler.magFilter can be only "
                       "9728 or 9729"
                    << std::endl;
          return nullptr;
        }
    }

  if (min_filter == std::nullopt)
    tmp->m_min_filter = std::nullopt;
  else
    {
      switch (min_filter.value ())
        {
        case static_cast<int> (GLTFTextureFilter::nearest):
          tmp->m_min_filter = GLTFTextureFilter::nearest;
          break;

        case static_cast<int> (GLTFTextureFilter::linear):
          tmp->m_min_filter = GLTFTextureFilter::linear;
          break;

        case static_cast<int> (GLTFTextureFilter::nearest_mipmap_nearest):
          tmp->m_min_filter = GLTFTextureFilter::nearest_mipmap_nearest;
          break;

        case static_cast<int> (GLTFTextureFilter::linear_mipmap_nearest):
          tmp->m_min_filter = GLTFTextureFilter::linear_mipmap_nearest;
          break;

        case static_cast<int> (GLTFTextureFilter::nearest_mipmap_linear):
          tmp->m_min_filter = GLTFTextureFilter::nearest_mipmap_linear;
          break;

        case static_cast<int> (GLTFTextureFilter::linear_mipmap_linear):
          tmp->m_min_filter = GLTFTextureFilter::linear_mipmap_linear;
          break;

        default:
          std::cout << "[W] glTF 2.0 5.26.2: sampler.minFilter can be only "
                       "9728, 9729, 9984, 9985, 9986 or 9987"
                    << std::endl;
          return nullptr;
        }
    }

  if (wrap_s == std::nullopt)
    tmp->m_wrap_s = GLTFTextureWrap::repeat;
  else
    {
      switch (wrap_s.value ())
        {
        case static_cast<int> (GLTFTextureWrap::clamp_to_edge):
          tmp->m_wrap_s = GLTFTextureWrap::clamp_to_edge;
          break;

        case static_cast<int> (GLTFTextureWrap::mirrored_repeat):
          tmp->m_wrap_s = GLTFTextureWrap::mirrored_repeat;
          break;

        case static_cast<int> (GLTFTextureWrap::repeat):
          tmp->m_wrap_s = GLTFTextureWrap::repeat;
          break;

        default:
          std::cout << "[W] glTF 2.0 5.26.3: sampler.wrapS can be only "
                       "33071, 33648 or 10497"
                    << std::endl;
          return nullptr;
        }
    }

  if (wrap_t == std::nullopt)
    tmp->m_wrap_t = GLTFTextureWrap::repeat;
  else
    {
      switch (wrap_s.value ())
        {
        case static_cast<int> (GLTFTextureWrap::clamp_to_edge):
          tmp->m_wrap_t = GLTFTextureWrap::clamp_to_edge;
          break;

        case static_cast<int> (GLTFTextureWrap::mirrored_repeat):
          tmp->m_wrap_t = GLTFTextureWrap::mirrored_repeat;
          break;

        case static_cast<int> (GLTFTextureWrap::repeat):
          tmp->m_wrap_t = GLTFTextureWrap::repeat;
          break;

        default:
          std::cout << "[W] glTF 2.0 5.26.4: sampler.wrapT can be only "
                       "33071, 33648 or 10497"
                    << std::endl;
          return nullptr;
        }
    }

  return tmp;
}
}
