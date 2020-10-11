#!/bin/bash
set -euo pipefail # Use Bash strict mode

# shellcheck disable=SC1090
source "${PWD}/get_build_options.sh"

PKGNAME=$1
CMAKE_OPTIONS=${2:-""}
EXTRA_MAKE_OPTIONS=${3:-""}

APKG_SRC=$SRC_DIR/$PKGNAME
APKG_BUILD_FOLDER=$TMP_DIR/$PKGNAME
APKG_PREFIX=$PREFIX

echo "Src folder: " "$APKG_SRC"
echo "Build folder: " "$APKG_BUILD_FOLDER"
echo "Prefix folder: " "$APKG_PREFIX"

# Build a given package
rm -rf "$APKG_BUILD_FOLDER"
mkdir -p "$APKG_BUILD_FOLDER"

pushd "$APKG_BUILD_FOLDER"
set -x

if [[ -z "$CMAKE_OPTIONS" ]]; then
    $CMAKE "$APKG_SRC" -DCMAKE_INSTALL_PREFIX="$APKG_PREFIX" -DCMAKE_BUILD_TYPE=Release
else
    $CMAKE "$APKG_SRC" -DCMAKE_INSTALL_PREFIX="$APKG_PREFIX" -DCMAKE_BUILD_TYPE=Release "$CMAKE_OPTIONS"
fi

make "$BUILD_OPTS"
make install
set +x
# Return to the original folder.
popd

# Cleanup build folder
rm -rf "$APKG_BUILD_FOLDER"
