from PIL import Image
import matplotlib.pyplot as plt
from matplotlib import colors
import numpy as np
import os
from numpy import genfromtxt

# Dir to the map
map_dir = './input.csv'
# Dir to the path
path_dir = './path.csv'

f = open(map_dir)
next(f)
next(f)
world = genfromtxt(f, delimiter=',')
path = genfromtxt(path_dir, delimiter=',')

EMPTY_CELL = 0
OBSTACLE_CELL = 1
START_CELL = 2
GOAL_CELL = 3
MOVE_CELL = 4
# create discrete colormap
cmap = colors.ListedColormap(['white', 'black', 'green', 'red', 'blue'])
bounds = [EMPTY_CELL, OBSTACLE_CELL, START_CELL, GOAL_CELL, MOVE_CELL ,MOVE_CELL + 1]
norm = colors.BoundaryNorm(bounds, cmap.N)

def generate_path(data, path):
	n = path.shape[0]
	data[int(path[0][0])][int(path[0][1])] = START_CELL
	data[int(path[n-1][0])][int(path[n-1][1])] = GOAL_CELL
	for i in range(1, n-1):
		data[int(path[i][0])][int(path[i][1])] = MOVE_CELL

def plot_grid(data, path, saveImageName):
	# plot grid map
	rows = data.shape[0]
	cols = data.shape[1]
	fig, ax = plt.subplots()
	ax.imshow(data, cmap=cmap, norm=norm)
	# draw gridlines
	ax.grid(which='major', axis='both', linestyle='-', color='k', linewidth=1)
	ax.set_xticks(np.arange(0.5, rows, 1))
	ax.set_yticks(np.arange(0.5, cols, 1))
	plt.tick_params(axis='both', which='both', bottom=False,   
                    left=False, labelbottom=False, labelleft=False)
	fig.set_size_inches((8.5, 11), forward=False)

	plt.savefig(saveImageName, dpi=500)

if __name__ == "__main__":
	generate_path(world, path)
	plot_grid(world, path, "result.png")
	im = Image.open(r"./result.png")
	size = (im.size[0]/8, im.size[1]/8)
	im.thumbnail(size)
	im.show() 