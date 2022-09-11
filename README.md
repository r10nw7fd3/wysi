# WYSI

![logo](./WYSI_shade.png)

Brainfuck dialect

This repository contains the language itself as well as the bf2wysi converter

## Wordlist

| BF | WYSI   |
|----|--------|
| >  | when   |
| <  | you    |
| +  | almost |
| -  | see    |
| .  | it     |
| ,  | shige  |
| [  | 727    |
| ]  | wysi   |

## Building

```
./build.sh
```

## Notes

### Comments

Comment sections are defined like this:

```
[[ This is a test comment! ]]
```

They can also be nested:

```
[[ [[ hello ]] world! ]]
```

### Credits

"Hello world!"s are stolen from [Wikipedia](https://ru.wikipedia.org/wiki/Brainfuck)
