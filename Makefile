# make simple         # Builds simple_test_generator.exe
# make fancy          # Builds fancy_test_generator.exe
# make answerkey      # Builds answer_key_generator.exe (HW3B, Task 1)
# make math           # Builds math_test_generator.exe (HW3B, Task 2)
# make all            # Builds all four executables
# make clean          # Removes all generated files

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
RM = rm -f

TARGETS = simple_test_generator fancy_test_generator answer_key_generator math_test_generator

COMMON_OBJS = problem.o \
              tex_problem_bank_parser.o \
              ShuffleSelector.o 

SIMPLE_OBJS = simple_test_generator.o SimpleTestWriter.o
FANCY_OBJS = fancy_test_generator.o FancyTestWriter.o

ANSWER_OBJS = anOswer_key_generator.o AnswerKeyWriter.o 
MATH_OBJS = math_test_generator.o MathTestWriter.o FastSelector.o \
          MathProblem.o MathProblemBankParser.o AuthorConstraint.o \
          LengthConstraint.o


all: $(TARGETS)


simple_test_generator: $(COMMON_OBJS) $(A_SIMPLE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

fancy_test_generator: $(COMMON_OBJS) $(A_FANCY_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

answer_key_generator: $(COMMON_OBJS) $(B1_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

math_test_generator: $(COMMON_OBJS) $(B2_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGETS) *.o *.tex *.pdf *.log *.aux
	
.PHONY: all clean simple fancy answerkey math