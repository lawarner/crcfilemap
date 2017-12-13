
#include "debug.h"
#include "direlement.h"
#include <unistd.h>
#include <sys/param.h>
using std::string;


static string getLastComponent(const string& path) {
    auto ii = path.rfind('/');
    if (ii == string::npos) {
        return path;
    }
    return path.substr(ii + 1);
}


DirElement::DirElement(const std::string& fullPath)
    : fullPath_(fullPath)
    , attributesFilled_(false)
    , attributes_() {
    if (fullPath_.empty() || fullPath_.front() != '/') {
        fullPath_ = resolveFullPath(fullPath_);
    }
    baseName_ = getLastComponent(fullPath_);
}

DirElement::DirElement(const DirElement& root, const std::string& relativePath)
    : fullPath_(root.getPath() + "/")
    , attributesFilled_(false)
    , attributes_() {
    if (0 == relativePath.find("./")) {
        fullPath_ += relativePath.substr(2);
    } else {
        fullPath_ += relativePath;
    }
    baseName_ = getLastComponent(fullPath_);
}

const Attributes& DirElement::getAttributes() {
    if (!attributesFilled_) {
        attributesFilled_ = attributes_.fill(fullPath_);
    }
    return attributes_;
}

const std::string& DirElement::getBaseName() const {
    return baseName_;
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
    if (0 == retval.find("./")) {
        return retval.substr(2);
    }
    return retval;
}

std::ostream& operator<<(std::ostream& os, DirElement& direlement) {
    os << direlement.getPath() << " " << direlement.getAttributes();
    return os;
}
