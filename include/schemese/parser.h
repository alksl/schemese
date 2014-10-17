#ifndef _SCHEMESE_PARSER_H
#define _SCHEMESE_PARSER_H

#include <schemese/scanner.h>


namespace Schemese {
  class Expression {
    public:
      virtual ~Expression() { }
  };

  class Scalar : public Expression {
    public:
      Scalar(Token t) : token(t) { }
      const Token token;
  };

  class SExpression : public Expression {
    public:
      SExpression(Expression* e1, Expression* e2) : car(e1), cdr(e2) { }
      SExpression() : car(NULL), cdr(NULL) { }
      bool empty() { return car == NULL; }

      const Expression* car;
      const Expression* cdr;
  };

  class Integer : public Scalar {
    public:
      Integer(Token integer_token) : Scalar(integer_token) { }
  };

  class TokenStream {
    public:
      void push(Token token);
      Token read();
    private:
      std::queue<Token> queue;
  };

  class Parser {
    public:
      Parser(TokenStream stream);
      SExpression* parse();
    private:
      TokenStream token_stream;
      SExpression* tree = NULL;
  };
}

#endif
