#ifndef _SCHEMESE_PARSER_H
#define _SCHEMESE_PARSER_H

#include <schemese/scanner.h>


namespace Schemese {
  class Ast {
    public:
      std::vector<Ast*> children;
      Token* token;
  };

  class TokenStream {
    public:
      void push(Token token);
      Token read();
    private:
      std::queue<Token> queue;
  };

  class Parser {
    public:
      Parser(TokenStream stream);
      Ast* parse();
    private:
      TokenStream token_stream;
      Ast* root = NULL;
  };
}

#endif
