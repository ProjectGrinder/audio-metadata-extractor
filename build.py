#!/usr/bin/env python3
import sys
import platform
import subprocess

target = sys.argv[1] if len(sys.argv) > 1 else "all"

targets = ["win64", "linux64", "linux-arm64"]
if platform.system() == "Darwin":
    targets.append("macos-universal")

def build_target(preset):
    print(f"\033[0;36m========================================\033[0m")
    print(f"\033[0;36mBuilding Target Preset: {preset}\033[0m")
    print(f"\033[0;36m========================================\033[0m")
    
    subprocess.run(["cmake", "--preset", preset], check=True)
    subprocess.run(["cmake", "--build", "--preset", preset, "--parallel"], check=True)

try:
    if target == "all":
        for t in targets:
            build_target(t)
    else:
        build_target(target)
    print("\033[0;32m==> All requested builds finished! Binaries placed in project/bin/\033[0m")
except subprocess.CalledProcessError as e:
    print(f"\033[0;31m==> Build failed on step: {e.cmd}\033[0m")
    sys.exit(1)
