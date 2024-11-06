/*
Copyright (c) 2024 Bert Melis. All rights reserved.

This work is licensed under the terms of the MIT license.  
For a copy, see <https://opensource.org/licenses/MIT> or
the LICENSE file.
*/

#pragma once

#include <esp32-hal-log.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#if defined(DEBUG_ONKYORI)
// Logging is en/disabled by Arduino framework macros
#define ori_log_i(...) log_i(__VA_ARGS__)
#define ori_log_e(...) log_e(__VA_ARGS__)
#define ori_log_w(...) log_w(__VA_ARGS__)
#else
// Logging is disabled
#define ori_log_i(...)
#define ori_log_e(...)
#define ori_log_w(...)
#endif
