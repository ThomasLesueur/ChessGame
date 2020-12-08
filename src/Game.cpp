#include "Game.hpp"

Game::Game()
{
    _infos.setTurn(Black);
}

Game::Game(int timeLimit)
{
    this->_timeLimit = timeLimit;
    _infos.setTurn(Black);
}

Game::~Game()
{
}

void Game::initBoard()
{
    std::vector<std::vector<char>> v(8);
    for (int i = 0; i < 8; i++)
         v[i].resize(8);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            v[i][j] = ' ';
        }
    }
    for (auto i = 0; i < 8; i++) {
        ChessMan _pawn(1, i, Black, Pawn);
        ChessMan _pawn2(6, i, White, Pawn);
        v[1][i] = 'p';
        v[6][i] = 'P';
        _pieces.push_back(_pawn);
        _pieces.push_back(_pawn2);
    }
    initSpecialPieces();
    v[0][0] = 'r';
    v[0][1] = 'n';
    v[0][2] = 'b';
    v[0][3] = 'q';
    v[0][4] = 'k';
    v[0][5] = 'b';
    v[0][6] = 'n';
    v[0][7] = 'r';
    v[7][0] = 'R';
    v[7][1] = 'N';
    v[7][2] = 'B';
    v[7][3] = 'Q';
    v[7][4] = 'K';
    v[7][5] = 'B';
    v[7][6] = 'N';
    v[7][7] = 'R';

    _infos.setBoard(v);
}

void Game::initBoard(std::vector<std::vector<char>> board)
{
    char piece;
    _infos.setBoard(board);
    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board[i].size(); j++) {
            piece = board[i][j];
            switch (piece)
            {
            case 'p':{
                ChessMan blackPawn(i, j, Black, Pawn);
                _pieces.push_back(blackPawn);
                break;
            }
            case 'P': {
                ChessMan whitePawn(i, j, White, Pawn);
                _pieces.push_back(whitePawn);
                break;
            }
            case 'r': {
                ChessMan blackRook(i, j, Black, Rook);
                _pieces.push_back(blackRook);
                break;
            }
            case 'R': {
                ChessMan whiteRook(i, j, White, Rook);
                _pieces.push_back(whiteRook);
                break;
            }
            case 'b': {
                ChessMan blackBishop(i, j, Black, Bishop);
                _pieces.push_back(blackBishop);
                break;
            }
            case 'B': {
                ChessMan whiteBishop(i, j, White, Bishop);
                _pieces.push_back(whiteBishop);
                break;
            }
            case 'n': {
                ChessMan blackKnight(i, j, Black, Knight);
                _pieces.push_back(blackKnight);
                break;
            }
            case 'N': {
                ChessMan whiteKnight(i, j, White, Knight);
                _pieces.push_back(whiteKnight);
                break;
            }
            case 'q': {
                ChessMan blackQueen(i, j, Black, Queen);
                _pieces.push_back(blackQueen);
                break;
            }
            case 'Q': {
                ChessMan whiteQueen(i, j, White, Queen);
                _pieces.push_back(whiteQueen);
                break;
            }
            case 'k': {
                ChessMan blackKing(i, j, Black, King);
                _pieces.push_back(blackKing);
                break;
            }
            case 'K': {
                ChessMan whiteKing(i, j, White, King);
                _pieces.push_back(whiteKing);
                break;
            }
            default:
                break;
            }
        }
    }
}

void Game::initSpecialPieces()
{
    ChessMan blackRook(0, 0, Black, Rook);
    ChessMan blackRook2(0, 7, Black, Rook);
    ChessMan whiteRook(7, 0, White, Rook);
    ChessMan whiteRook2(7, 7, White, Rook);
    ChessMan blackKnight(0, 1, Black, Knight);
    ChessMan blackKnight2(0, 6, Black, Knight);
    ChessMan whiteKnight(7, 1, White, Knight);
    ChessMan whiteKnight2(7, 6, White, Knight);
    ChessMan blackBishop(0, 2, Black, Bishop);
    ChessMan blackBishop2(0, 5, Black, Bishop);
    ChessMan whiteBishop(7, 2, White, Bishop);
    ChessMan whiteBishop2(7, 5, White, Bishop);
    ChessMan blackQueen(0, 3, Black, Queen);
    ChessMan blackKing(0, 4, Black, King);
    ChessMan whiteQueen(7, 3, White, Queen);
    ChessMan whiteKing(7, 4, White, King);

    _pieces.push_back(whiteRook);
    _pieces.push_back(whiteRook2);
    _pieces.push_back(whiteKnight);
    _pieces.push_back(whiteKnight2);
    _pieces.push_back(whiteBishop);
    _pieces.push_back(whiteBishop2);
    _pieces.push_back(whiteQueen);
    _pieces.push_back(whiteKing);
    _pieces.push_back(blackRook);
    _pieces.push_back(blackRook2);
    _pieces.push_back(blackKnight);
    _pieces.push_back(blackKnight2);
    _pieces.push_back(blackBishop);
    _pieces.push_back(blackBishop2);
    _pieces.push_back(blackQueen);
    _pieces.push_back(blackKing);
}

void Game::initMap()
{
     _rowMap = {
        {"1", 7},
        {"2", 6},
        {"3", 5},
        {"4", 4},
        {"5", 3},
        {"6", 2},
        {"7", 1},
        {"8", 0}
    };
    _columnMap = {
        {"A", 0},
        {"B", 1},
        {"C", 2},
        {"D", 3},
        {"E", 4},
        {"F", 5},
        {"G", 6},
        {"H", 7}
    };
}

void Game::start()
{
    initMap();
    gameLoop();
}

void Game::gameLoop()
{
    while (!isMate(_infos.getTurn())) {
        _infos.printBoard();
        _infos.changeTurn();
        proceedTurn();
    }
}

void Game::proceedTurn()
{
    std::vector<int> pos;
    std::vector<std::vector<int>> moves;


    while (true) {
        moves.clear();
        pos = selectPiece();
        for (size_t i = 0; i < _pieces.size(); i++) {
            if (_pieces[i].getPosition()[0] == pos[0] \
                && _pieces[i].getPosition()[1] == pos[1] \
                && _pieces[i].getColor() == _infos.getTurn() \
                && _pieces[i].isRemoved() == false) {
                    if (_infos.isAlreadyCheck(_infos.getTurn())) {
                        moves = _referee.computePossibleMovesInCheck(_pieces, 
                        _pieces[i].computeMoves(), pos, _infos.getTurn());
                    }
                    else {
                        moves = _referee.computePossibleMoves(_pieces, _pieces[i].computeMoves(), pos);
                    }
                _infos.printMoves("Possible moves: ", moves);
                break;
            }
        }
        if (moves.size() == 0) {
            std::cout << "No possible move for this piece." << std::endl;
            continue;
        }
        // Decision making : Change piece or move piece
        if(makeDecision() == false)
            continue;
        else
            movePiece(pos, moves);
        break;
    }
}


std::vector<int> Game::selectPiece()
{
    std::string input;
    std::vector<int> pos;

    while(true) {
        std::cout << "Select a piece position: ";
        std::cin >> input;
        pos = getSelectedPosition(input);
        if(pos[0] != -1) {
            break;
        }
    }
    return (pos);
}

std::vector<int > Game::getSelectedPosition(std::string input)
{
    std::vector<int> pos;

    if (input.size() > 2 || input.size() < 2 ) {
        pos.push_back(-1);
        std::cout << "Bad position." << std::endl;
        return (pos);
    }
    //ADD ERROR HANDLING
    pos.push_back(_columnMap[input.substr(0, 1)]);
    pos.push_back(_rowMap[input.substr(1, 1)]);
    return (pos);
}

bool Game::makeDecision()
{
    std::string input;

    std::cout << "What to do ? :" << std::endl;
    std::cout << "\t- 1: Move selected piece." << std::endl;
    std::cout << "\t- 2: Select another piece." << std::endl;
    while (true) {
        std::cout << "> ";
        std::cin >> input;
        if (input == "1") {
            return (true);
        }
        else if (input == "2") {
            return (false);
        }
        else
            std::cout << "Bad input. Type 1 or 2" << std::endl;
    }
}

void Game::movePiece(std::vector<int> pos, std::vector<std::vector<int>> moves)
{
    std::string input;
    std::vector<int> newPos;

    if (_pieces[_referee.getIndexByPositions(pos)].getType() == King && checkCastling())
        return;
    while(true) {
        std::cout << "New position ?: ";
        std::cin >> input;
        newPos = getSelectedPosition(input);
        if (_referee.isMoveIsInPossibleMoves(newPos, moves))
            break;
        else
            std::cout << "This move is not possible. Try again." << std::endl;
    }
    if (_referee.getIndexByPositions(newPos) != (size_t)-1)
        _pieces[_referee.getIndexByPositions(newPos)].setPosition(-1, -1);
    _pieces[_referee.getIndexByPositions(pos)].setFirstMoveStatement(false);
    _pieces[_referee.getIndexByPositions(pos)].setPosition(newPos[1], newPos[0]);
    _infos.updateBoard(pos, newPos);
    checkPromotion(newPos);
    isCheck(newPos);
}

void Game::checkPromotion(std::vector<int> pos)
{
    std::string input;
    size_t index = _referee.getIndexByPositions(_pieces, pos);
    Color color = _pieces[index].getColor();

    if (_pieces[index].getType() == Pawn) {
        if (pos[1] == 0 || pos[1] == 7) {
            std::cout << "Promotion !" << std::endl;
            std::cout << "Which piece would you like ?" << std::endl;
            while (true) {
                std::cout << "\t1: Queen" << std::endl;
                std::cout << "\t2: Rook" << std::endl;
                std::cout << "\t3: Bishop" << std::endl;
                std::cout << "\t4: Knight" << std::endl;
                std::cout << "> ";
                std::cin >> input;
                if (input == "1" || input == "2" || input == "3" || input == "4")
                    break;
            }
        }
        if (input == "1") {
            _pieces[index].setType(Queen);
            _infos.changePieceTypeOnBoard(pos, 'Q', color);
        }
        else if (input == "2") {
            _pieces[index].setType(Rook);
            _infos.changePieceTypeOnBoard(pos, 'R', color);
        }
        else if (input == "3") {
            _pieces[index].setType(Bishop);
            _infos.changePieceTypeOnBoard(pos, 'B', color);
        }
        else if (input == "4") {
            _pieces[index].setType(Knight);
            _infos.changePieceTypeOnBoard(pos, 'N', color);
        }
    }
}

bool Game::canCastling()
{
    Color color = _infos.getTurn();
    if (_referee.canKingsideCastling(color))
        return (true);
    if (_referee.canQueensideCastling(color))
        return (true);
    return (false);
}

bool Game::checkCastling()
{
    std::string input;

    if (canCastling()) {
        std::cout << "1: Classic Move" << std::endl;
        std::cout << "2: Castling" << std::endl;
        while (true) {
            std::cout << "> ";
            std::cin >> input;
            if (input != "1" && input != "2") {
                std::cout << "Bad input : type 1 or 2";
                continue;
            }
            break;
        }
        if (input == "2") {
            std::cout << "In which side would you do castling ?:" << std::endl;
            if (_referee.canKingsideCastling(_infos.getTurn()))
                std::cout << "\t- 1 : Kingside" << std::endl;
            if (_referee.canQueensideCastling(_infos.getTurn()))
                std::cout << "\t- 2 : Queenside" << std::endl;
            while (true) {
                std::cout << "> ";
                std::cin >> input;
                if (input != "1" && input != "2") {
                    std::cout << "Bad Input : Retry" << std::endl;
                    continue;
                }
                if (input == "1" && _referee.canKingsideCastling(_infos.getTurn()) == false) {
                    std::cout << "You can't do Kingside Castling" << std::endl;
                    continue;
                }
                else if (input == "2" && _referee.canQueensideCastling(_infos.getTurn()) == false) {
                    std::cout << "You can't do Queenside Castling" << std::endl;
                    continue;
                }
                break;
            }
            if (input == "1")
                doCastling(true);
            else
                doCastling(false);
            return (true);
        }
    }
    return (false);
}

void Game::doCastling(bool isKingside)
{
    size_t kingIndex, rookIndex;

    kingIndex = _referee.getIndexByTypeAndColor(King, _infos.getTurn());
    if (isKingside == true) {
        rookIndex = _referee.getIndexByPositions({_pieces[kingIndex].getPosition()[0] + 3, _pieces[kingIndex].getPosition()[1]});
        _pieces[kingIndex].setPosition(_pieces[kingIndex].getPosition()[1], _pieces[kingIndex].getPosition()[0] + 2);
        _pieces[rookIndex].setPosition(_pieces[rookIndex].getPosition()[1], _pieces[rookIndex].getPosition()[0] - 2);
        _infos.updateBoard({_pieces[kingIndex].getPosition()[0] - 2, _pieces[kingIndex].getPosition()[1]}, _pieces[kingIndex].getPosition());
        _infos.updateBoard({_pieces[rookIndex].getPosition()[0] + 2, _pieces[rookIndex].getPosition()[1]}, _pieces[rookIndex].getPosition());
    }
    if (isKingside == false) {
        rookIndex = _referee.getIndexByPositions({_pieces[kingIndex].getPosition()[0] - 4, _pieces[kingIndex].getPosition()[1]});
        _pieces[kingIndex].setPosition(_pieces[kingIndex].getPosition()[1], _pieces[kingIndex].getPosition()[0] - 2);
        _pieces[rookIndex].setPosition(_pieces[rookIndex].getPosition()[1], _pieces[rookIndex].getPosition()[0] + 3);
        _infos.updateBoard({_pieces[kingIndex].getPosition()[0] + 2, _pieces[kingIndex].getPosition()[1]}, _pieces[kingIndex].getPosition());
        _infos.updateBoard({_pieces[rookIndex].getPosition()[0] - 3, _pieces[rookIndex].getPosition()[1]}, _pieces[rookIndex].getPosition());
    }
    isCheck(_pieces[rookIndex].getPosition());
}

bool Game::isCheck(std::vector<int> newPos)
{
    std::vector<int> kingPos;
    Color color = _infos.getTurn();
    std::vector<std::vector<int>> nextMoves;

    if (color == White)
        color = Black;
    else
        color = White;

    kingPos = _pieces[_referee.getIndexByTypeAndColor(King, color)].getPosition();
    nextMoves = _referee.computePossibleMoves(_pieces,\
     _pieces[_referee.getIndexByPositions(_pieces, newPos)].computeMoves(), newPos);
    if(std::find(nextMoves.begin(), nextMoves.end(), kingPos) != nextMoves.end()) {
        std::cout << "Check !" << std::endl;
        _infos.setCheck(color, true);
        return (true);
    }
    else { 
        _infos.setCheck(color, false);
        return(false);
    }
}

bool Game::isMate(Color color)
{
    std::vector<std::vector<int>> moves;
    bool isCheck;

    if (color==White)
        color = Black;
    else
        color = White;

    isCheck = _infos.isAlreadyCheck(color);
    if (isCheck)
        moves = _referee.computeAllPossibleMoves(_pieces, color, true);
    else
        moves = _referee.computeAllPossibleMoves(_pieces, color, false);
    if (moves.size() == 0) {
        _infos.printEnd(color);
        _infos.printBoard();
        return (true);
    }
    return (false);
}