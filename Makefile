build: main.cpp
	g++ main.cpp -o RayTracing

run: RayTracing
	./RayTracing > image.ppm

show: image.ppm
	imv -u nearest_neighbour image.ppm
