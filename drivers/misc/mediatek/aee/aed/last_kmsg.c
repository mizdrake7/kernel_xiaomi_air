#include <linux/proc_fs.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/kallsyms.h>
#include <linux/slab.h>
#include <asm/memory.h>
#include <asm/sections.h>
#include <linux/mm.h>
#include <linux/sizes.h>
#include <linux/err.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/of_reserved_mem.h>

static char *console_buffer;
static ssize_t console_bufsize;

#define PSTORE_CONSOLE_SIZE     0x40000
#define PSTORE_CONSOLE_OFFSET   0x8f000

static ssize_t last_kmsg_read(struct file *file, char __user *buf,
		size_t len, loff_t *offset)
{
	ssize_t rd;

	rd = simple_read_from_buffer(buf, len, offset, console_buffer, console_bufsize);
	if(rd < 0){
		pr_err("Failed to read from buffer\n");
	}
	return rd;
}
static const struct proc_ops last_kmsg_fops = {
	.proc_read          = last_kmsg_read,
	.proc_lseek         = default_llseek,
};

static int last_kmsg_init(void)
{
	struct proc_dir_entry *last_kmsg_entry = NULL;

	last_kmsg_entry = proc_create_data("last_kmsg", S_IFREG | S_IRUGO,
				NULL, &last_kmsg_fops, NULL);
	if (!last_kmsg_entry) {
		pr_err("Failed to create last_kmsg\n");
	}
	return 0;
}

int last_kmsg_driver_init(void)
{
	void *cpy;
	struct device_node *node;
	struct reserved_mem *rmem = NULL;
	phys_addr_t paddr;
	unsigned long total_size;
	void* kinfo_vaddr;

	node = of_find_compatible_node(NULL, NULL, "mediatek,pstore");
	if (IS_ERR_OR_NULL(node)) {
		pr_err("Failed to get pstore node\n");
		return -1;
	}

	rmem = of_reserved_mem_lookup(node);
	if (rmem) {
		paddr = rmem->base;
		total_size = rmem->size;
	} else {
		pr_err("Failed to get pstore mem\n");
		return -1;
	}

	paddr += PSTORE_CONSOLE_OFFSET;
	console_bufsize = PSTORE_CONSOLE_SIZE;
	console_buffer=(char *)kmalloc(console_bufsize, GFP_KERNEL);
	if(!console_buffer){
		pr_err("Failed to get console_buffer\n");
		return -1;
	}

	kinfo_vaddr = memremap(paddr, console_bufsize, MEMREMAP_WB);
	if (!kinfo_vaddr) {
		pr_err("[aed] failed to map console_buf\n");
	}else{
		cpy = memcpy(console_buffer, kinfo_vaddr,console_bufsize);
		if(!cpy){
			pr_err("Failed to memcpy console_buffer\n");
		}
		memunmap(kinfo_vaddr);
	}
	last_kmsg_init();
	return 0;
}
