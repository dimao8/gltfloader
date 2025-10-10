#ifndef BUFFER_H
#define BUFFER_H

#include "gltfnamedobject.h"

#include <cstdint>
#include <string>
#include <vector>

namespace gltfloader
{

///
/// \brief glTF 2.0 buffer
///
/// This class encapsulate glTF 2.0 buffer and it's data. It is associated with
/// buffers[n] property of the glTF root object.
///
/// There are two methods for storing raw data, defined in glTF 2.0 standard.
/// - Store data in external binary file (typically with .bin extension).
/// - Store data in URI property of the buffer in Base64 encoding.
///
/// For the first case use the GLTFBuffer (const std::string &name, const
/// std::string &path) constructor. Provide the filesystem path to the binary
/// file via \c path argument to load it's content into the internal storage
/// of the glTF buffer object.
///
/// For Base64 embedded data there are two overloaded constructors with that
/// accepts the raw data:
/// - GLTFBuffer (const std::string &name, const std::vector<uint8_t> &data)
/// - GLTFBuffer (const std::string &name, const uint8_t *data, size_t sz)
///
/// All constructors have \c name argument that can store optional glTF object
/// name. If there is no name, pass an empty string through this argument.
/// GLTFBuffer class will generate name based on UUID.
///
/// Data is stored in the buffer in a read-only manner and cannot be modified
/// or deleted after construction. The data() method can be used to retrieve
/// the data as a in form of std::vector<uint8_t>.
///
/// The class provides an error checking mechanism that does not rely on
/// exceptions. If a constructor fails to load data (e.g., the external file is
/// not found), the buffer is marked as invalid. In this case, the is_bad()
/// method will return \c true. Always check this method after creating a buffer
/// to ensure it was constructed correctly.
///
class GLTFBuffer : public GLTFNamedObject
{
private:
  std::string m_path;          ///< Path to the .bin file
  std::vector<uint8_t> m_data; ///< Raw binary data

  ///
  /// \brief Set data
  /// \param [in] data -- Pointer to the data
  /// \param [in] sz   -- Size of the data
  ///
  void set (const uint8_t *data, size_t sz);

public:
  GLTFBuffer () = delete;
  GLTFBuffer (const GLTFBuffer &) = delete;

  ///
  /// \brief Create buffer from data vector
  /// \param [in] name -- glTF name of the buffer object
  /// \param [in] data -- Data vector
  ///
  GLTFBuffer (const std::string &name, const std::vector<uint8_t> &data);

  ///
  /// \brief Create buffer from data array
  /// \param [in] name -- glTF name of the buffer object
  /// \param [in] data -- Pointer to the data array
  /// \param [in] sz   -- Size of the data
  ///
  GLTFBuffer (const std::string &name, const uint8_t *data, size_t sz);

  ///
  /// \brief Create buffer from binary file
  /// \param [in] name -- glTF name of the buffer object
  /// \param [in] path -- Path to the binary file
  ///
  GLTFBuffer (const std::string &name, const std::string &path);
  virtual ~GLTFBuffer () {}

  ///
  /// \brief Get file path
  /// \return Return file path if it is exists.
  ///
  const std::string &path () const;

  ///
  /// \brief Check buffer for correctness
  /// \return Return true if GLTFBuffer object is valid buffer
  ///
  bool is_bad () const;

  ///
  /// \brief Get raw data
  /// \return Vector of raw buffer data
  ///
  const std::vector<uint8_t> &data () const;
};

}

#endif // BUFFER_H
