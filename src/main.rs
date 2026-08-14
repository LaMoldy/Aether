mod cli;

fn main() {
    let exit_code = match aether::run() {
        Ok(code) => code,
        Err(err) => {
            eprintln!("Error: {}", err);
            1
        }
    };
    std::process::exit(exit_code);
}
