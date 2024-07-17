//
// Copyright (c) 2024 - despawn.dev, All rights reserved.
//

#ifndef CONSOLE_COLORS_SRC_CONSOLE_COLORS_H_
#define CONSOLE_COLORS_SRC_CONSOLE_COLORS_H_

#include <cstdio>

#ifdef CONSOLE_COLORS_DEBUG
#define DBG(fmt, ...) printf("console_colors - DEBUG: " fmt "\n", __VA_ARGS__)
#else
#define DBG(fmt, ...)
#endif

#endif // CONSOLE_COLORS_SRC_CONSOLE_COLORS_H_
