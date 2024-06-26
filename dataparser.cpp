#include "dataparser.h"

DataParser::DataParser(QObject *parent)
    : QObject{parent}
{
    moveList.resize(5);
    for(int i = 0;i<5;i++) {
        moveList[i].resize(2);
    }
}

void DataParser::pTagRoster(QString roster)
{
    //0 - Event 1 - Date 2 - Result 3 - White  4 - Black
    QMap<QString,QString> tags;
    tags["Event"];
    tags["Date"];
    tags["White"];
    tags["Black"];
    tags["Result"];
    for (auto line : QStringTokenizer{roster, u'\n'}){
        int i =0;
        QString key;
        for (auto tag : QStringTokenizer{line, u'\"'}){
            i++;
            if(i == 3 )continue;
            if(i == 1 && tag.length() > 0){
                tag = tag.sliced(1);
                if(tag.length() > 1) tag = tag.sliced(0, tag.length()-1);
                if(tags.keys().contains(tag)) key = tag.toString();
                continue;
            }
            if(!key.isEmpty()){
                tags[key] = tag.toString();
            }
            //if(i == 3 || i ==1) continue;
        }
    }
    QStringList selected_tags;
    selected_tags.append(tags["Event"]);
    selected_tags.append(tags["Date"]);
    selected_tags.append(tags["Result"]);
    selected_tags.append(tags["White"]);
    selected_tags.append(tags["Black"]);
    emit parsedTagRoster(selected_tags);
}

QList<QStringList> DataParser::pMoveText(QString moves)
{
    moveList.clear();
    int turn = 0;
    int nmove = 0;
    int index = 0;
    for (auto line : QStringTokenizer{moves, u'\n'}){

        for (auto move : QStringTokenizer{line, u' '}){
            //skip file index
            if(index%3 ==0){
                if(index!=0){
                    turn++;
                    nmove = 0;
                }
                index++;
                continue;
            }
            if(moveList.size()<=turn){
                moveList.resize(turn+1);
                moveList[turn].resize(2);
            }
            moveList[turn][nmove].append(move);
            index++;
            nmove++;
        }
    }

    //placeholder

    return moveList;
}
