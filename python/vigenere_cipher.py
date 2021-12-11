# vigenere cipher

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# i=0
# while i<26:
#     print(alphabet[i:] + alphabet[:i])
#     i+=1

def vigenere_cipher(plaintext, key):
    table = [
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
    "BCDEFGHIJKLMNOPQRSTUVWXYZA",
    "CDEFGHIJKLMNOPQRSTUVWXYZAB",
    "DEFGHIJKLMNOPQRSTUVWXYZABC",
    "EFGHIJKLMNOPQRSTUVWXYZABCD",
    "FGHIJKLMNOPQRSTUVWXYZABCDE",
    "GHIJKLMNOPQRSTUVWXYZABCDEF",
    "HIJKLMNOPQRSTUVWXYZABCDEFG",
    "IJKLMNOPQRSTUVWXYZABCDEFGH",
    "JKLMNOPQRSTUVWXYZABCDEFGHI",
    "KLMNOPQRSTUVWXYZABCDEFGHIJ",
    "LMNOPQRSTUVWXYZABCDEFGHIJK",
    "MNOPQRSTUVWXYZABCDEFGHIJKL",
    "NOPQRSTUVWXYZABCDEFGHIJKLM",
    "OPQRSTUVWXYZABCDEFGHIJKLMN",
    "PQRSTUVWXYZABCDEFGHIJKLMNO",
    "QRSTUVWXYZABCDEFGHIJKLMNOP",
    "RSTUVWXYZABCDEFGHIJKLMNOPQ",
    "STUVWXYZABCDEFGHIJKLMNOPQR",
    "TUVWXYZABCDEFGHIJKLMNOPQRS",
    "UVWXYZABCDEFGHIJKLMNOPQRST",
    "VWXYZABCDEFGHIJKLMNOPQRSTU",
    "WXYZABCDEFGHIJKLMNOPQRSTUV",
    "XYZABCDEFGHIJKLMNOPQRSTUVW",
    "YZABCDEFGHIJKLMNOPQRSTUVWX",
    "ZABCDEFGHIJKLMNOPQRSTUVWXY",]

    repeated_key = key
    while len(repeated_key) < len(plaintext):
        repeated_key += key # concatenate

    ciphertext = ""
    for i,_ in enumerate(plaintext):
        y = ord(plaintext[i].upper())-65
        x = ord(repeated_key[i].upper())-65
        ciphertext += table[y][x]

    return ciphertext


if __name__ == "__main__":
    # test
    plaintext = "attackatdawn"
    key = "LEMON"
    ciphertext = vigenere_cipher(plaintext, key)
    if ciphertext != "LXFOPVEFRNHR":
        print("ERROR")
    
    print(ciphertext)

