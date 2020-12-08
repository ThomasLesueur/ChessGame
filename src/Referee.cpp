#include "Referee.hpp"

Referee::Referee()
{
}

Referee::~Referee()
{
}

std::vector<std::vector<int>> Referee::computePossibleMoves(
            std::vector<ChessMan> pieces,
        std::vector<std::vector<int>> moves,
        std::vector<int> startPosition
)
{
    _moves = moves;
    _pieces = pieces;
    _startPosition = startPosition;
    std::vector<std::vector<int>> possibleMoves;

    for (size_t i = 0; i < _moves.size(); i++) {
        if (isMovePossible(moves[i], detectDirection(moves[i]))) {
            possibleMoves.push_back(moves[i]);
        }
    }
    return (possibleMoves);
}

std::vector<std::vector<int>> Referee::computePossibleMovesInCheck(
            std::vector<ChessMan> pieces,
            std::vector<std::vector<int>> moves,
            std::vector<int> startPosition,
            Color color
        )
{
    std::vector<std::vector<int>> possibleMoves = computePossibleMoves(pieces, moves, startPosition);
    std::vector<std::vector<int>> possibleMovesInCheck;
    std::vector<std::vector<int>> enemyPossibleMoves;
    std::vector<std::vector<int>> allEnemiesPossibleMoves;

    std::vector<int> kingPos = pieces[getIndexByTypeAndColor(King, color)].getPosition();

    for (size_t i = 0; i < possibleMoves.size(); i++) {
        allEnemiesPossibleMoves.clear();
        if (isPieceOnPosition(possibleMoves[i])) {
            _pieces[getIndexByPositions(possibleMoves[i])].setPosition(-1, -1);
        }
        _pieces[getIndexByPositions(startPosition)].setPosition(possibleMoves[i][1], possibleMoves[i][0]);
        kingPos = _pieces[getIndexByTypeAndColor(King, color)].getPosition();
        for (size_t j = 0; j < _pieces.size(); j++) {
            if (_pieces[j].getColor() != color) {
                enemyPossibleMoves = computePossibleMoves(_pieces, _pieces[j].computeMoves(), _pieces[j].getPosition());
                allEnemiesPossibleMoves.insert(allEnemiesPossibleMoves.end(), enemyPossibleMoves.begin(), enemyPossibleMoves.end());
            }
        }
        if(std::find(allEnemiesPossibleMoves.begin(), allEnemiesPossibleMoves.end(), kingPos) == allEnemiesPossibleMoves.end()) {
            possibleMovesInCheck.push_back(possibleMoves[i]);
        }
    }
    return (possibleMovesInCheck);
}

std::vector<std::vector<int>> Referee::computeAllPossibleMoves(
            std::vector<ChessMan> pieces,
            Color color,
            bool isCheck
        )
{
    std::vector<std::vector<int>> allpossibleMoves;
    std::vector<std::vector<int>> curentPiecePossibleMoves;

    for (size_t i = 0; i < pieces.size(); i++) {
        curentPiecePossibleMoves.clear();
        if (pieces[i].getColor() == color) {
            if (!isCheck)
                curentPiecePossibleMoves = computePossibleMoves(
                    pieces,
                    pieces[i].computeMoves(),
                    pieces[i].getPosition());
            else
                curentPiecePossibleMoves = computePossibleMovesInCheck(pieces,
                pieces[i].computeMoves(),
                pieces[i].getPosition(), color);
            allpossibleMoves.insert(
                allpossibleMoves.end(), 
                curentPiecePossibleMoves.begin(), 
                curentPiecePossibleMoves.end());
        }
    }
    return (allpossibleMoves);
}

Direction Referee::detectDirection(std::vector<int> end)
{
    if (_startPosition[0] == end[0] && _startPosition[1] < end[1])
        return Back;
    if (_startPosition[0] == end[0] && _startPosition[1] > end[1])
        return Forward;
    if (_startPosition[0] < end[0] && _startPosition[1] == end[1])
        return Right;
    if (_startPosition[0] > end[0] && _startPosition[1] == end[1])
        return Left;
    if (_startPosition[0] < end[0] && _startPosition[1] < end[1])
        return Right_Back;
    if (_startPosition[0] > end[0] && _startPosition[1] > end[1])
        return Left_Forward;
    if (_startPosition[0] > end[0] && _startPosition[1] < end[1])
        return Left_Back;
    if (_startPosition[0] < end[0] && _startPosition[1] > end[1])
        return Right_Forward;
    return (None);
}

bool Referee::isLeftDirectPossible(std::vector<int> end)
{
    std::vector<int> tmp = _startPosition;

    for (int i = _startPosition[0] ; i > end[0]; i--) {
        tmp[0] = i;
        if (i != _startPosition[0] && isPieceOnPosition(tmp)) {
            return (false);
        }
    }
    return (true);
}

bool Referee::isRightDirectPossible(std::vector<int> end)
{
    std::vector<int> tmp = _startPosition;

    for (int i = _startPosition[0] ; i < end[0]; i++) {
        tmp[0] = i;
        if (i != _startPosition[0] && isPieceOnPosition(tmp)) {
            return (false);
        }
    }
    return (true);
}

bool Referee::isForwardDirectPossible(std::vector<int> end)
{
    std::vector<int> tmp = _startPosition;

    if ((getChessManByPosition(_startPosition).getType() == Pawn) && isPieceOnPosition(end))
        return (false);
    for (int i = _startPosition[1] ; i > end[1]; i--) {
        tmp[1] = i;
        if (i != _startPosition[1] && isPieceOnPosition(tmp)) {
            return (false);
        }
    }
    return (true);
}

bool Referee::isBackDirectPossible(std::vector<int> end)
{
    std::vector<int> tmp = _startPosition;

    if ((getChessManByPosition(_startPosition).getType() == Pawn) && isPieceOnPosition(end))
        return (false);
    for (int i = _startPosition[1] ; i < end[1]; i++) {
        tmp[1] = i;
        if (i != _startPosition[1] && isPieceOnPosition(tmp)) {
            return (false);
        }
    }
    return (true);
}

bool Referee::isLeftForwardDirectPossible(std::vector<int> end)
{
    std::vector<int> tmp = _startPosition;
    int j = _startPosition[0];

    for (int i = _startPosition[1] ; i > end[1]; i--) {
        tmp[0] = j;
        tmp[1] = i;
        if (tmp != _startPosition && isPieceOnPosition(tmp)) {
            return (false);
        }
        j -= 1;
    }
    return (true);
}

bool Referee::isRightForwardDirectPossible(std::vector<int> end)
{
    std::vector<int> tmp = _startPosition;
    int j = _startPosition[0];

    for (int i = _startPosition[1] ; i > end[1]; i--) { 
        tmp[0] = j;
        tmp[1] = i;
        if (tmp != _startPosition && isPieceOnPosition(tmp)) {
            return (false);
        }
        j += 1;
    }
    return (true);
}

bool Referee::isLeftBackDirectPossible(std::vector<int> end)
{
    std::vector<int> tmp = _startPosition;
    int j = _startPosition[0];

    for (int i = _startPosition[1] ; i < end[1]; i++) {
        tmp[0] = j;
        tmp[1] = i;
        if (tmp != _startPosition && isPieceOnPosition(tmp)) {
            return (false);
        }
        j -= 1;
    }
    return (true);
}

bool Referee::isRightBackDirectPossible(std::vector<int> end)
{
    std::vector<int> tmp = _startPosition;
    int j = _startPosition[0];

    for (int i = _startPosition[1] ; i < end[1]; i++) {
        tmp[0] = j;
        tmp[1] = i;
        if (tmp != _startPosition && isPieceOnPosition(tmp)) {
            return (false);
        }
        j += 1;
    }
    return (true);
}

ChessMan Referee::getChessManByPosition(std::vector<int> pos)
{
    for (size_t i = 0; i < _pieces.size(); i++) {
        if (_pieces[i].getPosition()[0] == pos[0] && \
        _pieces[i].getPosition()[1] == pos[1])
        return (_pieces[i]);
    }
    ChessMan none(-1, -1, NoneColor, NoneType);
    none.setFirstMoveStatement(false);
    return (none);
}

ChessMan Referee::getChessManByPosition(int x, int y)
{
    for (size_t i = 0; i < _pieces.size(); i++) {
        if (_pieces[i].getPosition()[0] == y && \
        _pieces[i].getPosition()[1] == x)
        return (_pieces[i]);
    }
    ChessMan none(-1, -1, NoneColor, NoneType);
    none.setFirstMoveStatement(false);
    return (none);
}


size_t Referee::getIndexByPositions(std::vector<int> pos)
{
    for (size_t i = 0; i < _pieces.size(); i++) {
        if (_pieces[i].getPosition()[0] == pos[0] && \
        _pieces[i].getPosition()[1] == pos[1])
        return (i);
    }
    return (-1);
}
size_t Referee::getIndexByPositions(std::vector<ChessMan> pieces, std::vector<int> pos)
{
    for (size_t i = 0; i < pieces.size(); i++) {
        if (pieces[i].getPosition()[0] == pos[0] && \
        pieces[i].getPosition()[1] == pos[1])
        return (i);
    }
    return (-1);
}


size_t Referee::getIndexByTypeAndColor(Type type, Color color)
{
    for (size_t i = 0; i < _pieces.size(); i++) {
        if (_pieces[i].getColor() == color && \
        _pieces[i].getType() == type)
        return (i);
    }
    return (-1);
}

bool Referee::isPieceOnPosition(std::vector<int> pos)
{
    for (size_t i = 0; i < _pieces.size(); i++) {
        if (_pieces[i].getPosition()[0] == pos[0] && \
        _pieces[i].getPosition()[1] == pos[1])
        return (true);
    }
    return (false);
}

bool Referee::isMovePossible(std::vector<int> end, Direction direction)
{
    if (isPieceOnPosition(end)) {
        if (getChessManByPosition(end).getColor() == getChessManByPosition(_startPosition).getColor())
            return (false);
    }
    if (getChessManByPosition(_startPosition).getType() == Knight)
        return (true);
    if (direction == Left)
        return isLeftDirectPossible(end);
    if (direction == Right)
        return isRightDirectPossible(end);
    if (direction == Forward)
        return isForwardDirectPossible(end);
    if (direction == Back)
        return isBackDirectPossible(end);
    if (getChessManByPosition(_startPosition).getType() == Pawn) {
        if  (!isPieceOnPosition(end))
            return (false);
        if (getChessManByPosition(end).getColor() != getChessManByPosition(_startPosition).getColor()) {
            return (true);
        }
        else
            return (false);
    }
    if (direction == Left_Forward)
        return isLeftForwardDirectPossible(end);
    if (direction == Left_Back)
        return isLeftBackDirectPossible(end);
    if (direction == Right_Forward)
        return isRightForwardDirectPossible(end);
    if (direction == Right_Back)
        return isRightBackDirectPossible(end);
    return (false);
}

bool Referee::isMoveIsInPossibleMoves(std::vector<int> move, std::vector<std::vector<int>> moves)
{
    for (size_t i = 0; i < moves.size(); i++) {
        if (moves[i][0] == move[0] && moves[i][1] == move[1])
            return (true);
    }
    return (false);
}

bool Referee::canKingsideCastling(Color color)
{
    std::vector<int> rookPos, kingPos;
    std::vector<std::vector<int>> transitPos;

    if (color == White) {
        kingPos.push_back(4);
        kingPos.push_back(7);
        rookPos.push_back(7);
        rookPos.push_back(7);
        transitPos.push_back({5,7});
        transitPos.push_back({6,7});
        color = Black;
    }
    else {
        kingPos.push_back(4);
        kingPos.push_back(0);
        rookPos.push_back(7);
        rookPos.push_back(0);
        transitPos.push_back({5,0});
        transitPos.push_back({6,0});
        color = White;
    }
    return(isCastlingPossible(kingPos, rookPos, transitPos, color));
}

bool Referee::canQueensideCastling(Color color)
{
    std::vector<int> rookPos, kingPos;
    std::vector<std::vector<int>> transitPos;

    if (color == White) {
        kingPos.push_back(4);
        kingPos.push_back(7);
        rookPos.push_back(0);
        rookPos.push_back(7);
        transitPos.push_back({3,7});
        transitPos.push_back({2,7});
        transitPos.push_back({1,7});
        color = Black;
    }
    else {
        kingPos.push_back(4);
        kingPos.push_back(0);
        rookPos.push_back(0);
        rookPos.push_back(0);
        transitPos.push_back({3,0});
        transitPos.push_back({2,0});
        transitPos.push_back({1,0});
        color = White;
    }
    return(isCastlingPossible(kingPos, rookPos, transitPos, color));
}

bool Referee::isCastlingPossible(
            std::vector<int> kingPos,
            std::vector<int> rookPos, 
            std::vector<std::vector<int>> transitPos,
            Color enemyColor)
{
    std::vector<std::vector<int>> ennemyTreatPos = computeAllPossibleMoves(_pieces, enemyColor, false);

    if (getChessManByPosition(kingPos).getFirstMoveStatement() == false ||
        getChessManByPosition(rookPos).getFirstMoveStatement() == false)
            return (false);
    for (size_t i = 0; i < transitPos.size(); i++) {
        if (getChessManByPosition(transitPos[i]).getType() != NoneType)
            return (false);
    }
    if (std::find(ennemyTreatPos.begin(), ennemyTreatPos.end(), kingPos) != ennemyTreatPos.end())
        return (false);
    for (int i = 0; i < 2; i++) {
        if (std::find(ennemyTreatPos.begin(), ennemyTreatPos.end(), transitPos[i]) != ennemyTreatPos.end())
            return (false);
    }
    return (true);
}

std::vector<ChessMan> Referee::getPieces()
{
    return (_pieces);
}