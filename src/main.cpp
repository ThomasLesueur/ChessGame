#include "Game.hpp"
#include <fstream>

void runWithArg(int ac, char **av, Game game)
{
    std::vector<std::vector<char>> board;
    std::vector<char> line;
    char c;
    std::fstream f(av[1], std::fstream::in);
    while (f >> std::noskipws >> c) {
        if (c != '\n')
            line.push_back(c);
        else {
            board.push_back(line);
            line.clear();
        }
    }
    board.push_back(line);
    game.initBoard(board);
    game.start();
}

int main(int ac, char **av)
{
    Game game(30);

    if (ac > 1)
        runWithArg(ac, av, game);
    else {
        game.initBoard();
        game.start();
    }
}