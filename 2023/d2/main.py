max_cubes = {
    "red": 12,
    "green": 13,
    "blue": 14,
}

# game
  # subsets
    # types
      # number and color

def is_possible(game):
    for subset in game:
            cube_types = subset.split(',')
            for ctype in cube_types:
                num, color = ctype.strip().split(' ')
                if int(num) > max_cubes[color]:
                    return False
    return True

with open("input.txt") as f:
    possible_games = []
    for line in f:
        line = line.strip()
        colon_index = line.find(':')
        game_id = line[5:colon_index]
        print(f'game id {game_id}')
        game = line[colon_index+2:].split(';')
        if is_possible(game):
           possible_games.append(int(game_id))
    print(sum(possible_games))
    # print(possible_games)
