NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -rf

BOLD      = \033[1m
CGREEN    = \033[32m
CCYAN     = \033[36m

SRC =	list.c lexer.c expand.c builts_in_tools_0.c  set_status.c\
		built_in_main_functions_2.c get_next_line.c free.c libftPlus.c \
		libft.c minishell.c quotes.c utils.c ft_split.c signals.c \
		get_next_line_utils.c joining.c parsing.c garbage_collector.c\
		excutiion.c built_in_main_functions.c built_in_main_functions_1.c \
		builts_in_tools_1.c builts_in_tools_2.c builts_in_tools_3.c \
		execution_tools_5.c execution_tools_4.c execution_tools_3.c \
		execution_tools_2.c execution_tools_1.c execution_tools_0.c  \

OBJ = ${SRC:.c=.o}

all: print ${NAME}

print:
	@echo "$(BOLD )\033[35m __  __ _       _ ____  _          _ _ \033[0m"
	@echo "$(BOLD )\033[35m|  \/  (_)_ __ (_) ___|| |__   ___| | |\033[0m"
	@echo "$(BOLD )\033[35m| |\/| | | '_ \| \___ \| '_ \ / _ \ | |\033[0m"
	@echo "$(BOLD )\033[35m| |  | | | | | | |___) | | | |  __/ | |\033[0m"
	@echo "$(BOLD )\033[35m|_|  |_|_|_| |_|_|____/|_| |_|\___|_|_|\033[0m"
	@echo "$(BOLD )\033[35m                                       \033[0m"

${NAME}: ${OBJ}
	@echo "$(BOLD)$(CGREEN)building the project...\033[0m"
	${CC} ${CFLAGS} ${OBJ} -lreadline -o ${NAME}

clean:
	@echo "$(BOLD)$(CGREEN)cleaning ...\033[0m"
	${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re