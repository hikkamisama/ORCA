import matplotlib.pyplot as plt
from IPython.display import clear_output
import imageio
import os
import numpy as np
plt.figure(figsize=(5, 5))
ax = plt.gca()
ax.set_xlim(-15, 15)
ax.set_ylim(-15, 15)
filenames = []

def draw_line(x1, x2, y1, y2):
    vx = x2 - x1
    vy = y2 - y1 
    xans_min = x1 - vx * 10 
    xans_max = x2 + vx * 10
    yans_min = y1 - vy * 10
    yans_max = y2 + vy * 10
    return xans_min, xans_max, yans_min, yans_max
SPEED = 1
PERCENT = 0.2
f = open("test.txt", "r")

frames = []
dicts = []
x_lim_min = np.inf
x_lim_max = -np.inf
y_lim_min = np.inf
y_lim_max = -np.inf

number = 0

for l in f.readlines():
    x = l[:-1].split("; ")
    d = {i.split()[0] : i.split()[1:] for i in x}
    for key in d:
        for i, s in enumerate(d[key]):
            try: 
                d[key][i] = int(d[key][i])
            except ValueError:
                try:
                    d[key][i] = float(d[key][i])
                except ValueError:
                    pass
        if len(d[key]) == 1:
            d[key] = d[key][0]
    if d['type'] == 'END':
        frames += [dicts]
        dicts = []
        continue
    dicts += [d]
    if d['type'] == 'AGENT' :
        if x_lim_min > d['x'] - d['r']:
            x_lim_min = d['x'] - d['r']
        if x_lim_max < d['x'] + d['r']:
            x_lim_max = d['x'] + d['r']
        if y_lim_min > d['y'] - d['r']:
            y_lim_min = d['y'] - d['r']
        if y_lim_max < d['y'] + d['r']:
            y_lim_max = d['y'] + d['r']
        number = max(number, d['num'])

number += 1
h = y_lim_max - y_lim_min
w = x_lim_max - x_lim_min

if w < h:
    x_lim_min -= (h - w) / 2
    x_lim_max += (h - w) / 2
else:
    y_lim_min -= (w - h) / 2
    y_lim_max += (w - h) / 2

x_lim_min -= max(w, h) * PERCENT
x_lim_max += max(w, h) * PERCENT
y_lim_min -= max(w, h) * PERCENT
y_lim_max += max(w, h) * PERCENT

ax = plt.gca()
ax.set_xlim(x_lim_min, x_lim_max)
ax.set_ylim(y_lim_min, y_lim_max)

colors = ['C' + str(i) for i in range(number)]
colors_for_debug = colors

with imageio.get_writer('mygif.gif', mode='I') as writer:
    for i in range(len(frames)):
        for d in frames[i]:
            if d['type'] == 'VEC':
                plt.scatter(d['x'], d['y'], color=colors_for_debug[d['num']])
            if d['type'] == 'AGENT':
                drawing = plt.Circle((d['x'], d['y']), d['r'], color=colors[d['num']])
                ax.add_patch(drawing)
            if d['type'] == 'LINE':
                x1, x2, y1, y2 = draw_line(d['x1'], d['x2'], d['y1'], d['y2'])
                plt.plot([x1, x2], [y1, y2], color=colors_for_debug[d['num']])
        filename = 'tmp.png'
        plt.savefig(filename)
        plt.close()
        plt.figure(figsize=(5, 5))
        ax = plt.gca()
        ax.set_xlim(x_lim_min, x_lim_max)
        ax.set_ylim(y_lim_min, y_lim_max)
        image = imageio.imread(filename)
        writer.append_data(image)
        if i == 0:
            for j in range(4 * SPEED):
                writer.append_data(image)
        else:
            for j in range(SPEED):
                writer.append_data(image)
        os.remove(filename)