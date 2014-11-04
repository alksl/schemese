#include <schemese/parser.h>

namespace Schemese {

/*
 * TokenStream
 */
void TokenStream::push(const Token& token) {
  queue.push(token);
}

Token& TokenStream::read() {
  Token& front = queue.front();
  queue.pop();
  return front;
}

const Token& TokenStream::peek() const {
  return queue.front();
}

void TokenStream::consume() {
  queue.pop();
}


TokenStream& operator<<(TokenStream& stream, const Token& token) {
  stream.push(token);
  return stream;
}

/*
 * Expression
 */
const Token& ScalarExpr::token() {
  return _token;
}

void ListExpr::visit(IAstVisitor& visitor) {
  visitor.list_begin();
  for(ListContents::iterator it = _contents.begin() ; it != _contents.end(); ++it) {
    (*it)->visit(visitor);
  }
  visitor.list_end();
}

void VectorExpr::visit(IAstVisitor& visitor) {
  visitor.vector_begin();
  for(VectorContents::iterator it = _contents.begin() ; it != _contents.end(); ++it) {
    (*it)->visit(visitor);
  }
  visitor.vector_end();
}

void Integer::visit(IAstVisitor& visitor) {
  visitor.integer(*this);
}

void Symbol::visit(IAstVisitor& visitor) {
  visitor.symbol(*this);
}

/*
 * Parser
 */
const char* ParserException::what() const throw() {
 return _message.c_str();
}

Parser::Parser(TokenStream stream) {
  _stream = stream;
}

Expression* Parser::parse() {
  Token token = _stream.read();
  switch(token.type()) {
    case LPAREN:
      return parse_list();
    case LBRACKET:
      return parse_vector();
    case INTEGER:
      return new Integer(token);
    case IDENTIFIER:
      return new Symbol(token);
    default:
      throw ParserException("Parser::parse, Unrecognized token");
  }
}

ListExpr* Parser::parse_list() {
  const Token peek = _stream.peek();
  if(peek.type() == RPAREN) {
    _stream.consume();
    return new ListExpr();
  } else {
    ListContents contents = parse_list_contents();
    return new ListExpr(contents);
  }
}

VectorExpr* Parser::parse_vector() {
  const Token peek = _stream.peek();
  if(peek.type() == RBRACKET) {
    _stream.consume();
    return new VectorExpr();
  } else {
    VectorContents contents = parse_vector_contents();
    return new VectorExpr(contents);
  }
}

VectorContents Parser::parse_vector_contents() {
  VectorContents contents;
  while(true) {
    const Token peek = _stream.peek();
    if(peek.type() == RBRACKET) {
      _stream.consume();
      return contents;
    }

    contents.push_back(parse());
  }
}

ListContents Parser::parse_list_contents() {
  ListContents contents;
  while(true) {
    const Token peek = _stream.peek();
    if(peek.type() == RPAREN) {
      _stream.consume();
      return contents;
    }

    contents.push_back(parse());
  }

}


} // namespace

