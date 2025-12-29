#ifndef GLTFTYPES_H
#define GLTFTYPES_H

#include <array>

namespace gltfloader
{

enum class GLTFComponentType
{
  byte = 5120,
  unsigned_byte = 5121,
  sshort = 5122,
  unsigned_short = 5123,
  unsigned_int = 5125,
  ffloat = 5126
};

enum class GLTFAccessorType
{
  scalar,
  vec2,
  vec3,
  vec4,
  mat2,
  mat3,
  mat4
};

enum class GLTFAlphaMode
{
  opaque,
  mask,
  blend
};

enum class GLTFAnimationPath
{
  translation,
  rotation,
  scale,
  weights
};

enum class GLTFBufferViewTarget
{
  array_buffer = 34962,
  element_array_buffer = 34963
};

enum class GLTFCameraType
{
  orthographic,
  perspective
};

enum GLTFDrawMode
{
  points = 0,
  lines = 1,
  line_loop = 2,
  line_strip = 3,
  triangles = 4,
  triangle_strip = 5,
  triangle_fan = 6
};

enum class GLTFImageMIMEType
{
  png,
  jpeg
};

enum class GLTFInterpolationMethod
{
  step,
  linear,
  cubic
};

enum class GLTFTextureFilter
{
  nearest = 9728,
  linear = 9729,
  nearest_mipmap_nearest = 9984,
  linear_mipmap_nearest = 9985,
  nearest_mipmap_linear = 9986,
  linear_mipmap_linear = 9987
};

enum class GLTFTextureWrap
{
  clamp_to_edge = 33071,
  mirrored_repeat = 33648,
  repeat = 10497
};

typedef std::array<float, 4> GLTFVector4f;

}

#endif // GLTFTYPES_H