OBJ= main.o board.o
CXXFLAGS= -std=c++17 -Wall -O2
CXX= g++

connect6: $(OBJ)
	$(CXX) $(CXXFLAGS) -o connect6 $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o connect6