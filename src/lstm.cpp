#include "lstm.h"

void printHelp();

int main(int argc, char *argv[])
{
    start = time(nullptr);
    lastPoint = start;
    char action = 'x', cRole = 'x';
    int epochsT = 1, epochsP = 1, ch;
    if (argc == 1)
    {
        cout << "Use \"lstm -h\" to get help.\n"
             << endl;
        do
        {
            cout << "\nInput your cRole:\n(1)SERVER  (2)CLIENT\ncRole:" << flush;
            cin.get(cRole).get();
        } while (cRole != '1' && cRole != '2');
        do
        {
            cout << "\nInput your action:\n(1)Triples Gen   (2)Triples Check   (3)Share Gen   (4)LSTM\naction:"
                 << flush;
            cin.get(action).get();
        } while (action != '1' && action != '2' && action != '3' && action != '4');
        cout << "Input peopleNum:" << flush;
        cin >> dataSetNum;
        role = (cRole == '1') ? SERVER : CLIENT;
    }
    else
    {
        while ((ch = getopt(argc, argv, "r:a:n:d:u:i:p:s:t:l:m:h")) != -1)
        {
            switch (ch)
            {
            case 'r':
                role = (!strcmp(optarg, "1")) ? SERVER : CLIENT;
                break;
            case 'a':
                action = optarg[0];
                break;
            case 'n':
                dataSetNum = stoi(optarg);
                break;
            case 'd':
                dataSetStartIndex = stoi(optarg);
                break;
            case 'u':
                userStartIndex = stoi(optarg);
                break;
            case 's':
                steps = stoi(optarg);
                break;
            case 't':
                dataSetStartIndex = stoi(optarg);
                dataSetNum = dataSetStartIndex + 1;
                break;
            case 'l':
                userLimit = stoi(optarg);
                userCountsFLAG = 1;
                break;
            case 'i':
                IP = optarg;
                break;
            case 'p':
                PORT = stoi(optarg);
                break;
            case 'm':
                modNumIndex = stoi(optarg);
                break;
            case '?':
                printf("unknow option:%c\n", optopt);
                break;
            case 'h':
            default:
                printHelp();
                return 0;
            }
        }
    }
    cout << "\nYou are " << ((role == SERVER) ? "SERVER" : "CLIENT") << endl;

    dir(); //确认及创建文件夹
    Lstm lstm;

    switch (action)
    {
    case '1':
        cout << "Triples Gen" << endl;
        cout << "\nInput training rounds:" << flush;
        cin >> epochsT;
        cin.get();
        cout << "\nInput predict rounds:" << flush;
        cin >> epochsP;
        cin.get();
        lstm.triplesGen(epochsT, epochsP);
        break;
    case '2':
        cout << "Triples Check" << endl;
        check();
        break;
    case '3':
        cout << "Share Gen" << endl;
        shareGen();
        break;
    case '4':
        cout << "LSTM" << endl;
        lstm.train();
        break;
    case '5':
        cout << "Plain Matrix" << endl;
        plainMatrix();
        break;
    default:
        exit(1);
    }
    showTime(1);
    return 0;
}

void printHelp()
{
    cout << "\n Usage :"
         << "\tlstm [Options] <Destination>\n\n"
         << " Options      Destination\n"
         << "  -r          (1)SERVER        (2)CLIENT\n"
         << "  -a          (1)Triples Gen   (2)Triples Check   (3)Share Gen   (4)LSTM\n"
         << "  -n          Number of Data Set, input an interger.\n"
         << "  -d          Start Index of Data Set, input an interger.\n"
         << "  -u          Start Index of User, input an interger.\n"
         << "  -i          IP Address, input a string.\n"
         << "  -p          Port Number, input an interger.\n"
         << "  -h          Help\n"
         << endl;
}