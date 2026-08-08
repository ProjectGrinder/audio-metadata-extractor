#!/usr/bin/env python3
import sys
import platform
import subprocess

target = sys.argv[1] if len(sys.argv) > 1 else "all"

targets = ["win64", "linux64", "linux-arm64"]
if platform.system() == "Darwin":
    targets.append("macos-universal")


def build_target(preset):
    print(R"========================================")
    print(f"Building Target Preset: {preset}")
    print("========================================")

    subprocess.run(["cmake", "--preset", preset], check=True)
    subprocess.run(["cmake", "--build", "--preset",
                   preset, "--parallel"], check=True)


try:
    if target == "all":
        for t in targets:
            build_target(t)
    else:
        build_target(target)
    print(
        "==> All requested builds finished! Binaries placed in",
        "godot/addons/audio_metadata_extension/bin/")
except subprocess.CalledProcessError as e:
    print(f"==> Build failed on step: {e.cmd}")
    sys.exit(1)
