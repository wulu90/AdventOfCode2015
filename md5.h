#ifndef MD5_H
#define MD5_H

#include <cstddef>
#include <string>

class md5 {
  public:
    static std::string hash(const std::string& str);

  private:
    std::byte* data_;
    size_t length_;
};

#endif
