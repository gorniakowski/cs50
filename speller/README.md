# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

longest wird in english, lung disease.
## According to its man page, what does `getrusage` do?

return resurces usage

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

otherwise every time you call before and after there will be a now copy made. In short to save resources.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The main for loop uses function fgetc to read every single character from file until it reaches EOF (end og file). it also stores character
in varaiable c. Then if statement check wheter character stored in c is a valid charcter: letter of an alphabet or ' sign (apostrophy can't be
at the beginnig of a word). If the statement is true we append a charter to an array and increse the index (letter count) by one. If the string
is too long to be a word, we iterate do end of it and reset index to . We do the same if the word contains digits. Then if we found the
whole word ie index is greater than 0 we terminate the word with \0 sign and update the word counter.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?
It's hard to exclude numeric character from fscanf fucntion. It is also har to forsee the memeory nedded to be alocated.


## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

because they are not to be changend during the whole eexecution of a program.
