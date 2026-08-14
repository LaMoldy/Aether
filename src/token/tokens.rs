use std::fmt::{Display, Formatter, Result};

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Token {
    pub token_type: TokenType,
    pub line: u64,
    pub column: u64,
}

impl Token {
    pub fn new(token_type: TokenType, line: u64, column: u64) -> Self {
        Self {
            token_type,
            line,
            column,
        }
    }

    pub fn is_keyword(ident: &str) -> bool {
        matches!(ident, "ret")
    }

    pub fn keyword_to_token_type(ident: &str) -> TokenType {
        match ident {
            "ret" => TokenType::Return(ident.to_string()),
            _ => TokenType::Identifier(ident.to_string()),
        }
    }

    pub fn to_string(&self) -> String {
        format!(
            "\t{{\n\t\tType: {}\n\t\tLine: {}\n\t\tColumn: {}\n\t}},",
            self.token_type, self.line, self.column
        )
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum TokenType {
    Unknown(String),
    Return(String),
    Identifier(String),
    Operator(String),
    Symbol(String),
    Integer(i64),
    String(String),
    Eof(String),
}

impl TokenType {
    pub fn as_str(&self) -> &str {
        match self {
            TokenType::Unknown(val) => val.as_str(),
            TokenType::Return(val) => val.as_str(),
            TokenType::Identifier(val) => val.as_str(),
            TokenType::Operator(val) => val.as_str(),
            TokenType::Symbol(val) => val.as_str(),
            TokenType::Integer(_) => "",
            TokenType::String(val) => val.as_str(),
            TokenType::Eof(_) => "",
        }
    }

    pub fn as_number(&self) -> Option<i64> {
        match self {
            TokenType::Integer(val) => Some(*val),
            _ => None,
        }
    }
}

impl Display for TokenType {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result {
        match self {
            TokenType::Unknown(val) => write!(f, "Unknown({})", val),
            TokenType::Return(val) => write!(f, "Return({})", val),
            TokenType::Identifier(val) => write!(f, "{}", val),
            TokenType::Operator(val) => write!(f, "{}", val),
            TokenType::Symbol(val) => write!(f, "{}", val),
            TokenType::Integer(val) => write!(f, "{}", val),
            TokenType::String(val) => write!(f, "\"{}\"", val),
            TokenType::Eof(_) => write!(f, "EOF"),
        }
    }
}
