#ifndef _SCHEMESE_PARSER_H
#define _SCHEMESE_PARSER_H

#include <schemese/scanner.h>


namespace Schemese {
  // Forward declaration
  class IAstVisitor;

  class Expression {
    public:
      virtual void visit(IAstVisitor& visitor) = 0;
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
      virtual void visit(IAstVisitor& visitor);
    private:
      ListContents _contents;
  };

  class Integer : public ScalarExpr {
    public:
      Integer(Token integer_token) : ScalarExpr(integer_token) { }
      virtual void visit(IAstVisitor& visitor);
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

  class IAstVisitor {
    public:
      virtual void list_begin() = 0;
      virtual void list_end() = 0;
      virtual void visit_integer(Integer& integer) = 0;
      virtual ~IAstVisitor() { }
  };

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
