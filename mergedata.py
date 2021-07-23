import csv

finaldata = []

with open("data.csv") as csvfile:
    storedData = csv.reader(csvfile)
    with open("merge.csv") as csvfile2:
        mergeData = csv.reader(csvfile2)
        for row in mergeData:
            for storedrow in storedData:
                if row[0] == storedrow[0]:
                    finaldata.append(storedrow)

            else:
                finaldata.append(row)

        for storedrow in storedData:
            print(storedrow)
            for finalrow in storedData:
                print(storedrow[0], finalrow)
                if storedrow[0] == finalrow[0]:
                    break
            
            else:
                finaldata.append(storedrow)

with open("data.csv", "w") as f:
    f.write("\n".join([",".join(item for item in row) for row in finaldata]))
