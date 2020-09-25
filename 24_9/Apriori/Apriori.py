import pandas as pd
from itertools import combinations

# read data_______________________________________________________________________________________________________
df = pd.read_csv('dataSet_csv.csv', index_col='TID')
# print(df)

# declaration of important variables______________________________________________________________________________
min_support = 2
items = df.columns.to_list()
transactions = df.index.to_list()

# create item set for transactions________________________________________________________________________________
item_set = {}
# row[0] is transaction id
# row[1] is values for this id in series type
for row in df.iterrows():
    # return all item in transaction 1
    item_set[row[0]] = set([value for value in row[1].index if row[1][value] == 1])
print(item_set)

# get qualified items above min support___________________________________________________________________________
item_count = {}
for item in df.columns:
    series = df[item].value_counts()
    # print(item,'->',series)
    if 1 in series:
        if series[1] >= min_support:
            item_count[item] = series[1] if 1 in series else 0
    else:
        continue
print(item_count)

# get all possible sets _______________________________________________________________
all_Combinations = [[set for set in combinations(item_count.keys(), i)] for i in range(2, len(item_count.keys()) + 1)]
print(all_Combinations)

#
