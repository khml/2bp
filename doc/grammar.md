# EBNF

| Usage | Notation |
| ----  | ----     |
| definition | "=" |
| termination | ";" |
| alternation | "|" |
| optional | [...]  // zero or one |
| repetition | {...}  // zero and more |
| repetition | ...+  // one and more |
| repetition | ...*  // zero and more |
| grouping | (...) |
| terminal string | "..." |


# Blue Print Grammar

code = statement*

statement = expression | statements

statements = "{" { statements | expression } "}"

expression = [ "return" ] equation | function | ifControl | forControl | whileControl

function = "fn" identifier defArgs "->" type statements

ifControl = "if" conditionBlock { "elif" conditionBlock } { "else" conditionBlock }

conditionBlock = "(" condition ")" statement

forControl = "for" "(" equation [condition] ";" [condition] ")" statement

whileControl = "while" "(" condition ")" statement

equation = ( assignment | condition ) ";"

assignment = identifier [ ":" type ] “=“ condition

condition = comparison { “&&” comparison | “||” comparison }

comparison = sum { ( "==" | <" | "<=" | ">=" | ">" ) sum }

type = identifier

sum = mul { “+” mul | “-“ mul }

mul = unary { “*” unary | “/“  unary | “%” unary }

unary = [ "+" | "-" ] priority

priority = incr | “(“ condition “)”

increment = [ "++" | "--" ] primary | primary [ "++" | "--" ]

primary = identifier [ calleeArgs ]

defArgs = "(" [ identifier ":" type { "," identifier ":" type } ] ")"

calleeArgs = "(" [ condition { "," condition } ] ")"

identifier = [_a-zA-Z][_a-zA-Z0-9]? | [0-9] ( "." [0-9]+ ) ( "f" )
