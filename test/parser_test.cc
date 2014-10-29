#include <gtest/gtest.h>
#include <schemese/parser.h>

namespace {

using namespace Schemese;

class ParserTest : public ::testing::Test {
  protected:
    SExpression* parse(TokenStream stream) {
      Parser parser(stream);
      return parser.parse();
    }

    void assert_token(
        Token token,
        TokenType expected_type,
        std::string expected_string) {
      EXPECT_EQ(expected_type, token.type());
      EXPECT_EQ(expected_string, token.value());
    }
};

TEST_F(ParserTest, parse_empty_list) {
  TokenStream token_stream;
  token_stream << Token(LPAREN, "(");
  token_stream << Token(INTEGER, "42");
  token_stream << Token(RPAREN, ")");
  SExpression* tree = parse(token_stream);
  Scalar* car = (Scalar*)tree->car;
  SExpression* cdr = (SExpression*)tree->cdr;
  assert_token(car->token, INTEGER, "42");
  EXPECT_EQ(true, cdr->empty());
}

}
