/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_SPI_H
#define ZRTOS_VFS_MODULE_AVR_SPI_H
#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#include <zrtos/vfs_plugin.h>
#include <zrtos/vfs/module/spi/spi.h>

zrtos_vfs_module_spi_args_t *zrtos_vfs_module_avr_spi__ctx;

void zrtos_vfs_module_avr_spi__on_interrupt(){
	uint8_t data_in = SPDR;
	uint8_t data_out;
	zrtos_error_t err = zrtos_vfs_module_spi__transfer(
		 zrtos_vfs_module_avr_spi__ctx
		,(void*)&data_in
		,(void*)&data_out
		,sizeof(uint8_t)
	);

	Serial.println("##zrtos_vfs_module_avr_spi__on_interrupt##");
	Serial.println("##zrtos_vfs_module_avr_spi__on_interrupt##");
	Serial.println("##zrtos_vfs_module_avr_spi__on_interrupt##");
	Serial.println("##zrtos_vfs_module_avr_spi__on_interrupt##");

	pinMode(11,OUTPUT);
	pinMode(13,OUTPUT);
	pinMode(3,OUTPUT);
	digitalWrite(3,HIGH);

	SPCR |= (1<<MSTR);                 // Set as master
	SPCR |= (1<<SPR0)|(1<<SPR1);       // divide clock by 128
	SPCR |= (1<<SPIE);                 // Enable SPI Interrupt
	SPCR |= (1<<SPE);                  // Enable SPI

	sei();

	SPDR = data_out;

	//Serial.println((int)err);
	if(zrtos_error__is_error(err)){
		Serial.println("##SPCR &= ~_BV(SPIE);##");
		SPCR = 0;
	}else{
		Serial.println("##SPCR |= _BV(SPIE);##");
		//SPCR |= _BV(SPIE);
		//SPCR = zrtos_vfs_module_avr_spi__ctx->last->control;
	}

}

ISR(SPI_STC_vect){
	zrtos_vfs_module_avr_spi__on_interrupt();
}

zrtos_error_t zrtos_vfs_module_avr_spi__on_mount(zrtos_vfs_dentry_t *thiz){
	zrtos_vfs_module_avr_spi__ctx = ZRTOS_CAST(
		 zrtos_vfs_module_spi_args_t*
		,zrtos_vfs_dentry__get_inode_data(thiz)
	);
	return ESUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_spi__on_umount(zrtos_vfs_dentry_t *thiz){
	zrtos_vfs_module_avr_spi__ctx = 0;
	return ESUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_spi__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	Serial.println("##zrtos_vfs_module_avr_spi__on_write##");
	zrtos_vfs_module_spi_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	zrtos_error_t ret = zrtos_vfs_module_spi__on_write(
		 thiz
		,path
		,buf
		,len
		,offset
		,out
	);
	Serial.println("##zrtos_vfs_module_avr_spi__on_write2##");
	Serial.println((uint32_t)file_data);
	Serial.println(file_data->control);
	Serial.println(0 == (SPSR & _BV(SPIF)));
	if(zrtos_error__is_success(ret)
	&& file_data->control & ZRTOS_VFS_MODULE_SPI_CONTROL__MODE_MASTER
	&& 0 == (SPSR & _BV(SPIF))){
		Serial.println("##zrtos_vfs_module_avr_spi__on_write->zrtos_vfs_module_avr_spi__on_interrupt##");
		Serial.println(zrtos_vfs_module_avr_spi__ctx->last->control);
		zrtos_vfs_module_avr_spi__on_interrupt();
	}
	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(avr_spi,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN(zrtos_vfs_module_spi__on_open)
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE(zrtos_vfs_module_spi__on_close)
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_avr_spi__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_avr_spi__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_spi__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_avr_spi__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(zrtos_vfs_module_spi__on_can_read)
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(zrtos_vfs_module_spi__on_can_write)
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL(zrtos_vfs_module_spi__on_ioctl)
);


#ifdef __cplusplus
}
#endif
#endif
