#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "environment.h"
//#include "syntax_objects/program.h"

class Program;
class Interpreter
{
    Environment environment;
  //  std::unique_ptr<Program> program;
public:
    Interpreter();
   // Interpreter(std::unique_ptr<Program> program);
};

#endif // INTERPRETER_H
