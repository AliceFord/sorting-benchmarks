import csv
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

sns.set_style("whitegrid")

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

fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2)
plots = [ax1, ax2, ax3, ax4]
titles = ["Random starting array", "Nearly sorted starting array", "Reversed starting array", "Few unique starting array"]

for i in range(4):
    ax = plots[i]
    ax.set_xlabel("Sorting Function")
    ax.set_ylabel("Successful sorts in 1s")
    ax.set_title(titles[i])
    ax.set_ylim(0, np.amax(plotdata[:,i]) + 100)

    ax.bar(labels, plotdata[:,i])

plt.show()
