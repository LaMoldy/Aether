pub mod ast;
pub mod cli;
pub mod lex;
pub mod parse;
pub mod source;
pub mod token;
pub mod translater;

use clap::Parser;

pub fn run() -> std::io::Result<i32> {
    let args = cli::Args::parse();

    match args.command {
        cli::Command::Run { file } => {
            let source = source::read_file(&file)?;

            let mut lexer = lex::Lexer::new(&source);
            let tokens = lexer.tokenize();

            // for token in tokens.clone() {
            //     println!("{:?}", token.to_string());
            // }

            let mut parser = parse::Parser::new(tokens);
            match parser.parse() {
                Ok(statements) => {
                    let program = ast::Program { statements };
                    let interpreter = translater::Interpreter::new();
                    let result = interpreter.execute(&program);
                    match result {
                        translater::ControlFlow::Continue => Ok(0),
                        translater::ControlFlow::Return(translater::Value::Integer(value)) => {
                            Ok(value as i32)
                        }
                        translater::ControlFlow::Return(translater::Value::String(_)) => Ok(0),
                    }
                }
                Err(err) => Err(std::io::Error::new(std::io::ErrorKind::Other, err)),
            }
        }
        cli::Command::Build { file } => {
            println!("file: {}", file);
            Ok(0)
        }
        cli::Command::Check { file } => {
            println!("file: {}", file);
            Ok(0)
        }
    }
}
