#include "xor.h"
#include <stdio.h>
#include <string.h>
#include <QDebug>
#include <QIODevice>
#include <QDataStream>

XOR::XOR()
{

}

bool XOR::encrypt(QString src_path, QString dst_path, const char *key)
{
    QFile src_file(src_path);
    QFile dst_file(dst_path);

    src_file.open(QIODevice::ReadOnly);
    dst_file.open(QIODevice::WriteOnly);

    QDataStream input(&src_file);
    QDataStream output(&dst_file);

    int n = strlen(key);
    int pos = 0;

    //int cnt = 0;

    char ch;
    int len;
    while(1) {
        len = input.readRawData(&ch, 1);
        if(len == 0) break;

        ch = ch ^ key[pos];
        output.writeRawData(&ch, 1);
        pos = (pos + 1) % n;

        //cnt++;
    }

    //qDebug() << "byte:" << cnt << endl;

    src_file.close();
    dst_file.close();

    return true;
}
