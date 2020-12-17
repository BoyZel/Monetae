#ifndef TOKENTYPES_H
#define TOKENTYPES_H

enum class TokenTypes{
        NUMBER,
        OR, // ||
        AND, // &&
        EQUAL, // ==
        NOT_EQUAL, // !=
        COMPARE, // [>, <, >=, <=]
        COMMENT, // //
        SEMICOLON, // ;
        WHILE, // while
        IF, // if
        ELSE, // else
        FUNCTION, // function
        VAR, // variable
        RETURN, // return
    	MAIN, //main
    	
        LEFT_PARENTHESIS, // (
        RIGHT_PARENTHESIS, // )
        LEFT_BRACE, // {
        RIGHT_BRACE, // }
        COMMA, // ,
        BREAK, // break
        CONTINUE, // continue
        ASSIGN, // =
        ADD, // [+, -]
        MULTIPLY, // [*, /]
        NEGATE, // !
        STRING, // "..."
        EOFTOKEN, // end of file
        NAME, // name of variable/function
        ERROR_TOO_LONG,
        OTHER // anything else
};


#endif // TOKENTYPES_H
