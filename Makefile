link:compile
	gcc build/io.o build/dictionary.o build/main.o -o app
compile:objectdir
	gcc -c -g src/main.c -o build/main.o
	gcc -c -g src/dictionary/dictionary.c -o build/dictionary.o
	gcc -c -g src/io/io.c -o build/io.o
objectdir:clean
	mkdir build
clean:
	rm -rf build
	rm -rf app
