#include<unistd.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <asm/system.h>
#include <asm/segment.h>

#define MAX_ARG_PAGES 32

share_mm mm[20];

int sys_shmget(int key, size_t size, int shmflg)
{
	int i;
	for(i=0;i<19;i++){
		if (key==mm[i].key)	break;
	}
	if(!mm[i].phys_addr){
		mm[i].key = key;
		mm[i].phys_addr = get_free_page();
	}
	printk("sys_shmget %d--%d--0x%08x\n",i,mm[i].key,mm[i].phys_addr);
	return i;
}

// void* sys_shmat(int shmid, const void *shmaddr, int shmflg)
// {

// 	unsigned long code_limit,data_limit,code_base,data_base,data_base1;
// 	unsigned long tmp,*page_table;
// 	int i;

// 	code_limit=get_limit(0x0f);
// 	data_limit=get_limit(0x17);
// 	code_base = get_base(current->ldt[1]);
// 	data_base1 = data_base = get_base(current->ldt[2]);

// 	share_mm *ssm = &mm[shmid];
// 	tmp = ssm->phys_addr;
// 	printk("sys_shmat is %d--%d--0x%08x\n",shmid,ssm->key,tmp);

// 	data_base += data_limit;
// 	for (i=MAX_ARG_PAGES-1 ; i>=0 ; i--) {
// 		data_base -= PAGE_SIZE;
// 		page_table = (unsigned long *) ((data_base>>20) & 0xffc);
// 		if (!((*page_table)&1)){
// 			break;
// 		}
// 	}
// 	tmp = put_page(tmp,data_base);
// 	printk("virtual adress is 0x%08x--0x%08x--0x%08x\n",data_base,data_base1,tmp);
// 	return data_base-data_base1;
// }

void * sys_shmat(int shmid, const void *shmaddr, int shmflg)
{
	unsigned long virtual_adrr = current->brk;
	current->brk += PAGE_SIZE;
	unsigned long tmp = mm[shmid].phys_addr;
    put_page(tmp,virtual_adrr + current->start_code);
    printk("virtual adress is 0x%08x---0x%08x\n",virtual_adrr,get_base(current->ldt[2]));
    return (void*)virtual_adrr;
}
