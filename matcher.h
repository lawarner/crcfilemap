#pragma once

#include <vector>

class Matcher {
public:
    using MatchList = std::vector<std::string>;
public:
    Matcher();
    ~Matcher() = default;
    void addMatch(const std::string& word);
    bool matches(const std::string& word) const;
private:
    MatchList matchList_;
};
