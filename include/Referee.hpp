#ifndef REFEREE_HPP_
#define REFEREE_HPP_

#include "ChessMan.hpp"

enum Direction{Left, Right, Forward, Back, Left_Forward, Left_Back, Right_Forward, Right_Back, None};

class Referee {
    public:
        Referee();
        ~Referee();

        std::vector<std::vector<int>> computePossibleMoves(
            std::vector<ChessMan> pieces,
        std::vector<std::vector<int>> moves,
        std::vector<int> startPosition
        );
        std::vector<std::vector<int>> computePossibleMovesInCheck(
            std::vector<ChessMan> pieces,
            std::vector<std::vector<int>> moves,
            std::vector<int> startPosition,
            Color color
        );
        std::vector<std::vector<int>> computeAllPossibleMoves(
            std::vector<ChessMan> pieces,
            Color color, bool isCheck
        );
        Direction detectDirection(std::vector<int> end);
        bool isLeftDirectPossible(std::vector<int> end);
        bool isRightDirectPossible(std::vector<int> end);
        bool isForwardDirectPossible(std::vector<int> end);
        bool isBackDirectPossible(std::vector<int> end);
        bool isLeftForwardDirectPossible(std::vector<int> end);
        bool isRightForwardDirectPossible(std::vector<int> end);
        bool isLeftBackDirectPossible(std::vector<int> end);
        bool isRightBackDirectPossible(std::vector<int> end);
        ChessMan getChessManByPosition(std::vector<int> pos);
        ChessMan getChessManByPosition(int x, int y);
        size_t getIndexByPositions(std::vector<int> pos);
        size_t getIndexByPositions(std::vector<ChessMan> pieces, std::vector<int> pos);
        size_t getIndexByTypeAndColor(Type type, Color color);
        bool isPieceOnPosition(std::vector<int> pos);
        bool isMovePossible(std::vector<int> end, Direction direction);
        bool isMoveIsInPossibleMoves(std::vector<int> move, std::vector<std::vector<int>> moves);
        bool canKingsideCastling(Color color);
        bool canQueensideCastling(Color color);
        bool isCastlingPossible(
            std::vector<int> kingPos,
            std::vector<int> rookPos, 
            std::vector<std::vector<int>> transitPos,
            Color color);
        std::vector<ChessMan> getPieces();
    private:
        std::vector<ChessMan> _pieces;
        std::vector<std::vector<int>> _moves;
        std::vector<int> _startPosition;
};

#endif /* !REFEREE_HPP_ */
