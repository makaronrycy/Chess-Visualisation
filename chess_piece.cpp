#include "chess_piece.h"

chess_piece::chess_piece(int x ,int y , QString pieceId, bool black)
{
    this->type = pieceId;
    this->black = black;
    if(pieceId == "0"){
        this->global_location.setX(x);
        this->global_location.setY(y);

        this->location[0] = -1;
        this->location[1] = -1;
        return;
    }
    this->captured = false;
    int offsetX = 30;
    int offsetY = 30;
    int mirror;
    QString sliced_type = type.sliced(1);
    if(black){
        mirror = -1;

    }else{
        mirror = 1;
    }
    //pawns
    int color = black ? 1:0;
    if(sliced_type.length() == 1 && sliced_type!= "K" && sliced_type!= "Q" ){
        if(black){
            offsetX = -180+60*y - offsetX;
        }else{
            offsetX += -240+60*y;
        }
        offsetY +=120;
        this->global_index = y+color*16;

    }else{
        this->global_index = y+color*16+8;
        offsetY += 180;
    }

    if(sliced_type.contains("Q")) offsetX -= 60;
    if(sliced_type.contains("B2")) offsetX += 60;
    if(sliced_type.contains("N2")) offsetX += 120;
    if(sliced_type.contains("R2")) offsetX += 180;
    if(sliced_type.contains("B1")) offsetX -= 120;
    if(sliced_type.contains("N1")) offsetX -= 180;
    if(sliced_type.contains("R1")) offsetX -= 240;

    this->global_location.setX(offsetX);
    this->global_location.setY(offsetY*mirror);

    this->location[0] = x;
    this->location[1] = y;


    qDebug()<<type<<" "<< global_location[0]<< " "<< global_location[1]<<" "<<global_index;
}

void chess_piece::updateLocation(int new_x, int new_y)
{
    int x_mov = (location[0] - new_x)*60;
    int y_mov = (location[1] - new_y)*60;

    global_location.setX(global_location.x()-y_mov);
    global_location.setY(global_location.y()-x_mov);
    location[0] = new_x;
    location[1] = new_y;
}
