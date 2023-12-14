def parse():
    with open("input.txt") as file:
        histories = []
        for line in file.readlines():
            line = line.strip()
            if not line: continue
            histories.append(list(map(int, line.split())))
        return histories

def compute_diffs(history):
    old_diff = history
    diffs = []
    while True:
        diff_arr = []
        for i in range(1, len(old_diff)):
            diff_arr.append(old_diff[i] - old_diff[i-1])
        if len(set(diff_arr)) == 1:
            diffs.append(diff_arr)
            return sum(d[-1] for d in diffs), get_backward_diff(diffs)
        else:
            diffs.append(diff_arr)
            old_diff = diff_arr

def get_backward_diff(diffs):
    for i in range(len(diffs) - 2, -1, -1):
        diffs[i][0] -= diffs[i+1][0]
    return diffs[0][0]

def solve():
    histories = parse()
    extrapolated_sum = 0
    extrapolated_sum_back = 0
    for history in histories:
        forward_diff, backward_diff = compute_diffs(history)
        extrapolated_sum += history[-1] + forward_diff
        extrapolated_sum_back += history[0] - backward_diff
    print(f"Part 1 ans: {extrapolated_sum}")
    print(f"Part 2 ans: {extrapolated_sum_back}")
        

solve()
            