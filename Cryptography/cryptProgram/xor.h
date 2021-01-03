#ifndef XOR_H
#define XOR_H
#include <QFile>
#include <QString>
using namespace std;

class XOR
{
public:
    XOR();

    static bool encrypt(QString src_path,
                        QString dst_path,
                        const char *key);
};

#endif // XOR_H
