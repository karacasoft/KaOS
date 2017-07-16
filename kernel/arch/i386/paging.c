#include <string.h>
#include <kernel/page_frames.h>
#include <kernel/paging.h>
#include <kernel/kheap.h>

extern uint32_t placement_address;

extern uint32_t *frames;
extern uint32_t nframes;

page_directory_t *kernel_directory = 0;
page_directory_t *current_directory = 0;

void alloc_frame(page_t *page, int is_kernel, int is_writable) {
  if(page->frame != 0) {
    return;
  }
  else
  {
    uint32_t idx = first_free_frame();
    if(idx == (uint32_t) -1) {
      // No free frames lol
      while(1);
    }
    set_frame(idx * 0x1000);
    page->present = 1;
    page->rw = (is_writable) ? 1 : 0;
    page->is_user = (is_kernel) ? 0 : 1;
    page->frame = idx;
  }
}

void free_frame(page_t *page) {
  uint32_t frame;
  if(!(frame = page->frame)) {
    return;
  } else {
    clear_frame(frame);
    page->frame = 0x0;
  }
}

void initialize_paging() {
  // We assume that the memory is 16MB
  uint32_t mem_end_page = 0x1000000;
  
  nframes = mem_end_page / 0x1000;
  frames = (uint32_t *) kmalloc(INDEX_FROM_BIT(nframes));
  memset(frames, 0, INDEX_FROM_BIT(nframes));
  
  kernel_directory = (page_directory_t *) kmalloc_a(sizeof(page_directory_t));
  memset(kernel_directory, 0, sizeof(page_directory_t));
  current_directory = kernel_directory;
  
  int i = 0;
  while((uint32_t) i < placement_address) {
    alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
    i += 0x1000;
  }
  
  switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory_t *dir) {
  current_directory = dir;
  asm volatile("mov %0, %%cr3" :  : "r"(&dir->tablesPhysical));
  uint32_t cr0;
  asm volatile("mov %%cr0, %0": "=r"(cr0));
  cr0 |= 0x80000000;
  asm volatile("mov %0, %%cr0" :  : "r"(cr0));
}

page_t *get_page(uint32_t address, int make, page_directory_t *dir) {
  address /= 0x1000;
  
  uint32_t table_idx = address / 1024;
  if (dir->tables[table_idx]) {
    return &dir->tables[table_idx]->pages[address%1024];
  }
  else if(make) 
  {
    uint32_t tmp;
    dir->tables[table_idx] = (page_table_t *) kmalloc_ap(sizeof(page_table_t), &tmp);
    memset(dir->tables[table_idx], 0, 0x1000);
    dir->tablesPhysical[table_idx] = tmp | 0x7;
    return &dir->tables[table_idx]->pages[address%1024];
  }
  else
  {
    return 0;
  }
}


