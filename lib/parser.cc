#include <schemese/parser.h>

namespace Schemese {

void TokenStream::push(const Token& token) {
  queue.push(token);
}

TokenStream& operator<<(TokenStream& stream, const Token& token) {
  stream.push(token);
  return stream;
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

} // namespace
