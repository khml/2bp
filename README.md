# BP
BP is small programming language (transpile to C++ program).

## dependencies

- GCC 7.5 and more

## Getting Started

#### build

```sh
$ git clone https://github.com/khml/2bp.git

$ cd 2bp

$ mkdir build && cd build

$ cmake ..

# build bp compiler(transpiler)
$ make

# bp is transpiler

$ ./bp
> 1+2*3
1 | IDENTIFIER | INTEGER
+ | ADD | OPERATOR
2 | IDENTIFIER | INTEGER
* | ASTERISK | OPERATOR
3 | IDENTIFIER | INTEGER
 | WHITESPACE | IDENTIFIER
> ^C

$ echo 'print("Hello")' > hello.bp

$ ./bp hello.bp

$ ./a.out
Hello

```
