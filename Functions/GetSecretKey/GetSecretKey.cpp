// GetSecretKey.cpp
// This function returns the secret key used by the Caesar cipher.
//
// Why it exists: before, the number 5 was written separately inside
// EncryptTextFile.cpp AND DecryptTextFile.cpp. If someone changed one and
// forgot the other, decryption would quietly produce garbage with NO error
// message at all - the nastiest kind of bug, because nothing looks broken.
//
// Now both functions ask this one function for the key, so the two can never
// disagree. To change the key for the whole program, change it HERE only.

int getSecretKey()
{
    return 5;
}
