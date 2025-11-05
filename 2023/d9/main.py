import sys

argc = len(sys.argv)
usage = 'USAGE: py main.py \'filepath\' \'(1 or 2) The part to solve\''
if (argc < 3):
    print('ERROR: Incomplete argumets')
    print(usage)
    exit(69)

filepath = sys.argv[1]

try:
    part = int(sys.argv[2])
except ValueError:
    print('ERROR: Invalid part')
    print(usage)
    exit(69)
    

with open(filepath) as f:
    nexts = []
    for line in f:
        history = []
        xs = list(map(int, line.strip().split()))
        history.append(xs)
        while (not all(x == 0 for x in xs)):
            new_list = [xs[i] - xs[i-1] for i in range(1, len(xs))]
            history.append(new_list)
            xs = new_list

        if (part == 1):
            before = history.pop()
            value = before[-1]
            size = len(history)
            for i in range(size):
                curr = history.pop()
                value = curr[-1] + value
            nexts.append(value)
        elif (part == 2):
            before = history.pop()
            value = before[0]
            size = len(history)
            for i in range(size):
                curr = history.pop()
                value = curr[0] - value
            nexts.append(value)
        else:
            print('Invalid Part')
            print(usage)
            exit(69)
    print (sum(nexts))
