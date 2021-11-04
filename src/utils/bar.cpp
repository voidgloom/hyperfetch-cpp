#include <string>

namespace ralsei {
    std::string bar(int total, int progress) {
        std::string returnValue;
        int i = 0;
        while (i < (progress * total / 100)) {
            returnValue += "● ";
            i++;
        }
        int alreadyDone = i;
        i = 0;
        while (i <= (total - alreadyDone)) {
            returnValue += "○ ";
            i++;
        }
        return returnValue;
    }
}
