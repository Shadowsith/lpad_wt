build:
	g++ -std=c++14 -o pad lpad.cpp -lwthttp -lwt

exec:
	./pad --docroot . --http-address 0.0.0.0 --http-port 9090

clean:
	rm ./pad

all:
	make clean
	make build
	make exec
