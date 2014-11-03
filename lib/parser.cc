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

void Integer::visit(IAstVisitor& visitor) {
  visitor.visit_integer(*this);
}

/*
 * Parser
 */
Parser::Parser(TokenStream stream) {
  _stream = stream;
}

Expression* Parser::parse() {
  Token token = _stream.read();
  if(token.type() == LPAREN) {
    return parse_list();
  } else if(token.type() == INTEGER) {
    return new Integer(token);
  }

  return NULL;
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

