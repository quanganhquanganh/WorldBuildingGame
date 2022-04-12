from re import X


GAME_NAME = "World Building Game"
PROJECT_NAME = "WorldBuildingGame"
TOOL_DIR = "tools"

V_MAJOR = 0
V_MINOR = 0

import sys, platform

PLATFORM = sys.platform
for x in platform.system().lower():
    if x in "win":
        PLATFORM = "win"
        break

def IsWindows():
  return PLATFORM == "win"

def IsLinux():
  return PLATFORM == "linux"

def IsMac():
  return PLATFORM == "darwin"

def ProcessArguments(argv):
  ret = {}
  for arg in argv:
    if arg.startswith("--"):
      arg = arg[2:]
      if "=" in arg:
        arg, val = arg.split("=")
        ret[arg] = val
      else:
        ret[arg] = True
  return ret

def GetArgument(argv, key, default=None):
  args = ProcessArguments(argv)
  if key in args:
    return args[key]
  return default