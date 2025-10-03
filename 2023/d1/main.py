with open('test.txt') as f:
    values = []
    for line in f:
        line = line.strip()
        stack = []
        for c in line:
            if c.isdigit():
                if len(stack) < 2:
                    stack.append(c)
                else:
                    stack[1] = c
        if (len(stack) < 2):
            stack.append(stack[0])
        values.append(stack)

    total = 0
    for value in values:
        total+=int("".join(value))
    print(total)
