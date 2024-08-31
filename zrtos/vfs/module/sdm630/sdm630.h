/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_SDM630_H
#define ZRTOS_VFS_MODULE_SDM630_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_module.h>
#include <zrtos/mem.h>

/*
zIotNodeSdm630Register zIotNodeSdm630RegisterAddressList[] = {
  ,{"SDM_PHASE_1_VOLTAGE",                           0x0000}                    //  V           |    1    |    1    |    1    |    1    |    1    |         |    1    |         
  ,{"SDM_PHASE_2_VOLTAGE",                           0x0002}                    //  V           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_3_VOLTAGE",                           0x0004}                    //  V           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_1_CURRENT",                           0x0006}                    //  A           |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,{"SDM_PHASE_2_CURRENT",                           0x0008}                    //  A           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_3_CURRENT",                           0x000A}                    //  A           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_1_POWER",                             0x000C}                    //  W           |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,{"SDM_PHASE_2_POWER",                             0x000E}                    //  W           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_3_POWER",                             0x0010}                    //  W           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_1_APPARENT_POWER",                    0x0012}                    //  VA          |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,{"SDM_PHASE_2_APPARENT_POWER",                    0x0014}                    //  VA          |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_3_APPARENT_POWER",                    0x0016}                    //  VA          |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_1_REACTIVE_POWER",                    0x0018}                    //  VAr         |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,{"SDM_PHASE_2_REACTIVE_POWER",                    0x001A}                    //  VAr         |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_3_REACTIVE_POWER",                    0x001C}                    //  VAr         |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_1_POWER_FACTOR",                      0x001E}                    //              |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,{"SDM_PHASE_2_POWER_FACTOR",                      0x0020}                    //              |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_3_POWER_FACTOR",                      0x0022}                    //              |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_1_ANGLE",                             0x0024}                    //  Degrees     |    1    |    1    |    1    |    1    |         |         |         |
  ,{"SDM_PHASE_2_ANGLE",                             0x0026}                    //  Degrees     |    1    |         |         |         |         |         |         |
  ,{"SDM_PHASE_3_ANGLE",                             0x0028}                    //  Degrees     |    1    |         |         |         |         |         |         |
  ,{"SDM_AVERAGE_L_TO_N_VOLTS",                      0x002A}                    //  V           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_AVERAGE_LINE_CURRENT",                      0x002E}                    //  A           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_SUM_LINE_CURRENT",                          0x0030}                    //  A           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_TOTAL_SYSTEM_POWER",                        0x0034}                    //  W           |    1    |         |         |         |         |    1    |    1    |
  ,{"SDM_TOTAL_SYSTEM_APPARENT_POWER",               0x0038}                    //  VA          |    1    |         |         |         |         |         |    1    |
  ,{"SDM_TOTAL_SYSTEM_REACTIVE_POWER",               0x003C}                    //  VAr         |    1    |         |         |         |         |         |    1    |
  ,{"SDM_TOTAL_SYSTEM_POWER_FACTOR",                 0x003E}                    //              |    1    |         |         |         |         |         |    1    |
  ,{"SDM_TOTAL_SYSTEM_PHASE_ANGLE",                  0x0042}                    //  Degrees     |    1    |         |         |         |         |         |         |
  ,{"SDM_FREQUENCY",                                 0x0046}                    //  Hz          |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,{"SDM_IMPORT_ACTIVE_ENERGY",                      0x0048}                    //  kWh/MWh     |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
  ,{"SDM_EXPORT_ACTIVE_ENERGY",                      0x004A}                    //  kWh/MWh     |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
  ,{"SDM_IMPORT_REACTIVE_ENERGY",                    0x004C}                    //  kVArh/MVArh |    1    |    1    |    1    |    1    |    1    |         |         |
  ,{"SDM_EXPORT_REACTIVE_ENERGY",                    0x004E}                    //  kVArh/MVArh |    1    |    1    |    1    |    1    |    1    |         |         |
  ,{"SDM_VAH_SINCE_LAST_RESET",                      0x0050}                    //  kVAh/MVAh   |    1    |         |         |         |         |         |         |
  ,{"SDM_AH_SINCE_LAST_RESET",                       0x0052}                    //  Ah/kAh      |    1    |         |         |         |         |         |         |
  ,{"SDM_TOTAL_SYSTEM_POWER_DEMAND",                 0x0054}                    //  W           |    1    |    1    |         |         |         |         |         |
  ,{"SDM_MAXIMUM_TOTAL_SYSTEM_POWER_DEMAND",         0x0056}                    //  W           |    1    |    1    |         |         |         |         |         |
  ,{"SDM_CURRENT_SYSTEM_POSITIVE_POWER_DEMAND",      0x0058}                    //  W           |         |    1    |         |         |         |         |         |
  ,{"SDM_MAXIMUM_SYSTEM_POSITIVE_POWER_DEMAND",      0x005A}                    //  W           |         |    1    |         |         |         |         |         |
  ,{"SDM_CURRENT_SYSTEM_REVERSE_POWER_DEMAND",       0x005C}                    //  W           |         |    1    |         |         |         |         |         |
  ,{"SDM_MAXIMUM_SYSTEM_REVERSE_POWER_DEMAND",       0x005E}                    //  W           |         |    1    |         |         |         |         |         |
  ,{"SDM_TOTAL_SYSTEM_VA_DEMAND",                    0x0064}                    //  VA          |    1    |         |         |         |         |         |         |
  ,{"SDM_MAXIMUM_TOTAL_SYSTEM_VA_DEMAND",            0x0066}                    //  VA          |    1    |         |         |         |         |         |         |
  ,{"SDM_NEUTRAL_CURRENT_DEMAND",                    0x0068}                    //  A           |    1    |         |         |         |         |         |         |
  ,{"SDM_MAXIMUM_NEUTRAL_CURRENT",                   0x006A}                    //  A           |    1    |         |         |         |         |         |         |
  ,{"SDM_REACTIVE_POWER_DEMAND",                     0x006C}                    //  VAr         |    1    |         |         |         |         |         |         |
  ,{"SDM_MAXIMUM_REACTIVE_POWER_DEMAND",             0x006E}                    //  VAr         |    1    |         |         |         |         |         |         |
  ,{"SDM_LINE_1_TO_LINE_2_VOLTS",                    0x00C8}                    //  V           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_LINE_2_TO_LINE_3_VOLTS",                    0x00CA}                    //  V           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_LINE_3_TO_LINE_1_VOLTS",                    0x00CC}                    //  V           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_AVERAGE_LINE_TO_LINE_VOLTS",                0x00CE}                    //  V           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_NEUTRAL_CURRENT",                           0x00E0}                    //  A           |    1    |         |         |         |         |         |    1    |
  ,{"SDM_PHASE_1_LN_VOLTS_THD",                      0x00EA}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_PHASE_2_LN_VOLTS_THD",                      0x00EC}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_PHASE_3_LN_VOLTS_THD",                      0x00EE}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_PHASE_1_CURRENT_THD",                       0x00F0}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_PHASE_2_CURRENT_THD",                       0x00F2}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_PHASE_3_CURRENT_THD",                       0x00F4}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_AVERAGE_LINE_TO_NEUTRAL_VOLTS_THD",         0x00F8}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_AVERAGE_LINE_CURRENT_THD",                  0x00FA}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_TOTAL_SYSTEM_POWER_FACTOR_INV",             0x00FE}                    //              |    1    |         |         |         |         |         |         |
  ,{"SDM_PHASE_1_CURRENT_DEMAND",                    0x0102}                    //  A           |    1    |    1    |         |         |         |         |         |
  ,{"SDM_PHASE_2_CURRENT_DEMAND",                    0x0104}                    //  A           |    1    |         |         |         |         |         |         |
  ,{"SDM_PHASE_3_CURRENT_DEMAND",                    0x0106}                    //  A           |    1    |         |         |         |         |         |         |
  ,{"SDM_MAXIMUM_PHASE_1_CURRENT_DEMAND",            0x0108}                    //  A           |    1    |    1    |         |         |         |         |         |
  ,{"SDM_MAXIMUM_PHASE_2_CURRENT_DEMAND",            0x010A}                    //  A           |    1    |         |         |         |         |         |         |
  ,{"SDM_MAXIMUM_PHASE_3_CURRENT_DEMAND",            0x010C}                    //  A           |    1    |         |         |         |         |         |         |
  ,{"SDM_LINE_1_TO_LINE_2_VOLTS_THD",                0x014E}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_LINE_2_TO_LINE_3_VOLTS_THD",                0x0150}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_LINE_3_TO_LINE_1_VOLTS_THD",                0x0152}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_AVERAGE_LINE_TO_LINE_VOLTS_THD",            0x0154}                    //  %           |    1    |         |         |         |         |         |         |
  ,{"SDM_TOTAL_ACTIVE_ENERGY",                       0x0156}                    //  kWh         |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
  ,{"SDM_TOTAL_REACTIVE_ENERGY",                     0x0158}                    //  kVArh       |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,{"SDM_L1_IMPORT_ACTIVE_ENERGY",                   0x015A}                    //  kWh         |    1    |         |         |         |         |         |         |
  ,{"SDM_L2_IMPORT_ACTIVE_ENERGY",                   0x015C}                    //  kWh         |    1    |         |         |         |         |         |         |
  ,{"SDM_L3_IMPORT_ACTIVE_ENERGY",                   0x015E}                    //  kWh         |    1    |         |         |         |         |         |         |
  ,{"SDM_L1_EXPORT_ACTIVE_ENERGY",                   0x0160}                    //  kWh         |    1    |         |         |         |         |         |         |
  ,{"SDM_L2_EXPORT_ACTIVE_ENERGY",                   0x0162}                    //  kWh         |    1    |         |         |         |         |         |         |
  ,{"SDM_L3_EXPORT_ACTIVE_ENERGY",                   0x0164}                    //  kWh         |    1    |         |         |         |         |         |         |
  ,{"SDM_L1_TOTAL_ACTIVE_ENERGY",                    0x0166}                    //  kWh         |    1    |         |         |         |         |         |         |
  ,{"SDM_L2_TOTAL_ACTIVE_ENERGY",                    0x0168}                    //  kWh         |    1    |         |         |         |         |         |         |
  ,{"SDM_L3_TOTAL_ACTIVE_ENERGY",                    0x016a}                    //  kWh         |    1    |         |         |         |         |         |         |
  ,{"SDM_L1_IMPORT_REACTIVE_ENERGY",                 0x016C}                    //  kVArh       |    1    |         |         |         |         |         |         |
  ,{"SDM_L2_IMPORT_REACTIVE_ENERGY",                 0x016E}                    //  kVArh       |    1    |         |         |         |         |         |         |
  ,{"SDM_L3_IMPORT_REACTIVE_ENERGY",                 0x0170}                    //  kVArh       |    1    |         |         |         |         |         |         |
  ,{"SDM_L1_EXPORT_REACTIVE_ENERGY",                 0x0172}                    //  kVArh       |    1    |         |         |         |         |         |         |
  ,{"SDM_L2_EXPORT_REACTIVE_ENERGY",                 0x0174}                    //  kVArh       |    1    |         |         |         |         |         |         |
  ,{"SDM_L3_EXPORT_REACTIVE_ENERGY",                 0x0176}                    //  kVArh       |    1    |         |         |         |         |         |         |
  ,{"SDM_L1_TOTAL_REACTIVE_ENERGY",                  0x0178}                    //  kVArh       |    1    |         |         |         |         |         |         |
  ,{"SDM_L2_TOTAL_REACTIVE_ENERGY",                  0x017A}                    //  kVArh       |    1    |         |         |         |         |         |         |
  ,{"SDM_L3_TOTAL_REACTIVE_ENERGY",                  0x017C}                    //  kVArh       |    1    |         |         |         |         |         |         |
  ,{"SDM_CURRENT_RESETTABLE_TOTAL_ACTIVE_ENERGY",    0x0180}                    //  kWh         |         |    1    |         |         |         |    1    |    1    |
  ,{"SDM_CURRENT_RESETTABLE_TOTAL_REACTIVE_ENERGY",  0x0182}                    //  kVArh       |         |    1    |         |         |         |         |         |
  ,{"SDM_CURRENT_RESETTABLE_IMPORT_ENERGY",          0x0184}                    //  kWh         |         |         |         |         |         |    1    |    1    |
  ,{"SDM_CURRENT_RESETTABLE_EXPORT_ENERGY",          0x0186}                    //  kWh         |         |         |         |         |         |    1    |    1    |
  ,{"SDM_CURRENT_RESETTABLE_IMPORT_REACTIVE_ENERGY", 0x0188}                    //  kVArh       |         |         |         |         |         |    1    |    1    |
  ,{"SDM_CURRENT_RESETTABLE_EXPORT_REACTIVE_ENERGY", 0x018A}                    //  kVArh       |         |         |         |         |         |    1    |    1    |
  ,{"SDM_NET_KWH",                                   0x018C}                    //  kWh         |         |         |         |         |         |         |    1    |
  ,{"SDM_NET_KVARH",                                 0x018E}                    //  kVArh       |         |         |         |         |         |         |    1    |
  ,{"SDM_IMPORT_POWER",                              0x0500}                    //  W           |         |         |         |         |         |    1    |    1    |
  ,{"SDM_EXPORT_POWER",                              0x0502}                    //  W  
  ,{0,0}
};
*/

typedef enum{
   ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_1_VOLTAGE =                           0x0000                    ///<  V           |    1    |    1    |    1    |    1    |    1    |         |    1    |         
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_2_VOLTAGE =                           0x0002                    ///<  V           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_3_VOLTAGE =                           0x0004                    ///<  V           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_1_CURRENT =                           0x0006                    ///<  A           |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_2_CURRENT =                           0x0008                    ///<  A           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_3_CURRENT =                           0x000A                    ///<  A           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_1_POWER =                             0x000C                    ///<  W           |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_2_POWER =                             0x000E                    ///<  W           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_3_POWER =                             0x0010                    ///<  W           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_1_APPARENT_POWER =                    0x0012                    ///<  VA          |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_2_APPARENT_POWER =                    0x0014                    ///<  VA          |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_3_APPARENT_POWER =                    0x0016                    ///<  VA          |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_1_REACTIVE_POWER =                    0x0018                    ///<  VAr         |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_2_REACTIVE_POWER =                    0x001A                    ///<  VAr         |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_3_REACTIVE_POWER =                    0x001C                    ///<  VAr         |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_1_POWER_FACTOR =                      0x001E                    ///<              |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_2_POWER_FACTOR =                      0x0020                    ///<              |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_3_POWER_FACTOR =                      0x0022                    ///<              |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_1_ANGLE =                             0x0024                    ///<  Degrees     |    1    |    1    |    1    |    1    |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_2_ANGLE =                             0x0026                    ///<  Degrees     |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_3_ANGLE =                             0x0028                    ///<  Degrees     |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__AVERAGE_L_TO_N_VOLTS =                      0x002A                    ///<  V           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__AVERAGE_LINE_CURRENT =                      0x002E                    ///<  A           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__SUM_LINE_CURRENT =                          0x0030                    ///<  A           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__TOTAL_SYSTEM_POWER =                        0x0034                    ///<  W           |    1    |         |         |         |         |    1    |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__TOTAL_SYSTEM_APPARENT_POWER =               0x0038                    ///<  VA          |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__TOTAL_SYSTEM_REACTIVE_POWER =               0x003C                    ///<  VAr         |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__TOTAL_SYSTEM_POWER_FACTOR =                 0x003E                    ///<              |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__TOTAL_SYSTEM_PHASE_ANGLE =                  0x0042                    ///<  Degrees     |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__FREQUENCY =                                 0x0046                    ///<  Hz          |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__IMPORT_ACTIVE_ENERGY =                      0x0048                    ///<  kWh/MWh     |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__EXPORT_ACTIVE_ENERGY =                      0x004A                    ///<  kWh/MWh     |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__IMPORT_REACTIVE_ENERGY =                    0x004C                    ///<  kVArh/MVArh |    1    |    1    |    1    |    1    |    1    |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__EXPORT_REACTIVE_ENERGY =                    0x004E                    ///<  kVArh/MVArh |    1    |    1    |    1    |    1    |    1    |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__VAH_SINCE_LAST_RESET =                      0x0050                    ///<  kVAh/MVAh   |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__AH_SINCE_LAST_RESET =                       0x0052                    ///<  Ah/kAh      |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__TOTAL_SYSTEM_POWER_DEMAND =                 0x0054                    ///<  W           |    1    |    1    |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__MAXIMUM_TOTAL_SYSTEM_POWER_DEMAND =         0x0056                    ///<  W           |    1    |    1    |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__CURRENT_SYSTEM_POSITIVE_POWER_DEMAND =      0x0058                    ///<  W           |         |    1    |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__MAXIMUM_SYSTEM_POSITIVE_POWER_DEMAND =      0x005A                    ///<  W           |         |    1    |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__CURRENT_SYSTEM_REVERSE_POWER_DEMAND =       0x005C                    ///<  W           |         |    1    |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__MAXIMUM_SYSTEM_REVERSE_POWER_DEMAND =       0x005E                    ///<  W           |         |    1    |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__TOTAL_SYSTEM_VA_DEMAND =                    0x0064                    ///<  VA          |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__MAXIMUM_TOTAL_SYSTEM_VA_DEMAND =            0x0066                    ///<  VA          |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__NEUTRAL_CURRENT_DEMAND =                    0x0068                    ///<  A           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__MAXIMUM_NEUTRAL_CURRENT =                   0x006A                    ///<  A           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__REACTIVE_POWER_DEMAND =                     0x006C                    ///<  VAr         |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__MAXIMUM_REACTIVE_POWER_DEMAND =             0x006E                    ///<  VAr         |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__LINE_1_TO_LINE_2_VOLTS =                    0x00C8                    ///<  V           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__LINE_2_TO_LINE_3_VOLTS =                    0x00CA                    ///<  V           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__LINE_3_TO_LINE_1_VOLTS =                    0x00CC                    ///<  V           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__AVERAGE_LINE_TO_LINE_VOLTS =                0x00CE                    ///<  V           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__NEUTRAL_CURRENT =                           0x00E0                    ///<  A           |    1    |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_1_LN_VOLTS_THD =                      0x00EA                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_2_LN_VOLTS_THD =                      0x00EC                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_3_LN_VOLTS_THD =                      0x00EE                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_1_CURRENT_THD =                       0x00F0                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_2_CURRENT_THD =                       0x00F2                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_3_CURRENT_THD =                       0x00F4                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__AVERAGE_LINE_TO_NEUTRAL_VOLTS_THD =         0x00F8                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__AVERAGE_LINE_CURRENT_THD =                  0x00FA                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__TOTAL_SYSTEM_POWER_FACTOR_INV =             0x00FE                    ///<              |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_1_CURRENT_DEMAND =                    0x0102                    ///<  A           |    1    |    1    |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_2_CURRENT_DEMAND =                    0x0104                    ///<  A           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__PHASE_3_CURRENT_DEMAND =                    0x0106                    ///<  A           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__MAXIMUM_PHASE_1_CURRENT_DEMAND =            0x0108                    ///<  A           |    1    |    1    |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__MAXIMUM_PHASE_2_CURRENT_DEMAND =            0x010A                    ///<  A           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__MAXIMUM_PHASE_3_CURRENT_DEMAND =            0x010C                    ///<  A           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__LINE_1_TO_LINE_2_VOLTS_THD =                0x014E                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__LINE_2_TO_LINE_3_VOLTS_THD =                0x0150                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__LINE_3_TO_LINE_1_VOLTS_THD =                0x0152                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__AVERAGE_LINE_TO_LINE_VOLTS_THD =            0x0154                    ///<  %           |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__TOTAL_ACTIVE_ENERGY =                       0x0156                    ///<  kWh         |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__TOTAL_REACTIVE_ENERGY =                     0x0158                    ///<  kVArh       |    1    |    1    |    1    |    1    |    1    |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L1_IMPORT_ACTIVE_ENERGY =                   0x015A                    ///<  kWh         |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L2_IMPORT_ACTIVE_ENERGY =                   0x015C                    ///<  kWh         |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L3_IMPORT_ACTIVE_ENERGY =                   0x015E                    ///<  kWh         |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L1_EXPORT_ACTIVE_ENERGY =                   0x0160                    ///<  kWh         |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L2_EXPORT_ACTIVE_ENERGY =                   0x0162                    ///<  kWh         |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L3_EXPORT_ACTIVE_ENERGY =                   0x0164                    ///<  kWh         |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L1_TOTAL_ACTIVE_ENERGY =                    0x0166                    ///<  kWh         |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L2_TOTAL_ACTIVE_ENERGY =                    0x0168                    ///<  kWh         |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L3_TOTAL_ACTIVE_ENERGY =                    0x016a                    ///<  kWh         |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L1_IMPORT_REACTIVE_ENERGY =                 0x016C                    ///<  kVArh       |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L2_IMPORT_REACTIVE_ENERGY =                 0x016E                    ///<  kVArh       |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L3_IMPORT_REACTIVE_ENERGY =                 0x0170                    ///<  kVArh       |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L1_EXPORT_REACTIVE_ENERGY =                 0x0172                    ///<  kVArh       |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L2_EXPORT_REACTIVE_ENERGY =                 0x0174                    ///<  kVArh       |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L3_EXPORT_REACTIVE_ENERGY =                 0x0176                    ///<  kVArh       |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L1_TOTAL_REACTIVE_ENERGY =                  0x0178                    ///<  kVArh       |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L2_TOTAL_REACTIVE_ENERGY =                  0x017A                    ///<  kVArh       |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__L3_TOTAL_REACTIVE_ENERGY =                  0x017C                    ///<  kVArh       |    1    |         |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__CURRENT_RESETTABLE_TOTAL_ACTIVE_ENERGY =    0x0180                    ///<  kWh         |         |    1    |         |         |         |    1    |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__CURRENT_RESETTABLE_TOTAL_REACTIVE_ENERGY =  0x0182                    ///<  kVArh       |         |    1    |         |         |         |         |         |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__CURRENT_RESETTABLE_IMPORT_ENERGY =          0x0184                    ///<  kWh         |         |         |         |         |         |    1    |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__CURRENT_RESETTABLE_EXPORT_ENERGY =          0x0186                    ///<  kWh         |         |         |         |         |         |    1    |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__CURRENT_RESETTABLE_IMPORT_REACTIVE_ENERGY = 0x0188                    ///<  kVArh       |         |         |         |         |         |    1    |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__CURRENT_RESETTABLE_EXPORT_REACTIVE_ENERGY = 0x018A                    ///<  kVArh       |         |         |         |         |         |    1    |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__NET_KWH =                                   0x018C                    ///<  kWh         |         |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__NET_KVARH =                                 0x018E                    ///<  kVArh       |         |         |         |         |         |         |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__IMPORT_POWER =                              0x0500                    ///<  W           |         |         |         |         |         |    1    |    1    |
  ,ZRTOS_VFS_MODULE_SDM630_REGISTER_ADDRESS__EXPORT_POWER =                              0x0502                    ///<  W  
}zrtos_vfs_module_sdm630_register_address_t;

#ifdef __cplusplus
}
#endif
#endif