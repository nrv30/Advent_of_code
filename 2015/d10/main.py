
def look_and_say(inp):
    say = []
    current = inp[0]
    count = 1
    print(current)
    for i in range(1, len(inp)):
        if (inp[i] == current): 
            count+=1
            continue
        say.append(f'{count}{current}')
        current = inp[i]
        count = 1
        if (i == len(inp)-1):
            say.append(f'{count}{current}')
    return ''.join(say)

inp = '1113222113'
for i in range(50):
    inp = look_and_say(inp)
print(len(inp))