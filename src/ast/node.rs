#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Expression {
    Integer(i64),
    Identifier(String),
    String(String),
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Statement {
    Return(Expression),
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Program {
    pub statements: Vec<Statement>,
}
