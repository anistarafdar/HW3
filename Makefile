CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -g

TARGETS = simple_test_generator fancy_test_generator

COMMON_OBJS = problem.o tex_problem_bank_parser.o ShuffleSelector.o

SIMPLE_OBJS = simple_test_generator.o SimpleTestWriter.o
FANCY_OBJS = fancy_test_generator.o FancyTestWriter.o

all: $(TARGETS)
pdf: $(PDFS)

simple_test_generator: $(COMMON_OBJS) $(SIMPLE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

fancy_test_generator: $(COMMON_OBJS) $(FANCY_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.pdf: %.tex
	pdflatex $<
	pdflatex $<

simple_test.tex: simple_test_generator
	./simple_test_generator.exe

fancy_test.tex: fancy_test_generator
	./fancy_test_generator.exe

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) *.o

.PHONY:	all clean