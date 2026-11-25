#!/bin/bash

set -eo pipefail

export TZ=Asia/Kolkata
export KBUILD_BUILD_USER=MAdMiZ
export KBUILD_BUILD_HOST=Kali
export LOCALVERSION="-AirStorm-Nethunter-OSS"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ -d "$SCRIPT_DIR/kernel-5.15" ] && [ -f "$SCRIPT_DIR/build/build.sh" ]; then
    ROOT_DIR="$SCRIPT_DIR"
elif [ -f "$SCRIPT_DIR/../build/build.sh" ]; then
    ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
else
    ROOT_DIR="$SCRIPT_DIR"
fi
KERNEL_DIR="$ROOT_DIR/kernel-5.15"

TC_DIR="$ROOT_DIR/tc/zyc_clang_23"
export HERMETIC_TOOLCHAIN=0

# Ensure KernelSU-Next (dev-susfs) is initialized
if [ ! -d "$KERNEL_DIR/KernelSU-Next/kernel" ]; then
    echo "Initializing KernelSU-Next..."
    git -C "$KERNEL_DIR" submodule update --init --recursive KernelSU-Next || {
        cd "$KERNEL_DIR"
        curl -LSs \
        https://raw.githubusercontent.com/pershoot/KernelSU-Next/dev-susfs/kernel/setup.sh \
        | bash -s dev-susfs
    }
else
    echo "KernelSU-Next already exists, skipping."
fi

if [ ! -x "$TC_DIR/bin/clang" ]; then
    echo "Downloading ZyC Clang 23..."
    mkdir -p "$TC_DIR"
    wget -O /tmp/zyc_clang_23.tar.gz \
    https://github.com/ZyCromerZ/Clang/releases/download/23.0.0git-20260130-release/Clang-23.0.0git-20260130.tar.gz
    tar -xzf /tmp/zyc_clang_23.tar.gz -C "$TC_DIR"
    rm -f /tmp/zyc_clang_23.tar.gz
    if [ ! -x "$TC_DIR/bin/clang" ]; then
        echo "ERROR: Clang not found after extraction!"
        exit 1
    fi
fi

export PATH="$TC_DIR/bin:$PATH"
export CLANG_PREBUILT_BIN="tc/zyc_clang_23/bin"
export CC="$TC_DIR/bin/clang"
export LD="$TC_DIR/bin/ld.lld"
export AR="$TC_DIR/bin/llvm-ar"
export NM="$TC_DIR/bin/llvm-nm"
export STRIP="$TC_DIR/bin/llvm-strip"
export OBJCOPY="$TC_DIR/bin/llvm-objcopy"
export OBJDUMP="$TC_DIR/bin/llvm-objdump"

echo "Clang Compiler: $CC"
"$CC" --version | head -1

DIST_DIR="$ROOT_DIR/out/android13-5.15/dist"
AK3_DIR="$ROOT_DIR/AnyKernel3"

ZIP_NAME="AirStorm-Nethunter-OSS-$(date +%Y%m%d-%H%M).zip"

cd "$ROOT_DIR"

BUILD_START=$(date +%s)

echo "Building Kernel ..."
BUILD_CONFIG=kernel-5.15/build.config.mtk.aarch64.mgk \
OUT_DIR=$ROOT_DIR/out/android13-5.15 \
build/build.sh 2>&1 | tee build.log

BUILD_END=$(date +%s)
BUILD_TIME=$((BUILD_END - BUILD_START))
BUILD_MIN=$((BUILD_TIME / 60))
BUILD_SEC=$((BUILD_TIME % 60))

echo "Preparing AnyKernel3 zip..."
if [ ! -d "$AK3_DIR" ]; then
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
