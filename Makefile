CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lboost_date_time -lboost_regex
DEPS =
OBJECTS = main.o
PROGRAM = ps7
# TEST = test

.PHONY: all clean lint

all: $(PROGRAM) # $(TEST)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

# $(TEST): $(OBJECTS) test.o
# 	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm -f *.o $(PROGRAM) $(TEST)

lint:
	cpplint *.cpp *.hpp
