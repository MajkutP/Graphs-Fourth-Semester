import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt 
import matplotlib.patches as patches
from glob import glob
from math import sin, cos

def get_file_name_from_user():
	while True:
		file_name = input("Please enter file name: ")
		if len(glob(file_name)) == 1:
			break
	return file_name


def read_from_file(file_name):
	edges = []
	number_of_vertices = 0;
	with open(file_name, 'r') as file:
		for line in file:
			if line=='a\n' or line=='\n':
				continue
			temp_line = list(line)
			temp_line = [ elem for elem in temp_line if elem != ' ' and elem != "\n"]
			print(temp_line) 
			for index in range (len(temp_line)):
				if temp_line[index] == '1':
					if tuple(reversed((number_of_vertices, index))) not in edges:
						edges.append((number_of_vertices, index))
			number_of_vertices += 1
	return edges, number_of_vertices

def plot_graph(number_of_vertices, edges):
	fig1 = plt.figure()
	fig1.set_size_inches(18.5, 10.5)
	ax1 = fig1.add_subplot(111, aspect='equal')
	ax1.set_xlim([-20, 20])
	ax1.set_ylim([-20, 20])
	ax1.axis('off')
	angle_delta = 2*3.14 / number_of_vertices
	for i in edges:
		x = [ 18 * cos(angle_delta * i[0]) , 18 * cos(angle_delta * i[1]) ]
		y = [ 18 * sin(angle_delta * i[0]) , 18 * sin(angle_delta * i[1]) ]
		ax1.plot(x, y, color = 'red', zorder = 1)
	for i in range(number_of_vertices):
		ax1.add_patch(patches.Circle((18 * cos(angle_delta*i), 18*sin(angle_delta*i)), 1, facecolor="#2EFE2E", zorder = 2))
		ax1.annotate(str(i+1), xy=(18 * cos(angle_delta*i) - 0.25, 18*sin(angle_delta*i)-0.25))
	fig1.savefig(get_output_file_name(), dpi=90, bbox_inches='tight')


def get_output_file_name():
	output_file = input("Please enter output file name: ")
	return output_file



file_name = get_file_name_from_user()
graph_parameters = read_from_file(file_name) 
plot_graph(graph_parameters[1], graph_parameters[0])



