#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <QString>
#include <QVector3D>
#include <QDebug>
class chess_piece
{
public:
    chess_piece(int x,int y, QString pieceId = "0", bool black = "w");
    void updateLocation(int new_x, int new_y);
    int location[2];
    QVector3D global_location;
    bool black;
    QString type;
    bool captured = false;
    int global_index;
};

#endif // CHESS_PIECE_H
