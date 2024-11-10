/*
Copyright (c) 2024 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#pragma once

#include <cstdint>
#include <cstddef>
#include <type_traits>  // std::underlying_type

#include <esp32-hal-rmt.h>

#include "Constants.h"
#include "Logging.h"

constexpr std::size_t OIR_NUMBER_DATABITS = 12;
constexpr std::size_t OIR_NUMBER_FRAMEBITS = 1 + 12 + 1;  // head + data + tail

class OnkyoRI_RMT {
 public:
  explicit OnkyoRI_RMT(int pin);
  ~OnkyoRI_RMT();

  bool begin();
  bool end();

  bool write(OnkyoRI::Command command);
  bool write(uint16_t command);

  bool busy();

 private:
  int _pin;
  rmt_data_t _data[OIR_NUMBER_FRAMEBITS];
};
