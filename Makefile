NAME = ft_nmap

CC = clang
RM = rm -f

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iinclude

LDFLAGS =

SRC_DIR = src
OBJ_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INCLUDE = $(wildcard include/*.h)

vpath %.c $(SRC_DIR) $(SRC_DIR)/parse
vpath %.h $(INCLUDE)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

##############
# Unit Tests #
##############

TEST_DIR = test
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_INCLUDE = $(wildcard $(TEST_DIR)/*.h)
TEST_INCLUDE += $(INCLUDE)

TEST_NAME = unit_tests

.PHONY: test
test: $(TEST_NAME)
	./$(TEST_NAME)

$(TEST_NAME): $(OBJ) $(TEST_OBJ)
	# Remove main.o from object files
	$(eval OBJ := $(filter-out $(OBJ_DIR)/main.o, $(OBJ)))
	$(CC) $(LDFLAGS) $(OBJ) $(TEST_OBJ) -o $(TEST_NAME)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: all clean fclean re test
