#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <schemese/parser.h>

namespace {

using namespace Schemese;
using namespace testing;

class MockVisitor : public IAstVisitor {
  public:
    MOCK_METHOD0(list_begin, void());
    MOCK_METHOD0(list_end, void());
    MOCK_METHOD1(visit_integer, void(Integer& integer));
};

class ParserTest : public Test {
  protected:
    void parse() {
      Parser parser(stream);
      Expression* tree = parser.parse();
      tree->visit(visitor);
    }

    Sequence s1;
    TokenStream stream;
    MockVisitor visitor;
    Expression* tree = NULL;
};

TEST_F(ParserTest, parse_empty_list) {
  stream << Token(LPAREN, "(");
  stream << Token(RPAREN, ")");

  EXPECT_CALL(visitor, list_begin())
    .InSequence(s1);
  EXPECT_CALL(visitor, list_end())
    .InSequence(s1);

  parse();
}

TEST_F(ParserTest, parse_integer) {
  stream << Token(INTEGER, "42");

  EXPECT_CALL(visitor, visit_integer(_));

  parse();
}

TEST_F(ParserTest, parse_list_with_number) {
  stream << Token(LPAREN, "(");
  stream << Token(INTEGER, "42");
  stream << Token(RPAREN, ")");

  EXPECT_CALL(visitor, list_begin())
    .InSequence(s1);
  EXPECT_CALL(visitor, visit_integer(_))
    .InSequence(s1);
  EXPECT_CALL(visitor, list_end())
    .InSequence(s1);

  parse();
}

} // anonymous namespace
