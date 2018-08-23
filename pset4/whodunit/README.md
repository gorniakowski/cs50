# Questions

## What's `stdint.h`?

Standard C library that allows to use exact-witdh integer types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

The program is portable and behaves the same in different platforms.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1,4,4,2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM,16973,424D

## What's the difference between `bfSize` and `biSize`?

biSize-number of bites requiered by the structure, bfSize- size of the bitmap file.

## What does it mean if `biHeight` is negative?

biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

he could not open/create a file.

## Why is the third argument to `fread` always `1` in our code?

because we read block of data only one time.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

changes the location of the pointer reading the file.

## What is `SEEK_CUR`?

speciefies that you change pointer offset from current location.
