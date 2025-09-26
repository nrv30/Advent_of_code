'''
referenced: https://aoc.just2good.co.uk/2015/19.html
'''

import re

def recurs (target_groups, target, patterns, count):
    print(f'target: {target}')
    if (target == 'e'): 
        return count
    index = 0
    for key in target_groups:
        pattern = patterns[index]
        matches = pattern.findall(target)
        matches_count = len(matches)
        if matches_count > 0:
            count+=matches_count
            next_target = re.sub(pattern, target_groups[key], target)
            return recurs (target_groups, next_target, patterns, count)
        index+=1
    return count
            
with open("input.txt") as f:
    target_groups = {}
    molecules = set()
    medicine_moluecule = ''
    for line in f:
        line = line.strip()
        if '=>' in line:
            equals_index = line.find('=>')
            target_groups[line[equals_index+3:]] =  line[0:equals_index-1]
        elif line != '\n': medicine_molecule = line

    print (target_groups)
    print (medicine_molecule)

    sorted_target_groups = dict(sorted(target_groups.items(), key=lambda item: len(item[0]), reverse=True))

    patterns = []
    for pattern in sorted_target_groups:
        print (pattern)
        patterns.append(re.compile(pattern))

    print(recurs(sorted_target_groups, medicine_molecule, patterns, 0))
    

    



    