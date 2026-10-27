// lua — a standalone interpreter through import mcpplibs.mwrap.lua, the
// options upstream's lua.c documents that its test suite uses:
//
//   lua [-e stat] [-l name] [-v] [--] [script [args]]
//
// (`-estat` and `-lname`, the value attached, as lua.c takes them too.)
// `arg` holds the script at 0, its arguments after, and the interpreter and
// options before (negative indices), as lua.c builds it. An error is printed
// with a traceback and the exit status is 1.
import std;
import mcpplibs.mwrap.lua;

using namespace mcpplibs::mwrap::lua::macros;

namespace {

int traceback(lua_State* L) {
    const char* msg = lua_tostring(L, 1);
    if (!msg) {
        if (luaL_callmeta(L, 1, "__tostring") && lua_type(L, -1) == LUA_TSTRING) return 1;
        msg = lua_pushfstring(L, "(error object is a %s value)", luaL_typename(L, 1));
    }
    luaL_traceback(L, L, msg, 1);
    return 1;
}

// Calls the function under the arguments with a traceback handler; prints
// the error and says so.
bool call(lua_State* L, int nargs, int nresults) {
    const int base = lua_gettop(L) - nargs;
    lua_pushcfunction(L, traceback);
    lua_insert(L, base);
    const int status = lua_pcall(L, nargs, nresults, base);
    lua_remove(L, base);
    if (status != LUA_OK) {
        std::println(std::cerr, "lua: {}", lua_tostring(L, -1));
        lua_pop(L, 1);
        return false;
    }
    return true;
}

}  // namespace

int main(int argc, char** argv) {
    lua_State* L = luaL_newstate();
    if (!L) {
        std::println(std::cerr, "lua: cannot create state: not enough memory");
        return 1;
    }
    luaL_openlibs(L);
    int script = argc;  // the index of the script, or argc
    bool ok = true;
    // `arg` first: -e and -l may read it.
    for (int i = 1; i < argc; ++i) {
        const std::string_view a = argv[i];
        if (a == "--") {
            script = i + 1 < argc ? i + 1 : argc;
            break;
        }
        if (a == "-e" || a == "-l") {
            ++i;
            continue;
        }
        if (a.starts_with("-e") || a.starts_with("-l")) continue;  // the value attached
        if (!a.starts_with("-") || a == "-") {
            script = i;
            break;
        }
    }
    lua_createtable(L, argc - script, script + 1);
    for (int i = 0; i < argc; ++i) {
        lua_pushstring(L, argv[i]);
        lua_rawseti(L, -2, i - (script < argc ? script : argc));
    }
    lua_setglobal(L, "arg");

    for (int i = 1; ok && i < script; ++i) {
        const std::string_view a = argv[i];
        if (a == "-v") {
            std::println("{}", LUA_COPYRIGHT);
        } else if (a.starts_with("-e") || a.starts_with("-l")) {
            const bool attached = a.size() > 2;
            if (!attached && i + 1 >= argc) {
                std::println(std::cerr, "lua: '{}' needs argument", a);
                ok = false;
                break;
            }
            const char* value = attached ? argv[i] + 2 : argv[++i];
            if (a[1] == 'e') {
                ok = luaL_loadbuffer(L, value, std::strlen(value), "=(command line)") == LUA_OK ? call(L, 0, 0)
                                                                                                : (std::println(std::cerr, "lua: {}", lua_tostring(L, -1)), false);
            } else {
                lua_getglobal(L, "require");
                lua_pushstring(L, value);
                ok = call(L, 1, 1);
                if (ok) lua_setglobal(L, value);
            }
        } else if (a != "--") {
            std::println(std::cerr, "lua: unrecognized option '{}'\nusage: lua [-e stat] [-l name] [-v] [--] [script [args]]", a);
            ok = false;
        }
    }
    if (ok && script < argc) {
        const std::string_view name = argv[script];
        const int loaded = name == "-" ? luaL_loadfile(L, nullptr) : luaL_loadfile(L, argv[script]);
        if (loaded != LUA_OK) {
            std::println(std::cerr, "lua: {}", lua_tostring(L, -1));
            ok = false;
        } else {
            for (int i = script + 1; i < argc; ++i) lua_pushstring(L, argv[i]);
            ok = call(L, argc - script - 1, LUA_MULTRET);
        }
    }
    lua_close(L);
    return ok ? 0 : 1;
}
