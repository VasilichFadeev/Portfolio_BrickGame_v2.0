CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11 -g
AR := ar
ARFLAGS := rcs

BUILD_DIR := build
LIB_NAME := brick_game.a
LIB_PATH := $(BUILD_DIR)/$(LIB_NAME)

SRC_TETRIS := $(wildcard brick_game/tetris/*.c)
SRC_CLI := $(wildcard gui/cli/*.c)
SRC := $(SRC_TETRIS) $(SRC_CLI)

OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))

all: $(LIB_PATH)

$(LIB_PATH): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

install:
	gcc $(filter-out brick_game/tetris/test.c, $(SRC_TETRIS)) $(SRC_CLI) -lncursesw -Wall -Wextra -Werror -std=c11 -g -o tetris
	cd brick_game/snake && make install
	cd brick_game/tetris && g++ -fPIC main.cpp tetris_game.cpp tetris_window.cpp ../../gui/desktop/tetris/userInput.cpp ../../gui/desktop/tetris/render.cpp ../../gui/desktop/tetris/placePiece.cpp ../../gui/desktop/tetris/getColorCode.cpp -o ./../../desktop_tetris `pkg-config --cflags --libs Qt5Widgets`

uninstall:
	rm -rf ./tetris ./snake ./desktop_tetris ./desktop_snake

clean:
	rm -rf $(BUILD_DIR) tetris test_app ./*.txt ./*.gcda ./*.gcno coverage_report ./*.info brick_game.tar.gz ./brick_game/tetris/*.png ./brick_game/snake/*.txt ./brick_game/tetris/*.txt ./desktop_snake ./snake ./desktop_tetris ./test_desktop_tetris ./test_terminal_snake ./test_terminal_tetris ./test_desktop_snake

start:
	gcc $(filter-out brick_game/tetris/test.c, $(SRC_TETRIS)) $(SRC_CLI) -lncursesw $(CFLAGS) -o game && ./game

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./test_app
	rm -rf ./test_app

clang-format:
	cd ../materials/linters && clang-format -i ../../src/brick_game/tetris/*.h ../../src/brick_game/tetris/*.c ../../src/brick_game/tetris/*.cpp ../../src/gui/cli/*.c ./../../src/brick_game/snake/desktop_snake/*.cpp ./../../src/brick_game/snake/desktop_snake/*.h ./../../src/brick_game/snake/snake/*.cpp ./../../src/brick_game/snake/snake/*.h ./../../src/gui/desktop/snake/*.cpp

cppcheck:
	cppcheck --enable=all --std=c11 --check-level=exhaustive --disable=information --suppress=missingIncludeSystem --suppress=missingInclude --suppress=checkersReport main.c $(SRC) brick_game.h test.c

EXCLUDE_TETRIS := brick_game/tetris/main.c brick_game/tetris/sleepWithLevel.c
EXCLUDE_CLI := gui/cli/setupTerminal.c gui/cli/setupColors.c gui/cli/renderGame.c gui/cli/handleQuit.c gui/cli/handleInput.c

TEST_SRC_TETRIS := $(filter-out $(EXCLUDE_TETRIS), $(SRC_TETRIS))
TEST_SRC_CLI := gui/cli/shapes.c

SNAKE_SRC_TERMINAL := brick_game/snake/snake/snake_terminal.cpp
SNAKE_SRC_COMMON := brick_game/snake/snake/convertFieldToInt.cpp brick_game/snake/snake/saveHighScore.cpp brick_game/snake/snake/loadHighScore.cpp
GUI_CLI_SRC := gui/cli/fillFieldWithFrame.cpp gui/cli/spawnSnake.cpp gui/cli/generateApple.cpp

test:
	$(CC) $(TEST_SRC_TETRIS) $(TEST_SRC_CLI) -lcheck -lm -lpthread -lrt -lsubunit $(CFLAGS) -o test_terminal_tetris
	g++ -fPIC brick_game/tetris/test.cpp brick_game/tetris/tetris_game.cpp gui/desktop/tetris/placePiece.cpp -o ./test_desktop_tetris `pkg-config --cflags --libs Qt5Widgets` -lgtest -lgtest_main -pthread
	g++ brick_game/snake/snake/test.cpp $(SNAKE_SRC_TERMINAL) $(GUI_CLI_SRC) $(SNAKE_SRC_COMMON) -o ./test_terminal_snake -lncursesw -lgtest -lgtest_main -pthread
	g++ -fPIC brick_game/snake/desktop_snake/test.cpp brick_game/snake/desktop_snake/generateApple.cpp brick_game/snake/desktop_snake/constructor.cpp gui/desktop/snake/*.cpp brick_game/snake/desktop_snake/loadHighScore.cpp brick_game/snake/desktop_snake/setupTimer.cpp brick_game/snake/desktop_snake/resetGame.cpp brick_game/snake/desktop_snake/updateGame.cpp brick_game/snake/desktop_snake/saveHighScore.cpp brick_game/snake/desktop_snake/updateCurrentState.cpp brick_game/snake/desktop_snake/updateSpeed.cpp brick_game/snake/desktop_snake/startGame.cpp brick_game/snake/desktop_snake/keyPressEvent.cpp brick_game/snake/desktop_snake/togglePause.cpp brick_game/snake/desktop_snake/toggleTurbo.cpp -o ./test_desktop_snake `pkg-config --cflags --libs Qt5Widgets` -lgtest -lgtest_main -pthread
	./test_terminal_tetris
	./test_desktop_tetris
	./test_terminal_snake
	LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0 ./test_desktop_snake

gcov_report:
	@echo "Compiling tetris tests with gcov flags..."
	$(CC) --coverage -fprofile-arcs -ftest-coverage $(TEST_SRC_TETRIS) $(TEST_SRC_CLI) \
		-lcheck -lm -lpthread -lrt -lsubunit $(CFLAGS) -o test_app
	
	@echo "Running tetris tests..."
	./test_app
	
	@echo "Generating tetris coverage data..."
	lcov --capture --directory . --output-file coverage_tetris.info \
		--exclude "*/brick_game/tetris/main.c" \
		--exclude "*/brick_game/tetris/sleepWithLevel.c" \
		--exclude "*/test.c" \
		--exclude "*/gui/*" \
		--ignore-errors source,unused,mismatch
	
	@echo "Compiling desktop tetris tests with gcov flags..."
	g++ --coverage -fprofile-arcs -ftest-coverage -fPIC \
		brick_game/tetris/test.cpp \
		brick_game/tetris/tetris_game.cpp \
		gui/desktop/tetris/placePiece.cpp \
		-lgtest -lgtest_main -pthread -lstdc++ \
		`pkg-config --cflags --libs Qt5Widgets` \
		-o test_desktop_tetris
	
	@echo "Running desktop tetris tests..."
	./test_desktop_tetris
	
	@echo "Generating desktop tetris coverage data..."
	lcov --capture --directory . --output-file coverage_desktop.info \
		--exclude "*/main.cpp" \
		--exclude "*/moc_*.cpp" \
		--ignore-errors source,unused,mismatch,gcov
	
	@echo "Compiling snake tests with gcov flags..."
	g++ --coverage -fprofile-arcs -ftest-coverage \
		brick_game/snake/snake/test.cpp \
		$(SNAKE_SRC_TERMINAL) \
		$(GUI_CLI_SRC) \
		$(SNAKE_SRC_COMMON) \
		-o test_terminal_snake \
		-lncursesw -lgtest -lgtest_main -pthread -lstdc++
	
	@echo "Running snake tests..."
	./test_terminal_snake
	
	@echo "Generating snake coverage data..."
	lcov --capture --directory . --output-file coverage_snake.info \
		--exclude "*/main.cpp" \
		--exclude "*/gui/*" \
		--ignore-errors source,unused,mismatch,gcov
	
	@echo "Combining coverage reports..."
	lcov --add-tracefile coverage_tetris.info --add-tracefile coverage_desktop.info --add-tracefile coverage_snake.info --output-file coverage.info
	
	@echo "Filtering system files..."
	lcov --remove coverage.info '/usr/include/*' '*/gtest/*' '*/gmock/*' '*/gui/*' --ignore-errors unused --output-file coverage.filtered.info
	
	@echo "Generating HTML report..."
	genhtml coverage.filtered.info --output-directory coverage_report \
		--title "Brick Game Test Coverage" \
		--prefix $(PWD) \
		--demangle-cpp \
		--legend
	
	@echo "Opening report in browser..."
	xdg-open coverage_report/index.html >/dev/null 2>&1 || open coverage_report/index.html >/dev/null 2>&1
	
	@echo "Cleaning up..."
	rm -f *.gcda *.gcno coverage_tetris.info coverage_desktop.info coverage_snake.info coverage.info coverage.filtered.info
	rm -f test_app test_desktop_tetris test_terminal_snake
	@echo "Coverage report generated at coverage_report/index.html"

PLANTUML = plantuml
UML_FILE = brick_game/tetris/diagram.uml

dvi: $(UML_FILE)
	$(PLANTUML) -tpng $(UML_FILE)

dist:
	tar czf brick_game.tar.gz brick_game/ gui/ Makefile