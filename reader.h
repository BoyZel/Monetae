#ifndef READER_H
#define READER_H
#include <istream>
#include <memory>
class Reader
{
public:
    std::shared_ptr<std::istream> stream;
    Reader(std::shared_ptr<std::istream>);
    char getChar();
    char peekChar();
    void unget();
};

#endif // READER_H
