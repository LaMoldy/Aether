use clap::Parser;

#[derive(Parser, Debug)]
#[command(name = "aether")]
#[command(version)]
#[command(about = "The Aether programming language", long_about = None)]
pub struct Args {
    /// Input Aether source file
    pub file: Option<String>,
}
