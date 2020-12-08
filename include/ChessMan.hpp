#ifndef CHESSMAN_HPP_
#define CHESSMAN_HPP_

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>

enum Color{White, Black, NoneColor};
enum Type{King, Queen, Knight, Bishop, Rook, Pawn, NoneType};

class ChessMan {
    public:
        ChessMan(int row, int column, Color color, Type type);
        ~ChessMan();

        std::vector<int>getPosition();
        Color getColor();
        Type getType();
        bool getFirstMoveStatement();
        bool isRemoved();
        void setPosition(int row, int column);
        void setColor(Color color);
        void setType (Type type);
        void setFirstMoveStatement(bool state);

        std::vector<std::vector<int>> computeMoves();
        std::vector<std::vector<int>> computeMovesPawn();
        std::vector<std::vector<int>> computeMovesRook();
        std::vector<std::vector<int>> computeMovesKnight();
        std::vector<std::vector<int>> computeMovesBishop();
        std::vector<std::vector<int>> computeMovesQueen();
        std::vector<std::vector<int>> computeMovesKing();
        std::vector<std::vector<int>> removeOutOfBondMoves(std::vector<std::vector<int>> moves);

        void debugPrint(std::vector<std::vector<int>> moves);
        void debugPrint(int nb);
        void debugPrint(std::string str);

    private:
        int _row;
        int _column;
        Color _color;
        Type _type;
        bool _removed;
        bool _firstMove;
};

#endif /* !CHESSMAN_HPP_ */