all:
	g++ -o code main.cpp

clean:
	rm -f code

.PHONY: all clean