import re

with open("input.txt") as f:
    # for line in f:
    #     print(line)
    # content = f.read()
    keys = []
    data = []
    molecules = set()
    content = ''
    for line in f:
        line = line.strip()
        if '=>' in line:
            equals_index = line.find('=>')
            keys.append(line[0:equals_index-1])
            data.append(line[equals_index+3:])
        elif line != '\n': content = line

    for i in range(len(keys)):
        pattern = re.compile(keys[i])
        matches = pattern.finditer(content)

        for m in matches:
            molecules.add(content[:m.span()[0]] + data[i] + content[m.span()[1]:])
    
    print(len(molecules))


    # print ()

