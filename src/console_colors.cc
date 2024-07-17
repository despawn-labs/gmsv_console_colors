//
// Copyright (c) 2024 - despawn.dev, All rights reserved.
//

#include <Windows.h>

#include "GarrysMod/Lua/Interface.h"
#include "GarrysMod/Lua/Types.h"
#include "console_colors.h"

uint32_t g_original_console_mode;

LUA_FUNCTION(MsgC) {
  using namespace GarrysMod::Lua;

  auto n_args = LUA->Top();

  printf("\x1B[0;39m");

  for (int i = 0; i < n_args; i++) {
    auto ri = -(n_args - i);

    switch (LUA->GetType(ri)) {
    case Type::String: {
      auto string = LUA->GetString(ri);
      printf("%s", string);
      break;
    }
    case Type::Table: {
      LUA->GetField(ri, "r");
      if (!LUA->IsType(-1, Type::Number))
        LUA->ThrowError("missing r property");
      auto r = (int)LUA->GetNumber();
      LUA->Pop();
      if (r > 255 || r < 0)
        LUA->ThrowError("r is out of range (0-255)");

      LUA->GetField(ri, "g");
      if (!LUA->IsType(-1, Type::Number))
        LUA->ThrowError("missing g property");
      auto g = (int)LUA->GetNumber();
      LUA->Pop();
      if (g > 255 || g < 0)
        LUA->ThrowError("g is out of range (0-255)");

      LUA->GetField(ri, "b");
      if (!LUA->IsType(-1, Type::Number))
        LUA->ThrowError("missing b property");
      auto b = (int)LUA->GetNumber();
      LUA->Pop();
      if (b > 255 || b < 0)
        LUA->ThrowError("b is out of range (0-255)");

      printf("\x1B[38;2;%d;%d;%dm", r, g, b);
      break;
    }
    default:
      LUA->PushSpecial(SPECIAL_GLOB);
      LUA->GetField(-1, "tostring");
      LUA->Push(ri - 2);
      LUA->Call(1, 1);

      printf("%s", LUA->GetString(-1));
      LUA->Pop(2);
    }
  }

  printf("\x1B[0;39m");

  return 0;
}

GMOD_MODULE_OPEN() {
  auto stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);

  DBG("Loading console colors.");

  if (!GetConsoleMode(stdout_handle,
                      reinterpret_cast<LPDWORD>(&g_original_console_mode))) {
    DBG("Failed to get console mode: %08lx", GetLastError());
    return 1;
  }

  if (!SetConsoleMode(stdout_handle, g_original_console_mode |
                                         ENABLE_VIRTUAL_TERMINAL_PROCESSING |
                                         ENABLE_PROCESSED_OUTPUT)) {
    DBG("Failed to set console mode: %08lx", GetLastError());
    return 1;
  }

  LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
  LUA->PushString("MsgC");
  LUA->PushNil();
  LUA->SetTable(-3);

  LUA->PushString("MsgC");
  LUA->PushCFunction(MsgC);
  LUA->SetTable(-3);

  return 0;
}

GMOD_MODULE_CLOSE() {
  auto stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);

  DBG("Shutting down console colors.");

  if (!SetConsoleMode(stdout_handle, g_original_console_mode)) {
    DBG("Failed to reset console mode: %08lx", GetLastError());
    return 1;
  }

  return 0;
}