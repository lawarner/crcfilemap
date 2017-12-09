
#include "debug.h"
#include "dirhandler.h"
#include <dirent.h>
#include <unistd.h>
#include <sys/param.h>


DirHandler::DirHandler(const std::string& rootPath)
    : root_(rootPath) {
    refresh();
}

const DirHandler::DirElements& DirHandler::getElements() const {
    return elements_;
}

const DirElement& DirHandler::getRoot() const {
    return root_;
}

bool DirHandler::refresh() {
    elements_.clear();
    if (root_.getAttributes().kind() != Attributes::Directory) {
        cerr << "Root is not a directory." << endl;
        return false;
    }
    DIR* dir = opendir(root_.getPath().c_str());
    if (!dir) {
        cerr << "Cannot open root directory." << endl;
        return false;
    }
    struct dirent* de = readdir(dir);
    while (de) {
        std::string name(de->d_name);
        if (name != "." && name != "..") {
            DirElement dirElem(root_, de->d_name);
            elements_.push_back(dirElem);
        }
        de = readdir(dir);
    }
    closedir(dir);
    return true;
}

size_t DirHandler::walkDirectory(DirVisitor visitor, bool recursive) {
    size_t visited = 0;
    for (auto& element : elements_) {
        ++visited;
        if (element.getAttributes().kind() == Attributes::Directory) {
            if (recursive) {
                cout << "Recurse into " << element.getPath() << endl;
                DirHandler dh(element.getPath());
                visited += dh.walkDirectory(visitor, recursive);
            } else {
                cout << "Skipping dir " << element.getPath() << endl;
            }
        } else {
            if (!visitor(element)) {
                break;
            }
        }
    }
    return visited;
}
