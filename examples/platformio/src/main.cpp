#include <avr/io.h>

#include <stdint.h>
#include <stddef.h>

#define ZRTOS_ARCH__ATMEGA2560
#define ZRTOS_BOARD__AVR_SOFTWARE_EMULATOR

//typedef uint8_t max_align_t;

#define ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX 10

#include <zrtos/error.h>
#include <zrtos/types.h>
#include <zrtos/malloc.h>

ZRTOS_MALLOC__GLOBAL_HEAP(heap,500);

#include <zrtos/vfs_plugin.h>
#include <zrtos/vfs_inode.h>
#include <zrtos/vfs_dentry.h>
#include <zrtos/vfs_file.h>
#include <zrtos/vfs_fd.h>
#include <zrtos/vfs_notify.h>

#include <zrtos/vfs/module/arduino/gpio.h>
#include <zrtos/vfs/module/avr/uart/uart1.h>
#include <zrtos/vfs/module/avr/uart/uart2.h>
#include <zrtos/vfs/module/avr/uart/uart3.h>

void setup(void){
	ZRTOS_MALLOC__GLOBAL_HEAP_INIT(heap);
	Serial.begin(9600);

	//pinMode(19,INPUT_PULLUP);

	sei();
}

void loop(void){
	zrtos_vfs_module_uart_inode_t uart1_args;

	zrtos_vfs_dentry_t dev;
	zrtos_vfs_dentry_t dev_uart1;

	zrtos_vfs_module_uart_inode__init(
		 &uart1_args
		,ZRTOS_VFS_MODULE_UART_BAUDRATE__9600
		,ZRTOS_VFS_MODULE_UART_MODE__8N1
	);

	zrtos_vfs_dentry__init(
		 &dev
		,(char*)"dev"
		,0
	);

	zrtos_vfs_dentry__init(
		 &dev_uart1
		,(char*)"uart1"
		,&dev
	);


	zrtos_vfs_dentry__mount(
		 &dev_uart1
		,ZRTOS_VFS_PLUGIN(avr_uart1)
		,&uart1_args
	);

	zrtos_vfs_fd_t fd_uart1;


	zrtos_vfs_fd__open((char*)"/dev/uart1",&fd_uart1,0);

	delay(10000);
	Serial.println("##START##");

	size_t outlen;
	char buffer[20] = "1234\n";
	while(true){
		while(zrtos_error__is_success(zrtos_vfs_fd__can_read(fd_uart1))){
			uint8_t data;
			zrtos_error_t err = zrtos_vfs_fd__read(
				 fd_uart1
				,(char*)""
				,&data
				,1
				,0
				,&outlen
			);
			Serial.print(err);
			Serial.print(':');
			Serial.print(outlen);
			Serial.print('[');
			Serial.print(data);
			Serial.print(']');
			Serial.println();
		}
		zrtos_vfs_fd__write(
			 fd_uart1
			,(char*)""
			,buffer
			,zrtos_str__len(buffer)
			,0
			,&outlen
		);

		//zrtos_cbuffer__debug(&uart1_args.cbuffer_out);

		Serial.println("##NEXT##");
		delay(5000);
	}
}