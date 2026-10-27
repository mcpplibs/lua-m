# lua

> 通过 C++23 模块使用 Lua 5.4（可嵌入的脚本语言）。

[English](README.md) · **简体中文** · [上游](https://www.lua.org) · [发布](https://github.com/mcpplibs/lua-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [索引](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/lua-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/lua-m/actions/workflows/ci.yml)

上游的 C API 保持不变：`lua_State`、`lua_pushinteger`、`luaL_newstate`、
`luaopen_base` 就是 `<lua.h>`、`<lauxlib.h>`、`<lualib.h>` 里的上游全局名字。
库本身是 `compat.lua` 5.4.7；本包把 Lua 的宏按原名映射成常量和函数。每次 CI
都会在一个只用本模块写成的独立解释器上跑 Lua 自带的测试集，并且全部通过。

## 模块

- `import mcpplibs.mwrap.lua;`：C API（`lua_*`、`luaL_*`、`luaopen_*` 和各个类型），并重新导出下面这个模块
- `import mcpplibs.mwrap.lua.macros;`：`LUA_OK`、`lua_pop`、`lua_tostring`、`luaL_dostring` 等，位于 `mcpplibs::mwrap::lua::macros`

> 更多模块 API -> [用法和 API](docs/usage.md)

## 快速开始

```sh
mcpp new scripted --template mcpplibs.mwrap.lua@5.4.7
cd scripted
mcpp run
```

默认模板注册一个 C++ 函数，运行一段调用它的脚本，再打印脚本的返回值。

```toml
[dependencies]
"mcpplibs.mwrap.lua" = "5.4.7"
```

```cpp
import std;
import mcpplibs.mwrap.lua;
using namespace mcpplibs::mwrap::lua::macros;  // lua_pop、lua_tostring、LUA_OK …

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_dostring(L, "return ('modules'):upper()")) std::println("error: {}", lua_tostring(L, -1));
    else std::println("{}", lua_tostring(L, -1));
    lua_close(L);
}
```

## 宏

具名模块不能导出宏。常量写成 `inline constexpr`（`macros::LUA_OK`、
`macros::LUA_REGISTRYINDEX`、`macros::LUA_VERSION`），函数式的宏写成函数，
对参数的求值和宏完全一样（`lua_pop`、`lua_pcall`、`lua_upvalueindex`、
`luaL_newlib` …）。`luaL_argcheck`、`luaL_argexpected`、`luaL_opt` 和
`luaL_intop` 写成函数就会改变求值方式，所以仍然是宏，放在
`<mwrap/lua/macros.hpp>` 里，在 import 之前包含。每个宏的处理和原因见
[docs/usage.md](docs/usage.md)。

## 示例

- [examples/lua](examples/lua)：只用本模块写成的独立解释器，`lua [-e stat] [-l name] [-v] [script [args]]`；
  [tools/run_conformance.py](tools/run_conformance.py) 在它上面跑 Lua 的测试集。

## 构建和测试

Linux、macOS、Windows 的 CI 构建模块并运行测试、导出审计
（[tools/check_exports.py](tools/check_exports.py)：三个头文件的每个声明都已导出，
每个宏都已映射或列出原因）以及 Lua 自带的测试集（`lua-5.4.7-tests`）。
另有一个作业把默认模板当作已安装的包来生成并运行。

## 许可证

包装部分为 [Apache-2.0](LICENSE)，作者 mcpp-community；Lua 本身仍是 MIT
（[upstream/lua/LICENSE](upstream/lua/LICENSE)）。
