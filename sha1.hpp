#include <iostream>
#include <string>
using namespace std;
class SHA1
{
public:
    SHA1();
    void update(const string &s);
    void update(istream &is);
    char* final1();
    static string from_file(const string &filename);

private:

    static const size_t DIGEST_INTS = 5;  /* number of 32bit integers per SHA1 digest */
    static const size_t BLOCK_INTS = 16;  /* number of 32bit integers per SHA1 block */
    static const size_t BLOCK_BYTES = BLOCK_INTS * 4;

    uint32_t digest[DIGEST_INTS];
    string buffer;
    uint64_t transforms;

    void reset();
    void transfor(uint32_t block[BLOCK_BYTES]);

    static void buffer_to_block(const string &buffer, uint32_t block[BLOCK_BYTES]);
    static void read(istream &is,string &s, int );
};
char * sha1(const char *strin);
