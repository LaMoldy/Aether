#[derive(Debug, Clone, PartialEq, Eq)]
pub enum TokenType {
    Unknown(String),
    Return,
    Identifier,
    Operator(String),
    Symbol(String),
    Integer(i64),
    String(String),
    Eof,
}

impl TokenType {
    pub fn is_keyword(ident: &str) -> bool {
        matches!(ident, "ret")
    }

    pub fn keyword_to_token_type(ident: &str) -> TokenType {
        match ident {
            "ret" => TokenType::Return,
            _ => TokenType::Identifier,
        }
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Token {
    pub token_type: TokenType,
    pub value: String,
    pub line: u64,
    pub column: u64,
}
