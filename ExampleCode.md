# BP Programming Language
bp is small programming language (transpile to C++ program).

# Example Codes

#### Hello World

hello.bp
```
print("Hello World")
```

helloFunc.bp
```
fn hello() -> void
    print("Hello World")

hello()
```

#### For Loop

forExample.bp
```
fn hello() -> void
    print("Hello World")

for(i :int = 0; i < 5; i++)
    hello()

```
