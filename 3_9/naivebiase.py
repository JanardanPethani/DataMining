import pandas as pd
import math

maindf = pd.read_csv('data.csv')
# print(maindf)
mainAttributes = maindf.columns[0:-1]
last = maindf.columns[-1]
# print(maindf[[mainAttributes[0],last]])

# find fre. of yes and no
uniqueC = maindf[last].value_counts()
totalYes = uniqueC.loc['yes']
totalNo = uniqueC.loc['no']

# To find frequencies of given attribute
def findFreq(df):
    # name of present attribute
    name = df.columns[0]
    attrUnique = list(df[name].unique())
    valueDict = {}
    for attr in attrUnique:
        df1 = df.loc[(df[name] == attr), [name, last]]
        tempC = df1[last].value_counts()
        # print(tempC)
        y = 0
        n = 0
        if len(tempC)>1:
            y = tempC.loc['yes']
            n = tempC.loc['no']
        elif len(tempC) == 1:
            if 'yes' in tempC:
                y = tempC.loc['yes']
            else:
                n = tempC.loc['no']
        lst = []
        lst.append((y/totalYes).__round__(4))
        lst.append((n/totalNo).__round__(4))
        valueDict[attr] = lst
    return  valueDict

freqDic = {}
for attr in mainAttributes:
    freqDic[attr] = findFreq(maindf[[attr,last]])
    print(attr,freqDic[attr])

# take input
inLst = []
freqY = 1
freqN = 1
total = totalYes + totalNo
for attr in mainAttributes:
    frqValues = freqDic[attr]
    ipValue = input(f"For {attr}:")
    freqY *= frqValues[ipValue][0]
    freqN *= frqValues[ipValue][1]
freqY *= totalYes/total
freqN *= totalNo/total

if freqN > freqY:
    print("Answer is No")
else:
    print("Answer is yes")





