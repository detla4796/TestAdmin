#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <include/encryption.h>

class Encryptor {
private:
    unsigned char key[32]; // 256 bit key
    unsigned char iv[16];  // 128 bit IV

public:
    Encryptor() {
        // Initialize OpenSSL
        OpenSSL_add_all_algorithms();
        
        // Generate random key and IV
        RAND_bytes(key, sizeof(key));
        RAND_bytes(iv, sizeof(iv));
    }

    ~Encryptor() {
        // Cleanup OpenSSL
        EVP_cleanup();
    }

    std::string encrypt(const std::string& plaintext) {
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        if(!ctx) {
            throw std::runtime_error("Failed to create cipher context");
        }

        if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to initialize encryption");
        }

        std::string ciphertext;
        ciphertext.resize(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
        int out_len1 = 0;
        int out_len2 = 0;

        if(1 != EVP_EncryptUpdate(ctx, (unsigned char*)&ciphertext[0], &out_len1,
                                (const unsigned char*)plaintext.c_str(), plaintext.size())) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to encrypt data");
        }

        if(1 != EVP_EncryptFinal_ex(ctx, (unsigned char*)&ciphertext[out_len1], &out_len2)) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to finalize encryption");
        }

        EVP_CIPHER_CTX_free(ctx);
        ciphertext.resize(out_len1 + out_len2);
        return ciphertext;
    }

    std::string decrypt(const std::string& ciphertext) {
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        if(!ctx) {
            throw std::runtime_error("Failed to create cipher context");
        }

        if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to initialize decryption");
        }

        std::string plaintext;
        plaintext.resize(ciphertext.size());
        int out_len1 = 0;
        int out_len2 = 0;

        if(1 != EVP_DecryptUpdate(ctx, (unsigned char*)&plaintext[0], &out_len1,
                                (const unsigned char*)ciphertext.c_str(), ciphertext.size())) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to decrypt data");
        }

        if(1 != EVP_DecryptFinal_ex(ctx, (unsigned char*)&plaintext[out_len1], &out_len2)) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to finalize decryption");
        }

        EVP_CIPHER_CTX_free(ctx);
        plaintext.resize(out_len1 + out_len2);
        return plaintext;
    }
};

// Example usage
int main() {
    try {
        Encryptor encryptor;
        std::string original = "Hello, OpenSSL encryption!";
        std::cout << "Original text: " << original << std::endl;

        // Encrypt the text
        std::string encrypted = encryptor.encrypt(original);
        std::cout << "Encrypted length: " << encrypted.length() << " bytes" << std::endl;

        // Decrypt the text
        std::string decrypted = encryptor.decrypt(encrypted);
        std::cout << "Decrypted text: " << decrypted << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
