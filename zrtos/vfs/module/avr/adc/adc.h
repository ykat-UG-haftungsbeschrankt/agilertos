/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_ADC_H
#define ZRTOS_VFS_MODULE_AVR_ADC_H
#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#include <zrtos/vfs_plugin.h>
#include <zrtos/types.h>
#include <zrtos/cast.h>
#include <zrtos/binary.h>

typedef enum{
	 ZRTOS_VFS_MODULE_AVR_ADC_PRESCALER__2   = ZRTOS_BINARY__00000000
	,ZRTOS_VFS_MODULE_AVR_ADC_PRESCALER__4   = ZRTOS_BINARY__00000010
	,ZRTOS_VFS_MODULE_AVR_ADC_PRESCALER__8   = ZRTOS_BINARY__00000011
	,ZRTOS_VFS_MODULE_AVR_ADC_PRESCALER__16  = ZRTOS_BINARY__00000100
	,ZRTOS_VFS_MODULE_AVR_ADC_PRESCALER__32  = ZRTOS_BINARY__00000101
	,ZRTOS_VFS_MODULE_AVR_ADC_PRESCALER__64  = ZRTOS_BINARY__00000110
	,ZRTOS_VFS_MODULE_AVR_ADC_PRESCALER__128 = ZRTOS_BINARY__00000111
}zrtos_vfs_module_avr_adc_prescaler_t;

typedef enum{
	 ZRTOS_VFS_MODULE_AVR_ADC_VREF__EXTERN = ZRTOS_BINARY__00000000
	,ZRTOS_VFS_MODULE_AVR_ADC_VREF__INTERN = ZRTOS_BINARY__01000000
	,ZRTOS_VFS_MODULE_AVR_ADC_VREF__MISC1  = ZRTOS_BINARY__10000000
	,ZRTOS_VFS_MODULE_AVR_ADC_VREF__MISC2  = ZRTOS_BINARY__11000000
}zrtos_vfs_module_avr_adc_vref_t;

#ifndef ZRTOS_VFS_MODULE_AVR_ADC__CFG_PRESCALER
#error "define ZRTOS_VFS_MODULE_AVR_ADC__CFG_PRESCALER as zrtos_vfs_module_avr_adc_prescaler_t value"
#endif

#ifndef ZRTOS_VFS_MODULE_AVR_ADC__CFG_VREF
#error "define ZRTOS_VFS_MODULE_AVR_ADC__CFG_VREF as zrtos_vfs_module_avr_adc_vref_t value"
#endif

#ifndef ZRTOS_VFS_MODULE_AVR_ADC__CFG_MAX_CHANNEL
#error "define ZRTOS_VFS_MODULE_AVR_ADC__CFG_MAX_CHANNEL"
#endif

#ifndef ZRTOS_VFS_MODULE_AVR_ADC__CFG_REFERENCE_VOLT
#warning "ZRTOS_VFS_MODULE_AVR_ADC__CFG_REFERENCE_VOLT not defined using 5 Volt"
#define ZRTOS_VFS_MODULE_AVR_ADC__CFG_REFERENCE_VOLT (5.0)
#endif

typedef struct zrtos_vfs_module_avr_adc_t{
	//zrtos_vfs_module_avr_adc_prescaler_t prescaler;
	//zrtos_vfs_module_avr_adc_vref_t      vref;
	uint16_t data[ZRTOS_VFS_MODULE_AVR_ADC__CFG_MAX_CHANNEL];
}zrtos_vfs_module_avr_adc_t;

zrtos_vfs_module_avr_adc_t zrtos_vfs_module_avr_adc__data;

float zrtos_vfs_module_avr_adc__to_volt(uint16_t val,float vref){
	return (((float)val) * vref) / 1024.0;
}

ISR(ADC_vect){
	static uint8_t channel = 0;
	uint16_t val = ADCL;
	val |= (ADCH<<8);

	zrtos_vfs_module_avr_adc__data.data[channel] = val;

	channel++;
	if(channel >= ZRTOS_VFS_MODULE_AVR_ADC__CFG_MAX_CHANNEL){
		channel = 0;
	}
	
#ifdef MUX5
	if (channel > 7) {
		ADCSRB |= _BV(MUX5);
		ADMUX = (ADMUX & ~(0x1F)) | ((channel-8) & 0x1F);
	} else {
		ADCSRB &= ~(_BV(MUX5));
		ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
	}
#else
	ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
#endif

	ADCSRA |= _BV(ADSC);
}

zrtos_error_t zrtos_vfs_module_avr_adc__on_mount(zrtos_vfs_dentry_t *thiz){
	ADMUX = ZRTOS_VFS_MODULE_AVR_ADC__CFG_VREF;
#ifdef MUX5
	ADCSRB &= ~(_BV(MUX5));
#endif
	ADCSRA = _BV(ADEN)
	       | _BV(ADSC)
	       | _BV(ADIE)
	       | ZRTOS_VFS_MODULE_AVR_ADC__CFG_PRESCALER
	;
	return ESUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_adc__on_umount(zrtos_vfs_dentry_t *thiz){
	ADCSRA = 0;
	return ESUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_adc__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_error_t ret = EFAULT;
	size_t start_offset = (size_t)offset;
	size_t channel = start_offset/sizeof(float);

	if(len != sizeof(float)
	||(start_offset % sizeof(float)) != 0){
		ret = EINVAL;
	}else if(channel < ZRTOS_VFS_MODULE_AVR_ADC__CFG_MAX_CHANNEL){
		float val = zrtos_vfs_module_avr_adc__to_volt(
			 zrtos_vfs_module_avr_adc__data.data[channel]
			,ZRTOS_VFS_MODULE_AVR_ADC__CFG_REFERENCE_VOLT
		);

		zrtos_mem__cpy(buf,&val,sizeof(float));

		ret = ESUCCESS;
	}

	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(avr_adc,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_avr_adc__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_avr_adc__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_avr_adc__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(zrtos_vfs_plugin__default_can_write_read_only)
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);


#ifdef __cplusplus
}
#endif
#endif
