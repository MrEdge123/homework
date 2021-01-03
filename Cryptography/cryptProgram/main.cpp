#include "widget.h"
#include "des.h"
#include "clib.h"
#include <QDebug>
#include <iostream>
#include <QApplication>
#include <QDataStream>
using namespace std;

void test() {
    /*
        qDebug() << CLIB::change_bit(5, 0);
        qDebug() << CLIB::select_random_num(64, 6);
        qDebug() << CLIB::cmp_bit(5, 4);
        qDebug() << CLIB::cmp_bit(5, 2);
        qDebug() << CLIB::cmp_bit(12, 10);
        DES des = DES();
        ULL msg = CLIB::generate_bit(64);
        ULL key = CLIB::generate_bit(64);
        ULL cpt1 = des.run(msg, key);
        msg = CLIB::change_bit(msg, 0);
        msg = CLIB::change_bit(msg, 1);
        ULL cpt2 = des.run(msg, key);
        qDebug() << CLIB::cmp_bit(cpt1, cpt2);

        cpt1 = des.run(msg, key);
        cpt2 = des.run(cpt1, key, -1);
        qDebug() << CLIB::cmp_bit(msg, cpt1);
    */

    //const UINT mod = 1e9 + 7;

    /*
        qDebug() << "2^10:" << CLIB::quick_pow(2, 10, mod) << endl;
        UINT inv1 = CLIB::inverse(2, mod);
        UINT inv2 = CLIB::quick_pow(2, mod-2, mod);
        if(inv1 == inv2 && (ULL)inv1 * 2 % mod == 1) qDebug() << "YES" << endl;
    */

    /*
        qDebug() << "25:" << (CLIB::is_prime(25) ? "prime" : "not prime") << endl;
        qDebug() << "47:" << (CLIB::is_prime(47) ? "prime" : "not prime") << endl;
        qDebug() << "49:" << (CLIB::is_prime(49) ? "prime" : "not prime") << endl;
        qDebug() << mod << ":" << (CLIB::is_prime(mod) ? "prime" : "not prime") << endl;
    */

    //qDebug() << "13:" << CLIB::prime_primitive_root(5) << endl;

    //qDebug() << CLIB::quick_pow((ULL)2, (ULL)10, (ULL)1e9);
    //qDebug() << CLIB::multi(4, 5, 10000);

    //QString in_path("C:/Users/user/Desktop/doc/crypt/in.txt");
    //QString out_path("C:/Users/user/Desktop/doc/crypt/out.txt");
    //QString out2_path("C:/Users/user/Desktop/doc/crypt/out2.txt");
    //ULL key = CLIB::generate_bit(64);

    //DES des(in_path, out_path, key, 1, 2);
    //DES des2(out_path, out2_path, key, 0, 2);
    //QFile file(in_path);
    //file.open(QIODevice::ReadOnly);
    //qDebug() << file.size();
    //file.close();
}


int main(int argc, char *argv[])
{
    srand(time(0));
    //test();
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("密码学算法演示");
    w.resize(800, 600);
    w.show();

    return a.exec();
}
