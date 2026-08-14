mod cli;

use clap::Parser;
use cli::Args;

fn main() {
    let _ = Args::parse();
}
