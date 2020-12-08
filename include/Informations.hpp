#ifndef INFORMATIONS_HPP_
#define INFORMATIONS_HPP_

#include "ChessMan.hpp"

class Informations {
    public:
        Informations();
        ~Informations();

        void setCheck(Color color, bool isCheck);
        void setTurn(Color turn);
        void setBoard(std::vector<std::vector<char>> board);

        Color getTurn();
        std::vector<std::vector<char>> getBoard();

        void printAllPieceInfos(std::vector<ChessMan> pieces);
        void printPieceInfos(ChessMan piece);
        void printBoard();
        void printMoves(std::string msg, std::vector<std::vector<int>> moves);
        void printEnd(Color color);
        void printGameState(std::vector<ChessMan> pieces);
        void changeTurn();
        void updateBoard(std::vector<int> oldPos, std::vector<int> newPos);
        void changePieceTypeOnBoard(std::vector<int> pos, char newType, Color color);
        bool isAlreadyCheck(Color color);

    private:
        Color _turn;
        std::unordered_map<int, std::string> _reverseRowMap;
        std::unordered_map<int, std::string> _reverseColumnMap;
        std::unordered_map<Type, std::string> _typeMap;
        std::vector<std::vector<char>> _board;
        bool _whiteKingCheck;
        bool _blackKingCheck;
};

#endif /* !INFORMATIONS_HPP_ */
