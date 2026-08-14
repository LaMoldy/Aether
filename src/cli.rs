use clap::Parser;
use clap::Subcommand;

#[derive(Parser)]
#[command(name = "aether")]
#[command(version)]
#[command(about = "The Aether programming language")]
pub struct Args {
    #[command(subcommand)]
    pub command: Command,
}

#[derive(Subcommand)]
pub enum Command {
    /// Runs the aether source file
    Run { file: String },

    /// Builds the aether source file
    Build { file: String },

    /// Checks the aether source file
    Check { file: String },
}
