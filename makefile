graph:
	@g++ -o graph src/*.cpp -Isrc/headers -Wall

clean:
	@rm graph
	@rm src/headers/*.o
