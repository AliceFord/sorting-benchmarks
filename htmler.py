import csv
import numpy as np

plotdata = []
labels = []

with open("data.csv") as csvfile:
    reader = csv.reader(csvfile)

    for i, row in enumerate(reader):
        plotdata.append([])
        for j, item in enumerate(row):
            if j > 0:
                plotdata[i].append(int(item))
            else:
                labels.append(item)

plotdata = np.array(plotdata)

lowers = []
uppers = []
for col in plotdata.T:
    lowers.append(np.median(sorted(col)[:len(col)//2]))
    uppers.append(np.median(sorted(col)[len(col)//2:]))

for i, label in enumerate(labels):
    print("<tr>")
    print(f"\t<td>{label}</td>")

    for j, item in enumerate(plotdata[i]):
        print("\t<td ", end='')
        if item <= lowers[j]:
            print("style=\"background:#fdd;\"", end='')
        elif item > lowers[j] and item < uppers[j]:
            print("style=\"background:#ffd;\"", end='')
        else:
            print("style=\"background:#dfd;\"", end='')

        print(f">{item}</td>")

    print("</tr>")
