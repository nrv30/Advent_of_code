
def issafe_level(diff, state) :
    if state > 0 and diff < 0:
        return False
    elif state < 0 and diff > 0:
        return  False
    
    abs_diff = abs(diff)
    if abs_diff == 0 or abs_diff > 3:
        return False
    
    return True

def consider_removing(index, report):
    print("considerint " + str(index))
    temp_list = (report.copy())
    temp_list.pop(index)
    print(temp_list)
    return issafe_report(temp_list)

def consider_all(report):
    print ("original list: ")
    print (report)
    for i in range (len(report)):
        if consider_removing(i, report):
            return True
    return False

def issafe_report(report):
    state = 69
    was_called = False
    safe_report = True
    for i in range(1, len(report)):
        if i > 0:
            diff = report[i] - report[i-1]
            if state == 69 and diff > 0:
                state = 1
            elif state == 69 and diff < 0:
                state = -1

        # Broken part for part two
        level_safe = issafe_level(diff, state)
        if not issafe_level(diff, state):
            return False
    
    return safe_report

def main():
    f = open("input.txt", "r")
    safe = 0
    for line in f:
        report = list(map(int, line.split()))
        print("report")
        print(report)
        if issafe_report(report):
            safe+=1
            print("SAFE")
        else: 
            print("UNSAFE")
            if consider_all(report):
                safe += 1
                print("SUCESSFUL REMOVAL")
            else: print("STILL UNSAFE")
    print(safe)

main()
