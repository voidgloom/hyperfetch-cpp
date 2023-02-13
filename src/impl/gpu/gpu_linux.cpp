
#include <cstdlib>
#include <dirent.h>
#include <iostream>
#include "cpu.hpp"
#include "impl/gpu/gpu_pci_list.hpp"
#include "impl/gpu/gpu_soc_list.hpp"
#include "cstring"
#include "utils/wrapper.hpp"

#define PCI_DEV_DIR_PATH "/sys/bus/pci/devices"
#define PCI_DEV_DIR "/sys/bus/pci/devices/"

void GpuModule::fetch() {
    struct dirent *dev;
    DWrap dir(PCI_DEV_DIR_PATH);
    while ((dev = readdir(dir)) != NULL) {
        if (dev->d_name[0] == '.')
            continue;
        Wrap<char *> dev_vendor_path(2048);
        strcat(dev_vendor_path, PCI_DEV_DIR);
        strcat(dev_vendor_path, dev->d_name);
        strcat(dev_vendor_path, "/vendor");
        FWrap vendor(dev_vendor_path, "r");
        Wrap<char *> dev_vendor(128);
        fgets(dev_vendor, 128, vendor);
        if (vendor_map.find(dev_vendor.o) == vendor_map.end()) continue;
        Wrap<char *> dev_device_path(2048);
        strcat(dev_device_path, PCI_DEV_DIR);
        strcat(dev_device_path, dev->d_name);
        strcat(dev_device_path, "/device");
        FWrap device(dev_device_path, "r");
        Wrap<char *> dev_device(128);
        fgets(dev_device, 128, device);

        std::map<std::string, std::string> map = vendor_map.at(dev_vendor.o);
        if (map.find(dev_device.o) != map.end()) {
            content = map[dev_device.o];
            break;
        }
    }
    // on arm socs the gpu might not be connected via pci(e). in that case we check a soc->gpu map.
    #ifdef __aarch64__
    if (content == "") {
        // get the cpu
        CpuModule cpu;
        cpu.fetch();
        content = gpu_soc_map[cpu.content];
    }   
    #endif
    prefix = "GPU";
    if (content == "")
        content = "Unknown";
}
