all: build

build: cpu_usage.cc
	g++ -o cpu_usage cpu_usage.cc
clean:
	rm cpu_usage
