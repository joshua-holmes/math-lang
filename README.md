# Math Lang

Hello, I am writing a compiler in C so I can learn about how compilers work and to improve my C skills (which are lacking).

The abomination I have spawned is called Math Lang. It's a bash-style case-insensitive ~~monstrosity~~ language focused on performing math operations on large data sets... Well it would be if I implemented the ability to accept large data sets. Look, it's a very rough prototype. Will it ever see it's potential? Probably not, but only time will tell.

# How It Works
The language is separated into commands, operands, names, and numbers.

## Command
A command performs a task and does not return anything as a result. This is similar to a statement in other languages. An example of a command would be `print`. `print 5` will print `5` to stdout.* Another example of a command is `make`, which is used for assigning variables and takes in 2 arguments, a name (we'll get to those later) and a number. `make x 8` will store the number `8` in memory under the name `x`. Since `make` is also a command (one is commanding a value to be stored in memory), it does not return anything.

* Currently, `print` can only print the first argument passed to it.

Here are the available commands and their arguments:
```
make <name> <number>
print <number>
```

## Operand
An operand performs a task and **does** return a value. Think of this as an expression in other languages. For example, `add` is an operand that takes in 2 arguments, both numbers, and then returns a number. `add 8 6` will add 8 and 6 and return the result. Since this is evaluated as a number, this can be chained together with commands. So `print add 8 6` will print `14` to the console. `make x add 4 4` will store `8` in memory under the name `x`.

Operands can also be chained together with other operands. `add 3 add 4 5` will return `12`. Let's walk through this. The compiler walks backward, so first `add 4 5` is evaluated as `9`. Then we have `add 3 9` left. `3` is evaluated as...well...`3`. It's already a number, so nothing really happens. Then `add 3 9` is evaluated as `12`.

What do you think this will print to the console?
```print add add 4 5 add 9 8```
The sky's the limit, but I wouldn't get to carried away, for the sake of your sanity.

Here are the available operands and their arguments:
```
add <number> <number>
sub <number> <number>
```

## Name
A name is used to store data and access it again later. Basically it's just variable names. When a name is used in the place of a number, the application looks for a value with that name and returns it. For example, the `add` operand requires 2 arguments, both numbers. We can substitute one of the numbers with a name. For example, this works just fine and will print `10` to the console.
```
make num 8
print add num 2
```

## Number
A number is a 32 bit integer. Currently floats are not supported and neither are negative numbers.
