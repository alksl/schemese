#ifndef _SCHEMESE_SCANNER_H_
#define _SCHEMESE_SCANNER_H_

#include <iostream>
#include <queue>
#include <string>

namespace Schemese {

enum TokenType {
  LPAREN,
  RPAREN,
  LBRACKET,
  RBRACKET,
  LCURLYBRACKET,
  RCURLYBRACKET,
  TRUE,
  FALSE,
  QUOTE,
  BACKQUOTE,
  UNQUOTE,
  UNQUOTESPLICE,
  IDENTIFIER,
  BOOLEAN,
  VECTOR_START,
  BYTEVECTOR_START,
  INTEGER,
  REAL,
  RATIONAL,
  CHARACTER,
  STRING
};

class ScannerBuffer {
  public:
    void read_bytes(std::istream& stream);
    unsigned long write_bytes(char* buf, int max_size);
  private:
    std::queue<char> buffer;
};

class Token {
  public:
    Token(TokenType t, std::string v);
    Token(TokenType t);

    TokenType type() const;
    std::string value() const;

    bool operator==(const Token& other) const;
  private:
    TokenType _type;
    std::string _value;
};

class Scanner {
  public:
    Scanner(std::istream& input);
    Token scan();

    static unsigned long read(char* buf, int max_size);
  private:
    std::istream& input_stream;
    static ScannerBuffer buffer;
};

};

#endif
