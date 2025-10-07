install:
	g++ -fPIC desktop_snake/constructor.cpp desktop_snake/generateApple.cpp desktop_snake/keyPressEvent.cpp desktop_snake/loadHighScore.cpp desktop_snake/main.cpp desktop_snake/resetGame.cpp desktop_snake/saveHighScore.cpp desktop_snake/setupTimer.cpp desktop_snake/startGame.cpp desktop_snake/togglePause.cpp desktop_snake/toggleTurbo.cpp desktop_snake/updateCurrentState.cpp desktop_snake/updateGame.cpp desktop_snake/updateSpeed.cpp ./../../gui/desktop/snake/*.cpp -o ./../../desktop_snake `pkg-config --cflags --libs Qt5Widgets`
	g++ snake/snake_terminal.cpp snake/main.cpp ./../../gui/cli/inputHandler.cpp ./../../gui/cli/turbo.cpp snake/run.cpp ./../../gui/cli/drawField.cpp snake/convertFieldToInt.cpp snake/saveHighScore.cpp snake/loadHighScore.cpp ./../../gui/cli/fillFieldWithFrame.cpp ./../../gui/cli/generateApple.cpp ./../../gui/cli/spawnSnake.cpp -o ./../../snake -lncursesw 

clean:
	rm -rf ./../../desktop_snake ./*.txt

clang-format:
	cd ./../../../materials/linters && clang-format -i ./../../src/brick_game/snake/desktop_snake/*.cpp ./../../src/brick_game/snake/snake/*.cpp ./../../src/brick_game/snake/snake/*.h ./../../src/gui/cli/*.cpp