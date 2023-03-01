RM = rm -f
CFLAGS = -Wall -Werror -Wextra
NAME = cub3D
INCLUDES = ./include/cub3d.h
SRCS_DIR = srcs/
SRCS = control.c\
       get_next_line.c\
	   main.c\
	   parsing.c\
	   check_file.c\
	   retrieve_textures.c\
	   retrieve_textures2.c\
	   retrieve_floor_ceiling.c\
	   retrieve_floor_ceiling2.c\
	   retrieve_floor_ceiling3.c\
	   retrieve_map.c\
	   retrieve_map2.c\
	   retrieve_map3.c\
	   retrieve_map4.c\
	   retrieve_map5.c\
	   frees.c\
	   frees2.c\
	   pixel_calcul.c\
	   raycasting.c\
	   utils.c\
	   utils2.c\
	   utils3.c\
	   buffer_manipulation.c\
	   initialise_main_fonctions.c\
	   loop_fonctions.c\
	   retrieve_position.c\
	   orientation_player.c\
	   minimap.c\
	   control2.c

SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))
OBJS = $(SRCS:.c=.o)

%.o: %.c
	${CC} -c ${CFLAGS} ${INCLUDES} $< -o $@ 

all: $(NAME)

$(NAME) : $(OBJS)
		$(MAKE) -C mlx_linux
		gcc -g -o $(NAME) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

$(OBJS): $(SRCS_PATH)
	gcc -c -g ${CFLAGS} ${CFLAGS} ${INCLUDES} ${SRCS_PATH}

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: fclean re all clean
