#ifndef IMAGE_H
#define IMAGE_H

#include "gltfnamedobject.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace gltfloader
{

class GLTFBufferView;

///
/// \brief MIME type enumerator
///
enum GLTFImageMIMEType
{
  image_png,    ///< image/png
  image_jpeg,   ///< image/jpeg
  unknown       ///< unknown type
};

///
/// \brief glTF 2.0 image class
///
///
///
class GLTFImage : public GLTFNamedObject
{
private:
  GLTFImageMIMEType m_mime_type;
  std::string m_path;
  std::vector<uint8_t> m_data;
  std::shared_ptr<GLTFBufferView> m_buffer_view;

  void set (const uint8_t *data, size_t sz);

public:
  GLTFImage () = delete;
  GLTFImage (const GLTFImage &) = delete;
  GLTFImage (const std::string &name, GLTFImageMIMEType mime_type,
             const std::string &path);
  GLTFImage (const std::string &name, GLTFImageMIMEType mime_type,
             const std::shared_ptr<GLTFBufferView> buffer_view);

  bool is_bad () const;
  GLTFImageMIMEType mime_type () const;
  const std::string &path () const;
  const std::vector<uint8_t> &data () const;
  const std::shared_ptr<GLTFBufferView> buffer_view () const;
};

}

#endif // IMAGE_H
