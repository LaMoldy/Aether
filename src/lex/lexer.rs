use crate::token::{Token, TokenType};

pub struct Lexer<'source> {
    source: &'source str,
    cursor: usize,
    char: u8,
    line: u64,
    col: u64,
}

impl<'source> Lexer<'source> {
    pub fn new(source: &'source str) -> Self {
        let mut lexer = Self {
            source,
            cursor: 0,
            char: 0,
            line: 1,
            col: 0,
        };
        lexer.read_char();
        lexer
    }

    pub fn tokenize(&mut self) -> Vec<Token> {
        let mut tokens = Vec::new();
        while self.char != 0 {
            tokens.push(self.get_next_token());
        }
        tokens
    }

    fn get_next_token(&mut self) -> Token {
        self.skip_whitespace();

        match self.char {
            0 => Token {
                token_type: TokenType::Eof(String::new()),
                line: self.line,
                column: self.col,
            },
            b'"' => self.read_string(),
            b'0'..=b'9' => self.read_number(),
            b'a'..=b'z' | b'A'..=b'Z' => self.read_identifier(),
            _ => {
                if self.is_operator(self.char) {
                    self.read_operator()
                } else if self.is_symbol(self.char) {
                    self.read_symbol()
                } else {
                    self.read_unknown()
                }
            }
        }
    }

    fn skip_whitespace(&mut self) {
        let mut last_char = self.char;
        while self.char.is_ascii_whitespace() {
            match self.char {
                b'\n' => {
                    if last_char == b'\r' {
                        self.line -= 1;
                    } else {
                        self.line += 1;
                        self.col = 1;
                    }
                }
                b'\r' => {
                    self.line += 1;
                    self.col = 1;
                }
                _ => {}
            }
            last_char = self.char;
            self.read_char();
        }
    }

    fn read_char(&mut self) {
        if self.cursor >= self.source.len() {
            self.char = 0;
        } else {
            self.char = self.source.as_bytes()[self.cursor];
            self.cursor += 1;
            self.col += 1;
        }
    }

    fn read_identifier(&mut self) -> Token {
        let line = self.line;
        let column = self.col;

        let mut value = String::new();

        while self.char.is_ascii_alphabetic() || self.char == b'_' {
            value.push(self.char as char);
            self.read_char();
        }

        let token_type = if Token::is_keyword(&value) {
            Token::keyword_to_token_type(&value)
        } else {
            TokenType::Identifier(value)
        };

        Token {
            token_type,
            line,
            column,
        }
    }

    fn read_number(&mut self) -> Token {
        let line = self.line;
        let column = self.col;

        let mut value = String::new();

        while self.char.is_ascii_digit() {
            value.push(self.char as char);
            self.read_char();
        }

        Token {
            token_type: TokenType::Integer(value.parse().unwrap()),
            line,
            column,
        }
    }

    fn is_operator(&self, char: u8) -> bool {
        char == b'+'
            || char == b'-'
            || char == b'*'
            || char == b'/'
            || char == b'='
            || char == b'<'
            || char == b'>'
            || char == b'!'
            || char == b'&'
            || char == b'|'
    }

    fn read_operator(&mut self) -> Token {
        let line = self.line;
        let column = self.col;

        let mut value = String::new();

        while self.is_operator(self.char) {
            value.push(self.char as char);
            self.read_char();
        }

        Token {
            token_type: TokenType::Operator(value.to_owned()),
            line,
            column,
        }
    }

    fn read_string(&mut self) -> Token {
        let line = self.line;
        let column = self.col;

        let mut value = String::new();

        self.read_char();
        while self.char != b'"' && self.char != 0 {
            value.push(self.char as char);
            self.read_char();
        }

        if self.char == b'"' {
            self.read_char();
        }

        Token {
            token_type: TokenType::String(value.to_owned()),
            line,
            column,
        }
    }

    fn is_symbol(&self, char: u8) -> bool {
        char == b'('
            || char == b')'
            || char == b'}'
            || char == b'{'
            || char == b','
            || char == b'.'
            || char == b':'
            || char == b';'
    }

    fn read_symbol(&mut self) -> Token {
        let line = self.line;
        let column = self.col;

        let value = self.char as char;
        self.read_char();

        Token {
            token_type: TokenType::Symbol(value.to_string()),
            line,
            column,
        }
    }

    fn read_unknown(&mut self) -> Token {
        let line = self.line;
        let column = self.col;

        let value = self.char.to_string();

        Token {
            token_type: TokenType::Unknown(value.to_owned()),
            line,
            column,
        }
    }
}
