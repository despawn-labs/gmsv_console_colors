# gmsv_console_colors

A Windows server-side module for Garry's Mod adding back support for terminal colors by replacing the default `MsgC`
implementation.

Note that this is only really useful for development environments where you may have multiple different addons with
different styled loggers producing messages.

## Usage

### Pre-Compiled Binaries

1. Download the **correct*** binary
   from [the releases page](https://github.com/despawn-labs/gmsv_console_colors/releases).
2. Place the `.dll` file in `garrysmod/lua/bin` within your servers root directory.
3. Initialize the module via `require("console_colors")`. It's recommended to this in the server-side lua autorun
   directory.
4. `MsgC` is now replaced with an implementation supporting 24-bit color.

**You must download the correct binary for your server's architecture. If you didn't specify `-beta x86-64` in SteamCMD,
then you're running the 32-bit version of the server, and will need the 32-bit version of the module.*

### Manual Compilation

You'll need the following tools,

* Visual Studio (with MSVC++)
* CMake

The following must be ran within the `Developer Command Prompt for VS XXXX`, where *XXXX* is the Visual Studio version,

```batch
git clone https://github.com/despawn-labs/gmsv_console_colors.git
cd gmsv_console_colors

mkdir build && cd build
cmake ..
msbuild console_colors.sln
```