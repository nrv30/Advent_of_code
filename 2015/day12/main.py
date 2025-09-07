import json

def check(obj):
    sum_obj = 0
    typeof = type(obj)
    if typeof is dict:
        for key in obj:
            if key != 'red' and obj[key] != 'red' :
                sum_obj += check(obj[key])
            else: return 0
    elif typeof is list:
        for nested_obj in obj:
            sum_obj += check(nested_obj)
    elif typeof is int:
        sum_obj+= obj
    return sum_obj

with open('input.txt', 'r') as file:
    data = json.load(file)
    print(check(data))