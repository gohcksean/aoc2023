def parse():
    hands, bid = [], []
    with open("input.txt") as file:
        for line in file:
            line = line.strip()
            parts = line.split()
            hands.append(parts[0])
            bid.append(int(parts[1]))
    
    return hands, bid


from enum import Enum

class HandType(Enum):
    FIVE_OF_A_KIND = 7
    FOUR_OF_A_KIND = 6
    FULL_HOUSE = 5
    THREE_OF_A_KIND = 4
    TWO_PAIR = 3
    ONE_PAIR = 2
    HIGH_CARD = 1
def get_hand_type(hand):
    count = {}
    for card in hand:
        count[card] = count.get(card, 0) + 1
    values = list(count.values())
    
    if len(values) == 1:
        return HandType.FIVE_OF_A_KIND
    elif len(values) == 2:
        if 4 in values and 1 in values:
            return HandType.FOUR_OF_A_KIND
        elif 3 in values and 2 in values:
            return HandType.FULL_HOUSE
    elif len(values) == 3:
        if 3 in values:
            return HandType.THREE_OF_A_KIND
        elif 2 in values:
            return HandType.TWO_PAIR
    elif len(values) == 4:
        return HandType.ONE_PAIR
    return HandType.HIGH_CARD

def get_hand_type_with_joker(hand):
    count = {}
    jokers = 0
    for card in hand:
        if card == "J":
            jokers += 1
        else:
            count[card] = count.get(card, 0) + 1
    if jokers == 0:
        return get_hand_type(hand)
    values = list(count.values())
    if jokers == 1:
        if len(values) == 1: # 4
            return HandType.FIVE_OF_A_KIND
        if len(values) == 2:
            if 3 in values: # 3 1
                return HandType.FOUR_OF_A_KIND
            if 2 in values: # 2 2
                return HandType.FULL_HOUSE
        if len(values) == 3: # 2 1 1
            return HandType.THREE_OF_A_KIND
        if len(values) == 4: # 1 1 1 1
            return HandType.ONE_PAIR
    if jokers == 2:
        if len(values) == 1: # 3
            return HandType.FIVE_OF_A_KIND
        if len(values) == 2: # 2 1
            return HandType.FOUR_OF_A_KIND
        if len(values) == 3: # 1 1 1
            return HandType.THREE_OF_A_KIND
    if jokers == 3:
        if len(values) == 1: # 2
            return HandType.FIVE_OF_A_KIND
        if len(values) == 2: # 1 1
            return HandType.FOUR_OF_A_KIND
    
    return HandType.FIVE_OF_A_KIND

def solve():
    hands, bids = parse()
    ranked_hands = []
    ranked_hands_with_joker = []
    CARD_RANKS = ['2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A']
    CARD_RANKS_JOKER = ['J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A']
    for hand, bid in zip(hands, bids):
        hand_type = get_hand_type(hand)
        ranked_hands.append((hand_type, hand, bid))
        hand_type_with_joker = get_hand_type_with_joker(hand)
        ranked_hands_with_joker.append((hand_type_with_joker, hand, bid))
        
    ranked_hands.sort(key=lambda h: (h[0].value, tuple(CARD_RANKS.index(c) for c in h[1])))
    total_winnings = 0
    for i, h in enumerate(h[2] for h in ranked_hands):
        total_winnings += (i + 1) * h
        
    ranked_hands_with_joker.sort(key=lambda h:(h[0].value, tuple(CARD_RANKS_JOKER.index(c) for c in h[1])))
    total_winnings_with_joker = 0
    for i, h in enumerate(h[2] for h in ranked_hands_with_joker):
        total_winnings_with_joker += (i + 1) * h
    print(f"Part 1 ans: {total_winnings}")
    print(f"Part 2 ans: {total_winnings_with_joker}")
    
solve()