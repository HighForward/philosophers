
NAME		=	philo_three
CC			= 	gcc
RM			=	rm -f
OBJS_DIR	=	./objects/
HEADERS		=	./includes/

CFLAGS		=   -I${HEADERS}

SRCSC		=	srcs/philo_three.c		\
				srcs/utils.c			\
				srcs/utils_two.c		\
				srcs/exec_processes.c	\
				srcs/init.c         	\
				srcs/message.c      	\

OBJS		= ${SRCSC:%.c=${OBJS_DIR}/%.o}

${OBJS_DIR}/%.o: %.c
			@mkdir -p ${@D}
			@printf "\033[2K\033[0;35mPHILO_ONE\033[0;0m:        \033[0;33mCompilation...    \033[0;31m%-15.15s\033[0;0m\r"
			@${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
			@${CC} ${CFLAGS} ${OBJS} -pthread -o ${NAME}
			@printf "\033[2K\033[0;35mPROJECT\033[0;0m:      \033[0;32mSuccess\033[0;0m\n"

all:		${NAME}

clean:
			@${RM} ${OBJS}
			@rm -rf objects
			@printf "\033[0;35mPROJECT\033[0;0m:      \033[0;32mCleaned\033[0;0m\n"

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

bonus:		${NAME}

.PHONY:		all clean fclean re bonus rc
