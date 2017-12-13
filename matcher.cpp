
#include "debug.h"
#include "matcher.h"
#include <regex.h>

static bool isRegex(const std::string& pattern) {
    bool retval = pattern.find("*?\\") != string::npos;
    return retval;
}

Matcher::Matcher() {
}

void Matcher::addMatch(const std::string& word) {
    matchList_.push_back(word);
}

bool Matcher::matches(const std::string& word) const {
    for (const auto& match : matchList_) {
        if (isRegex(match)) {
            regex_t re;
            if (!regcomp(&re, match.c_str(), REG_NOSUB)) {
                int rc = regexec(&re, word.c_str(), 0, NULL, 0);
                regfree(&re);
                if (rc == 0) {
                    return true;
                }
            }
        } else {
            if (word == match) {
                return true;
            }
        }
    }
    return false;
}

