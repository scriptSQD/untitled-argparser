#include <ArgParser.hpp>

SQD::ArgParser::ArgParser(int argc, char *argv[]) : argc(argc) {
    std::regex NonSeparatedArg("(-+\\w*)=(.*)",
                               std::regex::ECMAScript | std::regex::multiline);
    std::smatch RegexFound;
    for (int i = 1; i < argc; i++) {
        const std::string arg = argv[i];

        if (!std::regex_search(arg, RegexFound, NonSeparatedArg)) {
            this->argv.emplace_back(argv[i]);
            continue;
        }

        // std::smatch.str([0... size() - 1]) - matched groups.
        // std::smatch.str(0) - whole match, others are groups
        // Match group 1 - arg flag, Match group 2 - arg value
        for (int it = 1; it < RegexFound.size(); it++) {
            this->argv.emplace_back(RegexFound.str(it));
        }
    }
}

SQD::ArgParser::~ArgParser() = default;

size_t SQD::ArgParser::findIndex(std::vector<std::string> &searchSource,
                            const std::vector<std::string> &flags) {
    for (auto &flag : flags) {
        auto it = std::find(searchSource.begin(), searchSource.end(), flag);
        if (it != searchSource.end()) {
            return it - searchSource.begin();
        }
    }

    return -1;
}

SQD::ArgParser *SQD::ArgParser::IfFlagsSet(const std::vector<std::string> &flags) {
    const size_t flagIndex = ArgParser::findIndex(this->argv, flags);
    if (flagIndex == -1) {
        this->lastParsedFlagIndex = -1;
        return this;
    }

    this->lastParsedFlagIndex = flagIndex;
    return this;
}

SQD::ArgParser *SQD::ArgParser::GetFlagValue(bool &dest) {
    dest = this->lastParsedFlagIndex != -1;
    return this;
}

std::string SQD::ArgParser::parseByIndex(size_t &flagIndex) {
    if (flagIndex == -1)
        return "";

    if (this->argv.size() >= flagIndex + 1) {
        return this->argv.at(flagIndex + 1);
    }

    return "";
}
