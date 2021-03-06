#define BOOST_TEST_MODULE TestInterpretera
#include <boost/test/included/unit_test.hpp>
#include <memory>
#include <istream>
#include <fstream>
#include <vector>
#include "reader.h"
#include "lexer.h"
#include "parser.h"

BOOST_AUTO_TEST_CASE( Test1 )
{
    std::shared_ptr<std::ifstream> stream = std::make_shared<std::ifstream>("test1", std::ios::in | std::ios::binary);
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    Lexer lexer(reader);
    Token x;
    std::vector<Token> test;
    x = lexer.getNextToken();
    while(x.type != TokenTypes::EOFTOKEN){
        test.push_back(x);
        x = lexer.getNextToken();
    }
    BOOST_CHECK( test[0].type == TokenTypes::FUNCTION );
    BOOST_CHECK( test[6].type == TokenTypes::NUMBER );
    BOOST_CHECK( test[11].text == "<=" );
    BOOST_CHECK( test[12].value == 15 );
    BOOST_CHECK( test[18].line == 4 );
    BOOST_CHECK( test[1].line == 0 );
    BOOST_TEST( true /* test assertion */ );
}

BOOST_AUTO_TEST_CASE( TestLeksera2 )
{
    std::shared_ptr<std::ifstream> stream = std::make_shared<std::ifstream>("test2", std::ios::in | std::ios::binary);
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    Lexer lexer(reader);
    Token x;
    std::vector<Token> test;
    x = lexer.getNextToken();
    while(x.type != TokenTypes::EOFTOKEN){
        test.push_back(x);
        x = lexer.getNextToken();
    }
    BOOST_CHECK( test[0].type == TokenTypes::NAME );
    BOOST_CHECK( test[0].text == "pln" );
    BOOST_CHECK( test[4].positionInLine == 10 );
    BOOST_CHECK( test[5].positionInLine == 0 );
    BOOST_CHECK( test[5].type == TokenTypes::RETURN );
    BOOST_CHECK( test[6].text == "main" );
    BOOST_CHECK( test[7].type == TokenTypes::NUMBER );
    BOOST_CHECK( test[9].value == 132 );

    BOOST_TEST( true /* test assertion */ );
}

BOOST_AUTO_TEST_CASE( TestLeksera3 )
{
    std::shared_ptr<std::stringstream> stream = std::make_shared<std::stringstream>("rabarbar pln 3.2500");
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    Lexer lexer(reader);
    Token x;
    std::vector<Token> test;
    x = lexer.getNextTokenFromConfig();
    while(x.type != TokenTypes::EOFTOKEN){
        test.push_back(x);
        x = lexer.getNextTokenFromConfig();
    }
    BOOST_CHECK( test[0].type == TokenTypes::NAME );
    BOOST_CHECK( test[1].text == "pln" );
    BOOST_CHECK( test[2].valueDouble - 3.2500 < 1 );
}

BOOST_AUTO_TEST_CASE( TestLeksera4 )
{
    std::shared_ptr<std::stringstream> stream = std::make_shared<std::stringstream>("() <= ||");
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    Lexer lexer(reader);
    Token x;
    std::vector<Token> test;
    x = lexer.getNextToken();
    while(x.type != TokenTypes::EOFTOKEN){
        test.push_back(x);
        x = lexer.getNextToken();
    }
    BOOST_CHECK( test[0].type == TokenTypes::LEFT_PARENTHESIS );
    BOOST_CHECK( test[1].text == ")" );
    BOOST_CHECK( test[2].text == "<=" );
    BOOST_CHECK( test[3].text == "||" );
}

BOOST_AUTO_TEST_CASE( TestParsera1 )
{
    std::shared_ptr<std::stringstream> stream = std::make_shared<std::stringstream>("function a(){}");
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(reader));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera2)
{
    std::shared_ptr<std::stringstream> stream = std::make_shared<std::stringstream>("function a(){var p = 8;}");
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(reader));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera3)
{
    std::shared_ptr<std::stringstream> stream = std::make_shared<std::stringstream>("function a(){var p = 8; x=y+9;}");
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(reader));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera4)
{
    std::shared_ptr<std::stringstream> stream = std::make_shared<std::stringstream>("function a(){var p = 8; p=p+9; return 2+2;}");
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(reader));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera5)
{
    std::shared_ptr<std::stringstream> stream = std::make_shared<std::stringstream>("function a(){var p = 8; p=p+9; return 2+2; if(a>b){}}");
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(reader));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera6)
{
    std::shared_ptr<std::stringstream> stream = std::make_shared<std::stringstream>("function a(){var p = 8; p=p+9; return 2+2; if(a>b){} while(c>=10){}}");
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(reader));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera7)
{
    std::shared_ptr<std::stringstream> stream = std::make_shared<std::stringstream>("function a(){var p = 8; p=p+9; return 2+2; if(a>b){} while(c>=10){}}");
    std::shared_ptr<Reader> reader = std::make_shared<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(reader));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}
