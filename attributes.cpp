
#include "attributes.h"
#include "debug.h"
#include <string.h>
#include <sys/stat.h>


Attributes::Attributes(Kind kind, size_t fileSize, uint32_t crc)
    : kind_(kind)
    , fileSize_(fileSize)
    , crc_(crc)
    , numLinks_(0)
    , device_(0)
    , inode_(0) { }

bool Attributes::fill(const std::string& fullPath) {
    struct stat statbuf;
    if (lstat(fullPath.c_str(), &statbuf)) {
        cerr << "Cannot stat file \"" << fullPath << "\", error: " << strerror(errno) << endl;
        return false;
    }
    mode_t mode = statbuf.st_mode & S_IFMT;
    if (mode == S_IFIFO || mode == S_IFCHR ||
        mode == S_IFBLK || mode == S_IFSOCK) {
        kind_ = Device;
    } else if (mode == S_IFDIR) {
        kind_ = Directory;
    } else if (mode == S_IFLNK) {
        kind_ = SymbolicLink;
    } else {
        kind_ = File;
    }
    fileSize_ = statbuf.st_size;
    //TODO crc
    numLinks_ = statbuf.st_nlink;
    device_ = statbuf.st_dev;
    inode_ = statbuf.st_ino;

    return true;
}

std::ostream& operator<<(std::ostream& os, const Attributes& attribs) {
    os << "Kind=" << attribs.kind() << " size=" << attribs.fileSize()
       << " crc=" << attribs.crc() << " links=" << attribs.numLinks();
    return os;
}

std::ostream& operator<<(std::ostream& os, Attributes::Kind kind) {
    switch (kind) {
    case Attributes::Unknown:
        os << "Unknown";
        break;
    case Attributes::Device:
        os << "Device";
        break;
    case Attributes::Directory:
        os << "Dir.";
        break;
    case Attributes::File:
        os << "File";
        break;
    case Attributes::SymbolicLink:
        os << "SymLink";
        break;
    default:
        os << "(Bad Kind)";
        break;
    }
    return os;
}
