CC=g++
all:arquivos

arquivos: main.o output.o raytracer.o scene.o vector.o vectorTest.o
	$(CC) main.o output.o raytracer.o scene.o vector.o vectorTest.o -o executavel -lSOIL -lGL -lglut -lGLEW -lsfml-audio -lm
	@echo "\nCRIADO COM SUCESSO UTILIZE MAKE RUN PARA RODAR\n"

main.o: main.cpp
	$(CC) -o main.o -c main.cpp -lSOIL -lGL -lglut -lGLEW -lsfml-audio -lm

main.o: output.cpp
	$(CC) -o output.o -c output.cpp -lSOIL -lGL -lglut -lGLEW -lsfml-audio -lm
	
run:
	./executavel

clean:
	rm -rf *o arquivos
	@echo "Arquivos .o deletados com suecesso\n"

install:
	sudo apt-get install build-essential
	sudo apt-get install freeglut3-dev
	sudo apt-get install libglew1.6-dev
	sudo apt-get install libsfml-dev
	sudo apt-get install libsoil-dev
