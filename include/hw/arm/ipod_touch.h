#ifndef HW_ARM_IPOD_TOUCH_H
#define HW_ARM_IPOD_TOUCH_H

#include "qemu-common.h"
#include "exec/hwaddr.h"
#include "hw/boards.h"
#include "hw/arm/boot.h"
#include "hw/intc/pl192.h"
#include "hw/arm/ipod_touch_uart.h"
#include "hw/arm/ipod_touch_spi.h"
#include "hw/arm/ipod_touch_aes.h"
#include "hw/arm/ipod_touch_sha1.h"
#include "cpu.h"

#define TYPE_IPOD_TOUCH "iPod-Touch"

#define TYPE_IPOD_TOUCH_MACHINE   MACHINE_TYPE_NAME(TYPE_IPOD_TOUCH)

#define IPOD_TOUCH_MACHINE(obj) \
    OBJECT_CHECK(IPodTouchMachineState, (obj), TYPE_IPOD_TOUCH_MACHINE)

#define CLOCK1_CONFIG0 0x0
#define CLOCK1_CONFIG1 0x4
#define CLOCK1_CONFIG2 0x8
#define CLOCK1_PLLLOCK 0x40
#define CLOCK1_PLL0CON 0x20
#define CLOCK1_PLL1CON 0x24
#define CLOCK1_PLL2CON 0x28
#define CLOCK1_PLL3CON 0x2C
#define CLOCK1_PLLMODE 0x44

// timer stuff
#define TIMER_IRQSTAT 0x10000
#define TIMER_IRQLATCH 0xF8
#define TIMER_TICKSHIGH 0x80
#define TIMER_TICKSLOW 0x84
#define TIMER_STATE_START 1
#define TIMER_STATE_STOP 0
#define TIMER_STATE_MANUALUPDATE 2
#define NUM_TIMERS 7
#define TIMER_4 0xA0
#define TIMER_CONFIG 0 
#define TIMER_STATE 0x4
#define TIMER_COUNT_BUFFER 0x8
#define TIMER_COUNT_BUFFER2 0xC

// VIC
#define S5L8900_VIC_N	  2
#define S5L8900_VIC_SIZE  32

#define POWER_ID 0x44

#define S5L8900_SPI0_IRQ 0x9
#define S5L8900_SPI1_IRQ 0xA
#define S5L8900_SPI2_IRQ 0xB

typedef struct {
    MachineClass parent;
} IPodTouchMachineClass;

typedef struct s5l8900_clk1_s
{
	uint32_t	clk1_config0;
    uint32_t    clk1_config1;
    uint32_t    clk1_config2;
	uint32_t    clk1_pll1con;
    uint32_t    clk1_pll2con;
    uint32_t    clk1_pll3con;
	uint32_t    clk1_plllock;
	uint32_t	clk1_pllmode;

} s5l8900_clk1_s;

typedef struct s5l8900_timer_s
{
    uint32_t    ticks_high;
	uint32_t	ticks_low;
	uint32_t 	status;
	uint32_t    config;
	uint32_t    bcount1;
	uint32_t    bcount2;
	uint32_t    prescaler;
	uint32_t    irqstat;
    QEMUTimer *st_timer;
	uint32_t bcreload;
    uint32_t freq_out;
    uint64_t tick_interval;
    uint64_t last_tick;
    uint64_t next_planned_tick;
    uint64_t base_time;
	qemu_irq	irq;

} s5l8900_timer_s;

typedef struct {
	MachineState parent;
	qemu_irq **irq;
	PL192State *vic0;
	PL192State *vic1;
	S5L8900UartState *uart0;
	s5l8900_clk1_s *clock1;
	s5l8900_timer_s *timer1;
	S5L8900AESState *aes_state;
	S5L8900SHA1State *sha1_state;
	uint32_t kpc_pa;
	uint32_t kbootargs_pa;
	uint32_t uart_mmio_pa;
	ARMCPU *cpu;
	char kernel_filename[1024];
	char dtb_filename[1024];
	char kern_args[256];
	uint64_t printf_buffer[256];
} IPodTouchMachineState;

#endif