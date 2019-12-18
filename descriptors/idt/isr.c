#include "../../common/types.h"
#include "../../common/port/port.h"
#include  "../../drivers/monitor/monitor.h"
#include "isr.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(u8int entry, isr_t handler) {
    interrupt_handlers[entry] = handler;
}

void isr_handler(registers_t regs)
{
    monitor_write("Received an interrupt: ");
    monitor_write_hex(regs.int_no);
    monitor_write("\n");
}

void irq_handler(registers_t regs)
{
    monitor_write("handled in IRQ: ");
    monitor_write_hex(regs.int_no);
    monitor_write("\n");

    if (regs.int_no >= 40)
    {
        write_byte_to_port(0xA0, 0x20);
    }
    write_byte_to_port(0x20, 0x20);

    if (interrupt_handlers[regs.int_no != 0])
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}