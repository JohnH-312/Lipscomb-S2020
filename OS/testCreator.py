import random

matrixNo = int(input())
row = random.randint(20,250)
col = random.randint(20,250)
for i in range(matrixNo):
    print("{0} {1}".format(row,col))
    for j in range(row):
        for k in range(col):
            value = random.randint(0,100)
            print("{0} ".format(value),end = '')
        print("")
    row = col
    col = random.randint(20,250)
print("0 0")