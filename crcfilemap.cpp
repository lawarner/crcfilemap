
#include "dirhandler.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stddef.h>
#include <stdint.h>
using std::cout;
using std::endl;
using std::string;


/* CRC-32C (iSCSI) polynomial in reversed bit order. */
#define POLY 0x82f63b78

/* CRC-32 (Ethernet, ZIP, etc.) polynomial in reversed bit order. */
/* #define POLY 0xedb88320 */

uint32_t crc32c(uint32_t crc, const unsigned char *buf, size_t len)
{
    int k;

    crc = ~crc;
    while (len--) {
        crc ^= *buf++;
        for (k = 0; k < 8; k++)
            crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
    }
    return ~crc;
}

uint32_t calcCrc(DirElement& element) {
    uint32_t crc = 0;
    std::ifstream ifs(element.getPath(), std::ifstream::binary);
    constexpr int BUFSIZE = 65536;
    unsigned char buffer[BUFSIZE];
    while (ifs) {
        ifs.read((char *)buffer, BUFSIZE);
        crc = crc32c(crc, buffer, ifs.gcount());
    }
    return crc;
}

int main(int argc, char* argv[]) {
    string path(".");
    if (argc > 1) {
        path = argv[1];
    }
    //cout << "Scanning " << path << " for dups" << endl;
    DirHandler dirhand(path);
    auto root = dirhand.getRoot();
    //cout << "Root element:\n" << root << endl;
    size_t numFiles = dirhand.walkDirectory([](DirElement& element) {
            if (element.getAttributes().kind() == Attributes::File &&
                element.getAttributes().fileSize() > 0) {
                uint32_t crc = calcCrc(element);
                cout << "CRC " << std::hex << std::setfill('0') << std::setw(8) << crc << " sz "
                     << std::dec << element.getAttributes().fileSize()
                     << " " << element.getPath() << endl;
            }
            return true;
        }, true);
    //cout << "scanned " << numFiles << " files." << endl;
    return 0;
}
