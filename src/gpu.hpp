#ifndef GPU_H_
#define GPU_H_
#include "module.hpp"

class GpuModule : public HyperfetchModule {
public:
    void fetch();
};
#endif // GPU_H_
