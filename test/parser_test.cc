#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <schemese/parser.h>

namespace {

using namespace Schemese;
using namespace testing;

class ParserTest : public Test {
  protected:
    Expression* parse(TokenStream stream) {
      Parser parser(stream);
      return parser.parse();
    }
};

class MockVisitor : public IAstVisitor {
  public:
    MOCK_METHOD0(list_begin, void());
    MOCK_METHOD0(list_end, void());
    MOCK_METHOD1(visit_integer, void(Integer& integer));
};

TEST_F(ParserTest, parse_empty_list) {
  Sequence s1;
  TokenStream stream;
  MockVisitor visitor;

  stream << Token(LPAREN, "(");
  stream << Token(RPAREN, ")");

  EXPECT_CALL(visitor, list_begin())
    .InSequence(s1);
  EXPECT_CALL(visitor, list_end())
    .InSequence(s1);

  Expression* tree = parse(stream);
  tree->visit(visitor);
}

TEST_F(ParserTest, parse_integer) {
  TokenStream stream;
  MockVisitor visitor;

  stream << Token(INTEGER, "42");

  EXPECT_CALL(visitor, visit_integer(_));

  Expression* tree = parse(stream);
  tree->visit(visitor);
}

TEST_F(ParserTest, parse_list_with_number) {
  Sequence s1;
  TokenStream token_stream;
  MockVisitor visitor;

  token_stream << Token(LPAREN, "(");
  token_stream << Token(INTEGER, "42");
  token_stream << Token(RPAREN, ")");

  EXPECT_CALL(visitor, list_begin())
    .InSequence(s1);
  EXPECT_CALL(visitor, visit_integer(_))
    .InSequence(s1);
  EXPECT_CALL(visitor, list_end())
    .InSequence(s1);

  Expression* tree = parse(token_stream);
  tree->visit(visitor);
}

} // anonymous namespace
