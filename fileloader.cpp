#include "fileloader.h"

FileLoader::FileLoader(QObject *parent)
    : QObject{parent}
{}
void FileLoader::loadFile(QString fileUrl){
    QFile file(fileUrl);
    if(!file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        return;
    }
    QString tag_data;
    QString move_data;
    bool read_tag = true;
    QTextStream stream(&file);
    while(!stream.atEnd()){
        QString data =stream.readLine();
        if(data == "" && read_tag == true){
            read_tag = false;
            continue;
        }
        if(read_tag){
            tag_data+= data+'\n';
        }else{
            move_data+=data+'\n';
        }
    }
    file.close();
    emit movesEmitted(move_data);
    emit tagsEmitted(tag_data);
}


