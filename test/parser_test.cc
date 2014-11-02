#include <gtest/gtest.h>
#include <schemese/parser.h>

namespace {

using namespace Schemese;

class ParserTest : public ::testing::Test {
  protected:
    Expression* parse(TokenStream stream) {
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
  TokenStream stream;
  stream << Token(LPAREN, "(");
  stream << Token(RPAREN, ")");
  ListExpr* tree = (ListExpr*)parse(stream);
  EXPECT_EQ(true, tree->contents().empty());
}

TEST_F(ParserTest, parse_integer) {
  TokenStream stream;
  stream << Token(INTEGER, "42");

  Integer* integer = (Integer*)parse(stream);
  assert_token(integer->token(), INTEGER, "42");
}


TEST_F(ParserTest, parse_list_with_number) {
  TokenStream token_stream;
  token_stream << Token(LPAREN, "(");
  token_stream << Token(INTEGER, "42");
  token_stream << Token(RPAREN, ")");

  ListExpr* list = (ListExpr*)parse(token_stream);
  EXPECT_EQ(1, list->contents().size());

  Integer* integer = (Integer*)list->contents().at(0);
  assert_token(integer->token(), INTEGER, "42");
}

}
