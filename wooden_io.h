// wooden_io: 实现各种 IO 方式到统一接口的实现

#include <string>

#ifndef WOODEN_IO_H
#define WOODEN_IO_H
enum UnifiedInput {
    file_in = 1,
    stream_in = 2,
};

enum UnifiedOutput {
    file_out = 1,
    stream_out = 2,
};

class UnifiedIO {
    UnifiedInput input;
    UnifiedOutput output;
    char* name;
    void read(char* buf, int size) {
        if (input == file_in) {
            
        }
    }
};

#endif