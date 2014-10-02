#include <gtest/gtest.h>
#include <schemese/parser.h>

namespace {

using namespace Schemese;

class ParserTest : public ::testing::Test {
  protected:
    Ast* parse(TokenStream stream) {
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
  token_stream.push(Token(LPAREN, "("));
  token_stream.push(Token(RPAREN, ")"));
  Ast* ast = parse(token_stream);
  assert_token(*ast->children[0]->token, LPAREN, "(");
  assert_token(*ast->children[1]->token, RPAREN, ")");
}

}
