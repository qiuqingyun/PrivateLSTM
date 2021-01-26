#include "share.h"

void shareGen()
{
    start = time(nullptr);
    //指定文件路径=MAX(FREQUENCY(IF(B2:RM2=0,COLUMN(B2:RM2)),IF(B2:RM2<>0,COLUMN(B2:RM2))))
    string p[5] = {"input/data/center0.csv", "input/data/center1.csv", "input/data/center2.csv", "input/data/center3.csv", "input/data/center4.csv"};
    string fileName1[5] = {"input/data/SERVER_0.dat", "input/data/SERVER_1.dat", "input/data/SERVER_2.dat", "input/data/SERVER_3.dat", "input/data/SERVER_4.dat"};
    string fileName2[5] = {"input/data/CLIENT_0.dat", "input/data/CLIENT_1.dat", "input/data/CLIENT_2.dat", "input/data/CLIENT_3.dat", "input/data/CLIENT_4.dat"};

    for (int k = shareStart; k < shareEnd; k++)
    {
        ifstream _csvInput;
        _csvInput.open(p[k], ios::in);
        //定义一行数据为字符串
        string _Oneline;
        ofstream outfile1, outfile2;
        outfile1.open(fileName1[k], ios::out | ios::trunc);
        outfile2.open(fileName2[k], ios::out | ios::trunc);
        mpf_class x_f;
        mpz_class x_z;
        mpz_class server, client;
        int index = 0;
        vector<string> plaintext;
        while (getline(_csvInput, _Oneline))
            plaintext.push_back(_Oneline);
        string ciphertext[2][plaintext.size()];
        for (int p = 0; p < plaintext.size(); p++)
        {
            //定义字符串流对象
            istringstream _Readstr(plaintext[p]);
            string serverStr, clientStr;
            //一个人有480个数据点
            for (int r = 0; r < 480; r++)
            {
                //定义一行数据中的各个字串
                string _partOfstr;
                getline(_Readstr, _partOfstr, ',');
                x_f = stof(_partOfstr); //数据点
                mpf_mul_2exp(x_f.get_mpf_t(), x_f.get_mpf_t(), eAndC);
                server = randNumGen();
                x_z = x_f;
                client = x_z + modNum - server;
                serverStr += server.get_str();
                clientStr += client.get_str();
                int time = r % 48;
                int day = (r + 4) % 7;
                //将一行数据按'，'分割
                for (int i = 0; i < 57; i++)
                {
                    serverStr += ",";
                    clientStr += ",";
                    if ((i < 48 && i == time) || (i < 55 && i - 48 == day))
                        x_f = 1;
                    else
                        x_f = 0;
                    mpf_mul_2exp(x_f.get_mpf_t(), x_f.get_mpf_t(), eAndC);
                    server = randNumGen();
                    x_z = x_f;
                    client = x_z + modNum - server;
                    serverStr += server.get_str();
                    clientStr += client.get_str();
                }
                serverStr += "\n";
                clientStr += "\n";
                index++;
                cout << symbol[index / 10 % 4] << " No." << index / 480 << "|" << index % 480 << " \r" << flush;
            }
            ciphertext[0][p] = serverStr;
            ciphertext[1][p] = clientStr;
            showTime();
        }
        for (int p = 0; p < plaintext.size(); p++)
        {
            outfile1 << ciphertext[0][p];
            outfile2 << ciphertext[1][p];
        }
        outfile1.close();
        outfile2.close();
    }
    cout << "Share Gen OK" << endl;
}

CSVreader::CSVreader(const char *path)
{
    string p = "./dataSet.csv";
    _csvInput.open(p, ios::in);
    if (!_csvInput)
        cout << "read error" << endl;
}

//读取csv文件数据
int CSVreader::readline()
{
    //定义一行数据为字符串
    string _Oneline;
    //读取一行数据
    getline(_csvInput, _Oneline);

    //定义字符串流对象
    istringstream _Readstr(_Oneline);
    //定义一行数据中的各个字串
    string _partOfstr;
    //将一行数据按'，'分割
    for (int i = 0; i < 58; i++)
    {
        getline(_Readstr, _partOfstr, ',');
        data[i] = atof(_partOfstr.c_str());
    }
    //判断是否读完数据
    if ((data[49]) == 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
