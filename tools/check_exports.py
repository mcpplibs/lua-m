#!/usr/bin/env python3
"""Audit the module surface against Lua's public headers.

Every function (LUA_API, LUALIB_API, LUAMOD_API), every typedef and struct,
and lua_ident of <lua.h>, <lauxlib.h> and <lualib.h> must be exported by
src/lua.cppm. Every macro those headers define must be mapped in
src/macros.cppm, kept as a macro in <mwrap/lua/macros.hpp> (listed below,
with the reason a function cannot be it), or excluded below with a reason.
The headers are read from the upstream release tarball, the same bytes
compat.lua builds, fetched and checked against upstream/documents.json.
"""
import hashlib
import json
from pathlib import Path
import re
import sys
import tarfile
import urllib.request

# Macros that stay macros: <mwrap/lua/macros.hpp>.
SIDE_HEADER = {
    'luaL_argcheck': 'evaluates its message only when the condition fails',
    'luaL_argexpected': 'evaluates its type name only when the condition fails',
    'luaL_opt': 'evaluates the default or the call, not both',
    'luaL_intop': 'pastes an operator between its operands',
    'lua_writestring': "the standalone interpreter's stdio helper (defined only when the host has not)",
    'lua_writeline': "the standalone interpreter's stdio helper",
    'lua_writestringerror': "the standalone interpreter's stdio helper",
}

# Macros that are not part of the API a program calls.
EXCLUDED = {
    'lua_h': 'include guard',
    'lauxlib_h': 'include guard',
    'lualib_h': 'include guard',
    # Defined only under LUA_COMPAT_APIINTCASTS, which this build leaves off.
    'lua_pushunsigned': 'LUA_COMPAT_APIINTCASTS only',
    'lua_tounsignedx': 'LUA_COMPAT_APIINTCASTS only',
    'lua_tounsigned': 'LUA_COMPAT_APIINTCASTS only',
    'luaL_checkunsigned': 'LUA_COMPAT_APIINTCASTS only',
    'luaL_optunsigned': 'LUA_COMPAT_APIINTCASTS only',
    'luaL_checkint': 'LUA_COMPAT_APIINTCASTS only',
    'luaL_optint': 'LUA_COMPAT_APIINTCASTS only',
    'luaL_checklong': 'LUA_COMPAT_APIINTCASTS only',
    'luaL_optlong': 'LUA_COMPAT_APIINTCASTS only',
}

HEADERS = ('lua.h', 'lauxlib.h', 'lualib.h')


def fetch(root: Path) -> Path:
    """The upstream src/ directory, from the pinned tarball (cached in target/)."""
    pins = json.loads((root / 'upstream/documents.json').read_text(encoding='utf-8'))
    cache = root / 'target/upstream'
    tarball = cache / Path(pins['upstream']).name
    if not tarball.exists():
        cache.mkdir(parents=True, exist_ok=True)
        with urllib.request.urlopen(pins['upstream']) as response:
            tarball.write_bytes(response.read())
    digest = hashlib.sha256(tarball.read_bytes()).hexdigest()
    if digest != pins['upstream_sha256']:
        sys.exit(f'{tarball}: sha256 {digest}, pinned {pins["upstream_sha256"]}')
    top = tarball.name.removesuffix('.tar.gz')
    out = cache / top
    if not out.exists():
        with tarfile.open(tarball) as t:
            t.extractall(cache, filter='data')
    return out / 'src'


def strip_comments(text: str) -> str:
    return re.sub(r'/\*.*?\*/', '', text, flags=re.S)


def inventory(src: Path):
    names, macros = set(), set()
    for header in HEADERS:
        text = strip_comments((src / header).read_text(encoding='utf-8'))
        names |= set(re.findall(r'\b(?:LUA_API|LUALIB_API|LUAMOD_API)\b[^;{]*?\(\s*(\w+)\s*\)\s*\(', text))
        names |= set(re.findall(r'typedef\s+struct\s+(\w+)\s+\1\s*;', text))
        names |= set(re.findall(r'typedef\s+[\w\s\*]+?\b(lua\w*|luaL\w*)\s*;', text))
        names |= set(re.findall(r'typedef\s+[\w\s\*]+\(\s*\*\s*(\w+)\s*\)', text))
        names |= set(re.findall(r'^struct\s+(lua\w*|luaL\w*)\s*\{', text, flags=re.M))
        names |= set(re.findall(r'\}\s*(lua\w*|luaL\w*)\s*;', text))
        names |= set(re.findall(r'extern\s+const\s+char\s+(\w+)\s*\[', text))
        macros |= set(re.findall(r'^#define\s+(\w+)', text, flags=re.M))
    return names, macros


def main():
    root = Path(__file__).resolve().parents[1]
    names, macros = inventory(fetch(root))
    exported = set(re.findall(r'export using ::(\w+);', (root / 'src/lua.cppm').read_text(encoding='utf-8')))
    mapping = (root / 'src/macros.cppm').read_text(encoding='utf-8')
    mapping = mapping[mapping.index('export module'):]
    mapped = set(re.findall(r'inline constexpr (?:[\w:&]+\s+)+?(\w+)\s*=', mapping))
    # Functions: a definition's name at the start of a line, after its type.
    mapped |= set(re.findall(r'^(?:inline\s+|constexpr\s+)?(?:[\w:]+[\s*&]+)+(\w+)\s*\(', mapping, flags=re.M))
    problems = []
    missing = names - exported
    if missing:
        problems.append('src/lua.cppm lacks: ' + ', '.join(sorted(missing)))
    unknown = exported - names
    if unknown:
        problems.append('src/lua.cppm exports what the headers do not declare: ' + ', '.join(sorted(unknown)))
    unaccounted = macros - mapped - SIDE_HEADER.keys() - EXCLUDED.keys()
    if unaccounted:
        problems.append('macros neither mapped, side-header nor excluded: ' + ', '.join(sorted(unaccounted)))
    both = (SIDE_HEADER.keys() | EXCLUDED.keys()) & mapped
    if both:
        problems.append('listed as unmapped yet mapped: ' + ', '.join(sorted(both)))
    stale = (SIDE_HEADER.keys() | EXCLUDED.keys()) - macros
    if stale:
        problems.append('listed but not in the headers: ' + ', '.join(sorted(stale)))
    if problems:
        sys.exit('\n'.join(problems))
    print(f'{len(names)} declarations exported; {len(macros)} macros: {len(macros & mapped)} mapped, '
          f'{len(SIDE_HEADER)} kept as macros, {len(EXCLUDED)} excluded')


if __name__ == '__main__':
    main()
