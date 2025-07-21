
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
    temp_list = (report.copy())
    temp_list.pop(index)
    print(temp_list)
    if (issafe_report(temp_list, True)): return True
    else: return False

def issafe_report(report, was_called_recurs):
    state = 69
    was_called = False
    for i in range(1, len(report)):
        if i > 0:
            diff = report[i] - report[i-1]
            if state == 69 and diff > 0:
                state = 1
            elif state == 69 and diff < 0:
                state = -1

        if not issafe_level(diff, state) and not was_called_recurs and not was_called:
            if consider_removing(i, report): 
                print("removing successful")
                was_called = True
                print(was_called)
                continue
            elif consider_removing(i-1, report): 
                print("removing successful")
                was_called = True
                continue
            elif i != len(report)-1:
                print("removing successful")
                if consider_removing(i+1, report): 
                    was_called = True
                    continue
            return False
        elif not issafe_level(diff, state) and was_called_recurs:
            return False
    return True

def main():
    print("hello world")
    f = open("input.txt", "r")
    safe = 0
    for line in f:
        print(line)
        report = list(map(int, line.split()))
         
        if issafe_report(report, False):
            safe+=1
            print("SAFE")
        else: print("UNSAFE")
    print(safe)

main()
