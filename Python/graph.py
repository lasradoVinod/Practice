import os
import re
import matplotlib.pyplot as plt
import numpy as np

Data = {}
for dirname, dirnames, filenames in os.walk('./Logs'):
  for fileName in filenames:  
    protName = fileName.split(".")[0]
    match = re.match(r"([a-zA-Z]+)([0-9]+)", protName, re.I)
    if match:
      items = list(match.groups())
    Name = items[0]
    del items[0]
    temp = int(items[0])
    del items[0]
    ret = Data.get(temp)
    if ret == None:
      Data[temp] = {}
    with open("./Logs/"+fileName) as fp:
      for line in fp:
        if (line.find("Totals") != -1):
          start = line.find("Throughput: ")
          start = start + 12
          end = line.find("Mbps")
          value = float (line[start:end])
    Data[temp][Name] = value

print Data
fig = plt.figure()

ax = []
ax.append(fig.add_subplot(151))
ax.append(fig.add_subplot(152))
ax.append(fig.add_subplot(153))
ax.append(fig.add_subplot(154))
ax.append(fig.add_subplot(155))

ax[0].set_ylabel('Throughput')
p = 0 
for key, elem in Data.items():
  X = []
  Y = []
  for ke,ele in elem.items():
    Y.append(ele)
    X.append(ke)
  ind = np.arange(len(elem))  # tfor tick in ax.get_xticklabels():
  width = 0.35       # the width of the bars
  ax[p].bar(ind+width,Y,width)
  ax[p].set_title(str(key) + 'spoke(s)')
  ax[p].set_xticks(ind + width / 2)
  ax[p].set_xticklabels(tuple(X))
  for ticks in ax[p].get_xticklabels():
    ticks.set_rotation(90)
  p = p + 1

plt.show()
