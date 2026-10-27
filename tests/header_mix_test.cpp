// The raw header and the import in one translation unit (the side header
// first, the canonical order): the module's names are the very same
// entities, and the macros a function cannot be work beside them. While a
// header's macro is defined it expands even inside a qualified name, so
// `macros::LUA_OK` is only reachable with the macro set aside.
#include <mwrap/lua/macros.hpp>
#include <gtest/gtest.h>

import std;
import mcpplibs.mwrap.lua;

namespace {
constexpr int raw_ok = LUA_OK, raw_registry = LUA_REGISTRYINDEX;

int checked(lua_State* L) {
    const lua_Integer n = luaL_checkinteger(L, 1);
    luaL_argcheck(L, n > 0, 1, "must be positive");  // the macro: the message only on failure
    lua_pushinteger(L, luaL_opt(L, luaL_checkinteger, 2, 10) * n);
    return 1;
}
}  // namespace

#pragma push_macro("LUA_OK")
#pragma push_macro("LUA_REGISTRYINDEX")
#undef LUA_OK
#undef LUA_REGISTRYINDEX
static_assert(mcpplibs::mwrap::lua::macros::LUA_OK == raw_ok);
static_assert(mcpplibs::mwrap::lua::macros::LUA_REGISTRYINDEX == raw_registry);
#pragma pop_macro("LUA_REGISTRYINDEX")
#pragma pop_macro("LUA_OK")

TEST(HeaderMix, SameEntities) {
    static_assert(std::is_same_v<decltype(&::lua_gettop), int (*)(lua_State*)>);
    static_assert(std::is_same_v<luaL_Reg, ::luaL_Reg>);
    lua_State* L = luaL_newstate();
    lua_pushcfunction(L, checked);  // the macro again
    lua_setglobal(L, "checked");
    EXPECT_EQ(luaL_dostring(L, "return checked(4)"), LUA_OK);
    EXPECT_EQ(lua_tointeger(L, -1), 40);
    EXPECT_NE(luaL_dostring(L, "return checked(-1)"), LUA_OK);
    EXPECT_NE(std::string(lua_tostring(L, -1)).find("must be positive"), std::string::npos);
    lua_close(L);
}
