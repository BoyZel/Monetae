#include "reader.h"
int Reader::getLine() const
{
    return line;
}

int Reader::getAbsolutePosition() const
{
    return absolutePosition;
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

Reader::Reader(std::shared_ptr<std::istream> istream) : stream(istream)
{
}

char Reader::getChar()
{
    absolutePosition++;
    positionInLine++;
    return stream->get();
}

char Reader::peekChar()
{
    return stream->peek();
}

void Reader::unget()
{
    absolutePosition--;
    positionInLine--;
    stream->unget();
}
