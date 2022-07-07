# Log-reader

## Compile

```
gcc src/main.c src/services/buffer/buffer.c src/utils/utils.c src/services/lexer/lexer.c src/services/ast/ast.c src/services/parser/parser.c src/utils/stack.c src/services/symbol/symbol.c src/services/parser/expression.c -o app
```

## Run App

```
pws
.\app.exe input/test.intech
bash 
./app.exe input/test.intech
```

## Note

loop with while
and do a if case
check if we re into bracket so we make sure to be inside a function
else search for a function
