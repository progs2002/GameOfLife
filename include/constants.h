#pragma once
#include <stdint-gcc.h>
#include "utils.h"

extern RES size;

const uint8_t cell_size = 40;
const uint16_t rows = size.H / cell_size;
const uint16_t cols = size.W / cell_size;

