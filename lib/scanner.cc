#include <iterator>
#include <algorithm>
#include <schemese/scanner.h>
using namespace Schemese;

extern int yylex();
extern int yyleng;
extern char* yytext;

ScannerBuffer Scanner::buffer;

void ScannerBuffer::read_bytes(std::istream& stream) {
  char c;
  while((c = stream.get()) >= 0){
    buffer.push(c);
  }
}

unsigned long ScannerBuffer::write_bytes(char* buf, int max_size) {
  unsigned long written_bytes = 0;
  while(written_bytes < max_size && !buffer.empty()) {
    buf[written_bytes] = buffer.front();
    buffer.pop();
    written_bytes++;
  }

  return written_bytes;
}


Scanner::Scanner(std::istream& input) : input_stream(input) {
}

Token Scanner::scan() {
  buffer.read_bytes(input_stream);
  return Token((TokenType)yylex(), std::string(yytext));
}

unsigned long Scanner::read(char* buf, int max_size) {
  return buffer.write_bytes(buf, max_size);
}
