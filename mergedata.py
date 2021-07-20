import csv

finaldata = []

with open("data.csv") as csvfile:
    storedData = csv.reader(csvfile)
    with open("merge.csv") as csvfile2:
        mergeData = csv.reader(csvfile2)
        for row in mergeData:
            flag = False
            for storedrow in storedData:
                if row[0] == storedrow[0]:
                    finaldata.append(row)
                    flag = True

            if not flag:
                finaldata.append(row)

with open("data.csv", "w") as f:
    f.write("\n".join([",".join(item for item in row) for row in finaldata]))
