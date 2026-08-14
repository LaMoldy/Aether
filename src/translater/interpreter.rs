use crate::ast::{Expression, Program, Statement};

use std::fmt;

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Value {
    Integer(i64),
    String(String),
}

impl fmt::Display for Value {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Value::Integer(value) => write!(f, "{}", value),
            Value::String(value) => write!(f, "{}", value),
        }
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum ControlFlow {
    Continue,
    Return(Value),
}

pub struct Interpreter;

impl Interpreter {
    pub fn new() -> Self {
        Self
    }

    pub fn execute(&self, program: &Program) -> ControlFlow {
        for statement in &program.statements {
            match self.execute_statement(statement) {
                ControlFlow::Continue => {}
                ControlFlow::Return(value) => return ControlFlow::Return(value),
            }
        }
        ControlFlow::Continue
    }

    pub fn execute_statement(&self, statement: &Statement) -> ControlFlow {
        match statement {
            Statement::Return(expression) => {
                let value = self.evaluate_expression(expression);
                return ControlFlow::Return(value.unwrap_or(Value::Integer(0)));
            }
            Statement::Print(expression) => {
                let value = self.evaluate_expression(expression);
                println!("{}", value.unwrap_or(Value::String("".to_string())));
                return ControlFlow::Continue;
            }
        }
    }

    fn evaluate_expression(&self, expression: &Expression) -> Result<Value, String> {
        match expression {
            Expression::Integer(value) => Ok(Value::Integer(*value)),
            Expression::String(value) => Ok(Value::String(value.clone())),
            _ => Err("Unexpected expression".to_string()),
        }
    }
}
