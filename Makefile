motor: maq.o pilha.o motor.o

# Add
test: maq.o pilha.o test.o # Remova-me
# Add

clean:
	rm -f motor test *.o
