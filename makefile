all_sources = Main.cpp adder.cpp approximator.cpp baseConverter.cpp divider.cpp multiplier.cpp squareRoot.cpp subtractor.cpp
DEPS = adder.hpp approximator.hpp baseConverter.hpp divider.hpp multiplier.hpp squareRoot.hpp subtractor.hpp structs.hpp
all_objs = $(all_sources:.cpp=.o)
calculator : $(all_objs)
	g++ -o calculator $(all_objs)
%.o : %.cpp $(DEPS)
	g++ -c $<
source_file.o : $(all_sources)
	g++ -c $^
clean:
	rm calculator *.o
