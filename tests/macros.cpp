import mcpplibs.mwrap.lua.macros;
namespace macros = mcpplibs::mwrap::lua::macros;
static_assert(macros::LUA_VERSION_NUM == 504 && macros::LUA_VERSION_RELEASE_NUM == 50407);
static_assert(macros::LUA_OK == 0 && macros::LUA_YIELD == 1 && macros::LUA_ERRFILE == macros::LUA_ERRERR + 1);
static_assert(macros::LUA_TNONE == -1 && macros::LUA_NUMTYPES == 9 && macros::LUA_NUMTAGS == macros::LUA_NUMTYPES);
static_assert(macros::LUA_REGISTRYINDEX == -macros::LUAI_MAXSTACK - 1000);
static_assert(macros::lua_upvalueindex(1) == macros::LUA_REGISTRYINDEX - 1);
static_assert(macros::LUA_MASKCALL == 1 << macros::LUA_HOOKCALL && macros::LUA_MASKCOUNT == 1 << macros::LUA_HOOKCOUNT);
static_assert(macros::LUA_MULTRET == -1 && macros::LUA_NOREF == -2 && macros::LUA_REFNIL == -1);
static_assert(sizeof macros::LUA_SIGNATURE == 5 && macros::LUA_SIGNATURE[0] == '\x1b');
static_assert(macros::LUA_MAXINTEGER > 0 && macros::LUA_MININTEGER < 0);
int main() { return macros::LUA_VERSUFFIX[0] == '_' && macros::LUA_IDSIZE == 60 ? 0 : 1; }
