/* printsegaddr.c - printsegaddr */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  printsegaddr  -  prints the beginning, ending of bss,text and data segments
 *------------------------------------------------------------------------
 */
void printsegaddr()
{
	kprintf("text end at %08x following .. 0x%x%x \n",&etext, *(&etext+1), *(&etext+2));
	kprintf("data end at %08x following .. 0x%x%x \n",&edata, *(&edata+1), *(&edata+2));
	kprintf("bss end at %08x following ..  0x%x%x \n",&ebss, *(&ebss+1), *(&ebss+2) );

	kprintf("%10d bytes of Xinu text segment.\n",
			(uint32)&etext - (uint32)&text);
	kprintf("%10d bytes of Xinu data segment.\n",
				(uint32)&edata - (uint32)&data);
	kprintf("%10d bytes of Xinu bss segment.\n",
				(uint32)&ebss - (uint32)&bss);
}

