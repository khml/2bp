# Blue Print Grammar

## EBNF

program = statement*

statement = expr ";" | "{" program "}"

expr = (identifier “=“ ) equality

equality = relation ( “&&” relation | “||” relation)

relation = sum ( [ "==", <", "<=", ">=", ">" ] sum )*

sum = mul ( “+” mul | “-“ mul )*

mul = unary ( “*” unary | “/“  unary | “%” unary )*

unary = ( "+" | "-" ) priority

priority = chain | “(“ equality “)”

chain = primary ( “.” primary )*

primary = identifier ( args )

args = "(" ( equality ( “,” equality )* ) ")"

identifier = [_a-zA-Z][_a-zA-Z0-9]? | [0-9] ( "." [0-9]+ ) ( "f" )