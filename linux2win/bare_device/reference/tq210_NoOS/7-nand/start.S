.global _start				/* 声明一个全局的标号 */
_start:
		bl clock_init		/* 时钟初始 */
		bl uart_init		/* 串口初始化 */
		bl nand_init		/* NAND初始化 */
		bl main				/* 跳转到C函数去执行 */
halt:
		b halt
