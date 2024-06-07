/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_HD44780U_H
#define ZRTOS_VFS_MODULE_HD44780U_H
#ifdef __cplusplus
extern "C" {
#endif


#ifndef LCD_DELAY_BOOTUP
#define LCD_DELAY_BOOTUP   16000      /**< delay in micro seconds after power-on  */
#endif
#ifndef LCD_DELAY_INIT
#define LCD_DELAY_INIT      5000      /**< delay in micro seconds after initialization command sent  */
#endif
#ifndef LCD_DELAY_INIT_REP
#define LCD_DELAY_INIT_REP    64      /**< delay in micro seconds after initialization command repeated */
#endif
#ifndef LCD_DELAY_INIT_4BIT
#define LCD_DELAY_INIT_4BIT   64      /**< delay in micro seconds after setting 4-bit mode */ 
#endif
#ifndef LCD_DELAY_BUSY_FLAG
#define LCD_DELAY_BUSY_FLAG    4      /**< time in micro seconds the address counter is updated after busy flag is cleared */
#endif
#ifndef LCD_DELAY_ENABLE_PULSE
#define LCD_DELAY_ENABLE_PULSE 1      /**< enable signal pulse width in micro seconds */
#endif


typedef struct _zrtos_vfs_module_hd44780u_t{
	zrtos_gpio_t      *gpio;
	zrtos_bitfield_t  bits[5];//40
	uint8_t           idx;
	zrtos_time_t      ts;
	zrtos_error_t     error;
}zrtos_vfs_module_hd44780u_t;

ssize_t zrtos_vfs_module_hd44780u__init(
	 zrtos_vfs_module_hd44780u_t *thiz
	,void *buf
	,size_t len
	,off_t offset
){
	zrtos_gpio__set_mode_ex(
		 thiz->gpio
		,7
		,thiz->pin_rs   , ZRTOS_GPIO_MODE__OUTPUT
		,thiz->pin_rw   , ZRTOS_GPIO_MODE__OUTPUT
		,thiz->pin_e    , ZRTOS_GPIO_MODE__OUTPUT
		,thiz->pin_data0, ZRTOS_GPIO_MODE__OUTPUT
		,thiz->pin_data1, ZRTOS_GPIO_MODE__OUTPUT
		,thiz->pin_data2, ZRTOS_GPIO_MODE__OUTPUT
		,thiz->pin_data3, ZRTOS_GPIO_MODE__OUTPUT
	);
	zrtos_gpio__delay_microseconds(LCD_DELAY_BOOTUP);

    /* initial write to lcd is 8bit */
    LCD_DATA1_PORT |= _BV(LCD_DATA1_PIN);    // LCD_FUNCTION>>4;
    LCD_DATA0_PORT |= _BV(LCD_DATA0_PIN);    // LCD_FUNCTION_8BIT>>4;
    lcd_e_toggle();
    zrtos_gpio__delay_microseconds(LCD_DELAY_INIT);               /* delay, busy flag can't be checked here */
   
    /* repeat last command */ 
    lcd_e_toggle();      
    zrtos_gpio__delay_microseconds(LCD_DELAY_INIT_REP);           /* delay, busy flag can't be checked here */
    
    /* repeat last command a third time */
    lcd_e_toggle();      
    zrtos_gpio__delay_microseconds(LCD_DELAY_INIT_REP);           /* delay, busy flag can't be checked here */

    /* now configure for 4bit mode */
    LCD_DATA0_PORT &= ~_BV(LCD_DATA0_PIN);   // LCD_FUNCTION_4BIT_1LINE>>4
    lcd_e_toggle();
    zrtos_gpio__delay_microseconds(LCD_DELAY_INIT_4BIT);          /* some displays need this additional delay */

}

ssize_t zrtos_vfs_module_hd44780u__write(
	 zrtos_vfs_module_hd44780u_t *thiz
	,void *buf
	,size_t len
	,off_t offset
){
}

ssize_t zrtos_vfs_module_hd44780u__read(
	 zrtos_vfs_module_hd44780u_t *thiz
	,void *buf
	,size_t len
	,off_t offset
){
	uint8_t data = 0;

	zrtos_gpio__set_mode_input(thiz->gpio,thiz->pin_data0);
	zrtos_gpio__set_mode_input(thiz->gpio,thiz->pin_data1);
	zrtos_gpio__set_mode_input(thiz->gpio,thiz->pin_data2);
	zrtos_gpio__set_mode_input(thiz->gpio,thiz->pin_data3);

	zrtos_gpio__set_high(thiz->gpio,thiz->pin_e);
 	zrtos_gpio__delay_microseconds(LCD_DELAY_ENABLE_PULSE);
	zrtos_gpio__read(
		 thiz->gpio
		,4
		,thiz->pin_data0
		,thiz->pin_data1
		,thiz->pin_data2
		,thiz->pin_data3
	);
	if ( PIN(LCD_DATA0_PORT) & _BV(LCD_DATA0_PIN) ) data |= 0x10;
	if ( PIN(LCD_DATA1_PORT) & _BV(LCD_DATA1_PIN) ) data |= 0x20;
	if ( PIN(LCD_DATA2_PORT) & _BV(LCD_DATA2_PIN) ) data |= 0x40;
	if ( PIN(LCD_DATA3_PORT) & _BV(LCD_DATA3_PIN) ) data |= 0x80;
	zrtos_gpio__set_low(thiz->gpio,thiz->pin_e);
	/* read high nibble first */
        lcd_e_high();
        lcd_e_delay();        
        data = 0;
        if ( PIN(LCD_DATA0_PORT) & _BV(LCD_DATA0_PIN) ) data |= 0x10;
        if ( PIN(LCD_DATA1_PORT) & _BV(LCD_DATA1_PIN) ) data |= 0x20;
        if ( PIN(LCD_DATA2_PORT) & _BV(LCD_DATA2_PIN) ) data |= 0x40;
        if ( PIN(LCD_DATA3_PORT) & _BV(LCD_DATA3_PIN) ) data |= 0x80;
        lcd_e_low();

	return data;
}

static bool zrtos_driver_dht11__on_change(void *data){
	zrtos_driver_dht11_t *thiz = data;

	int val = zrtos_gpio__get_value(thiz->gpio);
	if(val > 0){
		thiz->ts = zrtos_time__get_microseconds();
	}else if(val == 0){
		if(zrtos_time__get_microseconds() - thiz->ts > 40){
			zrtos_bitfield__set(thiz->bits,thiz->idx,true);
		}

		if(++thiz->idx == 40){
			thiz->error = (bits[0] + bits[2] == bits[4])
			            ? 0
			            : EIO
			;
			goto L_REMOVE_INTERUPT;
		}
	}else if(val < 0){
		thiz->error = -val;
L_REMOVE_INTERUPT:
		zrtos_gpio__disable_interrupt(&thiz->gpio);
	}
}

ssize_t zrtos_vfs_module_dht11__pread(
	 zrtos_file_t *thiz
	,void *buf
	,size_t len
	,off_t offset
){
	zrtos_driver_dht11_t *dht11 = zrtos_vfs_inode__get_private_data(
		zrtos_vfs_file__get_inode(
			thiz
		)
	);
	ssize_t ret = -dht11->error;

	if(ret == 0){
		offset = ZRTOS_TYPES__MIN(offset,5);
		len = ZRTOS_TYPES__MIN(len,5 - offset);
		zrtos_mem__cpy(buf,thiz->bits + offset,len);
		ret = len;
	}

	return ret;
}

ssize_t zrtos_vfs_module_dht11__pwrite(
	 zrtos_file_t *thiz
	,void *buf
	,size_t len
	,off_t offset
){
	zrtos_driver_dht11_t *dht11 = zrtos_vfs_inode__get_private_data(
		zrtos_vfs_file__get_inode(
			thiz
		)
	);

	zrtos_bitfield__zero(dht11->bits,5);
	dht11->idx = 40;
	dht11->error = EAGAIN;
	dht11->ts = 0;

	zrtos_gpio__set_mode(dht11->gpio, ZRTOS_GPIO_MODE__OUTPUT);
	zrtos_gpio__digital_write(dht11->gpio,false);
	zrtos_gpio__delay_milliseconds(18);
	zrtos_gpio__digital_write(dht11->gpio,true);
	zrtos_gpio__delay_microseconds(40);
	zrtos_gpio__set_mode(dht11->gpio, ZRTOS_GPIO_MODE__INPUT);

	zrtos_gpio__enable_interrupt(&thiz->gpio);

	return len;
}

size_t zrtos_vfs_module_dht11__can_read(struct _zrtos_file_t *thiz){
	zrtos_driver_dht11_t *dht11 = zrtos_vfs_inode__get_private_data(
		zrtos_vfs_file__get_inode(
			thiz
		)
	);

	return dht11->error == 0 ? 5 : 0;
}

bool zrtos_vfs_module_dht11__can_write(struct _zrtos_file_t *thiz){
	return true;
}

zrtos_vfs_plugin_t zrtos_vfs_module_dht11 = {
	 .mount = zrtos_vfs_module_dht11__mount
	,.umount = zrtos_vfs_module_dht11__umount
	,.pread = zrtos_vfs_module_dht11__pread
	,.pwrite = zrtos_vfs_module_dht11__pwrite
};

/*
int dht11::read(int pin)
{
	// BUFFER TO RECEIVE


	// EMPTY BUFFER
	for (int i=0; i< 5; i++) bits[i] = 0;

	// REQUEST SAMPLE
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(18);
	digitalWrite(pin, HIGH);
	delayMicroseconds(40);
	pinMode(pin, INPUT);

	// ACKNOWLEDGE or TIMEOUT
	unsigned int loopCnt = 10000;
	while(digitalRead(pin) == LOW)
		if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;

	loopCnt = 10000;
	while(digitalRead(pin) == HIGH)
		if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;

	// READ OUTPUT - 40 BITS => 5 BYTES or TIMEOUT
	for (int i=0; i<40; i++)
	{
		loopCnt = 10000;
		while(digitalRead(pin) == LOW)
			if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;

		unsigned long t = micros();

		loopCnt = 10000;
		while(digitalRead(pin) == HIGH)
			if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;

		if ((micros() - t) > 40) bits[idx] |= (1 << cnt);
		if (cnt == 0)   // next byte?
		{
			cnt = 7;    // restart at MSB
			idx++;      // next byte!
		}
		else cnt--;
	}

	// WRITE TO RIGHT VARS
        // as bits[1] and bits[3] are allways zero they are omitted in formulas.
	humidity    = bits[0]; 
	temperature = bits[2]; 

	uint8_t sum = bits[0] + bits[2];  

	if (bits[4] != sum) return DHTLIB_ERROR_CHECKSUM;
	return DHTLIB_OK;
}
*/


#ifdef __cplusplus
}
#endif
#endif
