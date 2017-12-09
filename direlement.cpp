
#include "debug.h"
#include "direlement.h"
#include <unistd.h>
#include <sys/param.h>
using std::string;


DirElement::DirElement(const std::string& fullPath)
    : fullPath_(fullPath)
    , attributesFilled_(false)
    , attributes_() {
    if (fullPath_.empty() || fullPath_.front() != '/') {
        fullPath_ = resolveFullPath(fullPath_);
    }
}

DirElement::DirElement(const DirElement& root, const std::string& relativePath)
    : fullPath_(root.getPath() + "/" + relativePath)
    , attributesFilled_(false)
    , attributes_() {
}

const Attributes& DirElement::getAttributes() {
    if (!attributesFilled_) {
        attributesFilled_ = attributes_.fill(fullPath_);
    }
    return attributes_;
}

const std::string& DirElement::getPath() const {
    return fullPath_;
}

std::string DirElement::resolveFullPath(const std::string& path) {
    string retval;
    if (path.empty() || path.front() != '/') {
        // use current working directory
        char cwd[MAXPATHLEN + 1];
        getcwd(cwd, MAXPATHLEN);
        // resolve relative path to absolute
        if (path.empty()) {
            retval = cwd;
        } else {
            //TODO check (cwd len + '/' + pata len) < MAXPATHLEN
            retval = string(cwd) + '/' + path;
            
        }
        return retval;
    } else {
        retval = path;
    }
    //TODO clean up path from ./ and ../
    return retval;
}

std::ostream& operator<<(std::ostream& os, DirElement& direlement) {
    os << direlement.getPath() << " " << direlement.getAttributes();
    return os;
}
