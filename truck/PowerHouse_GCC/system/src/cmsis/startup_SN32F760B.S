/* File: startup_ARMCM0.S
 * Purpose: startup file for Cortex-M0 devices. Should use with
 *   GCC for ARM Embedded Processors
 * Version: V2.0
 * Date: 16 August 2013
 */
/* Copyright (c) 2011 - 2013 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/
	.syntax	unified
	.arch	armv6-m

	.section .stack
	.align	3
	.equ	Stack_Size, 0x200
	.globl	__StackTop
	.globl	__StackLimit
__StackLimit:
	.space	Stack_Size
	.size	__StackLimit, . - __StackLimit
__StackTop:
	.size	__StackTop, . - __StackTop

	.section .heap
	.align	3
	.equ	Heap_Size, 0
	.globl	__HeapBase
	.globl	__HeapLimit
__HeapBase:
	.if	Heap_Size
	.space	Heap_Size
	.endif
	.size	__HeapBase, . - __HeapBase
__HeapLimit:
	.size	__HeapLimit, . - __HeapLimit

	.section .isr_vector
	.align 2
	.globl	__isr_vector
__isr_vector:
	.long	__StackTop            /* Top of Stack */
	.long	Reset_Handler         /* Reset Handler */
	.long	NMI_Handler           /* NMI Handler */
	.long	HardFault_Handler     /* Hard Fault Handler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	SVC_Handler           /* SVCall Handler */
	.long	0                     /* Reserved */
	.long	0                     /* Reserved */
	.long	PendSV_Handler        /* PendSV Handler */
	.long	SysTick_Handler       /* SysTick Handler */
	
	/* External interrupts */
	.long   NDT_IRQHandler		  /* 16+ 0: NDT  */
	.long   0		  			  /* 16+ 1:  */
	.long   0		  			  /* 16+ 2:  */
	.long   0		              /* 16+ 3:  */
	.long   0					  /* 16+ 4:  */
	.long   0					  /* 16+ 5:  */
	.long   SPI0_IRQHandler		  /* 16+ 6:  */
	.long   0					  /* 16+ 7: Reserved */
	.long   0					  /* 16+ 8: Reserved */
	.long   0					  /* 16+ 9: Reserved */
	.long   I2C0_IRQHandler		  /* 16+10: Reserved */
	.long   0					  /* 16+11: Reserved */
	.long   UART0_IRQHandler	  /* 16+12: */
	.long   UART1_IRQHandler	  /* 16+13:  */
	.long   UART2_IRQHandler	  /* 16+14:  */
	.long   CT16B0_IRQHandler	  /* 16+15:  */
	.long   CT16B1_IRQHandler	  /* 16+16:  */
	.long   0                	  /* 16+17:  */
	.long   0					  /* 16+18: Reserved */
	.long   0	                  /* 16+19:  */
	.long   0					  /* 16+20: Reserved */
	.long   0	  				  /* 16+21:  */
	.long   0	  				  /* 16+22:  */
	.long   0		              /* 16+23:  */
	.long   ADC_IRQHandler		  /* 16+24: A/D Converter */
	.long   WDT_IRQHandler		  /* 16+25: Watchdog Timer   */
	.long   LVD_IRQHandler		  /* 16+26: Low Voltage Detect */
	.long   0		              /* 16+27: RTC */
	.long   P3_IRQHandler		  /* 16+28: PIO INT3 */
	.long   P2_IRQHandler		  /* 16+29: PIO INT2 */
	.long   P1_IRQHandler		  /* 16+30: PIO INT1 */
	.long   P0_IRQHandler		  /* 16+31: PIO INT0 */




	.size	__isr_vector, . - __isr_vector

	.text
	.thumb
	.thumb_func
	.align	1
	.globl	Reset_Handler
	.type	Reset_Handler, %function
Reset_Handler:
/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    __etext: LMA of start of the section to copy from. Usually end of text
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__etext
	ldr	r2, =__data_start__
	ldr	r3, =__data_end__

	subs	r3, r2
	ble	.L_loop1_done

.L_loop1:
	subs	r3, #4
	ldr	r0, [r1,r3]
	str	r0, [r2,r3]
	bgt	.L_loop1

.L_loop1_done:












/*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__bss_start__
	ldr	r2, =__bss_end__

	movs	r0, 0

	subs	r2, r1
	ble	.L_loop3_done

.L_loop3:
	subs	r2, #4
	str	r0, [r1, r2]
	bgt	.L_loop3
.L_loop3_done:

	bl	main

	.pool
	.size	Reset_Handler, . - Reset_Handler

	.align	1
	.thumb_func
	.weak	Default_Handler
	.type	Default_Handler, %function
Default_Handler:
	b	.
	.size	Default_Handler, . - Default_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
	.macro	def_irq_handler	handler_name
	.weak	\handler_name
	.set	\handler_name, Default_Handler
	.endm

	def_irq_handler	NMI_Handler
	def_irq_handler	HardFault_Handler
	def_irq_handler	SVC_Handler
	def_irq_handler	PendSV_Handler
	def_irq_handler	SysTick_Handler
	def_irq_handler NDT_IRQHandler
	def_irq_handler SPI0_IRQHandler
	def_irq_handler I2C0_IRQHandler
	def_irq_handler UART0_IRQHandler
	def_irq_handler UART1_IRQHandler
	def_irq_handler UART2_IRQHandler
	def_irq_handler CT16B0_IRQHandler
	def_irq_handler CT16B1_IRQHandler
	def_irq_handler ADC_IRQHandler
	def_irq_handler WDT_IRQHandler
	def_irq_handler LVD_IRQHandler
	def_irq_handler P3_IRQHandler
	def_irq_handler P2_IRQHandler
	def_irq_handler P1_IRQHandler
	def_irq_handler P0_IRQHandler
	
	.end
	
