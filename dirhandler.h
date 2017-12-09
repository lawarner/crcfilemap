#pragma once

#include "direlement.h"
#include <functional>
#include <vector>

class DirHandler {
public:
    using DirElements = std::vector<DirElement>;
    using DirVisitor = std::function<bool(DirElement&)>;
public:
    DirHandler(const std::string& rootPath = std::string());
    virtual ~DirHandler() = default;

    const DirElements& getElements() const;
    const DirElement& getRoot() const;
    bool refresh();
    size_t walkDirectory(DirVisitor visitor, bool recursive);
private:
    DirElement root_;
    DirElements elements_;
};
