# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jweber <jweber@student.42Lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/20 13:51:19 by jweber            #+#    #+#              #
#    Updated: 2025/09/01 13:03:43 by jweber           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := cc
CFLAGS := -Wall -Wextra -Werror

INCLUDES := -I includes/

UTILS_DIR := src/utils/
UTILS_FILES := ft_atoi_safe.c \
			   ft_isspace.c \
			   ft_strchr.c \
			   ft_get_time.c \
			   print_error_atoi_safe.c \
			   ft_putstr_fd.c \
			   ft_strlen.c \

EXECUTION_DIR := src/execution/
EXECUTION_FILES := start_philo.c \
				   launch_philo.c \

ROUTINE_DIR := src/routine/
ROUTINE_FILES := routine.c \
				 try_eat.c \
				 try_take_forks.c \
				 eat.c \
				 try_sleep.c \
				 try_think.c \
				 print_message_philo.c \
				 kill_philo.c \
				 check_death.c \

CLEAR_DIR := src/clear/
CLEAR_FILES := clear_mutex.c \
			   clear_all.c \

INIT_DIR := src/init/
INIT_FILES := init_values.c \
			  init_philos.c \
			  init_mutexes.c \
			  init_arr_philo.c \

C_FILES := philo.c \
		   $(addprefix $(UTILS_DIR), $(UTILS_FILES)) \
		   $(addprefix $(INIT_DIR), $(INIT_FILES)) \
		   $(addprefix $(CLEAR_DIR), $(CLEAR_FILES)) \
		   $(addprefix $(EXECUTION_DIR), $(EXECUTION_FILES)) \
		   $(addprefix $(ROUTINE_DIR), $(ROUTINE_FILES)) \

OBJECTS_DIR := .obj/
OBJECTS_FILES := $(addprefix $(OBJECTS_DIR), $(C_FILES:.c=.o))
D_FILES := $(OBJECTS_FILES:.o=.d)

.PHONY: all clean fclean re git git_update debug debug_clean debug_fclean debug_re

all: $(NAME)

-include $(D_FILES)

$(NAME): $(OBJECTS_FILES)
	$(CC) $(INCLUDE) $(CFLAGS) $^ -o $@ 

$(OBJECTS_DIR)%.o:%.c | $(OBJECTS_DIR)$(INIT_DIR) $(OBJECTS_DIR)$(UTILS_DIR) $(OBJECTS_DIR)$(CLEAR_DIR) $(OBJECTS_DIR)$(EXECUTION_DIR) $(OBJECTS_DIR)$(ROUTINE_DIR)
	$(CC) -c -MMD -MP $(CFLAGS) $(INCLUDES) $< -o $@

$(OBJECTS_DIR)$(ROUTINE_DIR):
	mkdir -p $@

$(OBJECTS_DIR)$(EXECUTION_DIR):
	mkdir -p $@

$(OBJECTS_DIR)$(CLEAR_DIR):
	mkdir -p $@

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
