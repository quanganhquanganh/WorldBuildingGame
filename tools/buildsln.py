from re import sub
import globals
import os, sys, subprocess

args = globals.ProcessArguments(sys.argv)
CONFIG = globals.GetArgumentValue(args, "config", "debug")

print("Building config: " + CONFIG)
print("\n")
ret = 0

if globals.IsWindows():
  # Get MSBuild's path:
  VS_BUILD_PATH = ""
  if "VS_BUILD_PATH" in os.environ:
    VS_BUILD_PATH = os.environ["VS_BUILD_PATH"]
  else:
    VS_WHERE = "C:\\Program Files (x86)\\Microsoft Visual Studio\\Installer\\vswhere.exe"
    if os.path.exists(VS_WHERE):
      VS_WHERE_ARGS = ["-latest", "-prerelease", "-products", "*", "-requires", "Microsoft.Component.MSBuild", "-find", "MSBuild\\**\\Bin\\MSBuild.exe"]
      VS_WHERE_CMD = [VS_WHERE] + VS_WHERE_ARGS
      VS_BUILD_PATH = subprocess.check_output(VS_WHERE_CMD).decode("utf-8").strip()
  if VS_BUILD_PATH != "":
    ret = subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, "{}.sln".format(globals.PROJECT_NAME), "/property:Configuration={}".format(CONFIG)])
  else:
    print("MSBuild path not found")
    ret = -1


if globals.IsLinux():
  ret = subprocess.call(["make", "-C", "build", "config={}".format(CONFIG)])

if globals.IsMac():
  ret = subprocess.call(["make", "-C", "build", "config={}".format(CONFIG)])
  if ret == 0:
    ret = subprocess.call(["xcodebuild", "-project", "{}.xcodeproj".format(globals.GAME_NAME), "-configuration", CONFIG, "-target", "ALL_BUILD", "-parallelizeTargets", "-jobs", "4", "-sdk", "macosx"])

sys.exit(ret)