#ifndef IMAGE_H
#define IMAGE_H

#include "gltfnamedobject.h"
#include "indexhelper.h"

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
enum class GLTFImageMIMEType
{
  png, ///< image/png
  jpeg ///< image/jpeg
};

///
/// \brief glTF 2.0 image class
///
/// The GLTFImage class encapsulates glTF 2.0 image. It is glTF object
/// associated with images[n] property in the glTF file.
///
/// There are two different types of methods for storing image data:
/// - External storage: reference a separate image file (e.g., PNG, JPEG) via
/// URI
/// - Store data array in glTF buffer and reference it via a bufferView.
///
/// For external image files, use the constructor that takes a file path:
/// ```c++
/// GLTFImage (const std::string &name, GLTFImageMIMEType mime_type,
/// const std::string &path)
/// ```
///
/// For buffer-stored images, use the constructor that takes a buffer view:
/// ```c++
/// GLTFImage (const std::string &name, GLTFImageMIMEType mime_type,
/// const std::shared_ptr<GLTFBufferView> buffer_view);
/// ```
///
/// Both constructors accept an MIME type via the mime_type parameter
/// which is described in [GLTFImageMIMEType](@ref GLTFImageMIMEType) section.
/// If MIME type is not defined the `GLTFImageMIMEType::unknown` value in
/// mime_type argument can be used. In this case, export/import adapters will
/// inspect the image signature to determine the appropriate MIME type
/// automatically.
///
/// \note When buffer storage constructor is used there is no raw data
/// stored in the GLTFImage. Check for empty result of data() function
/// to check for data presence. In this case, the data() method will return an
/// empty vector, and you should use the buffer_view() method to access the
/// image data through the associated buffer view.
///
/// Check the result of loading by calling the is_bad() method. It returns
/// \c false only when GLTFImage was successfully created.
///
class GLTFImage : public GLTFNamedObject
{
private:
  GLTFImageMIMEType m_mime_type;
  std::string m_path;
  std::vector<uint8_t> m_data;
  size_t m_buffer_view;

  GLTFImage (const std::string &name);

public:
  GLTFImage () = delete;
  GLTFImage (const GLTFImage &) = delete;

  virtual ~GLTFImage () {}

  // TODO : Move mime type to the separate file
  GLTFImageMIMEType mime_type () const;
  const std::string &path () const;
  const std::vector<uint8_t> &data () const;
  size_t data_size () const;
  size_t buffer_view () const;

  static const std::shared_ptr<GLTFImage>
  create (const IndexHelper &helper, const std::string &name, int buffer_view,
          const std::string &mime_type, const std::string &uri);
};

}

#endif // IMAGE_H
