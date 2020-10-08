/* 官方库文件 */
#include "sys.h"
/* 驱动库文件 */
#include "init.h"
/* 系统头文件 */
#include "start_task.h"

/********* 程序入口main *********/
int main(void)
{
	/* 驱动程序初始化 */
	DEVICE_INIT();
	/* 操作系统入口 */
	RTOS_START();
}


