/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_W5500_SOCKET_H
#define ZRTOS_VFS_MODULE_W5500_SOCKET_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_module.h>
#include <zrtos/vfs/network/network.h>

#include <zrtos/vfs/w5500/lib/w5500.h>


zrtos_error_t zrtos_vfs_module_w5500_socket__get_mode_register(
     zrtos_vfs_fd_t fd
    ,uint8_t socket
    ,uint8_t *mode
){
    
}

zrtos_error_t zrtos_vfs_module_w5500_socket__set_mode_register(
    zrtos_vfs_fd_t fd
    ,uint8_t socket
    ,uint8_t mode
){
    
}

zrtos_error_t zrtos_vfs_module_w5500_socket__get_command_register(
    zrtos_vfs_fd_t fd
    ,uint8_t socket
    ,uint8_t *command
){
    
}

zrtos_error_t zrtos_vfs_module_w5500_socket__set_command_register(
    zrtos_vfs_fd_t fd
    ,uint8_t socket
    ,uint8_t command
){
    
}

zrtos_error_t zrtos_vfs_module_w5500_socket__get_interrupt_register(
     zrtos_vfs_fd_t fd
    ,uint8_t socket
    ,uint8_t intrerrupt
){
    
}

zrtos_error_t zrtos_vfs_module_w5500_socket__get_status_register(
     zrtos_vfs_fd_t fd
    ,uint8_t socket
    ,uint8_t *status
){

}

zrtos_error_t zrtos_vfs_module_w5500_socket__get_port(
    zrtos_vfs_fd_t fd
    ,uint8_t socket
    ,zrtos_vfs_module_network_port_t *port
){
    
}

zrtos_error_t zrtos_vfs_module_w5500_socket__set_port(
     zrtos_vfs_fd_t fd
    ,uint8_t socket
    ,zrtos_vfs_module_network_port_t port
){
    
}

zrtos_error_t zrtos_vfs_module_w5500_socket__get_interrupt_mask(
     zrtos_vfs_fd_t fd
    ,uint8_t socket
    ,uint8_t *mask
){
    
}

zrtos_error_t zrtos_vfs_module_w5500_socket__set_interrupt_mask(
    zrtos_vfs_fd_t fd
    ,uint8_t socket
    ,uint8_t mask
){
    
}

/*
ZRTOS_VFS_PLUGIN__INIT(w5500_socket,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_w5500__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_w5500__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__5_ON_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL(zrtos_vfs_module_w5500__on_ioctl)
);
*/

#ifdef __cplusplus
}
#endif
#endif
