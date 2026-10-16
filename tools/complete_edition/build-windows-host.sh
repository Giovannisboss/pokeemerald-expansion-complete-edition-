#!/usr/bin/env bash
# Native Windows (MSYS2 MinGW64) or Ubuntu -> MinGW64 host-tool build.
# Requires cmake, ninja, git and a MinGW64 gcc/g++ toolchain.
set -euo pipefail

REPO_ROOT="${GITHUB_WORKSPACE:-$(pwd)}"
if command -v cygpath >/dev/null; then REPO_ROOT="$(cygpath -u "$REPO_ROOT")"; fi
OUT="${CE_HOST_OUT:-$REPO_ROOT/ce-windows-host}"
MGBA_COMMIT=26b7884bc25a5933960f3cdcd98bac1ae14d42e2 # upstream 0.10.5
PLAY_SOURCE="${CE_PLAY_SOURCE:-$REPO_ROOT/tools/complete_edition/play.c}"
test -f "$PLAY_SOURCE"
mkdir -p "$OUT/src" "$OUT/package"
git init "$OUT/src/mgba"
git -C "$OUT/src/mgba" remote add origin https://github.com/mgba-emu/mgba.git
git -C "$OUT/src/mgba" fetch --depth=1 origin "$MGBA_COMMIT"
git -C "$OUT/src/mgba" checkout --detach FETCH_HEAD
test "$(git -C "$OUT/src/mgba" rev-parse HEAD)" = "$MGBA_COMMIT"
cp "$PLAY_SOURCE" "$OUT/src/play.c"
cat > "$OUT/src/CMakeLists.txt" <<'CMAKE'
cmake_minimum_required(VERSION 3.16)
project(CEWindowsHost C CXX)
set(CMAKE_C_STANDARD 11)
set(LIBMGBA_ONLY ON CACHE BOOL "" FORCE)
set(M_CORE_GBA ON CACHE BOOL "" FORCE)
set(M_CORE_GB OFF CACHE BOOL "" FORCE)
set(ENABLE_SCRIPTING OFF CACHE BOOL "" FORCE)
set(USE_DEBUGGERS OFF CACHE BOOL "" FORCE)
set(USE_LZMA OFF CACHE BOOL "" FORCE)
set(USE_LUA OFF CACHE BOOL "" FORCE)
set(BUILD_LTO OFF CACHE BOOL "" FORCE)
set(BUILD_GL OFF CACHE BOOL "" FORCE)
set(BUILD_GLES2 OFF CACHE BOOL "" FORCE)
set(BUILD_GLES3 OFF CACHE BOOL "" FORCE)
add_subdirectory(mgba)
add_executable(ce-play play.c)
target_compile_definitions(ce-play PRIVATE BUILD_STATIC _WIN32_WINNT=0x0600)
target_compile_options(ce-play PRIVATE -Wall -Wextra)
target_link_options(ce-play PRIVATE -static -static-libgcc)
target_link_libraries(ce-play PRIVATE mgba)
CMAKE

EXTRA=()
case "$(uname -s)" in
  MINGW*|MSYS*) export CC=gcc CXX=g++ ;;
  Linux*) EXTRA+=(-DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_RC_COMPILER=x86_64-w64-mingw32-windres) ;;
  *) echo 'Unsupported build host' >&2; exit 2 ;;
esac
cmake -S "$OUT/src" -B "$OUT/build" -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_POLICY_VERSION_MINIMUM=3.5 "${EXTRA[@]}"
cmake --build "$OUT/build" --target ce-play --parallel 2
cp "$OUT/build/ce-play.exe" "$OUT/package/ce-play.exe"
cp "$OUT/src/mgba/LICENSE" "$OUT/package/mGBA-LICENSE.txt"
git -C "$OUT/src/mgba" archive --format=tar.gz --output="$OUT/package/mgba-source-0.10.5.tar.gz" HEAD
cp "$PLAY_SOURCE" "$OUT/package/play.c"
cp "${BASH_SOURCE[0]}" "$OUT/package/build-windows-host.sh"
cat > "$OUT/package/SOURCE.txt" <<EOF
Host controller: tools/complete_edition/play.c from this workflow's repository commit.
Repository commit: ${GITHUB_SHA:-local-build}
mGBA upstream: https://github.com/mgba-emu/mgba
mGBA version: 0.10.5
mGBA immutable source: $MGBA_COMMIT
mGBA license: Mozilla Public License 2.0 (included as mGBA-LICENSE.txt).
mGBA source is unmodified. Build recipe accompanies this workflow.
Full pinned mGBA source and bundled third-party notices: mgba-source-0.10.5.tar.gz.
This package contains the emulator host tool only: no ROMs, saves or game assets.
All gameplay must use run/pulse/walk/fight/advance buttons; read/position are inspection.
Do not use controller save/load commands as substitutes for ordinary game saving.
EOF
if command -v x86_64-w64-mingw32-strip >/dev/null; then
  x86_64-w64-mingw32-strip "$OUT/package/ce-play.exe"
else
  strip "$OUT/package/ce-play.exe"
fi
(cd "$OUT/package" && sha256sum ce-play.exe > SHA256SUMS.txt)
