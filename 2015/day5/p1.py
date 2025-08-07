import re;

def repeat(src):
    for i in range(len(src)):
        if src[i:i+1] == src[i+1:i+2]: return True
    return False

def is_valid(src):
    rule1 = r'[aeiou]'
    rule2 = r'^(?!.*ab)(?!.*cd)(?!.*pq)(?!.*xy).*'

    matches_rule1 = re.findall(rule1, src)
    matches_rule2 = re.findall(rule2, src)
    if len(matches_rule1) < 3: 
        print("Naughty due to rule 1")
        return False
    elif len(matches_rule2) <= 0: 
        print("Naughty due to rule 2")
        return False
    elif not repeat(src):
        print("Naughty due to rule 3")
        return False
    else: return True

def main():
    happy = 0
    f = open("input.txt")
    for line in f:
        src = line.strip()
        if is_valid(src): happy+=1
    print(happy)

    # src = 'ugknbfddgicrmopn'
    # print(is_valid(src))

main()

