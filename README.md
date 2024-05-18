# TSMMake

# A TSM Studios production

Developed by SaphirDeFeu

## TSMMake, a build tool for Cxx development

Made to ease the creation of Cxx projects while providing flexible tooling, allowing for pratically the same control as GNU Make, while staying easy and quick to setup like Cargo.

# Table of Contents

- [Usage](#usage)
  - [Setup](#project-setup)
  - [Configuration](#configurating)
  - [Building and running](#building-and-running)

# Usage

All commands of TSMMake are available through the command line with the `-h` (alias. `--help`, `help`) flag.

## Project setup

TSMMake projects are as quick and easy as can be. One command and you're set!  
Use `tsmmake new <project_name>` and TSMMake will create a new directory named `project_name` with pre-written config and code.

## Configurating

TSMMake will create a `TSMMake.toml` file in the root directory of the project, with default fields.

By default, the file looks like this upon project initialization :

```toml
[project]
name = "<project_name>"
version = "1.0.0"
lang = "cpp"
compiler = "g++"
compiler_flags = "-Wall"
```

As such will be configured a default compiler `g++` and includes compiler flags which can be tweaked to your desires.  
  
You can modify the default fields by specifying them in a `default.toml` file in the same folder as where you installed the tsmmake binary.  
For example, if the compiled binary is located at `/usr/local/bin/tsmmake/tsmmake.bin` : this means that you can add a default.toml file at `/usr/local/bin/tsmmake/default.toml` and it'll be picked up by the binary upon project creation.  
This can allow you to create new `TSMMake` for C quickly and easily.

## Building and running

### Building

When you wrote your program, you can build your project with the command `tsmmake build`  
This will build your source code into object files before linking them into a single executable file.  
When compiling your program, TSMMake will use the compiler flags you set in your configuration file to customize the way the compiler will work.

### Running

To run your program quickly, you can build and run your project with the command `tsmmake run`  
This both builds your source code and runs the resulting executable.  
You can pass in arguments to your program by adding arguments after a double-dash, i.e. `tsmmake run -- [args]`

### Building library files

You can add a `-i` (alias. `--include-deps`) flag to a build/run command to compile code contained inside the include folder of your project.  
This can be used to one-time compile user-defined libraries that aren't supposed to change often
