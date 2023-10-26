# PHP-Compiler-into-Java-byte-code

## How to use on Windows:

Step 1:
``` bash
.\bison.exe -d parser.y
```

Step 2:
``` bash
.\flex.exe lexer.l
```

Step 3: compile
``` bash
gcc -o result parser.tab.c lex.yy.c
```

Step 4:
``` bash
.\result.exe .\example.php > result.txt
```
