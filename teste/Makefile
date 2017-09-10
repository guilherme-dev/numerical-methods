#lib math.h
lib = -lm

all: main.c functions.c functions.h
	gcc main.c functions.c -o main -Wall $(lib)

# remove arquivos temporarios
clean:
	-rm $(objs) *~

# remove tudo que nao for codigo fonte
purge: clean
	-rm main