#include <avr/io.h>

#include <stdint.h>
#include <stddef.h>
/*
#define ZRTOS_ARCH__ATMEGA328P
#define ZRTOS_BOARD__AVR_SOFTWARE_EMULATOR

typedef uint8_t max_align_t;


#define ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX 10

#include <zrtos/error.h>
#include <zrtos/types.h>

typedef size_t off_t;

#include <zrtos/vfs_plugin.h>
#include <zrtos/vfs_inode.h>
#include <zrtos/vfs_dentry.h>
#include <zrtos/vfs_file.h>

#include <zrtos/vfs_module/zero/zero.h>
#include <zrtos/vfs_module/null/null.h>
#include <zrtos/vfs_module/random/random.h>
*/
int main(void){
	unsigned maxl = sizeof(max_align_t);
/*
	zrtos_vfs_dentry_t dev;
	zrtos_vfs_dentry_t dev_zero;
	zrtos_vfs_dentry_t dev_null;
	zrtos_vfs_dentry_t dev_random;

	zrtos_vfs_dentry__init(
		 &dev
		,"dev"
		,0
	);

	zrtos_vfs_dentry__init(
		 &dev_zero
		,"zero"
		,&dev
	);

	zrtos_vfs_dentry__init(
		 &dev_null
		,"null"
		,&dev
	);

	zrtos_vfs_dentry__init(
		 &dev_random
		,"random"
		,&dev
	);

	zrtos_vfs_dentry__mount(
		 &dev_zero
		,ZRTOS_VFS_PLUGIN(zero)
		,0
	);

	zrtos_vfs_dentry__mount(
		 &dev_random
		,ZRTOS_VFS_PLUGIN(random)
		,0
	);

	size_t ret;
	size_t fd;
	size_t fd2;
	uint8_t buffer[10];
		
	zrtos_vfs_file__open("/dev/zero",&fd);
	zrtos_vfs_file__open("/dev/random",&fd2);

	for(size_t l=5;l--;){
		zrtos_vfs_file__read(fd2,0,buffer,5,0,&ret);
	}
	zrtos_vfs_file__read(fd,0,buffer,5,0,&ret);

	return 0;
*/
}

