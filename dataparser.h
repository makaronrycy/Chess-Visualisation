#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>
#include <QQmlEngine>
#include <QRegularExpression>

class DataParser : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit DataParser(QObject *parent = nullptr);
    //tag pairs
    QString event;
    QString site;
    QString date;
    QString round;
    QString white;
    QString black;
    QString result;

    QList<QStringList> moveList;

public slots:

    void pTagRoster(QString roster);
    QList<QStringList> pMoveText(QString moves);
private:

signals:
    void parsedTagRoster(QStringList tags);
    void parsedMoveText(QString moves);
};

#endif // DATAPARSER_H
