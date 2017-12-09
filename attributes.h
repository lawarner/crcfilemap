#pragma once

#include <string>
#include <stdint.h>
#include <sys/types.h>


class Attributes {
public:
    enum Kind {
        Unknown,
        Device,
        Directory,
        File,
        SymbolicLink
    };
public:
    Attributes(Kind kind = Unknown, size_t fileSize = 0, uint32_t crc = 0);
    bool fill(const std::string& fullPath);

    Kind  kind() const { return kind_; }
    Kind& kind() { return kind_; }
    size_t  fileSize() const { return fileSize_; }
    size_t& fileSize() { return fileSize_; }
    uint32_t  crc() const { return crc_; }
    uint32_t& crc() { return crc_; }
    size_t  numLinks() const { return numLinks_; }
    size_t& numLinks() { return numLinks_; }
    dev_t  device() const { return device_; }
    dev_t& device() { return device_; }
    ino_t  inode() const { return inode_; }
    ino_t& inode() { return inode_; }
private:
    Kind kind_;
    size_t fileSize_;
    uint32_t crc_;
    // number of hard links
    size_t numLinks_;
    // device and inode
    dev_t device_;
    ino_t inode_;
};

std::ostream& operator<<(std::ostream& os, const Attributes& attribs);
std::ostream& operator<<(std::ostream& os, Attributes::Kind kind);
