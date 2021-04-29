#ifndef READER_H
#define READER_H
#include <istream>
#include <memory>
class Reader
{
private:
    int positionInLine = 0;
    int absolutePosition = 0;
    int line = 0;
public:
    std::shared_ptr<std::istream> stream;
    Reader(std::shared_ptr<std::istream>);
    char getChar();
    char peekChar();
    void unget();
    int getLine() const;
    int getAbsolutePosition() const;
    int getPositionInLine() const;
    void setNewLine();
};

#endif // READER_H
