import sys
import crypt
import string

if len(sys.argv) == 2:
    code = sys.argv[1]
else:
    raise ValueError("Usage is: python crack.py hash")
salt = code[0] + code[1]
alphabet = list(string.ascii_letters)

for i in alphabet:
    if crypt.crypt(i, salt) == code:
        print(i)
        sys.exit()

for j in alphabet:
    for i in alphabet:
        if crypt.crypt(i + j, salt) == code:
            print(i + j)
            sys.exit()

for k in alphabet:
    for j in alphabet:
        for i in alphabet:
            if crypt.crypt(i + j + k, salt) == code:
                print(i + j + k)
                sys.exit()

for l in alphabet:
    for k in alphabet:
        for j in alphabet:
            for i in alphabet:
                if crypt.crypt(i + j + k + l, salt) == code:
                    print(i + j + k + l)
                    sys.exit()
for m in alphabet:
    for l in alphabet:
        for k in alphabet:
            for j in alphabet:
                for i in alphabet:
                    if crypt.crypt(i + j + k + l + m, salt) == code:
                        print(i + j + k + l + m)
                        sys.exit()
