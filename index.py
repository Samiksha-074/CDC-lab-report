def encrypt_rail_fence(text, key):
    return ''.join(text[i::2*(key-1)] for i in range(key))



text_to_encrypt = "swastik college is at bhaktapur"
key = 3

encrypted_text = encrypt_rail_fence(text_to_encrypt, key)
print("Encrypted Text:", encrypted_text)

