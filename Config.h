#pragma once
#include <cstdint>

#include "Rect.h"

constexpr uint32_t kClientWidth = 1280;
constexpr uint32_t kClientHeight = 720;

extern float gravity;
extern Rect viewport;

extern float reductionFactor;
extern bool bDrawDebug;