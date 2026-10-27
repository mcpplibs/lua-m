// <mwrap/lua/macros.hpp> — Lua's macros as macros, for the ones a function
// cannot be: luaL_argcheck, luaL_argexpected and luaL_opt (an argument that
// is evaluated only on one branch), luaL_intop (an operator pasted in), and
// lua_writestring / lua_writeline / lua_writestringerror. Include it before
// `import mcpplibs.mwrap.lua;`: it is <lua.hpp>, so every other macro is
// defined too, and while a macro is defined it expands even inside
// `mcpplibs::mwrap::lua::macros::NAME`.
#pragma once
#include <lua.hpp>
