
int init_palloc(const char *path);
void pallocate(uint32_t lba, uint32_t len);
void pallocate_prepare(uint32_t lba, uint32_t len);
void pallocate_submit();
void pallocate_with_fd(uint32_t fd, uint32_t lba, uint32_t len);

void print_stat();

void reset();
