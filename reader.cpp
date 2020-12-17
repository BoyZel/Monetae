#include "reader.h"
Reader::Reader(std::shared_ptr<std::istream> istream) : stream(istream)
{
}

char Reader::getChar()
{
    return stream->get();
}

char Reader::peekChar()
{
    return stream->peek();
}

void Reader::unget()
{
    stream->unget();
}
