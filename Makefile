
LIBS = -lGL -lglut

all: raketka

raketka: *.c *.h 
	gcc *.c ${LIBS} -o raketka

clean: 
	rm raketka

