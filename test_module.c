#include <linux/module.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/kobject.h>
//#include <linux/init.h>
static struct kobject test_kobj;
extern const struct sysfs_ops kobj_sysfs_ops;
static char test_value[32] ;
static ssize_t test_show(struct kobject *kobj,struct kobj_attribute *attr,char *buf)
{
	ssize_t len = sprintf(buf,"%s\n",test_value);
	return len;

}
static ssize_t test_store(struct kobject *kobj,struct kobj_attribute *attr,const char *buf,size_t count)
{
	strncpy(test_value,buf,32);
	return 32;

}

static struct kobj_attribute test_attr = {
	.show = test_show,
	.store = test_store,
	.attr.name = "test_attr",
	.attr.mode = 0666,
};
static struct attribute *test_attr_group[] = {
	[0] = &test_attr.attr,
	[1] = NULL,
};
static struct kobj_type test_ktype = {
	.sysfs_ops = &kobj_sysfs_ops,
	.default_attrs = test_attr_group,
	.release = NULL,
};
static int __init test_init(void)
{
	int ret = -EINVAL;
	ret = kobject_init_and_add(&test_kobj,&test_ktype/*&driver_ktype*/,NULL,"test");
	if(!ret)
		printk(KERN_NOTICE "test_obj register succeed!\n");

	return ret;
}
static void __exit test_exit(void)
{
}
module_init(test_init);
module_exit(test_exit);
MODULE_AUTHOR("alex");
MODULE_LICENSE("GPL");
MODULE_VERSION("v0.1");
