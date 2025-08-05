import re

f = open("input.txt")
data = f.read()

matches = re.findall(r'[(,)]', data)
print(matches)

floor = 1
for i in range(len(matches)):
    match = matches[i]
    if (match == "("): floor += 1
    else: floor += -1
    if (floor < 0):
        print (i); exit(1);

print(floor)
f.close()