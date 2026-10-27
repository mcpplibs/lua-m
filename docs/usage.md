# Using mcpplibs.mwrap.lua

`import mcpplibs.mwrap.lua;` declares Lua 5.4.7's C API exactly as `<lua.h>`, `<lauxlib.h>` and `<lualib.h>` do. The names, types, signatures and behaviour are upstream's, and they are the very same entities as the header's (a translation unit may include the header too). The library is `compat.lua`, built from the same release.

## Modules

| Module | What it holds |
|---|---|
| `mcpplibs.mwrap.lua` | every function (`lua_*`, `luaL_*`, `luaopen_*`), type (`lua_State`, `lua_Debug`, `luaL_Reg`, `luaL_Buffer`, `luaL_Stream` …) and `lua_ident`; re-exports the one below |
| `mcpplibs.mwrap.lua.macros` | the macros, in `mcpplibs::mwrap::lua::macros` |

## Macros

A named module cannot export a macro. `mcpplibs::mwrap::lua::macros` has them under their original names:

- **Constants** as `inline constexpr`: `LUA_OK`, `LUA_TSTRING`, `LUA_MULTRET`, `LUA_REGISTRYINDEX`, `LUA_RIDX_GLOBALS`, `LUA_GCCOLLECT`, `LUA_MASKCALL` …; strings as arrays: `LUA_VERSION`, `LUA_RELEASE`, `LUA_COPYRIGHT`, `LUA_LOADED_TABLE`, `LUA_COLIBNAME` …; and the luaconf.h limits public macros are made of: `LUA_IDSIZE`, `LUAL_BUFFERSIZE`, `LUA_EXTRASPACE`, `LUAI_MAXSTACK`, `LUA_MAXINTEGER`, `LUA_MININTEGER`.
- **Function-like macros** as functions that evaluate their arguments as the macro does, once each, in the same order: `lua_pop`, `lua_tostring`, `lua_tonumber`, `lua_tointeger`, `lua_pcall`, `lua_call`, `lua_yield`, `lua_newtable`, `lua_register`, `lua_pushcfunction`, `lua_is*`, `lua_insert`, `lua_remove`, `lua_replace`, `lua_pushglobaltable`, `lua_upvalueindex` (constexpr), `luaL_dostring`, `luaL_dofile`, `luaL_loadbuffer`, `luaL_checkstring`, `luaL_typename`, `luaL_getmetatable`, `luaL_checkversion`, the `luaL_Buffer` helpers …
- **Templates** where the macro needs a literal or an array: `lua_pushliteral(L, "text")`, `luaL_newlibtable(L, regs)`, `luaL_newlib(L, regs)`.
- `luaL_dostring` and `luaL_dofile` return `bool` (true on an error), as the macros' `||` does.

`using namespace mcpplibs::mwrap::lua::macros;` makes code read as it does in C.

### What stays a macro

Five macros cannot be functions without changing what they evaluate. They stay macros in `<mwrap/lua/macros.hpp>`, which is `<lua.hpp>`:

| Macro | Why |
|---|---|
| `luaL_argcheck`, `luaL_argexpected` | the message or type name is evaluated only when the check fails |
| `luaL_opt` | evaluates the default or the call, not both |
| `luaL_intop` | pastes an operator between its operands |
| `lua_writestring`, `lua_writeline`, `lua_writestringerror` | the standalone interpreter's stdio helpers |

Include it before the import. While a header's macro is defined it expands even inside a qualified name, so `macros::LUA_OK` is not reachable there; use the plain `LUA_OK` (see [tests/header_mix_test.cpp](../tests/header_mix_test.cpp)).

Not mapped: the include guards, and `lua_pushunsigned`, `luaL_checkint` and the other `LUA_COMPAT_APIINTCASTS` aliases, which this build does not define. [tools/check_exports.py](../tools/check_exports.py) accounts for every macro of the three headers.

## Checks

- `mcpp test`: the C API through the module (states, the stack, C functions and closures, `lua_pcall` errors, userdata and metatables, the registry, buffers, coroutines), the mapped constants, and the header mixed with the import.
- `python3 tools/check_exports.py`: every declaration of the three headers is exported, every macro mapped or listed with its reason; the headers come from the pinned release tarball.
- `python3 tools/run_conformance.py`: Lua's own test suite (`lua-5.4.7-tests`, the portable user tests, `lua -e"_U=true" all.lua`) on [examples/lua](../examples/lua), a standalone interpreter written against the module.
