/**
 *
 *
 */

#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/module.h>
#include <linux/init.h>

int vfs_module_init(void)
{
	return 0;
}

void vfs_module_exit(void)
{

}

module_init(vfs_module_init);
module_exit(vfs_module_exit);

MODULE_LICENSE("GPL");
