#include "asset.h"

#include <iostream>
#include <regex>

namespace gltfloader
{

const std::string gltf_version_regex_string = "^([0-9]+)\\.([0-9]+)$";
std::regex gltf_version_regex (gltf_version_regex_string,
                               std::regex_constants::basic);

/* ************************** GLTFAsset::GLTFAsset ************************* */

GLTFAsset::GLTFAsset ()
    : GLTFObject (), m_version_int ({ 0, 0 }), m_min_version_int ({ 0, 0 })
{
  //
}

/* ************************** GLTFAsset::copyright ************************* */

const std::string &
GLTFAsset::copyright () const
{
  return m_copyright;
}

/* ************************** GLTFAsset::generator ************************* */

const std::string &
GLTFAsset::generator () const
{
  return m_generator;
}

/* *************************** GLTFAsset::version ************************** */

const std::string &
GLTFAsset::version () const
{
  return m_version;
}

/* ************************* GLTFAsset::min_version ************************ */

const std::string &
GLTFAsset::min_version () const
{
  return m_min_version;
}

/* *************************** GLTFAsset::create *************************** */

std::shared_ptr<GLTFAsset>
GLTFAsset::create (const std::string &version, const std::string &copyright,
                   const std::string &generator,
                   const std::string &min_version)
{
  std::shared_ptr<GLTFAsset> tmp (new GLTFAsset ());
  size_t n;

  if (!std::regex_match (version, gltf_version_regex,
                         std::regex_constants::match_any))
    {
      std::cout
          << "[W] glTF 2.0 5.9.3: The asset.version does not match regex \""
          << gltf_version_regex_string << "\"" << std::endl;
      return nullptr;
    }
  n = 0;
  for (std::smatch sm; std::regex_search (version, gltf_version_regex,
                                          std::regex_constants::match_any);)
    {
      tmp->m_version_int[n] = std::stoi (sm.str ());
      n++;
      if (n == 2)
        break;
    }
  if (tmp->m_version_int[0] != 2 || tmp->m_version_int[0] != 0)
    {
      std::cout << "[W] glTF 2.0: Only version 2.0 of glTF is supported"
                << std::endl;
      return nullptr;
    }
  tmp->m_version = version;

  if (!min_version.empty ())
    {
      if (!std::regex_match (version, gltf_version_regex,
                             std::regex_constants::match_any))
        {
          std::cout << "[W] glTF 2.0 5.9.4: The asset.minVersion does not "
                       "match regex \""
                    << gltf_version_regex_string << "\"" << std::endl;
          return nullptr;
        }
      n = 0;
      for (std::smatch sm;
           std::regex_search (min_version, gltf_version_regex,
                              std::regex_constants::match_any);)
        {
          tmp->m_min_version_int[n] = std::stoi (sm.str ());
          n++;
          if (n == 2)
            break;
        }
      if (tmp->m_min_version_int[0] != 2 || tmp->m_min_version_int[0] != 0)
        {
          std::cout << "[W] glTF 2.0: Only version 2.0 of glTF is supported"
                    << std::endl;
          return nullptr;
        }
      tmp->m_min_version = min_version;
    }

  if (!copyright.empty ())
    tmp->m_copyright = copyright;

  if (!generator.empty ())
    tmp->m_generator = generator;

  return tmp;
}

}