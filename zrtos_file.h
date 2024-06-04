
typedef struct _zrtos_file_t{
	zrtos_file_inode_t   *inode;
	size_t               offset;
	void                 *private_data;
}zrtos_file_t;

bool zrtos_file__init(zrtos_file_t *thiz){
	return thiz->offset < thiz->file->length;
}

uint8_t zrtos_file__deinit(zrtos_file_t *thiz){
	return zrtos_file__can_read(thiz);
}

bool zrtos_file__read(zrtos_file_t *thiz){
	return thiz->offset < thiz->file->length;
}

uint8_t zrtos_file__write(zrtos_file_t *thiz){
	return zrtos_file__can_read(thiz);
}

bool zrtos_file__pread(zrtos_file_t *thiz){
	return thiz->offset < thiz->file->length;
}

uint8_t zrtos_file__pwrite(zrtos_file_t *thiz){
	return zrtos_file__can_read(thiz);
}

size_t zrtos_file__strnlen(zrtos_file_t *thiz,size_t len){
	zrtos_file_t ptr = zrtos_file__clone(thiz);
	while(len-- && zrtos_file__get_uint8(&ptr)){
		zrtos_file__inc(&ptr);
	}
	return zrtos_file__get_distance(&ptr,thiz);
}

void zrtos_file__memcpy(zrtos_file_t *a,zrtos_file_t *b,size_t len){
	zrtos_file_t aa = zrtos_file__clone(a);
	zrtos_file_t bb = zrtos_file__clone(b);
	while(len--){
		zrtos_file__set_uint8(
			 &aa
			,zrtos_file__get_uint8(&bb)
		);
		zrtos_file__inc(&aa);
		zrtos_file__inc(&bb);
	}
}

int zrtos_file__memcmp(zrtos_file_t *a,zrtos_file_t *b,size_t len){
	zrtos_file_t aa = zrtos_file__clone(a);
	zrtos_file_t bb = zrtos_file__clone(b);
	while(len--){
		uint8_t aaa = zrtos_file__get_uint8(&aa);
		uint8_t bbb = zrtos_file__get_uint8(&bb);
		if(aaa < bbb){
			return -1;
		}else if(aaa > bbb){
			return 1;
		}
		zrtos_file__inc(&aa);
		zrtos_file__inc(&bb);
	}
	return 0;
}

int zrtos_file__strncmp(zrtos_file_t *a,zrtos_file_t *b,size_t len){
	size_t aa = zrtos_file__strnlen(a,len);
	size_t bb = zrtos_file__strnlen(b,len);
	if(aa < bb){
		return -1;
	}else if(aa > bb){
		return 1;
	}else{
		return zrtos_file__memcmp(a,b,aa);
	}
}

#define ZRTOS_FILE__EACH(fd)\
    for(size_t fd = 0\
       ; ZRTOS_TYPES__SIZE_MAX\
       != (fd = zrtos_bitfield__find_first_set(zrtos_file_descriptor_index,fd))\
       ;fd++\
    )