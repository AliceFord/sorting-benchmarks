import csv
import numpy as np

plotdata = []

with open("merge.csv") as csvfile:
    reader = csv.reader(csvfile)

    for i, row in enumerate(reader):
        plotdata.append([])
        for j, item in enumerate(row):
            plotdata[i].append(item)

plotdata = sorted(plotdata, key=lambda x: x[0])
finaldata = []

currents = [0, 0, 0, 0]
currentSum = 1

for it, item in enumerate(plotdata[:-1]):
    if item[0] == plotdata[it + 1][0]:
        for i in range(4):
            currents[i] += int(item[i + 1])
        currentSum += 1
    else:
        for i in range(4):
            currents[i] += int(item[i + 1])
            currents[i] //= currentSum

        finaldata.append([item[0]])
        for i in range(4):
            finaldata[-1].append(currents[i])

        currentSum = 1
        currents = [0, 0, 0, 0]

for i in range(4):
    currents[i] += int(plotdata[-1][i + 1])
    currents[i] //= currentSum

finaldata.append([plotdata[-1][0]])
for i in range(4):
    finaldata[-1].append(currents[i])

with open("data.csv", "w") as f:
    f.write("\n".join([",".join(str(item) for item in row) for row in finaldata]))
