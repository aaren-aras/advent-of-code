#include <memory>
#include <string>
#include <format>
#include <openssl/evp.h> // md5.h is deprecated but still usable? (low-level API)
#include <iostream>

std::string getMD5(const std::string& input) {
    /* 
        Uses RAII/smart pointers so EVP_MD_CTX_free gets auto-called when context goes out of scope.
        EVP_MD_CTX is a C struct, not a C++ obj, so `delete` doesn't work: needs EVP_MD_CTX_free
    */
    
    // Define container to keep track of hashing
    std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> context(EVP_MD_CTX_new(), EVP_MD_CTX_free);
    if (!context) throw std::runtime_error("*ERROR: Failed to create EVP_MD_CTX...");

    // Bind container context to MD5 algo 
    if (1 != EVP_DigestInit_ex(context.get(), EVP_md5(), nullptr)) // C-style error handling
        throw std::runtime_error("*ERROR: EVP_DigestInit_ex failed...");

    // Pass md5Input to MD5 algo
    if (1 != EVP_DigestUpdate(context.get(), input.c_str(), input.length())) 
        throw std::runtime_error("*ERROR: EVP_DigestUpdate failed...");

    // Local variables passed into OpenSSL funcs need to be unsigned 
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLength {};

    // Compute hash and write raw bytes to hash[]
    if (1 != EVP_DigestFinal_ex(context.get(), hash, &hashLength)) 
        throw std::runtime_error("*ERROR: EVP_DigestFinal_ex failed...");

    std::string hexResult;
    hexResult.reserve(hashLength * 2); // pre-allocate memory (32 bytes for MD5)
    
    // Convert raw bytes to hexadecimal string 
    for (int i = 0; i < hashLength; i++) hexResult += std::format("{:02x}", hash[i]);

    return hexResult;
}

int main() {
    std::string puzzleInput = "iwrupvqb";
    std::string md5Hash;
    int lowestPosNum {}; 

    // Keep making input strings until one generates an MD5 hash starting with "000000"
    while (!md5Hash.starts_with("000000")) {
        lowestPosNum++;
        
        std::string md5Input = puzzleInput + std::to_string(lowestPosNum);
        // std::cout << std::format("Input String: {}\n", md5Input); 
        
        md5Hash = getMD5(md5Input);
        // std::cout << std::format("Generated Hash: {}\n", md5Hash); 
    }
    std::cout << std::format("The lowest positive number producing such a hash is {}.\n", lowestPosNum);

    return 0;
}