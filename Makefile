NAME = minishell
CC = cc
CFLAGS = -g
RM = rm -rf

BOLD      = \033[1m
CGREEN    = \033[32m
CCYAN     = \033[36m


SRC =  checks.c list.c spliting.c checking.c expand.c \
	ft_memmove.c ft_strchr.c get_next_line.c free.c libftPlus.c \
	libft.c minishell.c moreUtils.c utils.c ft_split.c signals.c \
	builts_in.c get_next_line_utils.c joining.c parsing.c \

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