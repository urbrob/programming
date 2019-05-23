# Created By: Robert Urbaniak 215904 @ 04.10.2018 

roman = 'MCMDXXXIII'
arabic = 1997

roman_dict = {
    'M': 1000,
    'CM': 900,
    'D': 500,
    'CD': 400,
    'C': 100,
    'XC': 90,
    'L': 50,
    'XL': 40,
    'X': 10,
    'IX': 9,
    'V': 5,
    'IV': 4,
    'I': 1
}

def roman_to_arabic(number):
    result = 0
    max_letter = 'I'
    for letter in number[::-1]:
        if roman_dict[letter] < roman_dict[max_letter]:
            result -= roman_dict[letter]
        else:
            result += roman_dict[letter]
            max_letter = letter
    return result

def arabic_to_roman(number):
    result = ''
    while number > 0:
        for key, value in roman_dict.items():
            if number >= value:
                result += key
                number -= value
                break
    return result
            
    
