#include <map>
#include <string>

// yes, these strings contain \n on linux
const std::map<std::string, std::string> amd_device_map = {
{"0x743f\n", "AMD Radeon RX 6400/6500 XT"},
{"0x7422\n", "AMD Radeon PRO W6400"},
{"0x73ff\n", "AMD Radeon RX 6600/6600 XT/6600M"}
};


const std::map<std::string, std::string> nvidia_device_map = {};

const std::map<std::string, std::string> intel_device_map = {};

const std::map<std::string, std::map<std::string, std::string>> vendor_map = {
{"0x1002\n", amd_device_map},
{"0x10de\n", nvidia_device_map},
{"0x8086\n", intel_device_map}
};
