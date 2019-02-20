all: build

build: cpu_percentage.cc
	g++ -o cpu_percentage cpu_percentage.cc
clean:
	rm cpu_percentage
