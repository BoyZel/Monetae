#include "reader.h"
int Reader::getLine() const
{
    return line;
}

int Reader::tellg() const
{
    return stream.tellg();
}

int Reader::getPositionInLine() const
{
    return positionInLine;
}

void Reader::setNewLine()
{
   line ++;
   positionInLine = 0;
}

Reader::Reader(std::istream &istream) : stream(istream)
{
}

char Reader::getChar()
{
    positionInLine++;
    char tmp = stream.get();
    if(tmp == 10){
        line++;
        positionInLine = 0;
    }
    return tmp;
}

char Reader::peekChar()
{
    return stream.peek();
}

void Reader::unget()
{
    positionInLine--;
    stream.unget();
}
