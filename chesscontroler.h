#ifndef CHESSCONTROLER_H
#define CHESSCONTROLER_H
#include <chess_piece.h>
#include <QObject>
#include <QQmlEngine>
#include <QDebug>
#include <QtMath>
class ChessControler : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit ChessControler(QObject *parent = nullptr);

    chess_piece ***board = nullptr;
    QList<chess_piece*> pieces;
    QList<QStringList>loaded_game;
private:
    void new_game();
    int parseX(QString x);
    int parseY(QString y);
    bool validMove(QString piece, int row, int col, int dest_row,int dest_col);
    void changeLocation(chess_piece* selected_piece, int x, int y);
    void changePlayer();
    bool checkValidDiag(int src_x,int src_y, int dest_x,int dest_y);
    bool checkValidCard(int src_x,int src_y, int dest_x,int dest_y);

    int turn;
    int nr_turns;
    bool white_move;
public slots:

    Q_INVOKABLE void init();
    Q_INVOKABLE void game();
    Q_INVOKABLE void loadGame(QList<QStringList> moves);
signals:
    void emitSound(bool capture_sound);
    void moveEmitted(QVariantList move);
    void promotion(QVariantList promote);
    void capture(int i);
    void initFinished();
    void locationEmitted(QList<int> location);
};

#endif // CHESSCONTROLER_H
