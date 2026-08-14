use aether::lexer::{Lexer, TokenType};

#[test]
fn tokenizes_return() {
    let mut lexer = Lexer::new("ret 42");
    let tokens = lexer.tokenize();

    assert_eq!(tokens[0].token_type, TokenType::Return);
    assert_eq!(tokens[1].token_type, TokenType::Integer(42));
}

#[test]
fn tokenizes_string() {
    let mut lexer = Lexer::new(r#""hello""#);
    let tokens = lexer.tokenize();

    assert_eq!(tokens[0].token_type, TokenType::String("hello".to_string()));
}

#[test]
fn tokenizes_identifier() {
    let mut lexer = Lexer::new("answer");
    let tokens = lexer.tokenize();

    assert_eq!(tokens[0].token_type, TokenType::Identifier);
}

#[test]
fn tokenizes_expression() {
    let mut lexer = Lexer::new("42 + 10");
    let tokens = lexer.tokenize();

    assert_eq!(tokens[0].token_type, TokenType::Integer(42));
    assert_eq!(tokens[1].token_type, TokenType::Operator("+".to_string()));
    assert_eq!(tokens[2].token_type, TokenType::Integer(10));
}
