def parse():
    with open("input.txt") as file:
        times = list(map(int, file.readline().split(":")[1].strip().split()))
        distances = list(map(int, file.readline().split(":")[1].strip().split()))
        return times, distances

def get_bounds(t, d):
    left, right = 1, t - 1
    lower = upper = None
    while left <= right and (not upper and not lower):
        if (t - right) * right > d:
            upper = right
        else:
            right -= 1
        if (t - left) * left > d:
            lower = left
        else:
            left += 1
    return lower, upper
def solve():
    times, distances = parse()
    total = 1
    for t, d in zip(times, distances):
        lower, upper = get_bounds(t, d)
        total *= (upper - lower + 1)
    
    t = int("".join(map(str, times)))
    d = int("".join(map(str, distances)))
    lower, upper = get_bounds(t, d)
    print(f"Part 1 ans: {total}")  
    print(f"Part 2 ans: {upper - lower + 1}")  
    
solve()