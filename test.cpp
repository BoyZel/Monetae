#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <memory>
#include <istream>
#include <fstream>
#include <vector>
#include "reader.h"
#include "lexer.h"
using namespace std;

    BOOST_AUTO_TEST_CASE( test )
    {
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
        BOOST_CHECK( test[0].type == TokenTypes::FUNCTION );
        BOOST_CHECK( test[7].type == TokenTypes::NUMBER );
        BOOST_CHECK( test[11].text == "<=" );
        BOOST_CHECK( test[12].beforeDot == 15 );
        BOOST_CHECK( test[18].line == 4 );
        BOOST_CHECK( test[1].line == 0 );
}
