#include "zstd.h"
#include <bits/stdint-uintn.h>
#include <string>
#include <vector>

class ZstdDict {
  public:
    static constexpr uint32_t DICT_SIZE = 1 << 18;
    static constexpr int COMPRESSION_LEVEL = 9;
    
    // Build a dictionary using given list of files
    void build(const std::vector<std::string> &paths, const uint32_t dict_size = DICT_SIZE) {
        // Read the content of files
        std::string buffer(1000);
        
        
        
        // Build the dictionary
    }

    void read() {}

    void write() {}

  private:
    ZSTD_CDict* dictionary;
};

class ZstdCompressionAlgorithm {
  public:
  private:
};

class ZstdDecomressionAlgorithm {
  public:
  private:
};
