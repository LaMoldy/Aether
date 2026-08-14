pub mod cli;
pub mod lexer;
pub mod source;

use clap::Parser;

pub fn run() {
    let args = cli::Args::parse();

    match args.command {
        cli::Command::Run { file } => {
            let source = source::read_file(&file).unwrap();
            let mut lexer = lexer::Lexer::new(&source);
            let tokens = lexer.tokenize();
            println!("Tokens:");
            for token in tokens {
                println!("Token: {:?}", token);
            }
        }
        cli::Command::Build { file } => {
            println!("file: {}", file);
        }
        cli::Command::Check { file } => {
            println!("file: {}", file);
        }
    }
}
