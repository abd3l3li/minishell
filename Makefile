NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

BOLD      = \033[1m
CGREEN    = \033[32m
CCYAN     = \033[36m

SRC =	PART_1/list.c PART_1/lexer.c PART_1/expand.c PART_2/builts_in_tools_0.c  PART_2/set_status.c\
		PART_2/built_in_main_functions_2.c PART_1/get_next_line.c PART_1/free.c PART_1/libftPlus.c \
		PART_1/libft.c minishell.c PART_1/quotes.c PART_1/utils.c PART_1/ft_split.c PART_1/signals.c \
		PART_1/get_next_line_utils.c PART_1/joining.c PART_1/parsing.c PART_1/garbage_collector.c\
		PART_2/excutiion.c PART_2/built_in_main_functions.c PART_2/built_in_main_functions_1.c \
		PART_2/builts_in_tools_1.c PART_2/builts_in_tools_2.c PART_2/builts_in_tools_3.c \
		PART_2/execution_tools_5.c PART_2/execution_tools_4.c PART_2/execution_tools_3.c \
		PART_2/execution_tools_2.c PART_2/execution_tools_1.c PART_2/execution_tools_0.c PART_2/execution_tools_6.c \

OBJ = ${SRC:.c=.o}

all: print ${NAME}

print:
	@echo "$(BOLD )\033[35m                                                   \033[0m"
	@echo "$(BOLD )\033[35m         __  __ _       _ ____  _          _ _      \033[0m"
	@echo "$(BOLD )\033[35m        |  \/  (_)_ __ (_) ___|| |__   ___| | |    \033[0m"
	@echo "$(BOLD )\033[35m        | |\/| | | '_ \| \___ \| '_ \ / _ \ | |    \033[0m"
	@echo "$(BOLD )\033[35m        | |  | | | | | | |___) | | | |  __/ | |    \033[0m"
	@echo "$(BOLD )\033[35m        |_|  |_|_|_| |_|_|____/|_| |_|\___|_|_|    \033[0m"
	@echo "$(BOLD )\033[35m                                                   \033[0m"
	@echo "$(BOLD )\033[35m                                                   \033[0m"

${NAME}: ${OBJ}
	@echo "$(BOLD)$(CGREEN)building the project...\033[0m"
	@${CC} ${CFLAGS} ${OBJ} -lreadline -o ${NAME}

clean:
	@echo "$(BOLD)$(CGREEN)cleaning ...\033[0m"
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
.SECONDARY:
