from random import randrange, uniform
from copy import deepcopy
from queue import Queue

class Network:
	def __init__(self, N):
		self.layers = [[] for j in range (N)]
		counter = 1
		for i in self.layers:
			for j in range(randrange(2, N+1)):
				i.append(counter)
				counter+=1
		self.layers.insert(0, [0])
		self.layers.append([counter])
		self.sink_id = counter
		self.d_s = []
		self.p_s = []
		for vertex in range(self.sink_id + 1):
			self.d_s.append(99999) # inf
			self.p_s.append(-1) # NIL
		print(self.layers)

		
	def print_layers(self):
		for layer in self.layers:
			print(layer)


	def init_edges(self):
		''' Edge is represented by two-element tuple of ints representing
		vertices, capacity and flow '''
		self.edges = []
		connected_to = []
		for layer in range(len(self.layers) - 1):
			not_connected = deepcopy(self.layers[layer + 1])
			print(not_connected)
			for src in self.layers[layer]:
				if not_connected:
					dst = randrange(0, len(not_connected))
					dst = not_connected[dst]
					not_connected.remove(dst)
					self.edges.append([src, dst, 0, 0])
					connected_to.append(dst)
				else:
					dst = randrange(0, len(self.layers[layer+1]))
					dst = self.layers[layer+1][dst]
					self.edges.append([src, dst, 0, 0])
					connected_to.append(dst)
		for vertex in range(1, self.sink_id - 1):
			if vertex not in connected_to:
				for layer in range(len(self.layers)):
					if vertex in self.layers[layer]:
						src = randrange(0, len(self.layers[layer - 1]))
						src = self.layers[layer-1][src]
						connected_to.append(vertex)
						self.edges.append ([src, vertex, 0, 0])
		print(self.edges)
		self.add_random_edges(5)


	def generate_capacity(self, lower_bound, upper_bound):
		for edge in self.edges:
			edge[3] = randrange(lower_bound, upper_bound + 1)
		print(self.edges)


	def dump_to_dot(self):
		dot_representation = "digraph { \n rankdir = LR"
		layer_counter = 0
		for layer in self.layers:
			layer_counter += 1
			colorH = uniform(0.2,0.9)
			colorS = uniform(0.2,0.9)
			colorB = uniform(0.2,0.9)
			color = "\"" + str(colorH) + ", " + str(colorS) + ", " + str(colorB) + "\""
			dot_representation += "{ rank = same; "
			for vertex in layer:
				dot_representation += str(vertex) + "[style = filled, color = " + color +  "]"
			dot_representation += "} \n"
		for edge in self.edges:
			dot_representation += '''{} -> {} [label ="{}/{}"]; '''.format(str(edge[0]), str(edge[1]), edge[2], edge[3])
		dot_representation += "} \n"
		return dot_representation

	def dump_to_dot_flow(self):
		dot_representation = "digraph { \n rankdir = LR"
		layer_counter = 0
		for layer in self.layers:
			layer_counter += 1
			colorH = uniform(0.2,0.9)
			colorS = uniform(0.2,0.9)
			colorB = uniform(0.2,0.9)
			color = "\"" + str(colorH) + ", " + str(colorS) + ", " + str(colorB) + "\""
			dot_representation += "{ rank = same; "
			for vertex in layer:
				dot_representation += str(vertex) + "[style = filled, color = " + color +  "]"
			dot_representation += "} \n"
		for edge in self.edges:
			dot_representation += '''{} -> {} [label ="{}"]; '''.format(str(edge[0]), str(edge[1]), edge[2])
		dot_representation += "} \n"
		return dot_representation

	def save_to_file_flow(self, filename):
		with open(filename, "w") as f:
			f.write(self.dump_to_dot_flow())


	def save_to_file(self, filename):
		with open(filename, "w") as f:
			f.write(self.dump_to_dot())

	def find_edge(self, from_, to_):
		for i in self.edges:
			if i[0] == from_ and i[1] == to_:
				return i
		return None


	def add_random_edges(self, number):
		added_edges = 0
		iter_counter = 0
		while True:
			src = randrange(0, self.sink_id )
			dst = randrange(1, self.sink_id + 1)
			temp_edge = [src, dst, 0, 0]
			temp_rev_edge = [dst, src, 0, 0]
			if temp_edge not in self.edges:
				if temp_rev_edge not in self.edges:
					if src != dst:
						self.edges.append(temp_edge)
						added_edges += 1
			iter_counter += 1
			if added_edges == number:
				break
			if iter_counter == 1000:
				break

	def get_adjacency_list(self):
		vertices = [[] for i in range(self.sink_id + 1)]
		for edge in self.edges:
			vertices[edge[0]].append(edge[1])
		return vertices

	def print_adjacency_list(self):
		vertices = self.get_adjacency_list()
		for vertex in range(len(vertices)):
			print(str(vertex) + "->" + str(vertices[vertex]))
		return vertices


	def zero_flow(self):
		for edge in self.edges:
			edge[2] = 0

	def get_residual(self):
		residual = deepcopy(self)
		residual.edges = []
		for edge in self.edges:
			norm_edge = [edge[0], edge[1], edge[2], edge[3]]
			rev_edge = [edge[1], edge[0], edge[2], edge[3]]
			if edge[3] - edge[2] > 0:
				norm_edge[3] = edge[3] - edge[2]
				residual.edges.append(norm_edge)
			if edge[2] > 0:
				rev_edge[3] = edge[2]
				residual.edges.append(rev_edge)
		residual.zero_flow()
		return residual

	def get_edges_from_path(self, path):
		edges_in_path = []
		for vertex in range(0, len(path) - 1):
				new_edge = [path[vertex], path[vertex + 1], 0, 0]
				for edge in self.edges:
					if edge[0] == new_edge[0] and edge[1] == new_edge[1]:
						new_edge = deepcopy(edge)
						edges_in_path.append(new_edge)
						break
		return edges_in_path

	def BFS(self, s):
		self.d_s = []
		self.p_s = []
		for vertex in range(self.sink_id + 1):
			self.d_s.append(99999) # inf
			self.p_s.append(-1) # NIL
		self.d_s[s] = 0
		Q= Queue()
		Q.put(s)
		while not Q.empty():
			v = Q.get()
			adjacency_list = self.get_adjacency_list()
			for neighbour in adjacency_list[v]:
				if self.d_s[neighbour] == 99999:
					self.d_s[neighbour] = self.d_s[v] + 1
					self.p_s[neighbour] = v
					Q.put(neighbour)
		path = []
		if self.p_s[self.sink_id] != -1:
			current = self.sink_id
			while current != -1:
				path.append(current)
				current = self.p_s[current]
		path = list(reversed(path))
		return path




	def ford_fulkerson(self):
		self.zero_flow()
		max_flow = 0
		while True:
			print(self.edges)
			residual = self.get_residual()
			path = deepcopy(residual.BFS(0))
			print("Found path: {}".format(path))
			edges_in_path = residual.get_edges_from_path(path)
			if not edges_in_path:
				break
			c_f_p = min(edges_in_path, key = lambda x : x[3])
			max_flow += c_f_p[3]
			print("Cf(p) =  {}". format(c_f_p[3]))
			print("Current flow = {}".format(max_flow))
			for edge in edges_in_path:
				if self.find_edge(edge[0], edge[1]):
					index = self.find_edge(edge[0], edge[1])
					index[2] += c_f_p[3]
				else:
					index = self.find_edge(edge[1], edge[0])
					index[2] -= c_f_p[3]
		self.save_to_file_flow("result.dot")
		print("Max flow {}".format(max_flow))
