//
// Created by nk on 2023/10/23.
//

#include <boost/algorithm/hex.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

using boost::algorithm::hex;
using boost::uuids::detail::md5;

class UrlShortener {
    std::string_view prefix = "https://n.com/";
    const unsigned short size = 7;
    std::unordered_map<std::string, std::string> map = std::unordered_map<std::string, std::string>();

public:
    UrlShortener() = default;

    virtual ~UrlShortener() = default;

    std::string add(const std::string& origin) {
        if (this->isContained(origin) || this->isShorted(origin)) return std::string();
        std::string shorted = this->shorten(origin);
        this->map.insert(std::make_pair(origin, shorted));
        this->map.insert(std::make_pair(shorted, origin));
        std::stringstream ss;
        return shorted;
    }

    bool remove(const std::string &str) {
        if (!this->isContained(str)) return false;
        auto tmp = this->map.find(str)->second;
        this->map.erase(str);
        this->map.erase(tmp);
        return true;
    }

    std::string convert(const std::string& str) {
        std::stringstream ss;
        if (!this->isContained(str)) return ss.str();
        auto tmp = this->map.find(str)->second;
        if (this->isShorted(str)) return tmp;
        ss << this->prefix;
        ss << tmp;
        return ss.str();
    }

private:
    bool isContained(const std::string& str) {
        if (this->map.find(str) == this->map.end()) return false;
        return true;
    }

    bool isShorted(const std::string& str) {
        if (str.size() == this->size) return true;
        return false;
    }

    std::string shorten(const std::string& origin, int size = 7) {
        md5 hash;
        md5::digest_type digest;
        std::string newstr;

        hash.process_bytes(origin.data(), origin.size());
        hash.get_digest(digest);

        const auto charDigest = reinterpret_cast<const char *>(&digest);
        boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(newstr));

        return newstr.substr(0, size);
    }
};

void runUrlShortener() {
    auto us = std::make_unique<UrlShortener>();

    std::string a{"https://neok.netlify.app"};
    std::string as{us->add(a)};

    assert(a == us->convert(as));
    assert(us->convert(a) == ("https://n.com/" + as));
}