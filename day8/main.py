from collections import defaultdict, deque
def parse():
    with open("input.txt") as file:
        graph = defaultdict(list)
        lines = file.readlines()
        instructions = lines[0].strip()
        for line in lines[2:]:
            parts = line.strip().split("=")
            src = parts[0].strip()
            for dst in parts[1].strip()[1:-1].split(","):
                graph[src].append(dst.strip())
        return instructions, graph

def part1(instructions, graph):
    curr = "AAA"
    i = 0
    steps = 0
    while curr != "ZZZ":
        if i == len(instructions):
            i = 0
        if instructions[i] == "L":            
            curr = graph[curr][0]
        else:
            curr = graph[curr][1]
        i += 1
        steps += 1
    return steps

import math
def part2(instructions, graph):
    all_steps = []
    sources = [src for src in graph if src[-1] == "A"]
    for src in sources:
        curr = src
        i = 0
        steps = 0
        while curr[-1] != "Z":
            if i == len(instructions):
                i = 0
            if instructions[i] == "L":
                curr = graph[curr][0]
            else:
                curr = graph[curr][1]
            i += 1
            steps += 1
        all_steps.append(steps)
    return math.lcm(*all_steps)

def solve():
    instructions, graph = parse()
    print(f"Part 1 ans: {part1(instructions, graph)}")
    print(f"Part 2 ans: {part2(instructions, graph)}")

solve()
        