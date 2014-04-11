#include <schemese/scanner.h>

using namespace Schemese;

Token::Token(TokenType t, std::string v) : _type(t), _value(v) {

}

Token::Token(TokenType t) : _type(t), _value("") {

}

TokenType Token::type() const {
  return _type;
}

std::string Token::value() const {
  return _value;
}

bool Token::operator==(const Token &other) const {
  return (*this).type() == other.type() &&
    (*this).value() == other.value();
}

