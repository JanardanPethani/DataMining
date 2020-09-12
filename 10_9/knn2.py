import pandas as pd
import math
dS = pd.read_csv('resident.csv')
mainAttr = list(dS.columns[:-1])
lastCol = dS.columns[-1]
# dS.iloc[1,-1]


def minmax(dS):
    for attr in dS.columns[:-1]:
        minimum = min(dS[attr])
        maximum = max(dS[attr])
        for i in range(len(dS)):
            value = dS.loc[i, attr]
            newValue = (value - minimum)/(maximum - minimum)
            dS.loc[i, attr] = newValue.__round__(3)
    return dS

def takeIp(dS):
    ip = {}
    k = input("k :")
    for attr in dS.columns[:-1]:
        # print(attr)
        ip[attr] = float(input(f"for {attr}: "))
    return ip,k

def euclidion(dS,iD={}):
    ans = {}
    array = dS.to_numpy()
    rowNo = 0
    for row in array:
        cal = 0
        i = 0
        for attr in mainAttr:
            cal += math.pow((int(row[i]) - int(iD[attr])),2)
            i += 1
        ans[rowNo] = cal
        rowNo += 1
    lst = ans.items()
    slst = sorted(lst,key = lambda x : x[1])
    return slst

def takeDicision(k,distance,dS):
    valueDic = {}
    newlst = distance[:k]
    for value in newlst:
        valueDic[dS.iloc[value[0],-1]] = valueDic.get(dS.iloc[value[0],-1],0) + 1
    return max(valueDic,  key=valueDic.get)

dS = minmax(dS)
iD, k = takeIp(dS)
eulst = euclidion(dS, iD)
ans = takeDicision(int(k),eulst,dS)

print(ans)
