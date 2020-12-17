#include <iostream>
#include <memory>
#include <istream>
#include <fstream>
#include <vector>
#include "reader.h"
#include "lexer.h"
using namespace std;

  int main()  {
    std::shared_ptr<std::ifstream> stream = std::make_shared<std::ifstream>("plik", ios::in | ios::binary);
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    Lexer lexer(reader);
    Token x;
    vector<Token> test;
    x = lexer.getNextToken();
    cout<<x.text<<endl;
    while(x.type != TokenTypes::EOFTOKEN){
        test.push_back(x);
        x = lexer.getNextToken();

        //
        if(x.type == TokenTypes::NUMBER)
            cout<<x.beforeDot<<endl;
        else
            cout<<x.text<<endl;
        //
    }
    return 0;
}
