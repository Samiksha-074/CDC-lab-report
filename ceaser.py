
def encrypt_text(plaintext,n):
    ans = ""
    for i in range(len(plaintext)):
        ch = plaintext[i]
        # check if a character is uppercase then encrypt it accordingly 
        if (ch.isupper()):
            ans += chr((ord(ch) + n-65) % 26 + 65)
        # check if a character is lowercase then encrypt it accordingly
        elif ch.islower():
            ans += chr((ord(ch) + n-97) % 26 + 97)
        else:
            ans += ch
    
    return ans


def decrypt_text(text, shift):
    ans = ""
    for i in range(len(text)):
        ch = text[i]
        if ch.isupper():
                ans += chr((ord(ch) - shift - 65) % 26 + 65)
        elif ch.islower():
                ans += chr((ord(ch) - shift - 97) % 26 + 97)
        else:
             ans += ch
             
    return ans

plaintext = "HELLO WORLD"
shift = 3
et=encrypt_text(plaintext,shift)
dt=decrypt_text(et,shift)

print("Original Text:", plaintext)
print("Encrypted Text:", et)
print("Decrypted Text:", dt)



