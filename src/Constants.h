/*
Copyright (c) 2024 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#pragma once

#include <cstdint>

namespace OnkyoRI {

enum class Command : uint16_t {
  VOLUMEUP     = 0x0002,
  VOLUMEDOWN   = 0x0003,
  ONOFFTOGGLE  = 0x0004,
  TOGGLEMUTE   = 0x0005,
  SOURCECD     = 0x0020,
  POWERON      = 0x002F,
  NEXTINPUT    = 0x00D5,
  PREVINPUT    = 0x00D6,
  POWEROFF     = 0x00DA,
  INPUTLINEIN  = 0x00E3,
  SOURCEDOCK   = 0x0170,
  MUTINGTOGGLE = 0x0503
};

}  // end namespace OnkyoRI
