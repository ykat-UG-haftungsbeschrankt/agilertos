#include <avr/io.h>

#define ZRTOS_ARCH__ATMEGA328P
#define ZRTOS_BOARD__AVR_SOFTWARE_EMULATOR

typedef uint8_t max_align_t;


#define ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX 10

#include "zrtos_error.h"
#include "zrtos_types.h"

typedef size_t off_t;

#include "zrtos_vfs_plugin.h"
#include "zrtos_vfs_inode.h"
#include "zrtos_vfs_dentry.h"
#include "zrtos_vfs_file.h"

#include "zrtos_vfs_module/zero/zero.h"
#include "zrtos_vfs_module/null/null.h"

int main(void){

	zrtos_vfs_dentry_t dev;
	zrtos_vfs_dentry_t dev_zero;
	zrtos_vfs_dentry_t dev_null;

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

	zrtos_vfs_dentry__mount(
		 &dev_zero
		,ZRTOS_VFS_PLUGIN(zero)
		,0
	);

	size_t fd;
	zrtos_vfs_file__open("/dev/zero",&fd);
	

	return 0;
}

