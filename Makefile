#NAMES
NAME		= philo
MAKE		= make

#COMP USE CC INSTEAD?!?!??!
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

#SRC
SRC_DIR		= src
SRC			= $(SRC_DIR)/philosophers_main.c \
				$(SRC_DIR)/philosophers_error_free.c \
				$(SRC_DIR)/philosophers_utils.c \


#INC
INC_DIR		= inc
INC			= $(INC_DIR) philosophers.h

#OBJ
OBJ_DIR		= obj
OBJ			= $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRC:.c=.o))

#OBJ_INC
OBJ_INC		= -I $(INC_DIR)

#RMS
RM_DIR		= rm -rf
RM_FILE		= rm -f

#DEPS
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

#OBJ DEPS
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(OBJ_INC) -c $< -o $@

$(OBJ)		:	| $(OBJ_DIR)
$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

#RULES
all:	$(NAME)

clean:
		${RM_DIR} ${OBJ_DIR}

fclean:	clean
		${RM_FILE} $(NAME)

re:		fclean all

#OTHER
.PHONY: all clean fclean re