max_cubes = {
    "red": 12,
    "green": 13,
    "blue": 14,
}


def is_possible(game):
    for subset in game:
            cube_types = subset.split(',')
            for ctype in cube_types:
                num, color = ctype.strip().split(' ')
                if int(num) > max_cubes[color]:
                    return False
    return True

# game
  # subsets
    # types
      # number and color
def part1():
    with open("input.txt") as f:
        possible_games = []
        for line in f:
            line = line.strip()
            colon_index = line.find(':')
            game_id = line[5:colon_index]
            game = line[colon_index+2:].split(';')
            if is_possible(game):
                possible_games.append(int(game_id))
        print(sum(possible_games))

def get_min_cubes(game):
    min_cubes = [0,0,0] # 0 is red, 1 is blue, 2 is green
    for subset in game:
            cube_types = subset.split(',')
            for ctype in cube_types:
                num, color = ctype.strip().split(' ')
                num = int(num)
                if color == 'red' and num > min_cubes[0]:
                    min_cubes[0] = num
                if color == 'blue' and num > min_cubes[1]:
                    min_cubes[1] = num
                if color == 'green' and num > min_cubes[2]:
                    min_cubes[2] = num
    return min_cubes

def part2():
    power = 0
    with open("input.txt") as f:
        for line in f:
            line = line.strip()
            colon_index = line.find(':')
            game = line[colon_index+2:].split(';')
            min_cubes = get_min_cubes(game)
            power += min_cubes[0] * min_cubes[1] * min_cubes[2]

    print(power)

part1()
part2()