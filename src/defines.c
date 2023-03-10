#include "defines.h"

u64 mrnMemUsage = 0;
u64 mrnTotalAllocatedMem = 0;

void mrnLogCrntMemUsage() {
    LOG_DEBUG("Currently allocated memory by Marine-Runtime");
    LOG_DEBUG("===================================");
    LOG_DEBUG("%lliB", mrnMemUsage);
    LOG_DEBUG("%fKB", (float)(mrnMemUsage / 1024.0f));
    LOG_DEBUG("%fMB", (float)(mrnMemUsage / (1024.0f * 1024.0f)));
    LOG_DEBUG("%fGB", (float)(mrnMemUsage / (1024.0f * 1024.0f * 1024.0f))); 
    LOG_DEBUG("===================================");
}
