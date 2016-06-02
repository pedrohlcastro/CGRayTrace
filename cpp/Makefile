CC = g++
OPCOES_COMPILADOR= -Iinclude -lSOIL -lm
TODOS_ARQUIVOS_PONTOH = output.h ray.h raytracer.h scene.h vector.h
TODOS_ARQUIVOS_OBJ = main.o output.cpp raytracer.cpp scene.cpp vector.cpp vectorTest.cpp

%.o: ../%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	$(CC) -o main $^ $(OPCOES_COMPILADOR)

run:  all
	./main cena-simples.txt

clean:
	rm *.o main
