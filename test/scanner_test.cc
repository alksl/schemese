#include <sstream>
#include <gtest/gtest.h>
#include <schemese/scanner.h>

namespace {

using namespace Schemese;

class ScannerTest : public ::testing::Test {
  protected:
    Token scan(std::string input) {
      std::stringstream stream = string_to_stream(input);
      Scanner scanner(stream);
      return scanner.scan();
    }

    void assert_token(
        Token token,
        TokenType expected_type,
        std::string expected_string) {
      EXPECT_EQ(expected_type, token.type());
      EXPECT_EQ(expected_string, token.value());
    }

    std::stringstream string_to_stream(std::string& input) {
      std::stringstream stream;
      stream << input;
      stream << "\n";
      return stream;
    }
};

/*
 * Symbols
 */
TEST_F(ScannerTest, left_paren) {
  Token token = scan("(");
  assert_token(token, LPAREN, "(");
}

TEST_F(ScannerTest, right_paren) {
  Token token = scan(")");
  assert_token(token, RPAREN, ")");
}

TEST_F(ScannerTest, left_bracket) {
  Token token = scan("[");
  assert_token(token, LBRACKET, "[");
}

TEST_F(ScannerTest, right_bracket) {
  Token token = scan("]");
  assert_token(token, RBRACKET, "]");
}

TEST_F(ScannerTest, left_curly_bracket) {
  Token token = scan("{");
  assert_token(token, LCURLYBRACKET, "{");
}

TEST_F(ScannerTest, right_curly_bracket) {
  Token token = scan("}");
  assert_token(token, RCURLYBRACKET, "}");
}

TEST_F(ScannerTest, backquote) {
  Token token = scan("`");
  assert_token(token, BACKQUOTE, "`");
}

TEST_F(ScannerTest, quote) {
  Token token = scan("'");
  assert_token(token, QUOTE, "'");
}

TEST_F(ScannerTest, unquote) {
  Token token = scan(",");
  assert_token(token, UNQUOTE, ",");
}

TEST_F(ScannerTest, unquote_splicing) {
  Token token = scan(",@");
  assert_token(token, UNQUOTESPLICE, ",@");
}

/*
 * Identifiers
 */
TEST_F(ScannerTest, identifier_example1) {
  Token token = scan("myfn");
  assert_token(token, IDENTIFIER, "myfn");
}

TEST_F(ScannerTest, identifier_example2) {
  Token token = scan("...");
  assert_token(token, IDENTIFIER, "...");
}

TEST_F(ScannerTest, identifier_example3) {
  Token token = scan("+");
  assert_token(token, IDENTIFIER, "+");
}

TEST_F(ScannerTest, identifier_example4) {
  Token token = scan("+soup+");
  assert_token(token, IDENTIFIER, "+soup+");
}

TEST_F(ScannerTest, identifier_example5) {
  Token token = scan("<=?");
  assert_token(token, IDENTIFIER, "<=?");
}

TEST_F(ScannerTest, identifier_example6) {
  Token token = scan("->string");
  assert_token(token, IDENTIFIER, "->string");
}

TEST_F(ScannerTest, identifier_example7) {
  Token token = scan("a34kTMNs");
  assert_token(token, IDENTIFIER, "a34kTMNs");
}

TEST_F(ScannerTest, identifier_example8) {
  Token token = scan("lambda");
  assert_token(token, IDENTIFIER, "lambda");
}

TEST_F(ScannerTest, identifier_example9) {
  Token token = scan("list->vector");
  assert_token(token, IDENTIFIER, "list->vector");
}

TEST_F(ScannerTest, identifier_example10) {
  Token token = scan("q");
  assert_token(token, IDENTIFIER, "q");
}

TEST_F(ScannerTest, identifier_example11) {
  Token token = scan("V17a");
  assert_token(token, IDENTIFIER, "V17a");
}

TEST_F(ScannerTest, identifier_example12) {
  Token token = scan("|two words|");
  assert_token(token, IDENTIFIER, "two words");
}

TEST_F(ScannerTest, identifier_example13) {
  Token token = scan("|two\x20;words|");
  assert_token(token, IDENTIFIER, "two\x20;words");
}

/*
 * Strings
 */
TEST_F(ScannerTest, string) {
  Token token = scan("\"this is my string\"");
  assert_token(token, STRING, "this is my string");
}

/*
 * Characters
 */
TEST_F(ScannerTest, character_alarm) {
  Token token = scan("#\\alarm");
  assert_token(token, CHARACTER, "\a");
}

TEST_F(ScannerTest, character_backspace) {
  Token token = scan("#\\backspace");
  assert_token(token, CHARACTER, "\b");
}

TEST_F(ScannerTest, character_delete) {
  Token token = scan("#\\delete");

  assert_token(token, CHARACTER, "\x7f");
}

TEST_F(ScannerTest, character_escape) {
  Token token = scan("#\\escape");
  assert_token(token, CHARACTER, "\x1b");
}

TEST_F(ScannerTest, character_newline) {
  Token token = scan("#\\newline");
  assert_token(token, CHARACTER, "\n");
}

TEST_F(ScannerTest, character_null) {
  Token token = scan("#\\null");
  assert_token(token, CHARACTER, "\0");
}

TEST_F(ScannerTest, character_return) {
  Token token = scan("#\\return");
  assert_token(token, CHARACTER, "\x0d");
}

TEST_F(ScannerTest, character_space) {
  Token token = scan("#\\space");
  assert_token(token, CHARACTER, " ");
}

TEST_F(ScannerTest, character_tab) {
  Token token = scan("#\\tab");
  assert_token(token, CHARACTER, "\t");
}

TEST_F(ScannerTest, character_downcased) {
  Token token = scan("#\\a ");
  assert_token(token, CHARACTER, "a");
}

TEST_F(ScannerTest, character_upcased) {
  Token token = scan("#\\A ");
  assert_token(token, CHARACTER, "A");
}

TEST_F(ScannerTest, character_symbol) {
  Token token = scan("#\\(");
  assert_token(token, CHARACTER, "(");
}

TEST_F(ScannerTest, character_space_typed) {
  Token token = scan("#\\ ");
  assert_token(token, CHARACTER, " ");
}

// TODO Unicode characters
// #\x03bb
// #\iota

/*
 * Vectors
 */
TEST_F(ScannerTest, vector) {
  Token token = scan("#(");
  assert_token(token, VECTOR_START, "#(");
}

/*
 * Bytevectors
 */
TEST_F(ScannerTest, byte_vector) {
  Token token = scan("#u8(");
  assert_token(token, BYTEVECTOR_START, "#u8(");
}

/*
 * Numbers
 */
TEST_F(ScannerTest, integer_literal_example1) {
  Token token = scan("12345");
  assert_token(token, INTEGER, "12345");
}

TEST_F(ScannerTest, integer_literal_example22) {
  Token token = scan("1");
  assert_token(token, INTEGER, "1");
}

TEST_F(ScannerTest, decimal_literal_example1) {
  Token token = scan("123.123");
  assert_token(token, REAL, "123.123");
}

TEST_F(ScannerTest, decimal_literal_example2) {
  Token token = scan("123.");
  assert_token(token, REAL, "123.");
}

TEST_F(ScannerTest, decimal_literal_example3) {
  Token token = scan(".123");
  assert_token(token, REAL, ".123");
}

TEST_F(ScannerTest, decimal_literal_example4) {
  Token token = scan("1.1e21");
  assert_token(token, REAL, "1.1e21");
}

TEST_F(ScannerTest, decimal_literal_example5) {
  Token token = scan("1.1E21");
  assert_token(token, REAL, "1.1E21");
}

TEST_F(ScannerTest, decimal_literal_example6) {
  Token token = scan("1.1E-21");
  assert_token(token, REAL, "1.1E-21");
}

TEST_F(ScannerTest, decimal_literal_example7) {
  Token token = scan("1.1E+21");
  assert_token(token, REAL, "1.1E+21");
}

TEST_F(ScannerTest, decimal_literal_example8) {
  Token token = scan("1.E21");
  assert_token(token, REAL, "1.E21");
}

TEST_F(ScannerTest, decimal_literal_example9) {
  Token token = scan("1.E-21");
  assert_token(token, REAL, "1.E-21");
}

TEST_F(ScannerTest, decimal_literal_example10) {
  Token token = scan("1.E+21");
  assert_token(token, REAL, "1.E+21");
}

TEST_F(ScannerTest, decimal_literal_example11) {
  Token token = scan(".1E21");
  assert_token(token, REAL, ".1E21");
}

TEST_F(ScannerTest, decimal_literal_example12) {
  Token token = scan(".1E-21");
  assert_token(token, REAL, ".1E-21");
}

TEST_F(ScannerTest, decimal_literal_example13) {
  Token token = scan(".1E+21");
  assert_token(token, REAL, ".1E+21");
}

TEST_F(ScannerTest, decimal_literal_example14) {
  Token token = scan("1E20");
  assert_token(token, REAL, "1E20");
}

TEST_F(ScannerTest, decimal_literal_example15) {
  Token token = scan("1E-20");
  assert_token(token, REAL, "1E-20");
}

TEST_F(ScannerTest, decimal_literal_example16) {
  Token token = scan("1E+20");
  assert_token(token, REAL, "1E+20");
}

TEST_F(ScannerTest, rational) {
  Token token = scan("122/123");
  assert_token(token, RATIONAL, "122/123");
}

TEST_F(ScannerTest, binary_number) {
  Token token = scan("#b10101010101");
  assert_token(token, INTEGER, "#b10101010101");
}

TEST_F(ScannerTest, binary_rational) {
  Token token = scan("#b111/11");
  assert_token(token, RATIONAL, "#b111/11");
}

TEST_F(ScannerTest, octal_number) {
  Token token = scan("#o01234567");
  assert_token(token, INTEGER, "#o01234567");
}

TEST_F(ScannerTest, octal_rational) {
  Token token = scan("#o56/75");
  assert_token(token, RATIONAL, "#o56/75");
}

TEST_F(ScannerTest, decimal_number) {
  Token token = scan("#d159");
  assert_token(token, INTEGER, "#d159");
}

TEST_F(ScannerTest, decimal_rational) {
  Token token = scan("#d122/123");
  assert_token(token, RATIONAL, "#d122/123");
}

TEST_F(ScannerTest, hexadecimal_number) {
  Token token = scan("#x34AF");
  assert_token(token, INTEGER, "#x34AF");
}

TEST_F(ScannerTest, hexadecimal_rational) {
  Token token = scan("#x34/AF");
  assert_token(token, RATIONAL, "#x34/AF");
}

TEST_F(ScannerTest, exact_integer) {
  Token token = scan("#e45");
  assert_token(token, RATIONAL, "#e45");
}

TEST_F(ScannerTest, exact_decimal) {
  Token token = scan("#e45.5");
  assert_token(token, RATIONAL, "#e45.5");
}

TEST_F(ScannerTest, exact_rational) {
  Token token = scan("#e122/123");
  assert_token(token, RATIONAL, "#e122/123");
}

TEST_F(ScannerTest, inexact_integer) {
  Token token = scan("#i45");
  assert_token(token, REAL, "#i45");
}

TEST_F(ScannerTest, inexact_decimal) {
  Token token = scan("#i45.5");
  assert_token(token, REAL, "#i45.5");
}

TEST_F(ScannerTest, inexact_rational) {
  Token token = scan("#i122/123");
  assert_token(token, REAL, "#i122/123");
}

/*
 * TODO Literal data
 */

}
