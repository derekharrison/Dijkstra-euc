import numpy as np
import matplotlib.pyplot as plt
from numpy import *
import matplotlib.animation as manimation
import time

start_time = time.time()

coordinates_x, coordinates_y = np.genfromtxt(r'graph_coordinates.txt', unpack=True)
start_vertex, start_x, start_y, end_vertex, end_x, end_y, weight = np.genfromtxt(r'shortest_path_data.txt', unpack=True)

plt.rcParams['animation.ffmpeg_path']='C:/Users/d-w-h/Downloads/ffmpeg-20200818-1c7e55d-win64-static/ffmpeg-20200818-1c7e55d-win64-static/bin/ffmpeg.exe'
writer=manimation.FFMpegWriter(bitrate=20000, fps=15)

fig = plt.figure(figsize=(8,8))
ax = plt.axes(xlim=(0, 10), ylim=(0, 10))
print(size(start_vertex))

def animate(i):
    print(i)
    ax = plt.scatter(coordinates_x, coordinates_y, s=10, c='green')
    X = (start_x[i], end_x[i])
    Y = (start_y[i], end_y[i])
    dx = end_x[i] - start_x[i]
    dy = end_y[i] - start_y[i]
    cont = plt.plot(X, Y)
    #cont = plt.arrow(start_x[i], start_y[i], dx, dy, head_width = 0.15, length_includes_head = True)

    return cont

size_t = size(start_vertex)
anim = manimation.FuncAnimation(fig, animate, frames=size_t, repeat=False)

print("Done Animation, start saving")

anim.save('test.mp4', writer=writer, dpi=200)
    
print("--- %s seconds ---" % (time.time() - start_time))
