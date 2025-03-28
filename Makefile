OBJ= main.o board.o agent.o
CXXFLAGS= -std=c++17 -Wall -O2 -g
CXX= g++

connect6: $(OBJ)
	$(CXX) $(CXXFLAGS) -o connect6 $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o connect6