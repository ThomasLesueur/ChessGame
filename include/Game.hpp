#ifndef GAME_HPP_
#define GAME_HPP_

#include "Referee.hpp"
#include "Informations.hpp"

class Game {
    public:
        Game();
        Game(int timeLimit);
        ~Game();

        void initBoard();
        void initBoard(std::vector<std::vector<char>> board);
        void initSpecialPieces();
        void initMap();
        void start();
        void gameLoop();
        void proceedTurn();
        std::vector<int> selectPiece();
        std::vector<int> getSelectedPosition(std::string input);
        bool makeDecision();
        void movePiece(std::vector<int> pos, std::vector<std::vector<int>> moves);
        void checkPromotion(std::vector<int> pos);
        bool checkCastling();
        bool canCastling();
        void doCastling(bool isKingside);
        bool isCheck(std::vector<int> newPos);
        bool isMate(Color color);

    private:
        int _timeLimit;
        std::vector<ChessMan> _pieces;
        std::unordered_map<std::string, int> _rowMap;
        std::unordered_map<std::string, int> _columnMap;
        Referee _referee;
        Informations _infos;
};

#endif /* !GAME_HPP_ */