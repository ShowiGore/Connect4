import re
import sys

class Colors:
    RESET = "\033[0m"
    BOLD = "\033[1m"
    FAINT = "\033[2m"
    ITALIC = "\033[3m"
    UNDERLINE = "\033[4m"
    BLINK_SLOW = "\033[5m"
    BLINK_RAPID = "\033[6m"
    REVERSE = "\033[7m"
    CONCEAL = "\033[8m"
    CROSSED = "\033[9m"
    # FONT_PRIMARY = "\033[10m"
    # FONT_ALTERNATE = "\033[11-19m"
    # FRAKTUR = "\033[20m"
    DOUBLY_UNDERLINE = "\033[21m"
    NORMAL_COLOR = "\033[22m"
    ITALIC_FRAKTUR_OFF = "\033[23m"
    UNDERLINE_OFF = "\033[24m"
    BLINK_OFF = "\033[25m"
    PROPORTIONAL_SPACING = "\033[26m"
    REVERSE_OFF = "\033[27m"
    REVEAL = "\033[28m"
    CROSSED_OFF = "\033[29m"

    BLACK_FG = "\033[0;30m"
    RED_FG = "\033[0;31m"
    GREEN_FG = "\033[0;32m"
    YELLOW_FG = "\033[0;33m"
    BLUE_FG = "\033[0;34m"
    MAGENTA_FG = "\033[0;35m"
    CYAN_FG = "\033[0;36m"
    WHITE_FG = "\033[0;37m"


def applyArguments(n, h, w):
    positiveInteger = re.compile('^[1-9]+[0-9]*$')
    arguments = sys.argv
    arguments.remove(sys.argv[0])
    if len(arguments) == 1:
        if positiveInteger.match(arguments[0]):
            n = int(arguments[0])
    elif len(arguments) == 2:
        if positiveInteger.match(arguments[0]) and \
                positiveInteger.match(arguments[1]):
            h = int(arguments[0])
            w = int(arguments[1])
    elif len(arguments) == 3:
        if positiveInteger.match(arguments[0]) and \
                positiveInteger.match(arguments[1]) and \
                positiveInteger.match(arguments[2]):
            n = int(arguments[0])
            h = int(arguments[1])
            w = int(arguments[2])
    return n, h, w


def display(grid, enumeration):
    s = ""
    for h in range(len(grid)):
        for w in range(len(grid[h])):
            if grid[h][w] == 0:
                s += Colors.BLUE_FG + "| |" + Colors.RESET
            elif grid[h][w] == 1:
                s += Colors.BLUE_FG + "|" + Colors.RED_FG + "O" + Colors.BLUE_FG + "|" + Colors.RESET
            elif grid[h][w] == 2:
                s += Colors.BLUE_FG + "|" + Colors.YELLOW_FG + "O" + Colors.BLUE_FG + "|" + Colors.RESET
            elif grid[h][w] == 3:
                s += Colors.BLUE_FG + "|" + Colors.RED_FG + Colors.REVERSE + Colors.BLINK_SLOW + "O" + Colors.BLUE_FG + "|" + Colors.RESET
            elif grid[h][w] == 4:
                s += Colors.BLUE_FG + "|" + Colors.YELLOW_FG + Colors.REVERSE + Colors.BLINK_SLOW + "O" + Colors.BLUE_FG + "|" + Colors.RESET
            else:
                s += Colors.BLUE_FG + "|" + Colors.GREEN_FG + Colors.REVERSE + Colors.BLINK_SLOW + "?" + Colors.BLUE_FG + "|" + Colors.RESET
        s += "\n"
    print(s + enumeration)


def buildEnumeration(width):
    columns = [[d for d in str(x)] for x in range(1, width + 1)]
    s = ""
    for d in range(len(columns[width - 1])):
        for n in range(width):
            if len(columns[n]) > d:
                s += " " + columns[n][d] + " "
            else:
                s += "   "
        s += "\n"
    return s


def main():
    n = 4   # objective
    h = 6   # grid height
    w = 7   # grid width
    n, h, w = applyArguments(n, h, w)

    grid = [[0 for x in range(w)] for y in range(h)]

    enumeration = buildEnumeration(w)

    grid[0][0] = 0
    grid[0][1] = 1
    grid[0][2] = 2
    grid[0][3] = 3
    grid[0][4] = 4
    grid[0][5] = 5

    display(grid, enumeration)


if __name__ == "__main__":
    main()


'''
autopep8 --aggressive --in-place connectN.py
pycodestyle connectN.py
'''
