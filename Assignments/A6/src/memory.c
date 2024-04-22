#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

struct memory
{
  int *pages[0x10000];
};


// Function to create memory
struct memory *memory_create()
{
  return calloc(sizeof(struct memory), 1);
}


//Function to delete memory, goes through each element
void memory_delete(struct memory *mem)
{
  for (int j = 0; j < 0x10000; ++j)
  {
    if (mem->pages[j])
      free(mem->pages[j]);
  }
  free(mem);
}

// Get a specific page of the memory by shifting the given address 16 spaces to
// the right and then uses calloc to allocate memory and a pointer 65536 is
// same as 0x10000
int *get_page(struct memory *mem, int addr)
{
  int page_number = addr >> 16;
  if (mem->pages[page_number] == NULL)
  {
    mem->pages[page_number] = calloc(65536, 1);
  }
  return mem->pages[page_number];
}


//Writes a word to memory by using get_page, cehcks with 3 to see if it alligned
void memory_wr_w(struct memory *mem, int addr, int data)
{
  if (addr & 0x3)
  {
    printf("Unaligned word write to %x\n", addr);
    exit(-1);
  }
  int *page = get_page(mem, addr);
  page[(addr >> 2) & 0x3fff] = data;
}

//Writes a half word to memory by using get_page
void memory_wr_h(struct memory *mem, int addr, int data)
{
  if (addr & 0x1)
  {
    printf("Unaligned halfword write to %x\n", addr);
    exit(-1);
  }
  int *page = get_page(mem, addr);
  int index = (addr >> 2) & 0x3fff;
  if ((addr & 2) == 0)
    page[index] = (page[index] & 0xffff0000) | (data & 0x0000ffff);
  else
    page[index] = (page[index] & 0x0000ffff) | (data << 16);
}


//Writes a byte to memory by using get_page
void memory_wr_b(struct memory *mem, int addr, int data)
{
  int *page = get_page(mem, addr);
  int index = (addr >> 2) & 0x3fff;
  switch (addr & 0x3){
    case 0:
      page[index] = (page[index] & 0xffffff00) | (data & 0xff);
      break;
    case 1:
      page[index] = (page[index] & 0xffff00ff) | ((data & 0xff) << 8);
      break;
    case 2:
      page[index] = (page[index] & 0xff00ffff) | ((data & 0xff) << 16);
      break;
    case 3:
      page[index] = (page[index] & 0x00ffffff) | ((data & 0xff) << 24);
      break;
    }
}


//read a word from memory by using get_page
int memory_rd_w(struct memory *mem, int addr)
{
  int *page = get_page(mem, addr);
  if (addr & 0x3)
  {
    printf("Unaligned word read from %x\n", addr);
    exit(-1);
  }
  return page[(addr >> 2) & 0x3fff];
}


//read a halfword from memory by using get_page
int memory_rd_h(struct memory *mem, int addr)
{
  int *page = get_page(mem, addr);
  int index = (addr >> 2) & 0x3fff;
  if (addr & 0x1)
  {
    printf("Unaligned halfword read from %x\n", addr);
    exit(-1);
  }
  if ((addr & 2) == 0)
    return page[index] & 0xffff;
  else
    return (page[index] >> 16) & 0xffff;
}


//read a word from memory by using get_page
int memory_rd_b(struct memory *mem, int addr)
{
  int *page = get_page(mem, addr);
  int index = (addr >> 2) & 0x3fff;
  switch (addr & 0x3)
  {
  case 0:
    return page[index] & 0xff;
    break;
  case 1:
    return (page[index] >> 8) & 0xff;
    break;
  case 2:
    return (page[index] >> 16) & 0xff;
    break;
  case 3:
    return (page[index] >> 24) & 0xff;
    break;
  }
  return 0; // silence a warning
}
