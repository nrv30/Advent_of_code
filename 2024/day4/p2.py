def check_up(puzzle, puzzle_len, i, j):

def check_down(puzzle, puzzle_len, i, j):

def main():
    f = open("test_down.txt")
    puzzle = []

    for line in f:
        # list(map(str.strip, lst))
        temp = list(line)
        if temp[len(temp)-1] == '\n':
            temp.pop()
        puzzle.append(temp)
    f.close()
    for row in puzzle:
        print (row)
    exit(1);
    puzzle_len = len(puzzle)
    found = 0
    indices = []
    for i in range(puzzle_len):
        line = puzzle[i]
        line_len = len(line)
        for j in range(line_len):
            c = line[j]
            if i < puzzle_len - 3:
                # check down
            if i > 1:
                # check up
            if (c == 'M' and j < line_len - 2 and line[j+2] == 'M'
            and ) 
    print(found)

main()