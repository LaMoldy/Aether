use crate::token::{Token, TokenType};

use std::error::Error;
use std::fmt;

#[derive(Debug)]
pub enum ParseError {
    UnexpectedTokenError(Token, TokenType),
    UnexpectedError(Token),
}

impl fmt::Display for ParseError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            ParseError::UnexpectedTokenError(actual, expected) => {
                write!(
                    f,
                    "Unexpected token encountered when parsing source file\nExpected: {}, Actual: {}, at line {}, column {}",
                    expected, actual.token_type, actual.line, actual.column
                )
            }
            ParseError::UnexpectedError(actual) => {
                write!(
                    f,
                    "Unexpected token encountered: {:?}, at line {}, column {}",
                    actual.token_type, actual.line, actual.column
                )
            }
        }
    }
}

impl Error for ParseError {}
