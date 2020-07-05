##
## EPITECH PROJECT, 2020
## OOP_nanotekspice_2019
## File description:
## Makefile
##

NAME		=	nanotekspice

UTNAME		=	unit_tests

MAIN		=	main.cpp

SRC			=	src/UserInput.cpp			\
				src/Parser.cpp				\
				src/Errors.cpp				\
				src/logic_gate/G_NOR.cpp	\
				src/logic_gate/G_NAND.cpp	\
				src/logic_gate/G_XOR.cpp	\
				src/logic_gate/G_NOT.cpp	\
				src/logic_gate/G_OR.cpp		\
				src/logic_gate/G_AND.cpp	\
				src/components/Input.cpp	\
				src/components/True.cpp		\
				src/components/False.cpp	\
				src/components/Clock.cpp	\
				src/components/Output.cpp	\
				src/components/FlipFlop.cpp	\
				src/components/C_4001.cpp	\
				src/components/C_4008.cpp	\
				src/components/C_4011.cpp	\
				src/components/C_4013.cpp	\
				src/components/C_4017.cpp	\
				src/components/C_4030.cpp	\
				src/components/C_4040.cpp	\
				src/components/C_4069.cpp	\
				src/components/C_4071.cpp	\
				src/components/C_4081.cpp	\
				src/components/C_4514.cpp

OBJ			=	$(SRC:.cpp=.o)

SRC_TESTS	=	tests/test.cpp

INC			+=	-I./include					\
				-I./include/components		\
				-I./include/logic_gate		\

CXXFLAGS	+=	-Wall -W -Werror -Wextra

LIB			=	-lcriterion --coverage


all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) $(INC) -o $(NAME) $(OBJ) $(MAIN)

tests_run:	re
			@$(CXX) $(CXXFLAGS) $(INC) -o $(UTNAME) $(SRC) $(SRC_TESTS) $(LIB)
			./$(UTNAME)
			@gcovr --exclude tests/
			@gcovr -b --exclude tests/

%.o:		%.cpp
			$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $^

clean:
			@$(RM) $(OBJ)
			@$(RM) *~
			@$(RM) *.gc*

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) $(UTNAME)

re:			fclean all

.PHONY:		clean fclean re