#include <gtest/gtest.h>
#include <schemese/scanner.h>

using namespace Schemese;

TEST(Token, token_with_type) {
  Token token = Token(LPAREN);
  EXPECT_EQ(LPAREN, token.type());
  EXPECT_EQ("", token.value());
}

TEST(Token, token_with_type_and_value) {
  Token token = Token(IDENTIFIER, "...");
  EXPECT_EQ(IDENTIFIER, token.type());
  EXPECT_EQ("...", token.value());
}

TEST(Token, equality) {
  Token token1 = Token(IDENTIFIER, "...");
  Token token2 = Token(IDENTIFIER, "...");
  EXPECT_EQ(token1, token2);
}
