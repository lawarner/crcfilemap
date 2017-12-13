#pragma once

#include "attributes.h"
#include <stdint.h>
#include <string>
#include <vector>

class DirElement {
public:
    DirElement(const std::string& fullPath);
    DirElement(const DirElement& root, const std::string& relativePath);

    // Lazy get of attributes (thus not const)
    const Attributes& getAttributes();
    const std::string& getBaseName() const;
    const std::string& getPath() const;    
    std::string resolveFullPath(const std::string& path);
private:
    std::string fullPath_;
    std::string baseName_;
    bool attributesFilled_;
    Attributes attributes_;
};

//TODO manipulators for name, summary or long format
std::ostream& operator<<(std::ostream& os, DirElement& direlement);
