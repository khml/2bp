# Blue Print Grammar

## EBNF

code = statements*
statements = expression | "{" statements* "}"
expression = ( "return" ) equation| function
function = "fn" identifier defArgs : type "{" statements "}"
equation = assignment | condition ";"
assignment = identifier ( ":" type ) “=“ condition ";"
condition = comparison ( “&&” comparison | “||” comparison)*
comparison = sum ( [ "==", <", "<=", ">=", ">" ] sum )*
type = identifier
sum = mul ( “+” mul | “-“ mul )*
mul = unary ( “*” unary | “/“  unary | “%” unary )*
unary = ( "+" | "-" ) priority
priority = primary | “(“ condition “)”
primary = identifier ( calleeArgs )
defArgs = "(" ")" | "(" identifier ":" type ( "," identifier ":" type )*  ")"
calleeArgs = "(" ")" | "(" condition ( "," condition )*  ")"
identifier = [_a-zA-Z][_a-zA-Z0-9]? | [0-9] ( "." [0-9]+ ) ( "f" )
