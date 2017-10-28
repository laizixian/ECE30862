SOURCE = Container.cpp Creature.cpp Item.cpp Room.cpp Zork_final_with_fun.cpp Triggers.cpp
MYPROGRAM = Zork
CC = g++
FLAGS = -Wall -std=c++0x

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)

	$(CC) $(FLAGS) $(SOURCE) -o$(MYPROGRAM)

clean:

	rm -f $(MYPROGRAM)
