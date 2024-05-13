def vigenere_encrypt(plain_text, key):
    encrypted_text = ''
    key_repeated = (key * (len(plain_text) // len(key))) + key[:len(plain_text) % len(key)]

    for p, k in zip(plain_text, key_repeated):
        if p.isalpha():
            base = ord('a') if p.islower() else ord('A')
            encrypted_text += chr((ord(p) + ord(k) - 2 * base) % 26 + base)
        else:
            encrypted_text += p

    return encrypted_text

def vigenere_decrypt(encrypted_text, key):
    decrypted_text = ''
    key_repeated = (key * (len(encrypted_text) // len(key))) + key[:len(encrypted_text) % len(key)]

    for c, k in zip(encrypted_text, key_repeated):
        if c.isalpha():
            base = ord('a') if c.islower() else ord('A')
            decrypted_text += chr((ord(c) - ord(k) + 26) % 26 + base)
        else:
            decrypted_text += c

    return decrypted_text

# Example usage:
plain_text = "HelloWorld"
key = "KEY"
encrypted_text = vigenere_encrypt(plain_text, key)
decrypted_text = vigenere_decrypt(encrypted_text, key)

print(f'Plain Text: {plain_text}')
print(f'Key: {key}')
print(f'Encrypted Text: {encrypted_text}')
print(f'Decrypted Text: {decrypted_text}')
