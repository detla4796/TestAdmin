#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <fstream>
#include "include/encryption.h"

class Encryptor {
private:
    unsigned char key[32]; // 256-bit key
    unsigned char iv[16];  // 128-bit IV

    // Функция для загрузки ключа и IV из файла
    bool loadKeyAndIV(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        file.read(reinterpret_cast<char*>(key), sizeof(key));
        file.read(reinterpret_cast<char*>(iv), sizeof(iv));
        file.close();
        return true;
    }

    // Функция для сохранения ключа и IV в файл
    void saveKeyAndIV(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to save key and IV");
        }
        file.write(reinterpret_cast<const char*>(key), sizeof(key));
        file.write(reinterpret_cast<const char*>(iv), sizeof(iv));
        file.close();
    }

public:
    Encryptor() {
        OpenSSL_add_all_algorithms();

        // Попытка загрузить ключ и IV из файла
        if (!loadKeyAndIV("key_iv.bin")) {
            // Если файл не существует, генерируем новые ключ и IV
            RAND_bytes(key, sizeof(key));
            RAND_bytes(iv, sizeof(iv));

            // Сохраняем ключ и IV в файл
            saveKeyAndIV("key_iv.bin");
        }
    }

    ~Encryptor() {
        EVP_cleanup();
    }

    std::string encrypt(const std::string& plaintext) {
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        if (!ctx) {
            throw std::runtime_error("Failed to create cipher context");
        }

        if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to initialize encryption");
        }

        std::string ciphertext;
        ciphertext.resize(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
        int out_len1 = 0;
        int out_len2 = 0;

        if (1 != EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(&ciphertext[0]), &out_len1,
                                   reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size())) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to encrypt data");
        }

        if (1 != EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&ciphertext[out_len1]), &out_len2)) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to finalize encryption");
        }

        EVP_CIPHER_CTX_free(ctx);
        ciphertext.resize(out_len1 + out_len2);
        return ciphertext;
    }

    std::string decrypt(const std::string& ciphertext) {
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        if (!ctx) {
            throw std::runtime_error("Failed to create cipher context");
        }

        if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to initialize decryption");
        }

        std::string plaintext;
        plaintext.resize(ciphertext.size());
        int out_len1 = 0;
        int out_len2 = 0;

        if (1 != EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(&plaintext[0]), &out_len1,
                                   reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size())) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to decrypt data");
        }

        if (1 != EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&plaintext[out_len1]), &out_len2)) {
            EVP_CIPHER_CTX_free(ctx);
            throw std::runtime_error("Failed to finalize decryption");
        }

        EVP_CIPHER_CTX_free(ctx);
        plaintext.resize(out_len1 + out_len2);
        return plaintext;
    }
};

static Encryptor encryptor;

std::string encrypt(const std::string& plaintext) {
    return encryptor.encrypt(plaintext);
}

std::string decrypt(const std::string& ciphertext) {
    return encryptor.decrypt(ciphertext);
}