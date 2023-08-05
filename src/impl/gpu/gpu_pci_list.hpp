#include <map>
#include <string>

#define devMap std::map<std::string, std::string>

// yes, these strings contain \n on linux
const devMap amd_device_map = {
{"0x743f\n", "AMD Radeon RX 6400/6500 XT"},
{"0x7422\n", "AMD Radeon PRO W6400"},
{"0x73ff\n", "AMD Radeon RX 6600/6600 XT/6600M"}
};

const devMap microsoft_device_map = {
    {"0x008e\n", "Microsoft Corporation Basic Render Driver"},
    {"0x008c\n", "Microsoft Corporation Basic Render Driver"},
};

const devMap nvidia_device_map = {};

const devMap intel_device_map = {};

const std::map<std::string, devMap> vendor_map = {
{"0x1002\n", amd_device_map},
{"0x10de\n", nvidia_device_map},
{"0x8086\n", intel_device_map},
{"0x1414\n", microsoft_device_map}
};
