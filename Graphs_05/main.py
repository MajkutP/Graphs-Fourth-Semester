from Network import Network


if __name__ == '__main__':

	while True:
		try:
			N = int(input("Please enter number of layers:"))
			if N < 2 or N > 4:
				raise ValueError("Wrong N")
			break
		except:
			print("Try again")


	a = Network(N)

	a.print_layers()

	print('\n')
	a.init_edges()
	a.generate_capacity(1, 10)
	a.dump_to_dot()
	a.save_to_file("out1.dot")
	a.print_adjacency_list()
	a.ford_fulkerson()