
template<typename T>
T read_memory(uint32_t address) {
    return *(uint32_t *)address;
}

template<typedef T>
void write_memory(uint32_t address, T value) {
    *(T*)address = value;
}
