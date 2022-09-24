setup:
	rm -rf build
	mkdir build

dependency:
	cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graph.png
