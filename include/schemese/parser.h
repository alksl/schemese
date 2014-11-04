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

  typedef std::vector<Expression*> VectorContents;
  class VectorExpr : public Expression {
    public:
      VectorExpr(VectorContents& contents) : _contents(contents) { }
      VectorExpr() : _contents(VectorContents()) { }
      virtual void visit(IAstVisitor& visitor);
    private:
      VectorContents _contents;
  };

  class Integer : public ScalarExpr {
    public:
      Integer(Token& token) : ScalarExpr(token) { }
      virtual void visit(IAstVisitor& visitor);
  };

  class Symbol : public ScalarExpr {
    public:
      Symbol(Token& token) : ScalarExpr(token) { }
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
      virtual void vector_begin() = 0;
      virtual void vector_end() = 0;
      virtual void integer(Integer& integer) = 0;
      virtual void symbol(Symbol& symbol) = 0;
      virtual ~IAstVisitor() { }
  };

  class ParserException : public std::exception {
    public:
      ParserException(const char* message) : _message(message) { }
      virtual const char* what() const throw();
    private:
      std::string _message;
  };

  class Parser {
    public:
      Parser(TokenStream stream);
      Expression* parse();

    private:
      ListExpr* parse_list();
      VectorExpr* parse_vector();
      ListContents parse_list_contents();
      VectorContents parse_vector_contents();

      TokenStream _stream;
  };
}

#endif
