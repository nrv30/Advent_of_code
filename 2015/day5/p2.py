def rule1(src):
    src_len = len(src)
    for i in range(src_len):
        pair = src[i:i+2]
        for j in range (i+2, src_len):
            diff_pair = src[j:j+2]
            print(diff_pair)
            if pair == diff_pair:
                return True
    return False

def rule2(src):
    src_len = len(src)
    for i in range(src_len-1):
        c = src[i:i+1]
        other = src[i+2:i+3]
        print(c + " " + other)
        if c == src[i+2:i+3]: return True
    return False

def main():
    safe = 0
    f = open("input.txt")
    for line in f:
        src = line.strip()
        if rule1(src) and rule2(src): 
            safe += 1
    f.close()
    print(safe)

main()