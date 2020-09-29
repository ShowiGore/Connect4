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

    BLACK_FG = "\033[030m"
    RED_FG = "\033[031m"
    GREEN_FG = "\033[032m"
    YELLOW_FG = "\033[033m"
    BLUE_FG = "\033[034m"
    MAGENTA_FG = "\033[035m"
    CYAN_FG = "\033[036m"
    WHITE_FG = "\033[037m"


def apply_arguments(n, h, w):
    positive_integer = re.compile('^[1-9]+[0-9]*$')
    arguments = sys.argv
    arguments.remove(sys.argv[0])
    if len(arguments) == 1:
        if positive_integer.match(arguments[0]):
            n = int(arguments[0])
    elif len(arguments) == 2:
        if positive_integer.match(arguments[0]) and \
                positive_integer.match(arguments[1]):
            h = int(arguments[0])
            w = int(arguments[1])
    elif len(arguments) == 3:
        if positive_integer.match(arguments[0]) and \
                positive_integer.match(arguments[1]) and \
                positive_integer.match(arguments[2]):
            n = int(arguments[0])
            h = int(arguments[1])
            w = int(arguments[2])
    return n, h, w


def display(grid, p):
    s = ""
    for h in range(len(grid)):
        for w in range(len(grid[h])):
            if grid[h][w] == 0:
                s += Colors.BLUE_FG + "| |" \
                     + Colors.RESET
            elif grid[h][w] == 1:
                s += Colors.BLUE_FG + "|" \
                     + Colors.RED_FG + "O" \
                     + Colors.BLUE_FG + "|" \
                     + Colors.RESET
            elif grid[h][w] == 2:
                s += Colors.BLUE_FG + "|" \
                     + Colors.YELLOW_FG + "O" \
                     + Colors.BLUE_FG + "|" \
                     + Colors.RESET
            elif grid[h][w] == (1 + p):
                s += Colors.BLUE_FG + "|" \
                     + Colors.RED_FG + Colors.REVERSE + "O" \
                     + Colors.BLUE_FG + "|" \
                     + Colors.RESET
            elif grid[h][w] == (2 + p):
                s += Colors.BLUE_FG + "|" \
                     + Colors.YELLOW_FG + Colors.REVERSE + "O" \
                     + Colors.BLUE_FG + "|" + \
                     Colors.RESET
            else:
                s += Colors.BLUE_FG + "|" \
                     + Colors.GREEN_FG + Colors.REVERSE + "?" \
                     + Colors.BLUE_FG + "|" + \
                     Colors.RESET
        s += "\n"
    return s


def build_enumeration(width):
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


def draw(grid):
    for w in range(len(grid)):
        if grid[0][w] == 0:
            return False
    return True


def count_down(grid, row, column):
    count, i = 0, row + 1
    while i < len(grid) \
            and grid[row][column] == grid[i][column]:
        count += 1
        i += 1
    return count


def count_left(grid, row, column):
    count, j = 0, column - 1
    while j >= 0 \
            and grid[row][column] == grid[row][j]:
        count += 1
        j -= 1
    return count


def count_right(grid, row, column):
    count, j = 0, column + 1
    while j < len(grid[0]) \
            and grid[row][column] == grid[row][j]:
        count += 1
        j += 1
    return count


def count_upleft(grid, row, column):
    count, i, j = 0, row - 1, column - 1
    while i >= 0 and j >= 0 \
            and grid[row][column] == grid[i][j]:
        count += 1
        i -= 1
        j -= 1
    return count


def count_downright(grid, row, column):
    count, i, j = 0, row + 1, column + 1
    while i < len(grid) and j < len(grid[0]) \
            and grid[row][column] == grid[i][j]:
        count += 1
        i += 1
        j += 1
    return count


def count_downleft(grid, row, column):
    count, i, j = 0, row + 1, column - 1
    while i < len(grid) and j >= 0 \
            and grid[row][column] == grid[i][j]:
        count += 1
        i += 1
        j -= 1
    return count


def count_upright(grid, row, column):
    count, i, j = 0, row - 1, column + 1
    while i >= 0 and j < len(grid[0]) \
            and grid[row][column] == grid[i][j]:
        count += 1
        i -= 1
        j += 1
    return count


def mark_down(p, grid, row, column):
    i = row + 1
    while i < len(grid) \
            and grid[row][column] == grid[i][column]:
        grid[i][column] = grid[i][column] + p
        i += 1
    return grid


def mark_left(p, grid, row, column):
    j = column - 1
    while j >= 0 \
            and grid[row][column] == grid[row][j]:
        grid[row][j] = grid[row][j] + p
        j -= 1
    return grid


def mark_right(p, grid, row, column):
    j = column + 1
    while j < len(grid[0]) \
            and grid[row][column] == grid[row][j]:
        grid[row][j] = grid[row][j] + p
        j += 1


def mark_upleft(p, grid, row, column):
    i, j = row - 1, column - 1
    while i >= 0 and j >= 0 \
            and grid[row][column] == grid[i][j]:
        grid[i][j] = grid[i][j] + p
        i -= 1
        j -= 1
    return grid


def mark_downright(p, grid, row, column):
    i, j = row + 1, column + 1
    while i < len(grid) and j < len(grid[0]) \
            and grid[row][column] == grid[i][j]:
        grid[i][j] = grid[i][j] + p
        i += 1
        j += 1
    return grid


def mark_downleft(p, grid, row, column):
    i, j = row + 1, column - 1
    while i < len(grid) and j >= 0 \
            and grid[row][column] == grid[i][j]:
        grid[i][j] = grid[i][j] + p
        i += 1
        j -= 1
    return grid


def mark_upright(p, grid, row, column):
    i, j = row - 1, column + 1
    while i >= 0 and j < len(grid[0]) \
            and grid[row][column] == grid[i][j]:
        grid[i][j] = grid[i][j] + p
        i -= 1
        j += 1
    return grid


def main():
    # number of players, objective, grid height, grid width
    p, n, h, w = 2, 4, 6, 7

    n, h, w = apply_arguments(n, h, w)

    grid = []
    for y in range(h):
        grid.append(([0] * w))

    enumeration = build_enumeration(w)

    '''
    grid[0][0] = 0
    grid[0][1] = 1
    grid[0][2] = 2
    grid[0][3] = 3
    grid[0][4] = 4
    grid[0][5] = 5
    '''

    print(display(grid, p) + enumeration)


if __name__ == "__main__":
    main()

'''
autopep8  -- 1aggressive  -- 1in-place connectN.py
pycodestyle connectN.py
'''
