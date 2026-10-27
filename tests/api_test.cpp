// The Lua C API through the module: a state's lifecycle, the stack, C
// functions and closures called from Lua, errors through lua_pcall, userdata
// with metatables, the registry, string buffers and coroutines — every call
// spelled as <lua.h> documents it, the macros from the mapping.
#include <gtest/gtest.h>

import std;
import mcpplibs.mwrap.lua;

using namespace mcpplibs::mwrap::lua::macros;

namespace {

struct State {
    lua_State* L = luaL_newstate();
    State() { luaL_openlibs(L); }
    ~State() { lua_close(L); }
    State(const State&) = delete;
    State& operator=(const State&) = delete;
};

int add(lua_State* L) {
    lua_pushinteger(L, luaL_checkinteger(L, 1) + luaL_checkinteger(L, 2));
    return 1;
}

int counter(lua_State* L) {
    const lua_Integer n = lua_tointeger(L, lua_upvalueindex(1)) + 1;
    lua_pushinteger(L, n);
    lua_copy(L, -1, lua_upvalueindex(1));
    return 1;
}

struct Point {
    double x, y;
};

int point_length(lua_State* L) {
    auto* p = static_cast<Point*>(luaL_checkudata(L, 1, "Point"));
    lua_pushnumber(L, std::sqrt(p->x * p->x + p->y * p->y));
    return 1;
}

const luaL_Reg geometry[] = {{"add", add}, {nullptr, nullptr}};

}  // namespace

TEST(Api, StackAndTypes) {
    State s;
    lua_pushinteger(s.L, 42);
    lua_pushliteral(s.L, "hello");
    lua_pushboolean(s.L, 1);
    lua_pushnil(s.L);
    EXPECT_EQ(lua_gettop(s.L), 4);
    EXPECT_TRUE(lua_isnil(s.L, -1));
    EXPECT_TRUE(lua_isboolean(s.L, -2));
    EXPECT_STREQ(lua_tostring(s.L, -3), "hello");
    EXPECT_EQ(lua_tointeger(s.L, 1), 42);
    EXPECT_STREQ(luaL_typename(s.L, 2), "string");
    lua_insert(s.L, 1);  // nil to the bottom
    EXPECT_TRUE(lua_isnoneornil(s.L, 1));
    lua_remove(s.L, 1);
    lua_pop(s.L, 1);
    EXPECT_EQ(lua_gettop(s.L), 2);
    EXPECT_TRUE(lua_isnone(s.L, 3));
}

TEST(Api, ChunksCallCFunctionsAndClosures) {
    State s;
    lua_register(s.L, "add", add);
    lua_pushinteger(s.L, 0);
    lua_pushcclosure(s.L, counter, 1);
    lua_setglobal(s.L, "count");
    ASSERT_FALSE(luaL_dostring(s.L, "count(); count(); return add(40, count())"));
    EXPECT_EQ(lua_tointeger(s.L, -1), 43);
    luaL_newlib(s.L, geometry);
    lua_setglobal(s.L, "geometry");
    ASSERT_EQ(luaL_loadbuffer(s.L, "return geometry.add(1, 2)", 25, "=chunk"), LUA_OK);
    lua_call(s.L, 0, 1);
    EXPECT_EQ(lua_tointeger(s.L, -1), 3);
}

TEST(Api, ErrorsThroughPcall) {
    State s;
    ASSERT_EQ(luaL_loadstring(s.L, "error('nope')"), LUA_OK);
    EXPECT_EQ(lua_pcall(s.L, 0, 0, 0), LUA_ERRRUN);
    EXPECT_NE(std::string(lua_tostring(s.L, -1)).find("nope"), std::string::npos);
    EXPECT_EQ(luaL_loadstring(s.L, "return +"), LUA_ERRSYNTAX);
    lua_settop(s.L, 0);
    lua_register(s.L, "add", add);
    EXPECT_TRUE(luaL_dostring(s.L, "return add('x', 1)"));  // luaL_checkinteger raises
    EXPECT_NE(std::string(lua_tostring(s.L, -1)).find("bad argument #1"), std::string::npos);
}

TEST(Api, UserdataMetatablesAndTheRegistry) {
    State s;
    ASSERT_EQ(luaL_newmetatable(s.L, "Point"), 1);
    lua_pushcfunction(s.L, point_length);
    lua_setfield(s.L, -2, "__len");
    lua_pop(s.L, 1);
    auto* p = static_cast<Point*>(lua_newuserdatauv(s.L, sizeof(Point), 0));
    *p = {3, 4};
    luaL_setmetatable(s.L, "Point");
    EXPECT_EQ(luaL_testudata(s.L, -1, "Point"), p);
    lua_setglobal(s.L, "p");
    ASSERT_FALSE(luaL_dostring(s.L, "return #p"));
    EXPECT_DOUBLE_EQ(lua_tonumber(s.L, -1), 5.0);
    EXPECT_EQ(luaL_getmetatable(s.L, "Point"), LUA_TTABLE);
    lua_pushstring(s.L, "kept");
    const int ref = luaL_ref(s.L, LUA_REGISTRYINDEX);
    EXPECT_NE(ref, LUA_REFNIL);
    EXPECT_EQ(lua_rawgeti(s.L, LUA_REGISTRYINDEX, ref), LUA_TSTRING);
    EXPECT_STREQ(lua_tostring(s.L, -1), "kept");
    luaL_unref(s.L, LUA_REGISTRYINDEX, ref);
    lua_pushglobaltable(s.L);
    EXPECT_TRUE(lua_istable(s.L, -1));
}

TEST(Api, BuffersAndCoroutines) {
    State s;
    luaL_Buffer b;
    luaL_buffinit(s.L, &b);
    for (char c : std::string_view("module")) luaL_addchar(&b, c);
    luaL_addstring(&b, "s!");
    EXPECT_EQ(luaL_bufflen(&b), 8u);
    luaL_pushresult(&b);
    EXPECT_STREQ(lua_tostring(s.L, -1), "modules!");

    lua_State* co = lua_newthread(s.L);
    ASSERT_EQ(luaL_loadstring(co, "local a = coroutine.yield(1); return a * 2"), LUA_OK);
    int results = 0;
    EXPECT_EQ(lua_resume(co, s.L, 0, &results), LUA_YIELD);
    EXPECT_EQ(lua_tointeger(co, -1), 1);
    lua_pop(co, results);
    lua_pushinteger(co, 21);
    EXPECT_EQ(lua_resume(co, s.L, 1, &results), LUA_OK);
    EXPECT_EQ(lua_tointeger(co, -1), 42);
}

TEST(Api, VersionAndIdentity) {
    State s;
    EXPECT_EQ(lua_version(s.L), LUA_VERSION_NUM);
    EXPECT_NE(std::string_view(lua_ident).find("Lua 5.4.7"), std::string_view::npos);
    luaL_checkversion(s.L);
    EXPECT_EQ(std::string_view(LUA_VERSION), "Lua 5.4");
    EXPECT_EQ(std::string_view(LUA_RELEASE), "Lua 5.4.7");
}
