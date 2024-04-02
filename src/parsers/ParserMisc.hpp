#include <bits/stdc++.h>
#include "BaseParser.hpp"
using namespace std;
//Parser khusus untuk membaca file konfigurasi misc.
class ParserMisc : public BaseParser{
    private:
        int winningMoney;
        int winningWeight;
        pair<int,int> storageSize;
        pair<int,int> fieldSize;
        pair<int,int> farmSize;
    public:
        ParserMisc(){}
        ~ParserMisc(){}
        void ParseFile(string fileDirectory);
        void ClearParserData();
        friend ostream &operator<<(ostream &os, ParserMisc &PM); //untuk debugging, pake aja
};