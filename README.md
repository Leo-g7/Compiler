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

Il manque quelques éléments au programme pour pouvoir lancer les fonctions principales. Cependant la plupart des fonctions du parser sont fonctionnelles ainsi que la table des symboles. 
Les fonctions d'analyse retournent void car elles ne sont pas finies.
Nous avons commenté au mieux nos fonctions pour aider la compréhension du programme.
Il est possible de tester les différentes fonctions à l'aide d'un point de debug.

## Difficulté

Beaucoup de temps perdu sur le C, malgrè une bonne compréhension des différents éléments du compilateur.

## Axe d'amélioration

Manque de précision de notre part dans l'estimation du temps nécessaire pour réaliser les tâches.
Si ce projet était à refaire nous le referions dans un langage que l'on maîtrise mieux.
