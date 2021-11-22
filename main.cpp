#define BOOST_TEST_MODULE TestInterpretera
#include <boost/test/included/unit_test.hpp>
#include <memory>
#include <istream>
#include <fstream>
#include <vector>
#include "reader.h"
#include "lexer.h"
#include "parser.h"

BOOST_AUTO_TEST_CASE( TestRoznosci )
{
    std::stringstream stream("rabarbar pln 3.2500");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    Lexer lexer(std::move(reader));
    Token x;
    std::vector<Token> test;
    x = lexer.getNextTokenFromConfig();
    while(x.type != TokenTypes::EOFTOKEN){
        test.push_back(x);
        x = lexer.getNextTokenFromConfig();
    }
    BOOST_CHECK( test[0].type == TokenTypes::NAME );
    BOOST_CHECK( test[1].text == "pln" );
    BOOST_CHECK( test[2].valueDouble - 3.2500 < 0.1 );
}

BOOST_AUTO_TEST_CASE(TestOperatorow)
{
    std::stringstream stream("() {} + - * / = > < , ; ! . <= || == != >= &&");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    Lexer lexer(std::move(reader));
    Token x;
    std::vector<Token> test;
    x = lexer.getNextToken();
    while(x.type != TokenTypes::EOFTOKEN){
        test.push_back(x);
        x = lexer.getNextToken();
    }
    BOOST_CHECK( test[0].type == TokenTypes::LEFT_PARENTHESIS );
    BOOST_CHECK( test[1].text == ")" );
    BOOST_CHECK( test[2].text == "{" );
    BOOST_CHECK( test[3].text == "}" );
    BOOST_CHECK( test[4].text == "+" );
    BOOST_CHECK( test[5].text == "-" );
    BOOST_CHECK( test[6].type == TokenTypes::MULTIPLY );
    BOOST_CHECK( test[7].text == "/" );
    BOOST_CHECK( test[8].text == "=" );
    BOOST_CHECK( test[9].text == ">" );
    BOOST_CHECK( test[10].text == "<" );
    BOOST_CHECK( test[11].text == "," );
    BOOST_CHECK( test[12].text == ";" );
    BOOST_CHECK( test[13].text == "!" );
    BOOST_CHECK( test[14].text == "." );
    BOOST_CHECK( test[15].text == "<=" );
    BOOST_CHECK( test[16].text == "||" );
    BOOST_CHECK( test[17].text == "==" );
    BOOST_CHECK( test[18].text == "!=" );
    BOOST_CHECK( test[19].text == ">=" );
    BOOST_CHECK( test[20].text == "&&" );
    BOOST_CHECK( test[15].type == TokenTypes::COMPARE );
    BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE( TestLiczb )
{
    std::stringstream stream("1 3.2500 0.12 7 313 00 05");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    Lexer lexer(std::move(reader));
    Token x;
    std::vector<Token> test;
    x = lexer.getNextTokenFromConfig();
    while(x.type != TokenTypes::EOFTOKEN){
        test.push_back(x);
        x = lexer.getNextTokenFromConfig();
    }
    BOOST_CHECK( test[0].type == TokenTypes::NUMBER );
    BOOST_CHECK( test[1].valueDouble - 3.2500 < 0.1 );
    BOOST_CHECK( test[2].valueDouble - 0.12 < 0.1 );
    BOOST_CHECK( test[3].value == 7 );
    BOOST_CHECK( test[4].value == 313 );
    BOOST_CHECK( test[5].type == TokenTypes::OTHER );
    BOOST_CHECK( test[6].type == TokenTypes::OTHER );
    BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE( TestNazw )
{
    std::stringstream stream("Polak polak pol_ak if else white while return var main break continue function");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    Lexer lexer(std::move(reader));
    Token x;
    std::vector<Token> test;
    x = lexer.getNextTokenFromConfig();
    while(x.type != TokenTypes::EOFTOKEN){
        test.push_back(x);
        x = lexer.getNextTokenFromConfig();
    }
    BOOST_CHECK( test[0].type == TokenTypes::NAME );
    BOOST_CHECK( test[1].text == "polak" );
    BOOST_CHECK( test[2].text == "pol_ak");
    BOOST_CHECK( test[3].type == TokenTypes::IF );
    BOOST_CHECK( test[4].type == TokenTypes::ELSE );
    BOOST_CHECK( test[5].type == TokenTypes::NAME );
    BOOST_CHECK( test[6].type == TokenTypes::WHILE );
    BOOST_CHECK( test[7].type == TokenTypes::RETURN );
    BOOST_CHECK( test[8].type == TokenTypes::VAR );
    BOOST_CHECK( test[9].type == TokenTypes::MAIN );
    BOOST_CHECK( test[10].type == TokenTypes::BREAK );
    BOOST_CHECK( test[11].type == TokenTypes::CONTINUE );
    BOOST_CHECK( test[12].type == TokenTypes::FUNCTION );
    BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE( TestKomentarza )
{
    std::stringstream stream("xd //a dalej smieci \n schab");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    Lexer lexer(std::move(reader));
    Token x;
    std::vector<Token> test;
    x = lexer.getNextTokenFromConfig();
    while(x.type != TokenTypes::EOFTOKEN){
        test.push_back(x);
        x = lexer.getNextTokenFromConfig();
    }
    BOOST_CHECK( test[0].type == TokenTypes::NAME );
    BOOST_CHECK( test[1].text == "schab" );
    BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE( TestParsera1 )
{
    std::stringstream stream("function a(){}");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(std::move(reader)));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera2)
{
    std::stringstream stream("function a(){var p = 8;}");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(std::move(reader)));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera3)
{
    std::stringstream stream("function a(){var p = 8; x=y+9;}");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(std::move(reader)));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera4)
{
    std::stringstream stream("function a(){var p = 8; p=p+9; return 2+2;}");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(std::move(reader)));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera5)
{
    std::stringstream stream ("function a(){var p = 8; p=p+9; return 2+2; if(a>b){}}");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(std::move(reader)));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera6)
{
    std::stringstream stream("function a(){var p = 8; p=p+9; return 2+2; if(a>b){} while(c>=10){}}");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(std::move(reader)));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}

BOOST_AUTO_TEST_CASE( TestParsera7)
{
    std::stringstream stream("function a(){var p = 8; p=p+9; return 2+2; if(a>b){} while(c>=10){}}");
    std::unique_ptr<Reader> reader = std::make_unique<Reader>(stream);
    std::unique_ptr<Lexer> lexer(new Lexer(std::move(reader)));
    auto parser = Parser(std::move(lexer));
    BOOST_CHECK_NO_THROW(parser.parseProgram());
}
