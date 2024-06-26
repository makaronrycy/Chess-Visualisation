#ifndef FILELOADER_H
#define FILELOADER_H

#include <QObject>
#include <QtQml>
#include <QFile>
#include <QUrl>
#include <QString>
#include <QIODevice>
#include <QTextStream>
#include <QDebug>
class FileLoader : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit FileLoader(QObject *parent = nullptr);
public slots:
    Q_INVOKABLE void loadFile(QString fileUrl);
signals:
    void tagsEmitted(QString FileData);
    void movesEmitted(QString FileData);

};

#endif // FILELOADER_H
