# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/20 13:51:19 by jweber            #+#    #+#              #
#    Updated: 2025/08/20 17:34:55 by jweber           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := cc
CFLAGS := -Wall -Wextra -Werror

INCLUDES := -I includes/

UTILS_DIR := src/utils/
UTILS_FILES := ft_atoi.c \

INIT_DIR := src/init/
INIT_FILES := init_values.c \

C_FILES := philo.c \
		   $(addprefix $(UTILS_DIR), $(UTILS_FILES)) \
		   $(addprefix $(INIT_DIR), $(INIT_FILES))

OBJECTS_DIR := .obj/
OBJECTS_FILES := $(addprefix $(OBJECTS_DIR), $(C_FILES:.c=.o))
DEPS := $(OBJECTS_FILES:.o=.d)

.PHONY: all clean fclean re git git_update debug debug_clean debug_fclean debug_re

all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJECTS_FILES)
	$(CC) $(INCLUDE) $(CFLAGS) $^ -o $@ 

$(OBJECTS_DIR)%.o:%.c | $(OBJECTS_DIR)$(INIT_DIR) $(OBJECTS_DIR)$(UTILS_DIR)
	$(CC) -c -MMD -MP $(CFLAGS) $(INCLUDES) $< -o $@

$(OBJECTS_DIR)$(UTILS_DIR):
	mkdir -p $@

$(OBJECTS_DIR)$(INIT_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJECTS_DIR)

fclean:
	$(MAKE) clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

debug:
	$(MAKE) OBJECTS_DIR=".obj_debug/" CFLAGS="$(CFLAGS) -g3"

debug_clean:
	$(MAKE) clean OBJECTS_DIR=".obj_debug/" CFLAGS="$(CFLAGS) -g3"

debug_fclean:
	$(MAKE) fclean OBJECTS_DIR=".obj_debug/" CFLAGS="$(CFLAGS) -g3"

debug_re:
	$(MAKE) re OBJECTS_DIR=".obj_debug/" CFLAGS="$(CFLAGS) -g3" 
