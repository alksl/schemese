#ifndef _SCHEMESE_PARSER_H
#define _SCHEMESE_PARSER_H

#include <schemese/scanner.h>


namespace Schemese {
  class Expression {
    public:
      virtual ~Expression() { }
  };

  class ScalarExpr : public Expression {
    public:
      ScalarExpr(Token token) : _token(token) { }
      const Token& token();
    private:
      const Token _token;
  };

  typedef std::vector<Expression*> ListContents;
  class ListExpr : public Expression {
    public:
      ListExpr(ListContents& contents) : _contents(contents) {  }
      ListExpr() : _contents(ListContents()) { }

      ListContents& contents();

    private:
      ListContents _contents;
  };

  class Integer : public ScalarExpr {
    public:
      Integer(Token integer_token) : ScalarExpr(integer_token) { }
  };

  class TokenStream {
    public:
      void push(const Token& token);
      Token& read();
      const Token& peek() const;
      void consume();
    private:
      std::queue<Token> queue;
  };

  TokenStream& operator<<(TokenStream& stream, const Token& token);

  class Parser {
    public:
      Parser(TokenStream stream);
      Expression* parse();

    private:
      ListExpr* parse_list();
      ListContents parse_list_contents();

      TokenStream _stream;
  };
}

#endif
