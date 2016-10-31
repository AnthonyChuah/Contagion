OBJ=main.o city.o world.o icard.o pcard.o hero.o contPlanner.o Dispatcher.o Medic.o OpExpert.o QSpecialist.o Researcher.o Scientist.o
EXE=contagion
CXX=g++
CPPFLAGS=-std=c++11 -Wall -g -MMD

$(EXE): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<

-include $(OBJ:.o=.d)

.PHONY: clean

clean:
	rm -f $(EXE) $(OBJ) $(OBJ:.o=.d)
