TARGET = main
WARNINGS = -Wall -Wextra

all: $(TARGET)

main: $(TARGET).o smartstack.o
	gcc $(WARNINGS) -o $(TARGET) $(TARGET).o smartstack.o

smartstack.o: smartstack.c smartstack.h
	gcc -c $(WARNINGS) smartstack.c

main.o: main.c
	gcc -c $(WARNINGS) $(TARGET).c