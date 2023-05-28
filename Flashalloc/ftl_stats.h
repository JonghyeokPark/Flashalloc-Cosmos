#ifndef __FTL_STATS_H__
#define __FTL_STATS_H__

struct stats_ftl {
    uint64_t lpn_cnt;
    uint64_t page_program_cnt;
    uint64_t page_gc_program_cnt;
    uint64_t page_gc_read_cnt;
    uint64_t page_read_cnt;
    uint64_t block_erase_cnt;
    uint64_t discard_page_cnt;
    uint64_t discard_page_mapped_cnt;
    uint64_t share_page_cnt;
};
#endif
