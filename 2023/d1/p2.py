nums = {
    "one": 1,
    "two": 2,
    "three": 3,
    "four":4,
    "five":5,
    "six":6,
    "seven":7,
    "eight":8,
    "nine":9,
}

with open('input.txt') as f:
    total = 0
    values = []
    for line in f:
        line = line.strip()
        start = -1
        end = -1
        for i in range(len(line)):
            num = -1
            c = line[i]
            if c.isdigit():
                num = int(c)
            else:
                # print('reached')
                for j in range(5,2,-1):
                    sub = line[i:i+j]
                    # print(f'sub: {sub}')
                    if sub in nums:
                        num = nums[sub]
                        break
            
            if num != -1:
                if start == -1:
                    start = num
                else:
                    end = num 
        if (end == -1):
            end = start
        total += int(start)*10 + int(end)
    
    print(total)
