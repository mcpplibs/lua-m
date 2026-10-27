// mcpplibs.mwrap.lua.macros — the macros of <lua.h>, <lauxlib.h> and
// <lualib.h> (a named module cannot export a macro), under their original
// names in mcpplibs::mwrap::lua::macros:
//
//   - object-like constants as `inline constexpr` values (strings as
//     `const char[]`), with the luaconf.h limits public macros are made of
//     (LUA_IDSIZE, LUAL_BUFFERSIZE, LUA_EXTRASPACE, LUAI_MAXSTACK,
//     LUA_MAXINTEGER, LUA_MININTEGER);
//   - function-like macros as functions that evaluate their arguments as the
//     macro does: once each, in the same order. lua_pushliteral, and
//     luaL_newlibtable / luaL_newlib, are templates over an array, as the
//     macros need a literal or an array.
//
// luaL_argcheck, luaL_argexpected and luaL_opt evaluate an argument only on
// one branch, luaL_intop pastes an operator, and lua_writestring /
// lua_writeline / lua_writestringerror are the standalone interpreter's
// stdio helpers: those stay macros, in <mwrap/lua/macros.hpp>, included
// before the import. tools/check_exports.py accounts for every macro.
module;
#include <lua.hpp>

namespace mwrap_lua_capture {
inline constexpr int value_LUA_VERSION_MAJOR_N = LUA_VERSION_NUM / 100;
inline constexpr int value_LUA_VERSION_NUM = LUA_VERSION_NUM;
inline constexpr int value_LUA_VERSION_RELEASE_NUM = LUA_VERSION_RELEASE_NUM;
inline constexpr char value_LUA_VERSION_MAJOR[] = LUA_VERSION_MAJOR;
inline constexpr char value_LUA_VERSION_MINOR[] = LUA_VERSION_MINOR;
inline constexpr char value_LUA_VERSION_RELEASE[] = LUA_VERSION_RELEASE;
inline constexpr char value_LUA_VERSION[] = LUA_VERSION;
inline constexpr char value_LUA_RELEASE[] = LUA_RELEASE;
inline constexpr char value_LUA_COPYRIGHT[] = LUA_COPYRIGHT;
inline constexpr char value_LUA_AUTHORS[] = LUA_AUTHORS;
inline constexpr char value_LUA_SIGNATURE[] = LUA_SIGNATURE;
inline constexpr int value_LUA_MULTRET = LUA_MULTRET;
inline constexpr int value_LUA_REGISTRYINDEX = LUA_REGISTRYINDEX;
inline constexpr int value_LUA_OK = LUA_OK;
inline constexpr int value_LUA_YIELD = LUA_YIELD;
inline constexpr int value_LUA_ERRRUN = LUA_ERRRUN;
inline constexpr int value_LUA_ERRSYNTAX = LUA_ERRSYNTAX;
inline constexpr int value_LUA_ERRMEM = LUA_ERRMEM;
inline constexpr int value_LUA_ERRERR = LUA_ERRERR;
inline constexpr int value_LUA_TNONE = LUA_TNONE;
inline constexpr int value_LUA_TNIL = LUA_TNIL;
inline constexpr int value_LUA_TBOOLEAN = LUA_TBOOLEAN;
inline constexpr int value_LUA_TLIGHTUSERDATA = LUA_TLIGHTUSERDATA;
inline constexpr int value_LUA_TNUMBER = LUA_TNUMBER;
inline constexpr int value_LUA_TSTRING = LUA_TSTRING;
inline constexpr int value_LUA_TTABLE = LUA_TTABLE;
inline constexpr int value_LUA_TFUNCTION = LUA_TFUNCTION;
inline constexpr int value_LUA_TUSERDATA = LUA_TUSERDATA;
inline constexpr int value_LUA_TTHREAD = LUA_TTHREAD;
inline constexpr int value_LUA_NUMTYPES = LUA_NUMTYPES;
inline constexpr int value_LUA_NUMTAGS = LUA_NUMTAGS;
inline constexpr int value_LUA_MINSTACK = LUA_MINSTACK;
inline constexpr int value_LUA_RIDX_MAINTHREAD = LUA_RIDX_MAINTHREAD;
inline constexpr int value_LUA_RIDX_GLOBALS = LUA_RIDX_GLOBALS;
inline constexpr int value_LUA_RIDX_LAST = LUA_RIDX_LAST;
inline constexpr int value_LUA_OPADD = LUA_OPADD;
inline constexpr int value_LUA_OPSUB = LUA_OPSUB;
inline constexpr int value_LUA_OPMUL = LUA_OPMUL;
inline constexpr int value_LUA_OPMOD = LUA_OPMOD;
inline constexpr int value_LUA_OPPOW = LUA_OPPOW;
inline constexpr int value_LUA_OPDIV = LUA_OPDIV;
inline constexpr int value_LUA_OPIDIV = LUA_OPIDIV;
inline constexpr int value_LUA_OPBAND = LUA_OPBAND;
inline constexpr int value_LUA_OPBOR = LUA_OPBOR;
inline constexpr int value_LUA_OPBXOR = LUA_OPBXOR;
inline constexpr int value_LUA_OPSHL = LUA_OPSHL;
inline constexpr int value_LUA_OPSHR = LUA_OPSHR;
inline constexpr int value_LUA_OPUNM = LUA_OPUNM;
inline constexpr int value_LUA_OPBNOT = LUA_OPBNOT;
inline constexpr int value_LUA_OPEQ = LUA_OPEQ;
inline constexpr int value_LUA_OPLT = LUA_OPLT;
inline constexpr int value_LUA_OPLE = LUA_OPLE;
inline constexpr int value_LUA_GCSTOP = LUA_GCSTOP;
inline constexpr int value_LUA_GCRESTART = LUA_GCRESTART;
inline constexpr int value_LUA_GCCOLLECT = LUA_GCCOLLECT;
inline constexpr int value_LUA_GCCOUNT = LUA_GCCOUNT;
inline constexpr int value_LUA_GCCOUNTB = LUA_GCCOUNTB;
inline constexpr int value_LUA_GCSTEP = LUA_GCSTEP;
inline constexpr int value_LUA_GCSETPAUSE = LUA_GCSETPAUSE;
inline constexpr int value_LUA_GCSETSTEPMUL = LUA_GCSETSTEPMUL;
inline constexpr int value_LUA_GCISRUNNING = LUA_GCISRUNNING;
inline constexpr int value_LUA_GCGEN = LUA_GCGEN;
inline constexpr int value_LUA_GCINC = LUA_GCINC;
inline constexpr int value_LUA_HOOKCALL = LUA_HOOKCALL;
inline constexpr int value_LUA_HOOKRET = LUA_HOOKRET;
inline constexpr int value_LUA_HOOKLINE = LUA_HOOKLINE;
inline constexpr int value_LUA_HOOKCOUNT = LUA_HOOKCOUNT;
inline constexpr int value_LUA_HOOKTAILCALL = LUA_HOOKTAILCALL;
inline constexpr int value_LUA_MASKCALL = LUA_MASKCALL;
inline constexpr int value_LUA_MASKRET = LUA_MASKRET;
inline constexpr int value_LUA_MASKLINE = LUA_MASKLINE;
inline constexpr int value_LUA_MASKCOUNT = LUA_MASKCOUNT;
inline constexpr char value_LUA_GNAME[] = LUA_GNAME;
inline constexpr int value_LUA_ERRFILE = LUA_ERRFILE;
inline constexpr char value_LUA_LOADED_TABLE[] = LUA_LOADED_TABLE;
inline constexpr char value_LUA_PRELOAD_TABLE[] = LUA_PRELOAD_TABLE;
inline constexpr size_t value_LUAL_NUMSIZES = LUAL_NUMSIZES;
inline constexpr int value_LUA_NOREF = LUA_NOREF;
inline constexpr int value_LUA_REFNIL = LUA_REFNIL;
inline constexpr char value_LUA_FILEHANDLE[] = LUA_FILEHANDLE;
inline constexpr char value_LUA_VERSUFFIX[] = LUA_VERSUFFIX;
inline constexpr char value_LUA_COLIBNAME[] = LUA_COLIBNAME;
inline constexpr char value_LUA_TABLIBNAME[] = LUA_TABLIBNAME;
inline constexpr char value_LUA_IOLIBNAME[] = LUA_IOLIBNAME;
inline constexpr char value_LUA_OSLIBNAME[] = LUA_OSLIBNAME;
inline constexpr char value_LUA_STRLIBNAME[] = LUA_STRLIBNAME;
inline constexpr char value_LUA_UTF8LIBNAME[] = LUA_UTF8LIBNAME;
inline constexpr char value_LUA_MATHLIBNAME[] = LUA_MATHLIBNAME;
inline constexpr char value_LUA_DBLIBNAME[] = LUA_DBLIBNAME;
inline constexpr char value_LUA_LOADLIBNAME[] = LUA_LOADLIBNAME;
inline constexpr int value_LUA_IDSIZE = LUA_IDSIZE;
inline constexpr int value_LUAL_BUFFERSIZE = LUAL_BUFFERSIZE;
inline constexpr size_t value_LUA_EXTRASPACE = LUA_EXTRASPACE;
inline constexpr int value_LUAI_MAXSTACK = LUAI_MAXSTACK;
inline constexpr lua_Integer value_LUA_MAXINTEGER = LUA_MAXINTEGER;
inline constexpr lua_Integer value_LUA_MININTEGER = LUA_MININTEGER;
}  // namespace mwrap_lua_capture

// Every mapped name, so the definitions below are not rewritten.
#undef LUA_VERSION_MAJOR
#undef LUA_VERSION_MINOR
#undef LUA_VERSION_RELEASE
#undef LUA_VERSION_NUM
#undef LUA_VERSION_RELEASE_NUM
#undef LUA_VERSION
#undef LUA_RELEASE
#undef LUA_COPYRIGHT
#undef LUA_AUTHORS
#undef LUA_SIGNATURE
#undef LUA_MULTRET
#undef LUA_REGISTRYINDEX
#undef lua_upvalueindex
#undef LUA_OK
#undef LUA_YIELD
#undef LUA_ERRRUN
#undef LUA_ERRSYNTAX
#undef LUA_ERRMEM
#undef LUA_ERRERR
#undef LUA_TNONE
#undef LUA_TNIL
#undef LUA_TBOOLEAN
#undef LUA_TLIGHTUSERDATA
#undef LUA_TNUMBER
#undef LUA_TSTRING
#undef LUA_TTABLE
#undef LUA_TFUNCTION
#undef LUA_TUSERDATA
#undef LUA_TTHREAD
#undef LUA_NUMTYPES
#undef LUA_NUMTAGS
#undef LUA_MINSTACK
#undef LUA_RIDX_MAINTHREAD
#undef LUA_RIDX_GLOBALS
#undef LUA_RIDX_LAST
#undef LUA_OPADD
#undef LUA_OPSUB
#undef LUA_OPMUL
#undef LUA_OPMOD
#undef LUA_OPPOW
#undef LUA_OPDIV
#undef LUA_OPIDIV
#undef LUA_OPBAND
#undef LUA_OPBOR
#undef LUA_OPBXOR
#undef LUA_OPSHL
#undef LUA_OPSHR
#undef LUA_OPUNM
#undef LUA_OPBNOT
#undef LUA_OPEQ
#undef LUA_OPLT
#undef LUA_OPLE
#undef lua_call
#undef lua_pcall
#undef lua_yield
#undef LUA_GCSTOP
#undef LUA_GCRESTART
#undef LUA_GCCOLLECT
#undef LUA_GCCOUNT
#undef LUA_GCCOUNTB
#undef LUA_GCSTEP
#undef LUA_GCSETPAUSE
#undef LUA_GCSETSTEPMUL
#undef LUA_GCISRUNNING
#undef LUA_GCGEN
#undef LUA_GCINC
#undef lua_getextraspace
#undef lua_tonumber
#undef lua_tointeger
#undef lua_pop
#undef lua_newtable
#undef lua_register
#undef lua_pushcfunction
#undef lua_isfunction
#undef lua_istable
#undef lua_islightuserdata
#undef lua_isnil
#undef lua_isboolean
#undef lua_isthread
#undef lua_isnone
#undef lua_isnoneornil
#undef lua_pushliteral
#undef lua_pushglobaltable
#undef lua_tostring
#undef lua_insert
#undef lua_remove
#undef lua_replace
#undef lua_newuserdata
#undef lua_getuservalue
#undef lua_setuservalue
#undef LUA_HOOKCALL
#undef LUA_HOOKRET
#undef LUA_HOOKLINE
#undef LUA_HOOKCOUNT
#undef LUA_HOOKTAILCALL
#undef LUA_MASKCALL
#undef LUA_MASKRET
#undef LUA_MASKLINE
#undef LUA_MASKCOUNT
#undef LUA_GNAME
#undef LUA_ERRFILE
#undef LUA_LOADED_TABLE
#undef LUA_PRELOAD_TABLE
#undef LUAL_NUMSIZES
#undef luaL_checkversion
#undef LUA_NOREF
#undef LUA_REFNIL
#undef luaL_loadfile
#undef luaL_newlibtable
#undef luaL_newlib
#undef luaL_checkstring
#undef luaL_optstring
#undef luaL_typename
#undef luaL_dofile
#undef luaL_dostring
#undef luaL_getmetatable
#undef luaL_loadbuffer
#undef luaL_pushfail
#undef luaL_bufflen
#undef luaL_buffaddr
#undef luaL_addchar
#undef luaL_addsize
#undef luaL_buffsub
#undef luaL_prepbuffer
#undef LUA_FILEHANDLE
#undef LUA_VERSUFFIX
#undef LUA_COLIBNAME
#undef LUA_TABLIBNAME
#undef LUA_IOLIBNAME
#undef LUA_OSLIBNAME
#undef LUA_STRLIBNAME
#undef LUA_UTF8LIBNAME
#undef LUA_MATHLIBNAME
#undef LUA_DBLIBNAME
#undef LUA_LOADLIBNAME
#undef LUA_IDSIZE
#undef LUAL_BUFFERSIZE
#undef LUA_EXTRASPACE
#undef LUAI_MAXSTACK
#undef LUA_MAXINTEGER
#undef LUA_MININTEGER

export module mcpplibs.mwrap.lua.macros;

namespace c = mwrap_lua_capture;

export namespace mcpplibs::mwrap::lua::macros {

// ── <lua.h> ──────────────────────────────────────────────────────────────
inline constexpr auto& LUA_VERSION_MAJOR = c::value_LUA_VERSION_MAJOR;
inline constexpr auto& LUA_VERSION_MINOR = c::value_LUA_VERSION_MINOR;
inline constexpr auto& LUA_VERSION_RELEASE = c::value_LUA_VERSION_RELEASE;
inline constexpr int LUA_VERSION_NUM = c::value_LUA_VERSION_NUM;
inline constexpr int LUA_VERSION_RELEASE_NUM = c::value_LUA_VERSION_RELEASE_NUM;
inline constexpr auto& LUA_VERSION = c::value_LUA_VERSION;
inline constexpr auto& LUA_RELEASE = c::value_LUA_RELEASE;
inline constexpr auto& LUA_COPYRIGHT = c::value_LUA_COPYRIGHT;
inline constexpr auto& LUA_AUTHORS = c::value_LUA_AUTHORS;
inline constexpr auto& LUA_SIGNATURE = c::value_LUA_SIGNATURE;
inline constexpr int LUA_MULTRET = c::value_LUA_MULTRET;
inline constexpr int LUA_REGISTRYINDEX = c::value_LUA_REGISTRYINDEX;
inline constexpr int LUA_OK = c::value_LUA_OK;
inline constexpr int LUA_YIELD = c::value_LUA_YIELD;
inline constexpr int LUA_ERRRUN = c::value_LUA_ERRRUN;
inline constexpr int LUA_ERRSYNTAX = c::value_LUA_ERRSYNTAX;
inline constexpr int LUA_ERRMEM = c::value_LUA_ERRMEM;
inline constexpr int LUA_ERRERR = c::value_LUA_ERRERR;
inline constexpr int LUA_TNONE = c::value_LUA_TNONE;
inline constexpr int LUA_TNIL = c::value_LUA_TNIL;
inline constexpr int LUA_TBOOLEAN = c::value_LUA_TBOOLEAN;
inline constexpr int LUA_TLIGHTUSERDATA = c::value_LUA_TLIGHTUSERDATA;
inline constexpr int LUA_TNUMBER = c::value_LUA_TNUMBER;
inline constexpr int LUA_TSTRING = c::value_LUA_TSTRING;
inline constexpr int LUA_TTABLE = c::value_LUA_TTABLE;
inline constexpr int LUA_TFUNCTION = c::value_LUA_TFUNCTION;
inline constexpr int LUA_TUSERDATA = c::value_LUA_TUSERDATA;
inline constexpr int LUA_TTHREAD = c::value_LUA_TTHREAD;
inline constexpr int LUA_NUMTYPES = c::value_LUA_NUMTYPES;
inline constexpr int LUA_NUMTAGS = c::value_LUA_NUMTAGS;
inline constexpr int LUA_MINSTACK = c::value_LUA_MINSTACK;
inline constexpr int LUA_RIDX_MAINTHREAD = c::value_LUA_RIDX_MAINTHREAD;
inline constexpr int LUA_RIDX_GLOBALS = c::value_LUA_RIDX_GLOBALS;
inline constexpr int LUA_RIDX_LAST = c::value_LUA_RIDX_LAST;
inline constexpr int LUA_OPADD = c::value_LUA_OPADD;
inline constexpr int LUA_OPSUB = c::value_LUA_OPSUB;
inline constexpr int LUA_OPMUL = c::value_LUA_OPMUL;
inline constexpr int LUA_OPMOD = c::value_LUA_OPMOD;
inline constexpr int LUA_OPPOW = c::value_LUA_OPPOW;
inline constexpr int LUA_OPDIV = c::value_LUA_OPDIV;
inline constexpr int LUA_OPIDIV = c::value_LUA_OPIDIV;
inline constexpr int LUA_OPBAND = c::value_LUA_OPBAND;
inline constexpr int LUA_OPBOR = c::value_LUA_OPBOR;
inline constexpr int LUA_OPBXOR = c::value_LUA_OPBXOR;
inline constexpr int LUA_OPSHL = c::value_LUA_OPSHL;
inline constexpr int LUA_OPSHR = c::value_LUA_OPSHR;
inline constexpr int LUA_OPUNM = c::value_LUA_OPUNM;
inline constexpr int LUA_OPBNOT = c::value_LUA_OPBNOT;
inline constexpr int LUA_OPEQ = c::value_LUA_OPEQ;
inline constexpr int LUA_OPLT = c::value_LUA_OPLT;
inline constexpr int LUA_OPLE = c::value_LUA_OPLE;
inline constexpr int LUA_GCSTOP = c::value_LUA_GCSTOP;
inline constexpr int LUA_GCRESTART = c::value_LUA_GCRESTART;
inline constexpr int LUA_GCCOLLECT = c::value_LUA_GCCOLLECT;
inline constexpr int LUA_GCCOUNT = c::value_LUA_GCCOUNT;
inline constexpr int LUA_GCCOUNTB = c::value_LUA_GCCOUNTB;
inline constexpr int LUA_GCSTEP = c::value_LUA_GCSTEP;
inline constexpr int LUA_GCSETPAUSE = c::value_LUA_GCSETPAUSE;
inline constexpr int LUA_GCSETSTEPMUL = c::value_LUA_GCSETSTEPMUL;
inline constexpr int LUA_GCISRUNNING = c::value_LUA_GCISRUNNING;
inline constexpr int LUA_GCGEN = c::value_LUA_GCGEN;
inline constexpr int LUA_GCINC = c::value_LUA_GCINC;
inline constexpr int LUA_HOOKCALL = c::value_LUA_HOOKCALL;
inline constexpr int LUA_HOOKRET = c::value_LUA_HOOKRET;
inline constexpr int LUA_HOOKLINE = c::value_LUA_HOOKLINE;
inline constexpr int LUA_HOOKCOUNT = c::value_LUA_HOOKCOUNT;
inline constexpr int LUA_HOOKTAILCALL = c::value_LUA_HOOKTAILCALL;
inline constexpr int LUA_MASKCALL = c::value_LUA_MASKCALL;
inline constexpr int LUA_MASKRET = c::value_LUA_MASKRET;
inline constexpr int LUA_MASKLINE = c::value_LUA_MASKLINE;
inline constexpr int LUA_MASKCOUNT = c::value_LUA_MASKCOUNT;

// luaconf.h's limits that public macros and structures are made of.
inline constexpr int LUA_IDSIZE = c::value_LUA_IDSIZE;
inline constexpr int LUAL_BUFFERSIZE = c::value_LUAL_BUFFERSIZE;
inline constexpr size_t LUA_EXTRASPACE = c::value_LUA_EXTRASPACE;
inline constexpr int LUAI_MAXSTACK = c::value_LUAI_MAXSTACK;
inline constexpr lua_Integer LUA_MAXINTEGER = c::value_LUA_MAXINTEGER;
inline constexpr lua_Integer LUA_MININTEGER = c::value_LUA_MININTEGER;

constexpr int lua_upvalueindex(int i) noexcept { return LUA_REGISTRYINDEX - i; }

inline void lua_call(lua_State* L, int n, int r) { lua_callk(L, n, r, 0, nullptr); }
inline int lua_pcall(lua_State* L, int n, int r, int f) { return lua_pcallk(L, n, r, f, 0, nullptr); }
inline int lua_yield(lua_State* L, int n) { return lua_yieldk(L, n, 0, nullptr); }
inline void* lua_getextraspace(lua_State* L) { return static_cast<void*>(reinterpret_cast<char*>(L) - LUA_EXTRASPACE); }
inline lua_Number lua_tonumber(lua_State* L, int i) { return lua_tonumberx(L, i, nullptr); }
inline lua_Integer lua_tointeger(lua_State* L, int i) { return lua_tointegerx(L, i, nullptr); }
inline void lua_pop(lua_State* L, int n) { lua_settop(L, -n - 1); }
inline void lua_newtable(lua_State* L) { lua_createtable(L, 0, 0); }
inline void lua_pushcfunction(lua_State* L, lua_CFunction f) { lua_pushcclosure(L, f, 0); }
inline void lua_register(lua_State* L, const char* n, lua_CFunction f) {
    lua_pushcfunction(L, f);
    lua_setglobal(L, n);
}
inline bool lua_isfunction(lua_State* L, int n) { return lua_type(L, n) == LUA_TFUNCTION; }
inline bool lua_istable(lua_State* L, int n) { return lua_type(L, n) == LUA_TTABLE; }
inline bool lua_islightuserdata(lua_State* L, int n) { return lua_type(L, n) == LUA_TLIGHTUSERDATA; }
inline bool lua_isnil(lua_State* L, int n) { return lua_type(L, n) == LUA_TNIL; }
inline bool lua_isboolean(lua_State* L, int n) { return lua_type(L, n) == LUA_TBOOLEAN; }
inline bool lua_isthread(lua_State* L, int n) { return lua_type(L, n) == LUA_TTHREAD; }
inline bool lua_isnone(lua_State* L, int n) { return lua_type(L, n) == LUA_TNONE; }
inline bool lua_isnoneornil(lua_State* L, int n) { return lua_type(L, n) <= 0; }
// The macro pastes "" before its argument, so only a literal compiles; an
// array reference is as close as a function comes.
template <size_t N>
const char* lua_pushliteral(lua_State* L, const char (&s)[N]) { return lua_pushstring(L, s); }
inline void lua_pushglobaltable(lua_State* L) { static_cast<void>(lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS)); }
inline const char* lua_tostring(lua_State* L, int i) { return lua_tolstring(L, i, nullptr); }
inline void lua_insert(lua_State* L, int idx) { lua_rotate(L, idx, 1); }
inline void lua_remove(lua_State* L, int idx) {
    lua_rotate(L, idx, -1);
    lua_pop(L, 1);
}
inline void lua_replace(lua_State* L, int idx) {
    lua_copy(L, -1, idx);
    lua_pop(L, 1);
}
inline void* lua_newuserdata(lua_State* L, size_t s) { return lua_newuserdatauv(L, s, 1); }
inline int lua_getuservalue(lua_State* L, int idx) { return lua_getiuservalue(L, idx, 1); }
inline int lua_setuservalue(lua_State* L, int idx) { return lua_setiuservalue(L, idx, 1); }

// ── <lauxlib.h> ──────────────────────────────────────────────────────────
inline constexpr auto& LUA_GNAME = c::value_LUA_GNAME;
inline constexpr int LUA_ERRFILE = c::value_LUA_ERRFILE;
inline constexpr auto& LUA_LOADED_TABLE = c::value_LUA_LOADED_TABLE;
inline constexpr auto& LUA_PRELOAD_TABLE = c::value_LUA_PRELOAD_TABLE;
inline constexpr size_t LUAL_NUMSIZES = c::value_LUAL_NUMSIZES;
inline constexpr int LUA_NOREF = c::value_LUA_NOREF;
inline constexpr int LUA_REFNIL = c::value_LUA_REFNIL;
inline constexpr auto& LUA_FILEHANDLE = c::value_LUA_FILEHANDLE;

inline void luaL_checkversion(lua_State* L) { luaL_checkversion_(L, LUA_VERSION_NUM, LUAL_NUMSIZES); }
inline int luaL_loadfile(lua_State* L, const char* f) { return luaL_loadfilex(L, f, nullptr); }
template <size_t N>
void luaL_newlibtable(lua_State* L, const luaL_Reg (&)[N]) { lua_createtable(L, 0, static_cast<int>(N - 1)); }
template <size_t N>
void luaL_newlib(lua_State* L, const luaL_Reg (&l)[N]) {
    luaL_checkversion(L);
    luaL_newlibtable(L, l);
    luaL_setfuncs(L, l, 0);
}
inline const char* luaL_checkstring(lua_State* L, int n) { return luaL_checklstring(L, n, nullptr); }
inline const char* luaL_optstring(lua_State* L, int n, const char* d) { return luaL_optlstring(L, n, d, nullptr); }
inline const char* luaL_typename(lua_State* L, int i) { return lua_typename(L, lua_type(L, i)); }
// `||`: the chunk runs only when it loaded; true on an error, as the macro is.
inline bool luaL_dofile(lua_State* L, const char* fn) { return luaL_loadfile(L, fn) || lua_pcall(L, 0, LUA_MULTRET, 0); }
inline bool luaL_dostring(lua_State* L, const char* s) { return luaL_loadstring(L, s) || lua_pcall(L, 0, LUA_MULTRET, 0); }
inline int luaL_getmetatable(lua_State* L, const char* n) { return lua_getfield(L, LUA_REGISTRYINDEX, n); }
inline int luaL_loadbuffer(lua_State* L, const char* s, size_t sz, const char* n) { return luaL_loadbufferx(L, s, sz, n, nullptr); }
inline void luaL_pushfail(lua_State* L) { lua_pushnil(L); }
inline size_t luaL_bufflen(luaL_Buffer* bf) { return bf->n; }
inline char* luaL_buffaddr(luaL_Buffer* bf) { return bf->b; }
inline void luaL_addchar(luaL_Buffer* B, char c) {
    static_cast<void>(B->n < B->size || luaL_prepbuffsize(B, 1));
    B->b[B->n++] = c;
}
inline void luaL_addsize(luaL_Buffer* B, size_t s) { B->n += s; }
inline void luaL_buffsub(luaL_Buffer* B, size_t s) { B->n -= s; }
inline char* luaL_prepbuffer(luaL_Buffer* B) { return luaL_prepbuffsize(B, LUAL_BUFFERSIZE); }

// ── <lualib.h> ───────────────────────────────────────────────────────────
inline constexpr auto& LUA_VERSUFFIX = c::value_LUA_VERSUFFIX;
inline constexpr auto& LUA_COLIBNAME = c::value_LUA_COLIBNAME;
inline constexpr auto& LUA_TABLIBNAME = c::value_LUA_TABLIBNAME;
inline constexpr auto& LUA_IOLIBNAME = c::value_LUA_IOLIBNAME;
inline constexpr auto& LUA_OSLIBNAME = c::value_LUA_OSLIBNAME;
inline constexpr auto& LUA_STRLIBNAME = c::value_LUA_STRLIBNAME;
inline constexpr auto& LUA_UTF8LIBNAME = c::value_LUA_UTF8LIBNAME;
inline constexpr auto& LUA_MATHLIBNAME = c::value_LUA_MATHLIBNAME;
inline constexpr auto& LUA_DBLIBNAME = c::value_LUA_DBLIBNAME;
inline constexpr auto& LUA_LOADLIBNAME = c::value_LUA_LOADLIBNAME;

}  // namespace mcpplibs::mwrap::lua::macros
