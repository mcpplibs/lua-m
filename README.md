# lua

> Lua 5.4, the embeddable scripting language, through C++23 modules.

**English** · [简体中文](README.zh.md) · [Upstream](https://www.lua.org) · [Releases](https://github.com/mcpplibs/lua-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [Index](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/lua-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/lua-m/actions/workflows/ci.yml)

The upstream C API is unchanged: `lua_State`, `lua_pushinteger`, `luaL_newstate`,
`luaopen_base` are the upstream globals of `<lua.h>`, `<lauxlib.h>` and
`<lualib.h>`. The library is `compat.lua` 5.4.7; this package maps Lua's macros
to constants and functions under their original names. Lua's own test suite
passes on every CI run, on a standalone interpreter written against the module.

## Modules

- `import mcpplibs.mwrap.lua;`: the C API (`lua_*`, `luaL_*`, `luaopen_*`, the types), re-exporting the one below
- `import mcpplibs.mwrap.lua.macros;`: `LUA_OK`, `lua_pop`, `lua_tostring`, `luaL_dostring` … in `mcpplibs::mwrap::lua::macros`

> More Modules API -> [Usage and API](docs/usage.md)

## Getting started

```sh
mcpp new scripted --template mcpplibs.mwrap.lua@5.4.7
cd scripted
mcpp run
```

The default template registers a C++ function, runs a script that calls it, and
prints what the script returns.

```toml
[dependencies]
"mcpplibs.mwrap.lua" = "5.4.7"
```

```cpp
import std;
import mcpplibs.mwrap.lua;
using namespace mcpplibs::mwrap::lua::macros;  // lua_pop, lua_tostring, LUA_OK …

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_dostring(L, "return ('modules'):upper()")) std::println("error: {}", lua_tostring(L, -1));
    else std::println("{}", lua_tostring(L, -1));
    lua_close(L);
}
```

## Macros

A named module cannot export a macro. Constants are `inline constexpr`
(`macros::LUA_OK`, `macros::LUA_REGISTRYINDEX`, `macros::LUA_VERSION`), and
function-like macros are functions that evaluate their arguments as the macro
does (`lua_pop`, `lua_pcall`, `lua_upvalueindex`, `luaL_newlib` …).
`luaL_argcheck`, `luaL_argexpected`, `luaL_opt` and `luaL_intop` cannot be
functions without changing what they evaluate; they stay macros in
`<mwrap/lua/macros.hpp>`, included before the import. The table of every macro
and why is in [docs/usage.md](docs/usage.md).

## Examples

- [examples/lua](examples/lua): a standalone interpreter, `lua [-e stat] [-l name] [-v] [script [args]]`,
  written against the module; [tools/run_conformance.py](tools/run_conformance.py) runs Lua's test suite on it.

## Build and testing

Linux, macOS and Windows CI build the modules and run the tests, the export
audit ([tools/check_exports.py](tools/check_exports.py): every declaration of the
three headers exported, every macro mapped or listed with its reason) and Lua's
own test suite (`lua-5.4.7-tests`). A separate job scaffolds the default
template as an installed package and runs it.

## License

[Apache-2.0](LICENSE) for the wrapper, by mcpp-community; Lua remains MIT
([upstream/lua/LICENSE](upstream/lua/LICENSE)).
