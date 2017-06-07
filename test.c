#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/platform_device.h>

//////////////////////////////////////////
#define DEBUG_SWITCH_RC_DEVICE_INFO 1
//open the debug log
#if    DEBUG_SWITCH_RC_DEVICE_INFO
#define RC_DEVICE_INFO(fmt,arg...)      printk("<<-rc-device-info->> "fmt"\n",##arg)
#else
#define RC_DEVICE_INFO(fmt,args...) /*do nothing */
#endif

#define ZZF_PRINT(fmt,args...) printk("<<-rc-device-info->> "fmt"\n",##arg)
#define RC_DEVICE_INFO_DEFAULT_VALUE "no support"
/////////////////////////////////////

const char *rc_lcm_info=RC_DEVICE_INFO_DEFAULT_VALUE;
//char *rc_sub_camera_info=RC_DEVICE_INFO_DEFAULT_VALUE;
//char *rc_main_camera_info=RC_DEVICE_INFO_DEFAULT_VALUE;
char *rc_gsensor_info=RC_DEVICE_INFO_DEFAULT_VALUE;
char *rc_alps_info=RC_DEVICE_INFO_DEFAULT_VALUE;
char *rc_tp_info=RC_DEVICE_INFO_DEFAULT_VALUE;
char *rc_gyroscope_info=RC_DEVICE_INFO_DEFAULT_VALUE;
char *rc_compass_info=RC_DEVICE_INFO_DEFAULT_VALUE;
char *rc_tpfwver_info=RC_DEVICE_INFO_DEFAULT_VALUE;
char *rc_mem_info=RC_DEVICE_INFO_DEFAULT_VALUE;

static ssize_t show_LCMINFO(struct device *dev,struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", rc_lcm_info);
}
#if 0
static ssize_t show_sub_camera_info(struct device *dev,struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", rc_sub_camera_info);
}

static ssize_t show_main_camera_info(struct device *dev,struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", rc_main_camera_info);
}
#endif
static ssize_t show_gsensor_info(struct device *dev,struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", rc_gsensor_info);
}

static ssize_t show_alps_info(struct device *dev,struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", rc_alps_info);
}

static ssize_t show_tp_info(struct device *dev,struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", rc_tp_info);
}

static ssize_t show_gyroscope_info(struct device *dev,struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", rc_gyroscope_info);
}

static ssize_t show_compass_info(struct device *dev,struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", rc_compass_info);
}

static ssize_t show_tpfwver_info(struct device *dev,struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%s\n", rc_tpfwver_info);
}

static ssize_t show_mem_info(struct device *dev,struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%s\n", rc_mem_info);
}

static int __init lpddr3_name(char *p)
{
	if(p == NULL){
		return -EINVAL;
	}
	sprintf(rc_mem_info,"%s",p);
	return 0;
}
__setup("lpddr3_name=",lpddr3_name);
///////////////////////////////
static DEVICE_ATTR(LCMINFO, 0664, show_LCMINFO, NULL);
static DEVICE_ATTR(GSENSORINFO, 0664, show_gsensor_info, NULL);
static DEVICE_ATTR(ALPSINFO, 0664, show_alps_info, NULL);
//static DEVICE_ATTR(MAINCAMERAINFO, 0664, show_main_camera_info, NULL);
//static DEVICE_ATTR(SUBCAMERAINFO, 0664, show_sub_camera_info, NULL);
static DEVICE_ATTR(TPINFO, 0664, show_tp_info, NULL);
static DEVICE_ATTR(GYROSCOPEINFO, 0664, show_gyroscope_info, NULL);
static DEVICE_ATTR(COMPASSINFO, 0664, show_compass_info, NULL);
static DEVICE_ATTR(TPFWVERINFO, 0664, show_tpfwver_info, NULL);
static DEVICE_ATTR(MEMINFO, 0664, show_mem_info, NULL);


static int device_info_probe(struct platform_device *dev)
{
  int ret_device_file=0;
  RC_DEVICE_INFO("device_info_probe");
  ret_device_file = device_create_file(&(dev->dev), &dev_attr_LCMINFO);
  ret_device_file = device_create_file(&(dev->dev), &dev_attr_TPINFO);
 // ret_device_file = device_create_file(&(dev->dev), &dev_attr_SUBCAMERAINFO);
 // ret_device_file = device_create_file(&(dev->dev), &dev_attr_MAINCAMERAINFO);
  ret_device_file = device_create_file(&(dev->dev), &dev_attr_GSENSORINFO);
  ret_device_file = device_create_file(&(dev->dev), &dev_attr_ALPSINFO);
  ret_device_file = device_create_file(&(dev->dev), &dev_attr_GYROSCOPEINFO);
  ret_device_file = device_create_file(&(dev->dev), &dev_attr_COMPASSINFO);
  ret_device_file = device_create_file(&(dev->dev), &dev_attr_TPFWVERINFO);
  ret_device_file = device_create_file(&(dev->dev), &dev_attr_MEMINFO);
}

static int device_info_remove(struct platform_device *dev)    
{
    RC_DEVICE_INFO("device_info_remove");
    return 0;
}

static void device_info_shutdown(struct platform_device *dev)    
{
     RC_DEVICE_INFO("device_info_shutdown");   
      return 0;
}

static int device_info_suspend(struct platform_device *dev, pm_message_t state)    
{
    RC_DEVICE_INFO("device_info_suspend");   
    return 0;
}

static int device_info_resume(struct platform_device *dev)
{
   RC_DEVICE_INFO("device_info_resume"); 
    return 0;
}

struct platform_device device_info_device = {
    .name   = "device_info",
    .id	    = -1,
};

static struct platform_driver device_info_driver = {
    .probe        = device_info_probe,
    .remove       = device_info_remove,
    .shutdown     = device_info_shutdown,
    .suspend      = device_info_suspend,
    .resume        = device_info_resume,
    .driver     = {
        .name = "device_info",
    },
};

///////////////////////////////
static void device_info_init(void)
{
    int ret;
    ret = platform_device_register(&device_info_device);
    if (ret) {
    printk("<<-rc-device-info->> Unable to device register(%d)\n", ret);
	return ret;
    }
    ret = platform_driver_register(&device_info_driver);
    if (ret) {
    printk("<<-rc-device-info->> Unable to driver (%d)\n", ret);
	return ret;
    }
   
}

static void device_info_exit(void)
{
	RC_DEVICE_INFO("device info exit");
}

module_exit(device_info_exit);
module_init(device_info_init);


MODULE_DESCRIPTION("rc device info");
MODULE_LICENSE("GPL");
