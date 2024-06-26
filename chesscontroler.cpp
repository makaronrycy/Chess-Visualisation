#include "chesscontroler.h"
#include "qtimer.h"


ChessControler::ChessControler(QObject *parent)
    :QObject{parent}
{

}




int ChessControler::parseX(QString x)
{
    return(8 - x.toInt());

}

int ChessControler::parseY(QString y)
{
    int yR;
    if(y == "a") yR = 0;
    else if(y == "b") yR = 1;
    else if(y == "c") yR = 2;
    else if(y == "d") yR = 3;
    else if(y == "e") yR = 4;
    else if(y == "f") yR = 5;
    else if(y == "g") yR = 6;
    else  yR = 7;
    return yR;

}
bool ChessControler::checkValidDiag(int src_x, int src_y, int dest_x, int dest_y)
{
    int distance_x = abs(src_x-dest_x);
    int i_y,i_x;
    if(src_y < dest_y) i_y = 1;
    else i_y = -1;
    if(src_x < dest_x) i_x = 1;
    else i_x = -1;

    for(int i = 1; i<distance_x;i++){
        chess_piece *temp = board[src_x+i*i_x][src_y+i*i_y];
        qDebug();
        if(temp != nullptr){
            return false;
        }
    }
    return true;
}

bool ChessControler::checkValidCard(int src_x, int src_y, int dest_x, int dest_y)
{
    int distance_x = abs(src_x-dest_x);
    int distance_y = abs(src_y-dest_y);
    int i_y,i_x;
    if(src_y < dest_y) i_y = 1;
    else i_y = -1;
    if(src_x < dest_x) i_x = 1;
    else i_x = -1;
    if(distance_x == 0){
        for(int i = 1; i< distance_y; i++){
            chess_piece *temp = board[src_x][src_y+i*i_y];
            if(temp != nullptr) {
                return false;
            }
        }
    }
    if(distance_y == 0){
        for(int i = 1; i< distance_x; i++){
            chess_piece *temp = board[src_x+i*i_x][src_y];
            if(temp != nullptr){
                return false;
            }
        }
    }
    return true;
}
bool ChessControler::validMove(QString piece ,int row, int col, int dest_row, int dest_col)
{

    //pawn
    if(piece == "w" || piece == "b"){
        //if (col == dest_col && board[dest_row][dest_col] == nullptr && ((piece == 'w' && dest_row < row) || (piece == 'b' && dest_row > row))) return true;
        if(col == dest_col && board[dest_row][dest_col] == nullptr && ((piece == "w" && (dest_row+1 == row ||(dest_row+2 == row && row == 6))) || (piece == "b" && (dest_row-1 == row ||(dest_row-2 == row && row == 1))))) return true;
        if(abs(col - dest_col) == 1 && board[dest_row][dest_col] != nullptr && ((piece == "w" && dest_row+1 == row)|| (piece == "b" && dest_row -1 == row))) return true;
    }
    //Knight
    else if(piece.contains("N")){
        if((abs(row - dest_row) == 1 ||abs(row - dest_row) == 2) && (abs(col - dest_col) == 1 || abs(col-dest_col) == 2)) return true;
    }
    //Rook
    else if(piece.contains("R")){
        if((row == dest_row || col == dest_col) && checkValidCard(row,col,dest_row,dest_col)) return true;
    }
    //Bishop
    else if(piece.contains("B")){
        if(abs(row-dest_row) == abs(col - dest_col) && checkValidDiag(row,col,dest_row,dest_col)) return true;
    }
    //Queen
    else if(piece.contains("Q")){
        if(row == dest_row || col == dest_col || abs(row-dest_row) == abs(col - dest_col) && checkValidDiag(row,col,dest_row,dest_col) && checkValidCard(row,col,dest_row,dest_col)) return true;
    }
    //King
    else if(piece.contains("K")){
        if(abs(row- dest_row)<=1 && abs(col -dest_col) <=1) return true;
    }
    return false;
}

void ChessControler::init()
{
    //new game if elements already initialized
    if(!pieces.isEmpty()) pieces.clear();

    if(board != nullptr){
        for(int i = 0; i< 8; i++){

            for(int j = 0; j < 8; ++j){
                delete board[i][j];
            }
            delete[] board[i];
        }
        delete[] board;
    }

    turn = 0;
    white_move = true;
    //init board
    board = new chess_piece**[8];
    for(int i = 0; i< 8; i++){
        board[i] = new chess_piece*[8];
        for(int j = 0; j < 8; ++j){
            board[i][j] = nullptr;
        }
    }
    pieces.resize(32);
    //Init chess pieces and starting location
    for(int color = 0; color<2;color++){
        int start,dir;
        bool black;
        QString suffix;
        if(color == 0){
            //generating white pieces
            //pawns
            start = 6;
            suffix = "w";
            dir = 1;
            black = false;

        }else{
            start = 1;
            suffix = "b";
            dir = -1;
            black = true;
        }
        for(int piece = 1; piece <=8; piece++){
            int x = start + dir;
            int y = piece - 1 ;
            QString id = suffix+QString::number(piece);
            //pawns
            chess_piece *pawn = new chess_piece(start,y,id,black);
            //rook
            if(piece == 1 || piece ==8){
                id = suffix +"R"+ QString::number(int(y/4)+1);
            }
            //Knight
            else if(piece == 2 || piece == 7){
                id = suffix +"N"+ QString::number(int(y/4)+1);
            }
            //Bishop
            else if(piece == 3 || piece == 6){
                id = suffix +"B"+ QString::number(int(y/4)+1);
            }
            //Queen
            else if(piece == 4){
                id = suffix +"Q";
            }
            //King
            else if(piece == 5){
                id = suffix +"K";
            }
            chess_piece *specialPiece = new chess_piece(x,y,id,black);
            pieces[pawn->global_index]= pawn;
            pieces[specialPiece->global_index] = specialPiece;

        }

    }
    emit initFinished();
    for(int i = 0; i<32; i++){
        chess_piece *piece = pieces[i];
        board[piece->location[0]][piece->location[1]] = piece;
        changeLocation(piece,piece->location[0],piece->location[1]);
    }

}

void ChessControler::loadGame(QList<QStringList> moves)
{

    nr_turns = moves.length();
    //restart chess if a game is already loaded;
    if(!loaded_game.isEmpty()){
        init();
    }
    loaded_game.resize(nr_turns);
    for(int i = 0; i<nr_turns;i++){
        loaded_game[i].resize(2);
        loaded_game[i][0] = moves[i][0];
        loaded_game[i][1] = moves[i][1];
    }
}

void ChessControler::game()
{
    if(turn >= nr_turns-1) return;
    int index_move = white_move ? 0 : 1;
    QString move = loaded_game[turn][index_move];
    QString move_locationX;
    QString move_locationY;
    QString piece_id = (index_move == 0)? "w" : "b";
    QString promotion_choice = "";
    chess_piece *selected_piece;
    bool check = false;
    bool checkmate = false;
    bool promote = false;
    bool cap = false;


    //emit move for view
    QVariantList emitted_move;
    emitted_move.append(turn);
    emitted_move.append(move);
    emit moveEmitted(emitted_move);

    //capture
    if(move.contains("x")) {
        move.remove("x");
        cap = true;
    }
    //castle king side
    if(move == "O-O"){
        chess_piece *Rook;
        chess_piece *King;
        //white: king to g1 rook to f1  black: king to g8 rook to f8

        int row = white_move ? 7 : 0;

        Rook = board[row][7];
        King = board[row][4];

        board[row][5] = Rook;
        board[row][6] = King;

        board[row][7] = nullptr;
        board[row][4] = nullptr;

        changeLocation(Rook,row,5);
        changeLocation(King,row,6);
        emit emitSound(false);
        changePlayer();
        return;

    }
    //castle queen side
    if(move.contains("O-O-O")){
        chess_piece *Rook;
        chess_piece *King;
        //white: king to c1 rook to d1  black: king to c8 rook to d8

        int row = white_move ? 7 : 0;

        Rook = board[row][0];
        King = board[row][4];

        board[row][3] = Rook;
        board[row][2] = King;

        board[row][0] = nullptr;
        board[row][4] = nullptr;

        changeLocation(Rook,row,3);
        changeLocation(King,row,2);
        emit emitSound(false);
        changePlayer();
        return;
    }
    //check
    if(move.contains("+")){
        move.remove("+");
        check = true;
    }
    //checkmate
    if(move.contains("#")){
        move.remove("#");
        checkmate = true;
    }
    //promotion
    if(move.contains("=")) {
        int i = move.indexOf('=');
        QString temp1 = move.sliced(i);
        promotion_choice = temp1[1];
        move.remove("=");
        move.remove(promotion_choice);

        promote = true;
    }

    //parse piece and slice piece identifier
    if(move[0].isUpper()){
        piece_id = move[0];
        move = move.sliced(1);
    }

    //parse destination and slice destination identifiers
    move_locationY = move.sliced(move.length()-2,1);
    move_locationX = move.sliced(move.length()-1,1);
    move=move.sliced(0,move.length()-2);


    int x_source = -1;
    int y_source = -1;
    int x_dest = parseX(move_locationX);
    int y_dest = parseY(move_locationY);
    //get source if exists
    if(move.length() == 2){

        y_source = parseY(move[0]);
        x_source = parseX(move[1]);
    }else if(move.length() == 1){
        if(move[0].isLetter()){
            y_source = parseY(move);
        }else{
            x_source = parseX(move);
        }
    }
    //search for piece (iterate only current color pieces)

    for(int i = 0 + 16*index_move; i < 16 +16*index_move; i++){
        chess_piece* temp_piece = pieces[i];
        //slice piece id
        QString t_piece_id = temp_piece->type;
        if(t_piece_id[1].isLetter() || t_piece_id.contains("K") || t_piece_id.contains("Q")){
            t_piece_id = t_piece_id.sliced(1);
        }

        if(!t_piece_id.contains(piece_id) || temp_piece->captured) continue;
        if(x_source != -1 && x_source != temp_piece->location[0]) continue;
        if(y_source != -1 && y_source !=temp_piece->location[1]) continue;
        if(validMove(piece_id,temp_piece->location[0],temp_piece->location[1],x_dest,y_dest)) {
            selected_piece = temp_piece;
        }
    }
    //resolve capture
    if(cap){
        chess_piece *captured_piece = board[x_dest][y_dest];
        captured_piece->captured = true;
        emit capture(captured_piece->global_index);

    }
    //resolve promotion
    if(promote){
        QChar suffix = white_move ? 'w':'b';
        selected_piece->type = suffix + promotion_choice;
        emit promotion({selected_piece->global_index,promotion_choice});
    }

    //update board
    board[x_dest][y_dest] = selected_piece;
    board[selected_piece->location[0]][selected_piece->location[1]] = nullptr;


    //update piece location

    changeLocation(selected_piece,x_dest,y_dest);

    changePlayer();
    if(cap || check || checkmate){
        emit emitSound(true);
    }
    else{
        emit emitSound(false);
    }




}

void ChessControler::changeLocation(chess_piece* selected_piece, int x, int y)
{
    selected_piece->updateLocation(x,y);
    QList<int> loc;
    loc.append(selected_piece->global_index);
    loc.append(selected_piece->global_location[0]);
    loc.append(selected_piece->global_location[1]);
    emit locationEmitted(loc);
}

void ChessControler::changePlayer()
{
    //next player or next turn
    if(white_move){
        white_move = false;
    }else{
        white_move = true;
        turn++;
    }
}




