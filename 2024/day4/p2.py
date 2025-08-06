def in_range(i, j, puzzle, puzzle_len, line_len):
    if (i > 0 and i < puzzle_len-1 and j > 0 and j < line_len-1):
        return True
    else: return False

def consider(i, j, puzzle):
    is_match = False
    if (puzzle[i-1][j-1] == 'M' and puzzle[i-1][j+1] == 'M'
        and puzzle[i+1][j-1] == 'S' and puzzle[i+1][j+1] == 'S'):
            is_match = True
    if (puzzle[i-1][j-1] == 'S' and puzzle[i-1][j+1] == 'S'
        and puzzle[i+1][j-1] == 'M' and puzzle[i+1][j+1] == 'M'):
            is_match = True
    if (puzzle[i-1][j-1] == 'S' and puzzle[i-1][j+1] == 'M'
        and puzzle[i+1][j-1] == 'S' and puzzle[i+1][j+1] == 'M'):
            is_match = True
    if (puzzle[i-1][j-1] == 'M' and puzzle[i-1][j+1] == 'S'
        and puzzle[i+1][j-1] == 'M' and puzzle[i+1][j+1] == 'S'):
            is_match = True
    
    return is_match

def main():
    f = open("input.txt")
    puzzle = []

    for line in f:
        temp = list(line.replace('\n', ''))
        puzzle.append(temp)
    f.close()

    puzzle_len = len(puzzle)
    found = 0
    for i in range(puzzle_len):
        line = puzzle[i]
        line_len = len(line)
        for j in range(line_len):
            c = line[j]
            if c == 'A':
                if in_range(i, j, puzzle, puzzle_len, line_len): 
                    if consider(i, j, puzzle):
                        found+=1
    print(found)

main()