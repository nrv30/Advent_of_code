import re

f = open("input.txt")
input = f.read()
sum = 0

data = re.compile(r"\d{1,3}")
matches = re.findall(r"do\(\)|don't\(\)|mul\(\d{1,3},\d{1,3}\)", input)

should_multiply = True
for s in matches:
    if (s == 'do()'):
        should_multiply = True
    elif (s == 'don\'t()'):
        should_multiply = False
    elif should_multiply:
        numbers = re.findall(data, s)
        sum += int(numbers[0]) * int(numbers[1])

print(sum)


