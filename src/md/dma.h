#ifndef MD_DMA_H
#define MD_DMA_H

#include "types.h"

#define DmaVRAM    0x40000080LU
#define DmaCRAM    0xC0000080LU
#define DmaVSRAM   0x40000090LU

#define dma_now(cmd, from, to, len, inc) {	\
	dma_queue(cmd, from, to, len, inc);		\
	dma_pop();								\
}

extern void dma_queue(uint32_t cmd, uint32_t from, uint16_t to, uint16_t len, uint16_t inc);
extern void dma_pop(void);
extern void dma_flush(void);
extern void dma_clear(void);

// Will split DMA in two if it crosses 128K boundary
extern void dma_queue_rom(uint32_t cmd, uint32_t from, uint16_t to, uint16_t len, uint16_t inc);

#endif //MD_DMA_H
