#!/bin/bash

set -eo pipefail

export TZ=Asia/Kolkata
export KBUILD_BUILD_USER=MAdMiZ
export KBUILD_BUILD_HOST=Kali
export LOCALVERSION="-AirStorm-Nethunter-OSS"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ -f "$SCRIPT_DIR/../build/build.sh" ] && [ -d "$SCRIPT_DIR/../vendor/mediatek/kernel_modules" ] && [ -d "$SCRIPT_DIR/../kernel-5.15" ]; then
    ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
    KERNEL_DIR="$ROOT_DIR/kernel-5.15"
else
    EXISTING_REPO_ROOT=""
    CHECK_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
    while [ "$CHECK_DIR" != "/" ]; do
        if [ -d "$CHECK_DIR/.repo" ]; then
            EXISTING_REPO_ROOT="$CHECK_DIR"
            break
        fi
        CHECK_DIR="$(dirname "$CHECK_DIR")"
    done

    if [ -n "$EXISTING_REPO_ROOT" ]; then
        ROOT_DIR="$EXISTING_REPO_ROOT"
    else
        ROOT_DIR="$SCRIPT_DIR/workspace"
    fi
    KERNEL_DIR="$ROOT_DIR/kernel-5.15"

    if [ ! -f "$ROOT_DIR/build/build.sh" ] || [ ! -d "$ROOT_DIR/vendor/mediatek/kernel_modules" ] || [ ! -d "$KERNEL_DIR" ]; then
        if ! command -v repo >/dev/null 2>&1; then
            echo "ERROR: 'repo' tool not found in PATH!"
            exit 1
        fi
        echo "Initializing and syncing repo workspace in $ROOT_DIR..."
        mkdir -p "$ROOT_DIR"
        (
            cd "$ROOT_DIR"
            repo init -u https://github.com/mizdrake7/local_manifest -b kernel_airstorm </dev/null
            repo sync -c --force-sync --no-clone-bundle --no-tags -j4 </dev/null
        )
    fi
fi

TC_DIR="$ROOT_DIR/tc/zyc_clang"
export HERMETIC_TOOLCHAIN=0

# Ensure KernelSU-Next is initialized and linked
if [ ! -f "$KERNEL_DIR/KernelSU-Next/kernel/Makefile" ]; then
    echo "Initializing KernelSU-Next..."
    if [ -f "$KERNEL_DIR/.gitmodules" ] && grep -q "KernelSU-Next" "$KERNEL_DIR/.gitmodules"; then
        git -C "$KERNEL_DIR" submodule update --init --recursive KernelSU-Next
    else
        rm -rf "$KERNEL_DIR/KernelSU-Next"
        (
            cd "$KERNEL_DIR"
            curl -LSs \
                https://raw.githubusercontent.com/KernelSU-Next/KernelSU-Next/next/kernel/setup.sh \
                | bash -
        )
    fi
fi

if [ ! -f "$KERNEL_DIR/KernelSU-Next/kernel/Makefile" ]; then
    echo "ERROR: KernelSU-Next/kernel/Makefile not found!"
    exit 1
fi

if [ ! -e "$KERNEL_DIR/drivers/kernelsu/Makefile" ]; then
    ln -sfn ../KernelSU-Next/kernel "$KERNEL_DIR/drivers/kernelsu"
fi

if [ ! -x "$TC_DIR/bin/clang" ] || ! "$TC_DIR/bin/clang" --version 2>/dev/null | grep -q "clang version 23\."; then
    echo "Downloading ZyC Clang 23..."
    rm -rf "$TC_DIR"
    mkdir -p "$TC_DIR"
    wget -O "$TC_DIR/zyc_clang.tar.gz" \
    https://github.com/ZyCromerZ/Clang/releases/download/23.0.0git-20260130-release/Clang-23.0.0git-20260130.tar.gz
    tar -xzf "$TC_DIR/zyc_clang.tar.gz" -C "$TC_DIR"
    rm -f "$TC_DIR/zyc_clang.tar.gz"
    if [ ! -x "$TC_DIR/bin/clang" ]; then
        echo "ERROR: Clang not found after extraction!"
        exit 1
    fi
fi

cat <<'EOF' > "$TC_DIR/build.config.zyc"
CLANG_PREBUILT_BIN=tc/zyc_clang/bin
HERMETIC_TOOLCHAIN=0
KCFLAGS="${KCFLAGS} -Wno-int-conversion -Wno-strict-prototypes -Wno-enum-compare -Wno-sometimes-uninitialized"
EOF

export PATH="$TC_DIR/bin:$PATH"
export CC="$TC_DIR/bin/clang"
export LD="$TC_DIR/bin/ld.lld"
export AR="$TC_DIR/bin/llvm-ar"
export NM="$TC_DIR/bin/llvm-nm"
export STRIP="$TC_DIR/bin/llvm-strip"
export OBJCOPY="$TC_DIR/bin/llvm-objcopy"
export OBJDUMP="$TC_DIR/bin/llvm-objdump"

echo "Clang Compiler: $CC"
CC_VER="$("$CC" --version)"
echo "${CC_VER%%$'\n'*}"

DIST_DIR="$ROOT_DIR/out/android13-5.15/dist"
AK3_DIR="$ROOT_DIR/AnyKernel3"

ZIP_NAME="AirStorm-Nethunter-OSS-$(date +%Y%m%d-%H%M).zip"

cd "$ROOT_DIR"

BUILD_START=$(date +%s)

echo "Building Kernel ..."
BUILD_CONFIG=kernel-5.15/build.config.mtk.aarch64.mgk \
BUILD_CONFIG_FRAGMENTS=tc/zyc_clang/build.config.zyc \
OUT_DIR="$ROOT_DIR/out/android13-5.15" \
build/build.sh 2>&1 | tee "$ROOT_DIR/build.log"

BUILD_END=$(date +%s)
BUILD_TIME=$((BUILD_END - BUILD_START))
BUILD_MIN=$((BUILD_TIME / 60))
BUILD_SEC=$((BUILD_TIME % 60))

echo "Preparing AnyKernel3 zip..."
if [ ! -f "$AK3_DIR/anykernel.sh" ]; then
    rm -rf "$AK3_DIR"
    git clone \
        https://github.com/mizdrake7/AnyKernel3 \
        -b air \
        --depth=1 \
        "$AK3_DIR"
fi
if [ ! -f "$DIST_DIR/Image.gz" ]; then
    echo "ERROR: Image.gz not found!"
    exit 1
fi
rm -f "$AK3_DIR/Image.gz"
cp "$DIST_DIR/Image.gz" "$AK3_DIR/"
cd "$AK3_DIR"
find . -maxdepth 1 -name "*.zip" -delete

echo "Creating flashable zip..."
zip -r9 "$ZIP_NAME" ./*

echo "Uploading to sendit.sh..."
UPLOAD_URL=$(curl -fsSL -T "$ZIP_NAME" https://sendit.sh)
if [ -z "$UPLOAD_URL" ]; then
    echo "ERROR: Upload failed!"
    exit 1
fi

echo
echo "Build complete."
echo "Build completed in ${BUILD_MIN} minutes ${BUILD_SEC} seconds."
echo "ZIP: $AK3_DIR/$ZIP_NAME"
echo "URL: $UPLOAD_URL"
echo
