#include "ChessMan.hpp"

ChessMan::ChessMan(int row, int column, Color color, Type type)
{
    _row = row;
    _column = column;
    _color = color;
    _type = type;
    _removed = false;
    _firstMove = true;
}

ChessMan::~ChessMan()
{
}

std::vector<int>ChessMan::getPosition()
{
    std::vector<int> pos;

    pos.push_back(_column);
    pos.push_back(_row);
    return (pos);
}

Color ChessMan::getColor()
{
    return (_color);
}

Type ChessMan::getType()
{
    return (_type);
}

bool ChessMan::isRemoved()
{
    return (_removed);
}

bool ChessMan::getFirstMoveStatement()
{
    return (_firstMove);
}


void ChessMan::setPosition(int row, int column)
{
    _row = row;
    _column = column;
}

void ChessMan::setColor(Color color)
{
    _color = color;
}

void ChessMan::setType(Type type)
{
    _type = type;
}

void ChessMan::setFirstMoveStatement(bool state)
{
    _firstMove = state;
}

std::vector<std::vector<int>> ChessMan::computeMoves()
{
    std::vector<std::vector<int>> moves;

    if (_type == Pawn) {
        moves = computeMovesPawn();
    }
    if (_type == Rook) {
        moves = computeMovesRook();
    }
    if (_type == Knight) {
        moves = computeMovesKnight();
    }
    if (_type == Bishop) {
        moves = computeMovesBishop();
    }
    if (_type == Queen) {
        moves = computeMovesQueen();
    }
    if (_type == King) {
        moves = computeMovesKing();
    }
    moves = removeOutOfBondMoves(moves);

    return (moves);
}

std::vector<std::vector<int>> ChessMan::computeMovesPawn()
{
    std::vector<std::vector<int>> moves;
    std::vector<int> *move;

    if (_firstMove == true) {
        if (_color == White) {
            move = new std::vector<int>;
            move->push_back(_column);
            move->push_back(_row - 2);
            moves.push_back(*move);
        }
        else if (_color == Black) {
            move = new std::vector<int>;
            move->push_back(_column);
            move->push_back(_row + 2);
            moves.push_back(*move);
        }
    }
    if (_color == White) {
        move = new std::vector<int>;
        move->push_back(_column);
        move->push_back(_row - 1);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column - 1);
        move->push_back(_row - 1);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column + 1);
        move->push_back(_row - 1);
        moves.push_back(*move);
    }
    else if (_color == Black) {
        move = new std::vector<int>;
        move->push_back(_column);
        move->push_back(_row + 1);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column + 1);
        move->push_back(_row + 1);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column - 1);
        move->push_back(_row + 1);
        moves.push_back(*move);
    }
    return (moves);
}
std::vector<std::vector<int>> ChessMan::computeMovesRook()
{
    std::vector<std::vector<int>> moves;
    std::vector<int> *move;

    for (auto i = 1; i < 8; i++) {
        move = new std::vector<int>;
        move->push_back(_column);
        move->push_back(_row + i);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column + i);
        move->push_back(_row);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column);
        move->push_back(_row - i);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column - i);
        move->push_back(_row);
        moves.push_back(*move);
    }
    return (moves);
}
std::vector<std::vector<int>> ChessMan::computeMovesKnight()
{
    std::vector<std::vector<int>> moves;
    std::vector<int> *move;

    move = new std::vector<int>;
    move->push_back(_column  -2);
    move->push_back(_row - 1);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column - 2);
    move->push_back(_row + 1);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column + 2);
    move->push_back(_row - 1);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column + 2);
    move->push_back(_row + 1);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column - 1);
    move->push_back(_row + 2);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column + 1);
    move->push_back(_row + 2);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column - 1);
    move->push_back(_row - 2);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column + 1);
    move->push_back(_row - 2);
    moves.push_back(*move);
    return (moves);
}
std::vector<std::vector<int>> ChessMan::computeMovesBishop()
{
    std::vector<std::vector<int>> moves;
    std::vector<int> *move;

    for (auto i = 1; i < 8; i++) {
        move = new std::vector<int>;
        move->push_back(_column + i);
        move->push_back(_row + i);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column + i);
        move->push_back(_row - i);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column - i);
        move->push_back(_row - i);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column - i);
        move->push_back(_row + i);
        moves.push_back(*move);
    }
    return (moves);
}
std::vector<std::vector<int>> ChessMan::computeMovesQueen()
{
    std::vector<std::vector<int>> moves;
    std::vector<int> *move; 

    for (auto i = 1; i < 8; i++) {
        move = new std::vector<int>;
        move->push_back(_column);
        move->push_back(_row + i);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column + i);
        move->push_back(_row);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column);
        move->push_back(_row - i);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column - i);
        move->push_back(_row);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column + i);
        move->push_back(_row + i);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column + i);
        move->push_back(_row - i);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column - i);
        move->push_back(_row - i);
        moves.push_back(*move);
        move = new std::vector<int>;
        move->push_back(_column - i);
        move->push_back(_row + i);
        moves.push_back(*move);
    }
    return (moves);
}
std::vector<std::vector<int>> ChessMan::computeMovesKing()
{
    std::vector<std::vector<int>> moves;
    std::vector<int> *move;

    move = new std::vector<int>;
    move->push_back(_column);
    move->push_back(_row + 1);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column + 1);
    move->push_back(_row);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column);
    move->push_back(_row - 1);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column - 1);
    move->push_back(_row);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column + 1);
    move->push_back(_row + 1);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column + 1);
    move->push_back(_row - 1);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column - 1);
    move->push_back(_row - 1);
    moves.push_back(*move);
    move = new std::vector<int>;
    move->push_back(_column - 1);
    move->push_back(_row + 1);
    moves.push_back(*move);
    move = new std::vector<int>;
    return (moves);
}

std::vector<std::vector<int>> ChessMan::removeOutOfBondMoves(std::vector<std::vector<int>> moves)
{
    for(size_t i = 0 ; i < moves.size() ; i++) {
        if (moves[i][0] < 0 || moves[i][0] > 7 || moves[i][1] < 0 || moves[i][1] > 7) {
            moves.erase(moves.begin() + i);
            i--;
        }
    }
    return (moves);
}

void ChessMan::debugPrint(std::vector<std::vector<int>> moves)
{
    std::cerr << "--------------DEBUG---------------------" << std::endl;
    for (size_t i = 0; i < moves.size(); i++) {
        std::cout << "c :" << moves[i][0] << "; r:" << moves[i][1] << std::endl;
    }
    std::cerr << "--------------END---------------------" << std::endl;
}

void ChessMan::debugPrint(int nb)
{
    std::cerr << "--------------DEBUG---------------------" << std::endl;
    std::cerr << nb << std::endl;
    std::cerr << "--------------END---------------------" << std::endl;
}

void ChessMan::debugPrint(std::string str)
{
    std::cerr << "--------------DEBUG---------------------" << std::endl;
    std::cerr << str << std::endl;
    std::cerr << "--------------END---------------------" << std::endl;
}