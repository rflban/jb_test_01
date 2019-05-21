CC := g++
CFLAGS := -Wall

LFLAGS := 

PNAME := converter
$(PNAME).OBJS := main.o my_str.o exit.o

INPUT := ping.js


build: $(PNAME)

$(PNAME): $($(PNAME).OBJS)
	$(CC) $^ -o $@

main.o: main.cpp *.h
	$(CC) $< -c $(CFLAGS)

exit.o: exit.c *.h
	$(CC) $< -c $(CFLAGS)

my_str.o: my_str.c *.h
	$(CC) $< -c $(CFLAGS)

clean:
	rm $(PNAME) -f
	rm $($(PNAME).OBJS) -f

run:
	@echo 'input file:' $(INPUT)
	@cat $(INPUT)
	@echo
	./$(PNAME) $(INPUT)

