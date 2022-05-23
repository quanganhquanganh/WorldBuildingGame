import globals
import sys

print("WBG Tools - v{}.{}".format(globals.V_MAJOR, globals.V_MINOR))
if len(sys.argv) >= 2:
    print(", ".join(sys.argv))

sys.exit(0)