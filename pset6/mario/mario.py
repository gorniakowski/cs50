from cs50 import get_int


while True:
    n = get_int("Height: ")  # ask for number of line
    if n >= 0 and n <= 23:  # check input
        break
for i in range(n):  # go for every line
    for j in range(n - (i + 1)):  # print spcaes first
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")  # then #
    print("  ", end="")  # ten double space on the middle fo the tower
    for b in range(i + 1):
        print("#", end="")  # hashtag again
    print()  # new line
