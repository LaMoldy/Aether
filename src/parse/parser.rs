use super::errors::ParseError;
use crate::ast::{Expression, Statement};
use crate::token::{Token, TokenType};

pub struct Parser {
    tokens: Vec<Token>,
    position: usize,
}

impl Parser {
    pub fn new(tokens: Vec<Token>) -> Self {
        Self {
            tokens,
            position: 0,
        }
    }

    pub fn parse(&mut self) -> Result<Vec<Statement>, ParseError> {
        let mut statements = Vec::new();

        while self.current_token().token_type != TokenType::Eof("".to_string()) {
            let statement = self.parse_statement();
            if let Some(statement) = statement {
                statements.push(statement);
            }
        }

        Ok(statements)
    }

    fn current_token(&self) -> &Token {
        &self.tokens[self.position]
    }

    fn advance(&mut self) {
        if self.position < self.tokens.len() {
            self.position += 1;
        }
    }

    fn consume_token(&mut self, expected_type: TokenType) -> Result<(), ParseError> {
        if self.current_token().token_type != expected_type {
            return Err(ParseError::UnexpectedTokenError(
                self.current_token().clone(),
                expected_type,
            ));
        }
        self.advance();
        Ok(())
    }

    fn parse_statement(&mut self) -> Option<Statement> {
        match self.current_token().token_type {
            TokenType::Return(_) => self.parse_return_statement().ok(),
            TokenType::Print(_) => self.parse_print_statement().ok(),
            _ => {
                return None;
            }
        }
    }

    fn parse_expression(&mut self) -> Option<Expression> {
        match self.current_token().token_type {
            TokenType::Integer(_) => Some(self.parse_integer()),
            TokenType::Identifier(_) => Some(self.parse_identifier()),
            TokenType::String(_) => Some(self.parse_string()),
            _ => {
                return None;
            }
        }
    }

    fn parse_integer(&mut self) -> Expression {
        let token = self.current_token().clone();
        self.advance();
        Expression::Integer(token.token_type.as_number().unwrap_or(0))
    }

    fn parse_identifier(&mut self) -> Expression {
        let token = self.current_token().clone();
        self.advance();
        Expression::Identifier(token.token_type.as_str().to_string().clone())
    }

    fn parse_string(&mut self) -> Expression {
        let token = self.current_token().clone();
        self.advance();
        Expression::String(token.token_type.as_str().to_string().clone())
    }

    fn parse_return_statement(&mut self) -> Result<Statement, ParseError> {
        self.consume_token(TokenType::Return("ret".to_string()))?;
        let expression = self
            .parse_expression()
            .ok_or_else(|| ParseError::UnexpectedError(self.current_token().clone()))?;
        Ok(Statement::Return(expression))
    }

    fn parse_print_statement(&mut self) -> Result<Statement, ParseError> {
        self.consume_token(TokenType::Print("print".to_string()))?;
        self.advance();
        let expression = self
            .parse_expression()
            .ok_or_else(|| ParseError::UnexpectedError(self.current_token().clone()))?;
        self.advance();
        Ok(Statement::Print(expression))
    }
}
