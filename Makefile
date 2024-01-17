link:compile
	gcc build/dictionary.o build/main.o -o app
compile:objectdir
	gcc -c src/main.c -o build/main.o
	gcc -c src/dictionary/dictionary.c -o build/dictionary.o
objectdir:
	mkdir build
