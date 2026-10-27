#!/usr/bin/env python3
"""Run Lua's own test suite (lua-5.4.7-tests) on examples/lua, a standalone
interpreter written against import mcpplibs.mwrap.lua.

The test tarball is downloaded once into target/upstream and checked against
the SHA256 in upstream/documents.json; its files are used unchanged. The run
is upstream's documented one for an installed Lua: `lua -e"_U=true" all.lua`
(portable tests, no internal-test build). It must end with "final OK".
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tarfile
import urllib.request


def fetch(root: Path) -> Path:
    pins = json.loads((root / 'upstream/documents.json').read_text(encoding='utf-8'))['tests']
    cache = root / 'target/upstream'
    cache.mkdir(parents=True, exist_ok=True)
    archive = cache / Path(pins['url']).name
    if not archive.exists() or hashlib.sha256(archive.read_bytes()).hexdigest() != pins['sha256']:
        print('+ fetch', pins['url'], flush=True)
        with urllib.request.urlopen(pins['url'], timeout=120) as response:
            archive.write_bytes(response.read())
    digest = hashlib.sha256(archive.read_bytes()).hexdigest()
    if digest != pins['sha256']:
        sys.exit(f'test archive checksum {digest} != {pins["sha256"]}')
    with tarfile.open(archive) as tar:
        top = tar.getmembers()[0].name.split('/')[0]
        if not (cache / top).exists():
            tar.extractall(cache, filter='data')
    return cache / top


def interpreter(example: Path, mcpp: str, toolchain: str | None) -> Path:
    # Optimised, as upstream's lua is: the stack-overflow tests size the C
    # stack for it (an unoptimised build's frames overflow Windows' 1 MB).
    command = [mcpp, 'build', '--profile', 'release'] + (['--toolchain', toolchain] if toolchain else [])
    print('+', ' '.join(command), flush=True)
    subprocess.run(command, cwd=example, check=True)
    name = 'lua.exe' if os.name == 'nt' else 'lua'
    found = sorted((p for p in (example / 'target').rglob(name) if p.parent.name == 'bin'), key=lambda p: p.stat().st_mtime)
    if not found:
        sys.exit('examples/lua was not built')
    return found[-1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--mcpp', default='mcpp')
    parser.add_argument('--toolchain')
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    tests = fetch(root)
    lua = interpreter(root / 'examples/lua', args.mcpp, args.toolchain)
    print(f'+ {lua} -e"_U=true" all.lua  (in {tests})', flush=True)
    run = subprocess.run([str(lua), '-e_U=true', 'all.lua'], cwd=tests, capture_output=True, text=True, timeout=1800)
    sys.stdout.write(run.stdout[-4000:])
    sys.stderr.write(run.stderr[-4000:])
    sections = sum(1 for line in run.stdout.splitlines() if line.lower().startswith('testing'))
    if run.returncode != 0 or 'final OK' not in run.stdout:
        sys.exit(f'the test suite failed (exit {run.returncode})')
    print(f'lua-5.4.7-tests: final OK ({sections} sections)')


if __name__ == '__main__':
    main()
