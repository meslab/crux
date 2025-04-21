CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -fPIC
CFLAGS_RELEASE = -O2 -ffunction-sections -fdata-sections -flto -DNDEBUG
CFLAGS_DEBUG = -g -O0 -DDEBUG -Werror -fsanitize=address,undefined -fno-omit-frame-pointer
LDFLAGS_RELEASE = -Wl,--gc-sections -flto -s
LDFLAGS_DEBUG = -fsanitize=address,undefined

LIB_DIR = lib
INCLUDE_DIR = include
LIB_NAME = crux
STATIC_LIB_RELEASE = $(LIB_DIR)/release/lib$(LIB_NAME).a
STATIC_LIB_DEBUG = $(LIB_DIR)/debug/lib$(LIB_NAME).a
SHARED_LIB_RELEASE = $(LIB_DIR)/release/lib$(LIB_NAME).so
SHARED_LIB_DEBUG = $(LIB_DIR)/debug/lib$(LIB_NAME).so

TEST_DIR = test
TEST_SRC = $(wildcard test/src/*.c)
TEST_MAIN = $(wildcard test/*.c)
TEST_INCLUDE_DIR = test/include 
TEST_BIN_DIR = $(TEST_DIR)/bin
TEST_OBJ_DIR = $(TEST_DIR)/obj
TEST_STATIC_BIN_RELEASE = $(TEST_BIN_DIR)/release/test_crux
TEST_STATIC_BIN_DEBUG = $(TEST_BIN_DIR)/debug/test_crux
TEST_SHARED_BIN_DEBUG = $(TEST_BIN_DIR)/debug/test_crux_shared

# Gather all source files automatically
SRC_FILES := $(wildcard src/*.c)
OBJ_FILES_RELEASE := $(patsubst src/%.c, $(LIB_DIR)/release/%.o, $(SRC_FILES))
OBJ_FILES_DEBUG := $(patsubst src/%.c, $(LIB_DIR)/debug/%.o, $(SRC_FILES))
TEST_OBJ_FILES_DEBUG := $(patsubst test/src/%.c, $(TEST_OBJ_DIR)/debug/%.o, $(TEST_SRC))
TEST_OBJ_FILES_RELEASE := $(patsubst test/src/%.c, $(TEST_OBJ_DIR)/release/%.o, $(TEST_SRC))

# Create necessary directories at the start
$(shell mkdir -p $(LIB_DIR)/release $(LIB_DIR)/debug $(TEST_BIN_DIR)/release $(TEST_BIN_DIR)/debug $(TEST_OBJ_DIR)/debug $(TEST_OBJ_DIR)/release)

# Targets
all: debug release run_test_release run_test_debug run_test_shared_debug

release: CFLAGS += $(CFLAGS_RELEASE)
release: LDFLAGS += $(LDFLAGS_RELEASE)
release: $(STATIC_LIB_RELEASE) $(SHARED_LIB_RELEASE) $(TEST_STATIC_BIN_RELEASE)

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: LDFLAGS += $(LDFLAGS_DEBUG)
debug: $(STATIC_LIB_DEBUG) $(SHARED_LIB_DEBUG) $(TEST_STATIC_BIN_DEBUG) $(TEST_SHARED_BIN_DEBUG)

# Build static libraries
$(STATIC_LIB_RELEASE): $(OBJ_FILES_RELEASE)
	ar rcs $@ $^

$(STATIC_LIB_DEBUG): $(OBJ_FILES_DEBUG)
	ar rcs $@ $^

# Compile object files
$(LIB_DIR)/release/%.o: src/%.c
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) -I$(INCLUDE_DIR) -c $< -o $@

$(LIB_DIR)/debug/%.o: src/%.c
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -I$(INCLUDE_DIR) -c $< -o $@

# Build shared libraries
$(SHARED_LIB_RELEASE): $(OBJ_FILES_RELEASE)
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) -shared $(LDFLAGS_RELEASE) -o $@ $^

$(SHARED_LIB_DEBUG): $(OBJ_FILES_DEBUG)
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -shared $(LDFLAGS_DEBUG) -o $@ $^

$(TEST_OBJ_DIR)/debug/%.o: test/src/%.c
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -I$(INCLUDE_DIR) -I$(TEST_INCLUDE_DIR) -c $< -o $@

$(TEST_OBJ_DIR)/release/%.o: test/src/%.c
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) -I$(INCLUDE_DIR) -I$(TEST_INCLUDE_DIR) -c $< -o $@

# Test binaries
$(TEST_STATIC_BIN_RELEASE): $(STATIC_LIB_RELEASE) $(TEST_SRC) $(TEST_OBJ_FILES_RELEASE)
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) -I$(INCLUDE_DIR) -I$(TEST_INCLUDE_DIR) $(TEST_SRC) $(TEST_MAIN) $(STATIC_LIB_RELEASE) $(LDFLAGS_RELEASE) -o $(TEST_STATIC_BIN_RELEASE)

$(TEST_STATIC_BIN_DEBUG): $(STATIC_LIB_DEBUG) $(TEST_SRC) $(TEST_OBJ_FILES_DEBUG)
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -I$(INCLUDE_DIR) -I$(TEST_INCLUDE_DIR) $(TEST_SRC) $(TEST_MAIN) $(STATIC_LIB_DEBUG) $(LDFLAGS_DEBUG) -o $(TEST_STATIC_BIN_DEBUG)

$(TEST_SHARED_BIN_RELEASE): $(SHARED_LIB_RELEASE) $(TEST_SRC)
	$(CC) $(CFLAGS) $(CFLAGS_RELEASE) -I$(INCLUDE_DIR) -I$(TEST_INCLUDE_DIR) $(TEST_SRC) $(TEST_MAIN) -L$(LIB_DIR)/release -l$(LIB_NAME) $(LDFLAGS_RELEASE) -o $(TEST_SHARED_BIN_RELEASE)

$(TEST_SHARED_BIN_DEBUG): $(SHARED_LIB_DEBUG) $(TEST_SRC)
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -I$(INCLUDE_DIR) -I$(TEST_INCLUDE_DIR) $(TEST_SRC) $(TEST_MAIN) -L$(LIB_DIR)/debug -l$(LIB_NAME) $(LDFLAGS_DEBUG) -o $(TEST_SHARED_BIN_DEBUG)

# Run tests
run_test_release: 
	$(TEST_STATIC_BIN_RELEASE)

run_test_debug: 
	$(TEST_STATIC_BIN_DEBUG)

run_test_shared_debug: 
	LD_LIBRARY_PATH=$(LIB_DIR)/debug $(TEST_SHARED_BIN_DEBUG)

format:
	@find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} +
# Clean build artifacts
clean:
	rm -rf $(LIB_DIR) $(TEST_BIN_DIR) $(TEST_OBJ_DIR)

.PHONY: all debug release \
        run_test_release run_test_debug run_test_shared_debug \
        clean format

