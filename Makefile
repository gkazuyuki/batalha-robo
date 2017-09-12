motor: maq.o pilha.o motor.o

test: maq.o pilha.o test.o # Remova-me

clean:
	rm -f motor test *.o
