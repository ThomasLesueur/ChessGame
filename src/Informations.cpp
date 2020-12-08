#include "Informations.hpp"

Informations::Informations()
{
    _reverseRowMap = {
        {7, "1"},
        {6, "2"},
        {5, "3"},
        {4, "4"},
        {3, "5"},
        {2, "6"},
        {1, "7"},
        {0, "8"},
        {-1,""}
    };
    _reverseColumnMap = {
        {0, "A"},
        {1, "B"},
        {2, "C"},
        {3, "D"},
        {4, "E"},
        {5, "F"},
        {6, "G"},
        {7, "H"},
        {-1, "Captured"}
    };

    _typeMap = {
        {Pawn, "Pawn"},
        {Rook, "Rook"},
        {Knight, "Knight"},
        {Bishop, "Bishop"},
        {Queen, "Queen"},
        {King, "King"},
    };
    _whiteKingCheck = false;
    _blackKingCheck = false;
}

Informations::~Informations()
{
}

void Informations::setCheck(Color color, bool isCheck)
{
    if (color == White)
        _whiteKingCheck = isCheck;
    else
        _blackKingCheck = isCheck;
}

void Informations::setTurn(Color turn)
{
    _turn = turn;
}

void Informations::setBoard(std::vector<std::vector<char>> board)
{
    _board = board;
}

Color Informations::getTurn()
{
    return (_turn);
}

std::vector<std::vector<char>> Informations::getBoard()
{
    return (_board);
}

void Informations::printAllPieceInfos(std::vector<ChessMan> pieces)
{
    std::cout << "-----------PIECES INFORMATIONS-----------" << std::endl;
    for (size_t i = 0; i < pieces.size(); i++) {
        printPieceInfos(pieces[i]);
    }
    std::cout << "-----------------------------------------" << std::endl;
}


void Informations::printBoard()
{
    int row = 8;
    std::cout << "    A  B  C  D  E  F  G  H" << std::endl;
    for(auto i = _board.begin() ; i <_board.end() ; i++) {
        std::cout << "(" << row << ")";
        row--;
        for(auto j = i->begin() ; j < i->end() ; j++)
            std::cout << "[" << *j << "]"; 
        std::cout << std::endl;
    }
}

void Informations::printMoves(std::string msg, std::vector<std::vector<int>> moves)
{
    std::cout << msg;
    for (size_t i = 0; i < moves.size(); i++) {
        std::cout << _reverseColumnMap[moves[i][0]] << _reverseRowMap[moves[i][1]];
        std::cout << ", ";
    }
    std::cout << std::endl;
}

void Informations::changeTurn()
{
    std::cout << "--------------------------------------" << std::endl;
    if (_turn == White) {
        std::cout << "Black turn." << std::endl << std::endl;
        _turn = Black;
    }
    else if(_turn == Black) {
        std::cout << "White turn." << std::endl << std::endl;
        _turn = White;
    }

}

void Informations::printPieceInfos(ChessMan piece)
{
    std::cout << std::endl;
    std::cout << "Type: " << _typeMap[piece.getType()] << std::endl;
    if (piece.getColor() == White)
        std::cout << "Color: White" << std::endl;
    else
        std::cout << "Color: Black" << std::endl;
    std::cout << "Position: " << _reverseColumnMap[piece.getPosition()[0]];
    std::cout << _reverseRowMap[piece.getPosition()[1]] << std::endl;
}

void Informations::printEnd(Color color)
{
    std::string winner;
    if (color == White)
        winner = "Black";
    else
        winner = "White";
    if (isAlreadyCheck(color)) {
        std::cout << "Checkmate ! " << winner << " wins." << std::endl;
    }
    else {
        std::cout << "Stalemate ! Draw." << std::endl;
    }
}

void Informations::printGameState(std::vector<ChessMan> pieces)
{
    std::cout << "---------------Game State----------------" << std::endl << std::endl;
    std::cout << "Turn :" << _turn << std::endl;
    std::cout << "White king check :" << _whiteKingCheck << std::endl;
    std::cout << "Black king check :" << _whiteKingCheck << std::endl;
    printAllPieceInfos(pieces);
}


void Informations::updateBoard(std::vector<int> oldPos, std::vector<int> newPos)
{
    char tmp;

    tmp = _board[oldPos[1]][oldPos[0]];
    _board[oldPos[1]][oldPos[0]] = ' ';
    _board[newPos[1]][newPos[0]] = tmp;
}

void Informations::changePieceTypeOnBoard(std::vector<int> pos, char newType, Color color)
{
    if (color == Black)
        newType = tolower(newType);
    _board[pos[1]][pos[0]] = newType;
}


bool Informations::isAlreadyCheck(Color color)
{
    if (color == White)
        return (_whiteKingCheck);
    else
        return (_blackKingCheck);
}