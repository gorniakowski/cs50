from cs50 import get_int

while True:
    number = get_int("Number:")
    if number >= 0:
        break
sum_digits = 0
sum_odd = 0
card_type = 0
while number > 0:
    if number > 9 and number < 100:
        card_type = number
    sum_odd = sum_odd + number % 10
    number = (number - number % 10) / 10
    digit = (number % 10) * 2
    if number > 9 and number < 100:
        card_type = number
    while digit > 0:
        sum_digits = sum_digits + (digit % 10)
        digit = (digit - digit % 10) / 10
    number = (number - number % 10) / 10

if card_type == 34 or card_type == 37:
    print("AMEX")
elif card_type >= 51 and card_type <= 55:
    print("MASTERCARD")
elif card_type >= 40 and card_type <= 49:
    print("VISA")
else:
    print("INVALID")