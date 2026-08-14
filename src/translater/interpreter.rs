use crate::ast::{Expression, Program, Statement};

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Value {
    Integer(i64),
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
                return ControlFlow::Return(Value::Integer(value));
            }
        }
    }

    fn evaluate_expression(&self, expression: &Expression) -> i64 {
        match expression {
            Expression::Integer(value) => *value,
            _ => 0,
        }
    }
}
