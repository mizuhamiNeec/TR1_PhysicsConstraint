#pragma once
#include <cstdint>

#include "Rect.h"

constexpr uint32_t kClientWidth = 1920;
constexpr uint32_t kClientHeight = 1080;

extern float gravity;
extern Rect viewport;

extern float reductionFactor;
extern bool bDrawDebug;