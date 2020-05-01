# BluePrint

Now can parse only simple sentence.

## Example

```
=x+y*z
node: +, left: x, right: *
node: x
node: *, left: y, right: z
node: y
node: z
 | IDENTIFIER
x | IDENTIFIER
+ | ADD
y | IDENTIFIER
* | ASTERISK
z | IDENTIFIER
digraph AST {
  graph [
    dpi = 300;
    ratio = 0.5;
  ]
  4 [ label = "+" ]
  4->0
  4->3
  0 [ label = "x" ]
  3 [ label = "*" ]
  3->1
  3->2
  1 [ label = "y" ]
  2 [ label = "z" ]
}
```