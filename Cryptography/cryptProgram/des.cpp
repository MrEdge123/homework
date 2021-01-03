#include "des.h"

DES::DES() {

}

//mod=-1: 解密
DES::DES(ULL msg, ULL key, int mod)
{
    this->msg = msg;
    this->key = key;
    generate_subkey();   //生成子密钥
    if(mod == -1) reverse(subkey, subkey + 16);  //反转密钥顺序
    run();   //开始加密/解密
}

DES::DES(QString src_path, QString dst_path, ULL key, bool is_encrypt, int deal_short_mode)
{
    this->key = key;
    generate_subkey();
    if(is_encrypt == 0) reverse(subkey, subkey + 16);

    QFile src_file(src_path);
    QFile dst_file(dst_path);

    if(src_file.exists() == false) return;

    src_file.open(QIODevice::ReadOnly);
    dst_file.open(QIODevice::WriteOnly);

    QDataStream input(&src_file);
    QDataStream output(&dst_file);

    switch (deal_short_mode) {
    case 1:    //短块填充, 直接填0
        if(is_encrypt) {    //加密
            char in_buf[10], out_buf[10];
            while(1) {
                int len = input.readRawData(in_buf, 8);

                if(len < 8) {    //短块
                    ULL msg = 0;
                    msg = CLIB::read_buf_to_ULL(in_buf, len);

                    //添加短块
                    this->msg = msg;
                    run();
                    CLIB::write_ULL_to_buf(this->ans_msg, out_buf);
                    output.writeRawData(out_buf, 8);

                    //末尾添加短块长度
                    //this->msg = len;
                    //run();
                    out_buf[0] = len;
                    output.writeRawData(out_buf, 1);

                    //结束循环
                    break;
                }

                //普通块
                ULL msg = CLIB::read_buf_to_ULL(in_buf);
                this->msg = msg;
                run();    //DES加密
                CLIB::write_ULL_to_buf(this->ans_msg, out_buf);

                //qDebug() << "msg1:" << this->ans_msg;
                //qDebug() << "msg2:" << CLIB::read_buf_to_ULL(out_buf);

                output.writeRawData(out_buf, 8);
            }
        }
        else{    //解密
            char in_buf[10], out_buf[10];
            int len = input.readRawData(in_buf, 8);
            if(len != 8) break;

            //解密last
            ULL last = CLIB::read_buf_to_ULL(in_buf);
            this->msg = last;
            run();
            last = this->ans_msg;

            while(1) {
                len = input.readRawData(in_buf, 8);

                //解密now
                ULL now = CLIB::read_buf_to_ULL(in_buf);
                this->msg = now;
                run();
                now = this->ans_msg;

                //当前now为末尾
                if(input.atEnd()) {
                    len = in_buf[0];
                    if(len == 0) break;

                    //qDebug() << "len:" << len << endl;
                    CLIB::write_ULL_to_buf(last, out_buf, len);
                    output.writeRawData(out_buf, len);
                    break;
                }

                //写入last
                CLIB::write_ULL_to_buf(last, out_buf);
                output.writeRawData(out_buf, 8);

                //更新last
                last = now;
            }
        }
        break;
    case 2:    //密文挪用
        if(is_encrypt) {    //加密
            //空文件
            if(!src_file.size()) break;

            char in_buf[10], out_buf[10];

            ULL last = 0;
            this->msg = last;
            run();
            last = this->ans_msg;

            ULL last_encrypt = last;

            bool flag = false;  //false代表需要用到初始向量

            while(1) {
                int len = input.readRawData(in_buf, 8);

                if(len < 8) {
                    //一般情况
                    if(len) {
                        int cut_len = 8 - len;
                        ULL short_part = CLIB::read_buf_to_ULL(in_buf, len);          //短块
                        ULL cut_part = last_encrypt % (1ull << (8 * cut_len));        //补充块
                        ULL left_part = last_encrypt ^ cut_part;                      //剩下的块

                        //待加密的完整块
                        ULL now_part = (cut_part << (8 * len)) | short_part;

                        //加密
                        this->msg = now_part;
                        run();
                        now_part = this->ans_msg;

                        if(flag) {
                            //写入剩余块
                            CLIB::write_ULL_to_buf(left_part >> (8 * cut_len), out_buf, len);
                            output.writeRawData(out_buf, len);
                        }

                        //写入一整块
                        CLIB::write_ULL_to_buf(now_part, out_buf);
                        output.writeRawData(out_buf, 8);
                    }
                    //不可能存在该情况
                    else if(!flag && !len) {
                        qDebug() << "error" << endl;
                        break;
                    }
                    //完整的块
                    else if(!len && flag) {
                        //写入上一块
                        CLIB::write_ULL_to_buf(last_encrypt, out_buf);
                        output.writeRawData(out_buf, 8);
                    }

                    //结尾标志, 占1字节
                    int end_flag = (len << 1) | flag;
                    CLIB::write_ULL_to_buf(end_flag, out_buf, 1);
                    output.writeRawData(out_buf, 1);

                    break;
                }

                //写入上一次的加密块
                if(flag == false) {
                    flag = true;
                }
                else {
                    CLIB::write_ULL_to_buf(last_encrypt, out_buf);
                    output.writeRawData(out_buf, 8);
                }

                //普通块加密
                last = CLIB::read_buf_to_ULL(in_buf);
                this->msg = last;
                run();
                last_encrypt = this->ans_msg;
            }
        }
        else {    //解密
            //空文件
            if(!src_file.size()) break;

            char in_buf[10], out_buf[10];

            ULL last = 0;
            ULL last_decrypt = 0;

            bool flag = false;

            while(1) {
                int len = input.readRawData(in_buf, 8);

                if(input.atEnd()) {
                    //取标志
                    int end_flag = in_buf[len - 1];
                    flag = end_flag & 1;
                    len = end_flag >> 1;

                    //此时last未解密
                    if(len) {
                        ULL cut_part, left_part, short_part, now_part;
                        int cut_len = 8 - len;

                        //还原组合
                        //last作为挪用块
                        if(flag) {
                            short_part = CLIB::read_buf_to_ULL(in_buf, len);
                            cut_part = last % (1ull << (8 * cut_len));
                            left_part = last ^ cut_part;
                            now_part = (cut_part << (8 * len)) | short_part;
                        }
                        //初始向量作为挪用块
                        else {
                            now_part = last;
                        }

                        //解密
                        this->msg = now_part;
                        run();
                        now_part = this->ans_msg;

                        //还原
                        short_part = now_part % (1ull << (8 * len));
                        if(flag) {
                            cut_part = (now_part ^ short_part) >> (8 * len);
                            last = left_part | cut_part;
                        }

                        //写入上一块
                        if(flag) {
                            //解密上一块
                            this->msg = last;
                            run();
                            last = this->ans_msg;

                            //写入上一块
                            CLIB::write_ULL_to_buf(last, out_buf);
                            output.writeRawData(out_buf, 8);
                        }

                        //写入短块
                        CLIB::write_ULL_to_buf(short_part, out_buf, len);
                        output.writeRawData(out_buf, len);
                    }
                    //不可能存在该情况
                    else if(!flag && !len) {
                        qDebug() << "error" << endl;
                        break;
                    }
                    //完整的块
                    else if(!len && flag) {
                        //写入上一块
                        CLIB::write_ULL_to_buf(last_decrypt, out_buf);
                        output.writeRawData(out_buf, 8);
                    }

                    break;
                }

                if(flag == false) {
                    flag = true;
                }
                else {
                    CLIB::write_ULL_to_buf(last_decrypt, out_buf);
                    output.writeRawData(out_buf, 8);
                }

                //普通块解密
                last = CLIB::read_buf_to_ULL(in_buf);
                this->msg = last;
                run();
                last_decrypt = this->ans_msg;
            }
        }
        break;
    case 3:    //序列密码:用密钥的len*8位进行异或加密
        char in_buf[10], out_buf[10];
        while(1) {
            int len = input.readRawData(in_buf, 8);

            if(len < 8) {
                if(len == 0) break;

                ULL tmp_key = key;
                for(int i = 0; i < len; i++) {
                    char t = tmp_key % (1 << 8);
                    out_buf[i] = in_buf[i] ^ t;
                    tmp_key >>= 8;
                }

                output.writeRawData(out_buf, len);
                break;
            }

            //普通块加密/解密
            ULL msg = CLIB::read_buf_to_ULL(in_buf);
            this->msg = msg;
            run();    //DES加密/解密
            CLIB::write_ULL_to_buf(this->ans_msg, out_buf);
            output.writeRawData(out_buf, 8);
        }
        break;
    default:
        break;
    }

    src_file.close();
    dst_file.close();
}

//mod=-1: 解密
ULL DES::run(ULL msg, ULL key, int mod)
{
    this->msg = msg;
    this->key = key;
    generate_subkey();   //生成子密钥
    if(mod == -1) reverse(subkey, subkey + 16);  //反转密钥顺序
    run();   //开始加密/解密
    return get_ans_msg();
}

ULL DES::generate_64bit()
{
    ULL key = 0;
    for(int i = 0; i < 64; i++) {
        key = (key << 1) + rand() % 2;
    }
    return key;
}

ULL DES::get_ans_msg()
{
    return this->ans_msg;
}

UINT DES::Once_SBox(int S[][16], UINT msg)
{
    UINT row = (get_bit(msg, 5) << 1) + get_bit(msg, 0);  //行
    UINT col = 0;                                         //列
    for(int pos = 1; pos <= 4; pos++)
        col += get_bit(msg, pos) << (pos - 1);

    return S[row][col];
}

UINT DES::Once_SBox(int S_num, UINT msg)
{
    return Once_SBox(S[S_num], msg);
}

ULL DES::get_bit(ULL num, int pos)
{
    return (num >> pos) & 1;
}

ULL DES::set_position(ULL num, int p[], int len_p)
{
    ULL ans = 0;
    for(int i = 0; i < len_p; i++) {
        ans += get_bit(num, p[i] - 1) << i;
    }
    return ans;
}

ULL DES::SBox_transform(ULL msg)
{
    ULL ans = 0;
    for(int i = 0; i < 8; i++) {
        ans = (ans << 6) + Once_SBox(i, msg);
        msg >>= 6;
    }
    return ans;
}

void DES::generate_subkey()
{
    UINT C, D;
    C = set_position(key, P1C, 28);
    D = set_position(key, P1D, 28);

    for(int i = 0; i < 16; i++) {
        C <<= SHF_BIT[i];
        D <<= SHF_BIT[i];
        ULL merge = ((ULL)C << 28) + D;
        subkey[i] = set_position(merge, P2, 48);
    }
}

UINT DES::encrypt_function(UINT right, ULL key)
{
    ULL t = set_position(right, E, 48);
    t ^= key;

    ULL ans = SBox_transform(t);
    ans = set_position(ans, P, 32);
    return ans;
}

void DES::run()
{
    ULL t = set_position(msg, IP, 64);   //对原密文进行置换

    UINT L, R;
    L = t >> 32;           //左半部分
    R = t % (1ull << 32);  //右半部分

    //16次迭代过程
    for(int i = 0; i < 16; i++) {
        UINT F = encrypt_function(R, subkey[i]);  //加密函数

        UINT nextL = R;
        UINT nextR = L ^ F;

        L = nextL;
        R = nextR;
    }
    swap(L, R);   //最后一定要记得交换

    t = ((ULL)L << 32) + R;

    ans_msg = set_position(t, RIP, 64);   //最后再进行逆置换
}
