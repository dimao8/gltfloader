#ifndef BASE64_H
#define BASE64_H

#include <cstdint>
#include <string>
#include <vector>

namespace gltfloader
{

///
/// \brief Decode Base64 data
/// \param [out] out_buffer -- Output byte buffer
/// \param [in] str         -- Input string
/// \return Returns result of decoding.
///
bool base64_import (std::vector<uint8_t> &out_buffer, const std::string &str);

///
/// \brief Encode Base64 data
/// \param [out] str         -- Output string
/// \param [in] in_buffer -- Input byte buffer
/// \return Returns result of encoding.
///
bool base64_export (std::string &str, const std::vector<uint8_t> &in_buffer);

}

#endif // BASE64_H
