import sys
import re

N = 4   # objective
H = 6   # grid height
W = 7   # grid width


positiveInteger = re.compile('^[1-9]+[0-9]*$')

if len(sys.argv) == 2:
    if positiveInteger.match(sys.argv[1]):
        N = int(sys.argv[1])
elif len(sys.argv) == 3:
    if positiveInteger.match(sys.argv[1]) and \
            positiveInteger.match(sys.argv[2]):
        H = int(sys.argv[1])
        W = int(sys.argv[2])
elif len(sys.argv) == 4:
    if positiveInteger.match(sys.argv[1]) and \
            positiveInteger.match(sys.argv[2]) and \
            positiveInteger.match(sys.argv[3]):
        N = int(sys.argv[1])
        H = int(sys.argv[2])
        W = int(sys.argv[3])


print("Number of arguments:", len(sys.argv), "arguments.")

print("Argument List:", str(sys.argv))

print("N: ", N, "\tH: ", H, "\tW: ", W)
