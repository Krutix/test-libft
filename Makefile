.DEFAULT_GOAL := all
NAME = test

# libft path
LIB_PATH = ./eval-libft/


LIB = $(LIB_PATH)/libft.a

LIST = main.c

OBJ = $(patsubst %.c,%.o,$(LIST))

Libftest = ./Libftest/grademe.sh

unit = ./libft-unit-test

cfg = ./cfg/.vimrc

# ftst #
include ftst-unit-test-framework/ftst.mk
FTST_DIR = ftst-unit-test-framework/

########

INC = $(addprefix -I, $(LIB_PATH) ${FTST_INC})

all : run-my-test

$(NAME) : $(LIB) $(OBJ)
	gcc $(OBJ) -L$(LIB_PATH) -lft -o $(NAME) $(INC)

%.o : %.c
	gcc -c $< -o $@ $(INC)

$(LIB) : NONE
	@$(MAKE) -C $(LIB_PATH) -s

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

norm :
	cd $(LIB_PATH) && make clean && norminette .

run-my-test : $(NAME)
	@./$(NAME)

$(Libftest) :
	git clone https://github.com/jtoty/Libftest.git
	cp ./test-configs/my_config.sh ./Libftest

$(unit) :
	git clone https://github.com/alelievr/libft-unit-test.git
	cp ./test-configs/Makefile $(unit)

run-libftest : $(Libftest)
	$(Libftest) -n

run-unit : $(unit)
	cd $(unit) && make f

$(cfg) :
	git clone https://github.com/alexoleshk/cfg.git

grep-printf :
	cd $(LIB_PATH) && make clean && grep -RIn printf .

grep-malloc :
	cd $(LIB_PATH) && make clean && grep -RIn malloc .

myvim : $(cfg)
	vim -u $(cfg)

.PHONY : NONE norm run-my-test run-libftest run-unit grep-printf grep-malloc myvim
