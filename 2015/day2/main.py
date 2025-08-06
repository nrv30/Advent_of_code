def p1():
    f = open("input.txt")
    total = 0
    for line in f:
        line.replace('\n', '')
        a,b,c = map(int, line.split('x'))
        # print(f'a:{a}, b:{b}, c:{c}')

        surface_area = 0
        for side in sides:
            surface_area += 2 * side
        total += surface_area + min(sides)
    print(total)
    f.close()


def p2():
    f = open("input.txt")
    total = 0
    for line in f:
        line.replace('\n', '')
        a,b,c = map(int, line.split('x'))
        perims = [2*(a+b), 2*(b+c), 2*(a+c)]
        total += min(perims) + a*b*c
    f.close()
    print(total)

def main():
    p2()

main()