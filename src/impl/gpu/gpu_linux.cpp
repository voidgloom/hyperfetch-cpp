
#include <cstdlib>
#include <dirent.h>
#include "cpu.hpp"
#include "impl/gpu/gpu_pci_list.hpp"
#include "impl/gpu/gpu_soc_list.hpp"
#include "cstring"

#define PCI_DEV_DIR "/sys/bus/pci/devices"

void GpuModule::fetch() {
    struct dirent *dev;
    DIR *dir = opendir(PCI_DEV_DIR);
    while ((dev = readdir(dir)) != NULL) {
        if (dev->d_name[0] == '.')
            continue;
        char *dev_vendor_path = new char[2048];
        dev_vendor_path[0] = '\0';
        strcat(dev_vendor_path, PCI_DEV_DIR);
        strcat(dev_vendor_path, "/");
        strcat(dev_vendor_path, dev->d_name);
        strcat(dev_vendor_path, "/vendor");
        FILE *vendor = fopen(dev_vendor_path, "r");
        char *dev_vendor = new char[128];
        fgets(dev_vendor, 128, vendor);
        fclose(vendor);
        char *dev_device_path = new char[2048];
        dev_device_path[0] = '\0';
        strcat(dev_device_path, PCI_DEV_DIR);
        strcat(dev_device_path, "/");
        strcat(dev_device_path, dev->d_name);
        strcat(dev_device_path, "/device");
        FILE *device = fopen(dev_device_path, "r");
        char *dev_device = new char[128];
        fgets(dev_device, 128, device);
        fclose(device);
        if (vendor_map.find(dev_vendor) != vendor_map.end()) {
            std::map<std::string, std::string> map = vendor_map.at(dev_vendor);
            if (map.find(dev_device) != map.end()) {
               content = map[dev_device];
            }
        }
        delete[] dev_vendor_path;
        delete[] dev_device_path;
        delete[] dev_vendor;
        delete[] dev_device;
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
