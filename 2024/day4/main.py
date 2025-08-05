def right(j, line):
    if (line[j+1] == 'M' and line[j+2] == 'A'
        and line[j+3] == 'S'): return True
    else: return False 

def left(j, line):
    if (line[j-1] == 'M' and line[j-2] == 'A'
        and line[j-3] == 'S'): return True
    else: return False 
def down(i, j, puzzle):
    if (puzzle[i+1][j] == 'M' and puzzle[i+2][j] == 'A' 
        and puzzle[i+3][j] == 'S'): return True
    else: return False

def up(i, j, puzzle):
    if (puzzle[i-1][j] == 'M' and puzzle[i-2][j] == 'A' 
        and puzzle[i-3][j] == 'S'): return True
    else: return False

def down_right(i, j, puzzle):
    if (puzzle[i+1][j+1] == 'M' and puzzle[i+2][j+2] == 'A' 
        and puzzle[i+3][j+3] == 'S'): return True
    else: return False

def down_left(i, j, puzzle):
    if (puzzle[i+1][j-1] == 'M' and puzzle[i+2][j-2] == 'A' 
        and puzzle[i+3][j-3] == 'S'): return True
    else: return False

def up_right(i, j, puzzle):
    if (puzzle[i-1][j+1] == 'M' and puzzle[i-2][j+2] == 'A' 
        and puzzle[i-3][j+3] == 'S'): return True
    else: return False

def up_left(i, j, puzzle):
    if (puzzle[i-1][j-1] == 'M' and puzzle[i-2][j-2] == 'A' 
        and puzzle[i-3][j-3] == 'S'): return True
    else: return False

def main():
    f = open("input.txt")
    puzzle = []

    for line in f:
        # list(map(str.strip, lst))
        temp = list(line)
        if temp[len(temp)-1] == '\n':
            temp.pop()
        puzzle.append(temp)
    f.close()
            
    puzzle_len = len(puzzle)
    found = 0
    indices = []
    for i in range(puzzle_len):
        line = puzzle[i]
        line_len = len(line)
        for j in range(line_len):
            c = line[j]
            if c == 'X':
                if i <= puzzle_len-4:
                    if(down(i, j, puzzle)): 
                        found+=1
                        indices.append([i, j])
                #     break
                if j <= line_len - 4:
                    if(right(j, line)): 
                        found+=1
                        indices.append([i, j])
                        # break
                if j >= 3:
                    if (left(j, line)):
                        found+=1
                        indices.append([i, j])
                        # break
                if i >= 3:
                    if (up(i, j, puzzle)):
                        found+=1
                        indices.append([i, j])
                        # break
                if i >= 3 and j <= line_len - 4 :
                    if (up_right(i, j, puzzle)):
                        found+=1
                        indices.append([i, j])
                        # break
                if i >= 3 and j >= 3:
                    if (up_left(i, j, puzzle)):
                        found+=1
                        indices.append([i, j])
                        # break
                if i <= puzzle_len-4 and j <= line_len - 4 :
                    if (down_right(i, j, puzzle)):
                        found+=1
                        indices.append([i, j])
                        # break
                if i <= puzzle_len-4 and j >= 3:
                    if (down_left(i, j, puzzle)):
                        found+=1
                        indices.append([i, j])
                        # break


    print(found)
    print(indices)

main()