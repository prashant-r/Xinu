/* printsegaddr.c - printsegaddr */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  printsegaddr  -  prints the beginning, ending of bss,text and data segments
 *------------------------------------------------------------------------
 */
void printsegaddr()
{
	kprintf("End of text segment %08x \n",&etext);
	kprintf("End of data segment %08x \n",&edata);
	kprintf("End of bss segment %08x \n",&ebss);
	kprintf("\n");
	kprintf("\n");
	kprintf("8 bytes after text segment\n");
	kprintf("0x%x%x \n",*(&etext+1), *(&etext+2));

	kprintf("8 bytes after data segment\n");
	kprintf("0x%x%x \n",*(&edata+1), *(&edata+2));

	kprintf("8 bytes after bss segment\n");
	kprintf("0x%x%x \n",*(&ebss+1), *(&ebss+2));
	kprintf("\n");
	kprintf("\n");
	kprintf("%10d bytes of Xinu text segment.\n",
			(uint32)&etext - (uint32)&text);
	kprintf("%10d bytes of Xinu data segment.\n",
				(uint32)&edata - (uint32)&data);
	kprintf("%10d bytes of Xinu bss segment.\n",
				(uint32)&ebss - (uint32)&bss);
}

