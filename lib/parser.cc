#include <schemese/parser.h>

using namespace Schemese;

void TokenStream::push(Token token) {
  queue.push(token);
}

Token TokenStream::read() {
  Token front = queue.front();
  queue.pop();
  return front;
}

Parser::Parser(TokenStream stream) {
  token_stream = stream;
}

SExpression* Parser::parse() {
 return new SExpression(
      new Integer(Token(INTEGER, "42")),
      new SExpression());
}
