import pandas as pd
from itertools import combinations

data = pd.read_excel('dataSet.xlsx', sheet_name='Sheet1')

"""get transaction table"""
transactions = data["TID"].to_dict()
item_set = data['ItemSet'].to_dict()
item_set = {tid: value.split(',') for tid, value in item_set.items()}
print('Data:', item_set)

"""get count satisfying minimum support"""
min_support = 2
# min_support = int(input("Enter minimum support"))
frq_count = {}
# all_items = set( val for list in item_set.values() for val in list)
# print(all_items)
total_items = []
for value in item_set.values():
    total_items.extend(value)
# print(total_items)
uni_items = set(total_items)
# print(uni_items)

""" get all items above min support """
print('-' * 100)
frq_count = {item: total_items.count(item) for item in uni_items if total_items.count(item) >= min_support}
print('item-count:', frq_count)

"""get all possible combinations from item_set"""
print('-' * 100)
all_combinations = []
for value_list in item_set.values():
    for i in range(2, len(value_list) + 1):
        all_combinations.extend(combinations(value_list, i))
print('All-combinations:', all_combinations)

"""find count of sets"""
print('-' * 100)
set_count = {set_value: all_combinations.count(set_value) for set_value in all_combinations if
             all_combinations.count(set_value) >= min_support}
print('All-set-counts:', set_count)
max_length = 0
for key in set_count:
    if max_length < len(key):
        max_length = len(key)
print("max-length of set:", max_length)
