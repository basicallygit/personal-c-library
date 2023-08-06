#define FNV_PRIME 16777619
#define FNV_OFFSET_BASIS 2166136261

unsigned int fnv1a_hash(const char* input) {
    unsigned int hash = FNV_OFFSET_BASIS;
    const unsigned char* p = (const unsigned char*)input;

    while (*p) {
        hash ^= *p++;
        hash *= FNV_PRIME;
    }

    return hash;
}
