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

int main(void){

	zrtos_vfs_dentry_t root;

	zrtos_vfs_dentry_t zero;

	zrtos_vfs_dentry__init(
		 &root
		,"dev"
		,0
	);

	zrtos_vfs_dentry__init(
		 &zero
		,"zero"
		,&root
	);

	size_t fd;
	zrtos_vfs_file__open("/dev/zero",&fd);
	

	return 0;
}

