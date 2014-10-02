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
  root = new Ast();
}

Ast* Parser::parse() {
  Ast* lhs = new Ast();
  lhs->token = new Token(token_stream.read());
  Ast* rhs = new Ast();
  rhs->token = new Token(token_stream.read());
  root->children.push_back(lhs);
  root->children.push_back(rhs);
  return root;
}
