NAME = minishell
CC = cc
CFLAGS = -g
RM = rm -rf

SRC = builts_in.c checks.c list.c spliting.c checking.c ft_memmove.c ft_strchr.c get_next_line.c \
 libft.c minishell.c moreUtils.c utits.c ft_strjoin.c ft_split.c ft_strlen.c get_next_line_utils.c \

OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -lreadline -o ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re