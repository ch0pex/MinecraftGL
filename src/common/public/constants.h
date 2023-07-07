#pragma once

#include "primitive_types.h"

constexpr u8 kChunkSize = 16;
constexpr u16 kChunkletVolume = kChunkSize * kChunkSize * kChunkSize;
constexpr u32 kChunkVolume = kChunkletVolume * 16;
constexpr u8 kWaterLevel = 60;
constexpr u8 kMaxHeight = 255;
constexpr u8 kMinHeight = 0;



