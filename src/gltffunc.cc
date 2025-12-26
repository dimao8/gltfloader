#include "gltffunc.h"

namespace gltfloader
{

/* ******************************* is_unique ******************************* */

bool
is_unique (const std::vector<int> &vec, size_t i)
{
  size_t counter = 0;

  if (i >= vec.size ())
    return true;

  for (size_t j = 0; j < vec.size (); j++)
    {
      if (vec[i] == vec[j])
        {
          counter++;
          if (counter > 1)
            return false;
        }
    }

  if (counter <= 1)
    return true;
  else
    return false;
}

}
