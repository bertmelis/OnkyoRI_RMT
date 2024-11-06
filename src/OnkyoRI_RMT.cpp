/*
Copyright (c) 2024 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#include "OnkyoRI_RMT.h"

constexpr uint32_t OIR_HEAD_LEVEL0 = HIGH;
constexpr uint32_t OIR_HEAD_DURATION0 = 30;
constexpr uint32_t OIR_HEAD_LEVEL1 = LOW;
constexpr uint32_t OIR_HEAD_DURATION1 = 10;
constexpr uint32_t OIR_TAIL_LEVEL0 = HIGH;
constexpr uint32_t OIR_TAIL_DURATION0 = 10;
constexpr uint32_t OIR_TAIL_LEVEL1 = LOW;
constexpr uint32_t OIR_TAIL_DURATION1 = 200;
constexpr uint32_t OIR_BIT0_LEVEL0 = HIGH;
constexpr uint32_t OIR_BIT0_DURATION0 = 10;
constexpr uint32_t OIR_BIT0_LEVEL1 = LOW;
constexpr uint32_t OIR_BIT0_DURATION1 = 10;
constexpr uint32_t OIR_BIT1_LEVEL0 = HIGH;
constexpr uint32_t OIR_BIT1_DURATION0 = 10;
constexpr uint32_t OIR_BIT1_LEVEL1 = LOW;
constexpr uint32_t OIR_BIT1_DURATION1 = 20;

OnkyoRI_RMT::OnkyoRI_RMT(int pin)
: _pin(pin)
, _data{} {
  // populate data with head and tail
  _data[0].level0 = OIR_HEAD_LEVEL0;
  _data[0].duration0 = OIR_HEAD_DURATION0;
  _data[0].level1 = OIR_HEAD_LEVEL1;
  _data[0].duration1 = OIR_HEAD_DURATION1;
  _data[OIR_NUMBER_FRAMEBITS - 1].level0 = OIR_TAIL_LEVEL0;
  _data[OIR_NUMBER_FRAMEBITS - 1].duration0 = OIR_TAIL_DURATION0;
  _data[OIR_NUMBER_FRAMEBITS - 1].level0 = OIR_TAIL_LEVEL1;
  _data[OIR_NUMBER_FRAMEBITS - 1].duration0 = OIR_TAIL_DURATION1;
}

OnkyoRI_RMT::~OnkyoRI_RMT() {
  end();
}

bool OnkyoRI_RMT::begin() {
  // tx only on _pin, 1 memory block and 100ns tick
  if (rmtInit(_pin, RMT_TX_MODE, RMT_MEM_NUM_BLOCKS_1, 10000000)) {
    oir_log_i("init RMT succes");
    return true;
  }
  oir_log_e("init RMT failed");
  return false;
}

bool OnkyoRI_RMT::end() {
  return rmtDeinit(_pin);
}

bool OnkyoRI_RMT::write(OnkyoRI::Command command) {
  return write(static_cast<std::underlying_type<OnkyoRI::Command>>(command));
}

bool OnkyoRI_RMT::write(uint16_t command) {
  // checks
  if (busy) {
    oir_log_w("Could not write to RMT: busy");
    return false;
  }
  if (command > 0xFFF) {
    oir_log_w("Command will be truncated < 12bits");
    command &= 0xFFF;
  }

  // prepare data
  for (std::size_t i = 1; i <= OIR_NUMBER_FRAMEBITS; ++i) {
    if (command & 0x800) {
        _data[i].level0 = OIR_BIT1_LEVEL0;
        _data[i].duration0 = OIR_BIT1_DURATION0;
        _data[i].level1 = OIR_BIT1_LEVEL1;
        _data[i].duration1 = OIR_BIT1_DURATION1;
    } else {
        _data[i].level0 = OIR_BIT0_LEVEL0;
        _data[i].duration0 = OIR_BIT0_DURATION0;
        _data[i].level1 = OIR_BIT0_LEVEL1;
        _data[i].duration1 = OIR_BIT0_DURATION1;
    }
    command <<= 1;
  }

  // write
  if (rmtWriteAsync(_pin, &_data, OIR_NUMBER_FRAMEBITS)) {
    return true;
  }
  oir_log_e("Could not write to RMT");
  return false;
}

bool OnkyoRI_RMT::busy() {
  return !rmtTransmitCompleted(_pin);
}
