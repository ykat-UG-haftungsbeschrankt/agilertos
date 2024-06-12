/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_BOARD_ANSI_C_H
#define ZRTOS_BOARD_ANSI_C_H
#ifdef __cplusplus
extern "C" {
#endif


#if defined(ZRTOS_BOARD__ANSI_C) || defined(__DOXYGEN__)
#define ZRTOS_BOARD__FOUND


#define ZRTOS_BOARD__TICK_PERIOD_MS 1

void zrtos_board__start_tick_timer(void){
}

void zrtos_board__stop_tick_timer(void){
}

#define ZRTOS_BOARD__WATCH_DOG_START()

#define ZRTOS_BOARD__WATCH_DOG_STOP()

#define ZRTOS_BOARD__WATCH_DOG_RESET()

#endif


#ifdef __cplusplus
}
#endif
#endif