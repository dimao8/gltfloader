#include "base64.h"

namespace gltfloader
{

const std::string base64_alphabet
    = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* ***************************** base64_import ***************************** */

bool
base64_import (std::vector<uint8_t> &out_buffer, const std::string &str)
{
  if ((str.size () & 0x3) != 0)
    return false;

  uint32_t block;
  size_t tmp;

  out_buffer.clear ();
  for (auto i = 0; i < str.size () / 4; i++)
    {
      tmp = base64_alphabet.find (str[i * 4]) & 0x3F;
      if (tmp == std::string::npos)
        return false;
      else
        block = tmp << 18;

      tmp = base64_alphabet.find (str[i * 4 + 1]) & 0x3F;
      if (tmp == std::string::npos)
        return false;
      else
        block |= tmp << 12;

      tmp = base64_alphabet.find (str[i * 4 + 2]) & 0x3F;
      if (tmp == std::string::npos)
        return false;
      else
        block |= tmp << 6;

      tmp = base64_alphabet.find (str[i * 4 + 3]) & 0x3F;
      if (tmp == std::string::npos)
        return false;
      else
        block |= tmp;

      out_buffer.push_back (static_cast<uint8_t> (block >> 16));
      if (str[i * 4 + 2] != '=')
        out_buffer.push_back (static_cast<uint8_t> (block >> 8));
      if (str[i * 4 + 3] != '=')
        out_buffer.push_back (static_cast<uint8_t> (block));
    }
  return true;
}

/* ***************************** base64_export ***************************** */

bool
base64_export (std::string &str, const std::vector<uint8_t> &in_buffer)
{
  uint32_t block;

  for (auto i = 0; i < in_buffer.size () / 3; i++)
    {
      block = static_cast<uint32_t> (in_buffer[i * 3]) << 16;
      block |= static_cast<uint32_t> (in_buffer[i * 3 + 1]) << 8;
      block |= static_cast<uint32_t> (in_buffer[i * 3 + 2]);

      str.push_back (base64_alphabet[(block >> 18) & 0x3F]);
      str.push_back (base64_alphabet[(block >> 12) & 0x3F]);
      str.push_back (base64_alphabet[(block >> 6) & 0x3F]);
      str.push_back (base64_alphabet[block & 0x3F]);
    }

  switch (in_buffer.size () % 3)
    {
    case 1: // One extra byte. Add two '='
      block = static_cast<uint32_t> (in_buffer[in_buffer.size () - 1]) << 4;
      str.push_back (base64_alphabet[(block >> 6) & 0x3F]);
      str.push_back (base64_alphabet[block & 0x3F]);
      str += "==";
      break;

    case 2: // Two extra bytes
      block
          = (static_cast<uint32_t> (in_buffer[in_buffer.size () - 2]) << 10)
            | (static_cast<uint32_t> (in_buffer[in_buffer.size () - 1]) << 2);
      str.push_back (base64_alphabet[(block >> 12) & 0x3F]);
      str.push_back (base64_alphabet[(block >> 6) & 0x3F]);
      str.push_back (base64_alphabet[block & 0x3F]);
      str.push_back ('=');
      break;
    }

  return true;
}

}