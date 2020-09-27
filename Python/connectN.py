import sys
import re

RESET = "\033[0m"
BLACK = "\033[0;30m"
RED = "\033[0;31m"
GREEN = "\033[0;32m"
YELLOW = "\033[0;33m"
BLUE = "\033[0;34m"
MAGENTA = "\033[0;35m"
CYAN = "\033[0;36m"
WHITE = "\033[0;37m"
RED_M = "\033[0;31;7;5m"
GREEN_M = "\033[0;32;7;5m"
YELLOW_M = "\033[0;33;7;5m"

def applyArguments():
    g = globals()
    positiveInteger = re.compile('^[1-9]+[0-9]*$')
    if len(sys.argv) == 2:
        if positiveInteger.match(sys.argv[1]):
            g['N'] = int(sys.argv[1])
    elif len(sys.argv) == 3:
        if positiveInteger.match(sys.argv[1]) and \
                positiveInteger.match(sys.argv[2]):
            g['H'] = int(sys.argv[1])
            g['W'] = int(sys.argv[2])
    elif len(sys.argv) == 4:
        if positiveInteger.match(sys.argv[1]) and \
                positiveInteger.match(sys.argv[2]) and \
                positiveInteger.match(sys.argv[3]):
            g['N'] = int(sys.argv[1])
            g['H'] = int(sys.argv[2])
            g['W'] = int(sys.argv[3])

def display(grid):
    s = ""
    for h in range(len(grid)):
        for w in range(len(grid[h])):
            if grid[h][w] == 0:
                s += BLUE + "| |" + RESET
            elif grid[h][w] == 1:
                s += BLUE + "|" + RED + "O" + BLUE + "|" + RESET
            elif grid[h][w] == 2:
                s += BLUE + "|" + YELLOW + "O" + BLUE + "|" + RESET
            elif grid[h][w] == 3:
                s += BLUE + "|" + RED_M + "O" + BLUE + "|" + RESET
            elif grid[h][w] == 4:
                s += BLUE + "|" + YELLOW_M + "O" + BLUE + "|" + RESET
            else:
                s += BLUE + "|" + GREEN_M + "?" + BLUE + "|" + RESET
        s += "\n"
    print(s)

N = 4   # objective
H = 6   # grid height
W = 7   # grid width

applyArguments()

grid = [[0 for x in range(W)] for y in range(H)]

grid[0][0] = 0
grid[0][1] = 1
grid[0][2] = 2
grid[0][3] = 3
grid[0][4] = 4
grid[0][5] = 5

display(grid)














