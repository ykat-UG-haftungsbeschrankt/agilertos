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


typedef struct{
	uint8_t data[122*4];
}zrtos_vfs_module_sdm630_data_t;

#define ZRTOS_VFS_MODULE_SDM630__GET(function,addr,points,length,password)\
	(((function) << 24) | (addr << 8) | (length << 2) | (password << 1) | 0)

#define ZRTOS_VFS_MODULE_SDM630__SET(function,addr,points,length,password)\
	(((function) << 24) | (addr << 8) | (length << 2) | (password << 1) | 1)

typedef enum{
	 ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_1_VOLTAGE                           = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0000,2,4,0)                    ///<  V           |    1    |    1    |    1    |    1    |    1    |         |    1    |         
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_2_VOLTAGE                           = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0002,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_3_VOLTAGE                           = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0004,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_1_CURRENT                           = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0006,2,4,0)                    ///<  A           |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_2_CURRENT                           = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0008,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_3_CURRENT                           = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x000A,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_1_POWER                             = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x000C,2,4,0)                    ///<  W           |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_2_POWER                             = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x000E,2,4,0)                    ///<  W           |    1    |         |         |         |         |         |    1    |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_3_POWER                             = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0010,2,4,0)                    ///<  W           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_1_APPARENT_POWER                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0012,2,4,0)                    ///<  VA          |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_2_APPARENT_POWER                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0014,2,4,0)                    ///<  VA          |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_3_APPARENT_POWER                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0016,2,4,0)                    ///<  VA          |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_1_REACTIVE_POWER                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0018,2,4,0)                    ///<  VAr         |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_2_REACTIVE_POWER                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x001A,2,4,0)                    ///<  VAr         |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_3_REACTIVE_POWER                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x001C,2,4,0)                    ///<  VAr         |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_1_POWER_FACTOR                      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x001E,2,4,0)                    ///<              |    1    |    1    |    1    |    1    |    1    |         |    1    |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_2_POWER_FACTOR                      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0020,2,4,0)                    ///<              |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_3_POWER_FACTOR                      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0022,2,4,0)                    ///<              |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_1_ANGLE                             = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0024,2,4,0)                    ///<  Degrees     |    1    |    1    |    1    |    1    |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_2_ANGLE                             = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0026,2,4,0)                    ///<  Degrees     |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_3_ANGLE                             = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0028,2,4,0)                    ///<  Degrees     |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_AVERAGE_L_TO_N_VOLTS                      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x002A,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x002C,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_AVERAGE_LINE_CURRENT                      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x002E,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |    1    |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_SUM_LINE_CURRENT                          = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0030,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |    1    |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0032,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_TOTAL_SYSTEM_POWER                        = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0034,2,4,0)                    ///<  W           |    1    |         |         |         |         |    1    |    1    |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0036,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_TOTAL_SYSTEM_APPARENT_POWER               = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0038,2,4,0)                    ///<  VA          |    1    |         |         |         |         |         |    1    |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x003A,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_TOTAL_SYSTEM_REACTIVE_POWER               = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x003C,2,4,0)                    ///<  VAr         |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_TOTAL_SYSTEM_POWER_FACTOR                 = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x003E,2,4,0)                    ///<              |    1    |         |         |         |         |         |    1    |

	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0040,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_TOTAL_SYSTEM_PHASE_ANGLE                  = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0042,2,4,0)                    ///<  Degrees     |    1    |         |         |         |         |         |         |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0044,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_FREQUENCY                                 = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0046,2,4,0)                    ///<  Hz          |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_IMPORT_ACTIVE_ENERGY                      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0048,2,4,0)                    ///<  kWh/MWh     |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_EXPORT_ACTIVE_ENERGY                      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x004A,2,4,0)                    ///<  kWh/MWh     |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_IMPORT_REACTIVE_ENERGY                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x004C,2,4,0)                    ///<  kVArh/MVArh |    1    |    1    |    1    |    1    |    1    |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_EXPORT_REACTIVE_ENERGY                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x004E,2,4,0)                    ///<  kVArh/MVArh |    1    |    1    |    1    |    1    |    1    |         |         |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_VAH_SINCE_LAST_RESET                      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0050,2,4,0)                    ///<  kVAh/MVAh   |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_AH_SINCE_LAST_RESET                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0052,2,4,0)                    ///<  Ah/kAh      |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_TOTAL_SYSTEM_POWER_DEMAND                 = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0054,2,4,0)                    ///<  W           |    1    |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_MAXIMUM_TOTAL_SYSTEM_POWER_DEMAND         = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0056,2,4,0)                    ///<  W           |    1    |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_CURRENT_SYSTEM_POSITIVE_POWER_DEMAND      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0058,2,4,0)                    ///<  W           |         |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_MAXIMUM_SYSTEM_POSITIVE_POWER_DEMAND      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x005A,2,4,0)                    ///<  W           |         |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_CURRENT_SYSTEM_REVERSE_POWER_DEMAND       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x005C,2,4,0)                    ///<  W           |         |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_MAXIMUM_SYSTEM_REVERSE_POWER_DEMAND       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x005E,2,4,0)                    ///<  W           |         |    1    |         |         |         |         |         |

	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0060,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0062,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_TOTAL_SYSTEM_VA_DEMAND                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0064,2,4,0)                    ///<  VA          |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_MAXIMUM_TOTAL_SYSTEM_VA_DEMAND            = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0066,2,4,0)                    ///<  VA          |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_NEUTRAL_CURRENT_DEMAND                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0068,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_MAXIMUM_NEUTRAL_CURRENT                   = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x006A,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_REACTIVE_POWER_DEMAND                     = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x006C,2,4,0)                    ///<  VAr         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_MAXIMUM_REACTIVE_POWER_DEMAND             = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x006E,2,4,0)                    ///<  VAr         |    1    |         |         |         |         |         |         |

	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00C0,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00C2,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00C4,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00C6,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_LINE_1_TO_LINE_2_VOLTS                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00C8,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_LINE_2_TO_LINE_3_VOLTS                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00CA,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_LINE_3_TO_LINE_1_VOLTS                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00CC,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_AVERAGE_LINE_TO_LINE_VOLTS                = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00CE,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_NEUTRAL_CURRENT                           = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00E0,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |    1    |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00E2,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00E4,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00E6,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00E8,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_1_LN_VOLTS_THD                      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00EA,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_2_LN_VOLTS_THD                      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00EC,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_3_LN_VOLTS_THD                      = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00EE,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_1_CURRENT_THD                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00F0,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_2_CURRENT_THD                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00F2,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_3_CURRENT_THD                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00F4,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00F6,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_AVERAGE_LINE_TO_NEUTRAL_VOLTS_THD         = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00F8,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_AVERAGE_LINE_CURRENT_THD                  = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00FA,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00FC,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_TOTAL_SYSTEM_POWER_FACTOR_INV             = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x00FE,2,4,0)                    ///<              |    1    |         |         |         |         |         |         |

	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0100,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_1_CURRENT_DEMAND                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0102,2,4,0)                    ///<  A           |    1    |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_2_CURRENT_DEMAND                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0104,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PHASE_3_CURRENT_DEMAND                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0106,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_MAXIMUM_PHASE_1_CURRENT_DEMAND            = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0108,2,4,0)                    ///<  A           |    1    |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_MAXIMUM_PHASE_2_CURRENT_DEMAND            = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x010A,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_MAXIMUM_PHASE_3_CURRENT_DEMAND            = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x010C,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x010E,2,4,0)

	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0140,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0142,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0144,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0146,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0148,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x014A,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x014C,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_LINE_1_TO_LINE_2_VOLTS_THD                = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x014E,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_LINE_2_TO_LINE_3_VOLTS_THD                = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0150,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_LINE_3_TO_LINE_1_VOLTS_THD                = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0152,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_AVERAGE_LINE_TO_LINE_VOLTS_THD            = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0154,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_TOTAL_ACTIVE_ENERGY                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0156,2,4,0)                    ///<  kWh         |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_TOTAL_REACTIVE_ENERGY                     = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0158,2,4,0)                    ///<  kVArh       |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L1_IMPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x015A,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L2_IMPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x015C,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L3_IMPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x015E,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L1_EXPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0160,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L2_EXPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0162,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L3_EXPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0164,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L1_TOTAL_ACTIVE_ENERGY                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0166,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L2_TOTAL_ACTIVE_ENERGY                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0168,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L3_TOTAL_ACTIVE_ENERGY                    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x016A,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L1_IMPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x016C,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L2_IMPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x016E,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L3_IMPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0170,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L1_EXPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0172,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L2_EXPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0174,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L3_EXPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0176,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L1_TOTAL_REACTIVE_ENERGY                  = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0178,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L2_TOTAL_REACTIVE_ENERGY                  = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x017A,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_L3_TOTAL_REACTIVE_ENERGY                  = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x017C,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x017E,2,4,0)

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_CURRENT_RESETTABLE_TOTAL_ACTIVE_ENERGY    = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0180,2,4,0)                    ///<  kWh         |         |    1    |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_CURRENT_RESETTABLE_TOTAL_REACTIVE_ENERGY  = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0182,2,4,0)                    ///<  kVArh       |         |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_CURRENT_RESETTABLE_IMPORT_ENERGY          = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0184,2,4,0)                    ///<  kWh         |         |         |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_CURRENT_RESETTABLE_EXPORT_ENERGY          = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0186,2,4,0)                    ///<  kWh         |         |         |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_CURRENT_RESETTABLE_IMPORT_REACTIVE_ENERGY = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0188,2,4,0)                    ///<  kVArh       |         |         |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_CURRENT_RESETTABLE_EXPORT_REACTIVE_ENERGY = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x018A,2,4,0)                    ///<  kVArh       |         |         |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_NET_KWH                                   = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x018C,2,4,0)                    ///<  kWh         |         |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_NET_KVARH                                 = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x018E,2,4,0)                    ///<  kVArh       |         |         |         |         |         |         |    1    |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_IMPORT_POWER                              = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0500,2,4,0)                    ///<  W           |         |         |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_EXPORT_POWER                              = ZRTOS_VFS_MODULE_SDM630__GET(0x04,0x0502,2,4,0)                    ///<  W  


	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_DEMAND_PERIOD                             = ZRTOS_VFS_MODULE_SDM630__GET(0x03,0x0002,4,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_SYSTEM_TYPE                               = ZRTOS_VFS_MODULE_SDM630__GET(0x03,0x000A,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PULSE1_WIDTH                              = ZRTOS_VFS_MODULE_SDM630__GET(0x03,0x000C,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PASSWORD_LOCK                             = ZRTOS_VFS_MODULE_SDM630__GET(0x03,0x000E,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_NETWORK_PARITY_STOP                       = ZRTOS_VFS_MODULE_SDM630__GET(0x03,0x0012,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_NETWORK_NODE                              = ZRTOS_VFS_MODULE_SDM630__GET(0x03,0x0014,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PULSE1_DIVIDSOR1                          = ZRTOS_VFS_MODULE_SDM630__GET(0x03,0x0016,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PASSWORD                                  = ZRTOS_VFS_MODULE_SDM630__GET(0x03,0x0018,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_NETWORK_BAUD_RATE                         = ZRTOS_VFS_MODULE_SDM630__GET(0x03,0x001C,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_PULSE1_ENERGY_TYPE                        = ZRTOS_VFS_MODULE_SDM630__GET(0x03,0x0056,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_RESET                                     = ZRTOS_VFS_MODULE_SDM630__GET(0x10,0xFC10,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__GET_SERIAL_NUMBER                             = ZRTOS_VFS_MODULE_SDM630__GET(0x03,0xFC00,2,4,0)                    ///<  W  




	 ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_1_VOLTAGE                           = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0000,2,4,0)                    ///<  V           |    1    |    1    |    1    |    1    |    1    |         |    1    |         
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_2_VOLTAGE                           = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0002,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_3_VOLTAGE                           = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0004,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_1_CURRENT                           = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0006,2,4,0)                    ///<  A           |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_2_CURRENT                           = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0008,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_3_CURRENT                           = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x000A,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_1_POWER                             = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x000C,2,4,0)                    ///<  W           |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_2_POWER                             = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x000E,2,4,0)                    ///<  W           |    1    |         |         |         |         |         |    1    |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_3_POWER                             = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0010,2,4,0)                    ///<  W           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_1_APPARENT_POWER                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0012,2,4,0)                    ///<  VA          |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_2_APPARENT_POWER                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0014,2,4,0)                    ///<  VA          |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_3_APPARENT_POWER                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0016,2,4,0)                    ///<  VA          |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_1_REACTIVE_POWER                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0018,2,4,0)                    ///<  VAr         |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_2_REACTIVE_POWER                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x001A,2,4,0)                    ///<  VAr         |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_3_REACTIVE_POWER                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x001C,2,4,0)                    ///<  VAr         |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_1_POWER_FACTOR                      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x001E,2,4,0)                    ///<              |    1    |    1    |    1    |    1    |    1    |         |    1    |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_2_POWER_FACTOR                      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0020,2,4,0)                    ///<              |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_3_POWER_FACTOR                      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0022,2,4,0)                    ///<              |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_1_ANGLE                             = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0024,2,4,0)                    ///<  Degrees     |    1    |    1    |    1    |    1    |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_2_ANGLE                             = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0026,2,4,0)                    ///<  Degrees     |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_3_ANGLE                             = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0028,2,4,0)                    ///<  Degrees     |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_AVERAGE_L_TO_N_VOLTS                      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x002A,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x002C,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_AVERAGE_LINE_CURRENT                      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x002E,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |    1    |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_SUM_LINE_CURRENT                          = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0030,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |    1    |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0032,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_TOTAL_SYSTEM_POWER                        = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0034,2,4,0)                    ///<  W           |    1    |         |         |         |         |    1    |    1    |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0036,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_TOTAL_SYSTEM_APPARENT_POWER               = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0038,2,4,0)                    ///<  VA          |    1    |         |         |         |         |         |    1    |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x003A,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_TOTAL_SYSTEM_REACTIVE_POWER               = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x003C,2,4,0)                    ///<  VAr         |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_TOTAL_SYSTEM_POWER_FACTOR                 = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x003E,2,4,0)                    ///<              |    1    |         |         |         |         |         |    1    |

	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0040,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_TOTAL_SYSTEM_PHASE_ANGLE                  = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0042,2,4,0)                    ///<  Degrees     |    1    |         |         |         |         |         |         |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0044,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_FREQUENCY                                 = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0046,2,4,0)                    ///<  Hz          |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_IMPORT_ACTIVE_ENERGY                      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0048,2,4,0)                    ///<  kWh/MWh     |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_EXPORT_ACTIVE_ENERGY                      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x004A,2,4,0)                    ///<  kWh/MWh     |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_IMPORT_REACTIVE_ENERGY                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x004C,2,4,0)                    ///<  kVArh/MVArh |    1    |    1    |    1    |    1    |    1    |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_EXPORT_REACTIVE_ENERGY                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x004E,2,4,0)                    ///<  kVArh/MVArh |    1    |    1    |    1    |    1    |    1    |         |         |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_VAH_SINCE_LAST_RESET                      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0050,2,4,0)                    ///<  kVAh/MVAh   |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_AH_SINCE_LAST_RESET                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0052,2,4,0)                    ///<  Ah/kAh      |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_TOTAL_SYSTEM_POWER_DEMAND                 = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0054,2,4,0)                    ///<  W           |    1    |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_MAXIMUM_TOTAL_SYSTEM_POWER_DEMAND         = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0056,2,4,0)                    ///<  W           |    1    |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_CURRENT_SYSTEM_POSITIVE_POWER_DEMAND      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0058,2,4,0)                    ///<  W           |         |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_MAXIMUM_SYSTEM_POSITIVE_POWER_DEMAND      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x005A,2,4,0)                    ///<  W           |         |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_CURRENT_SYSTEM_REVERSE_POWER_DEMAND       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x005C,2,4,0)                    ///<  W           |         |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_MAXIMUM_SYSTEM_REVERSE_POWER_DEMAND       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x005E,2,4,0)                    ///<  W           |         |    1    |         |         |         |         |         |

	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0060,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0062,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_TOTAL_SYSTEM_VA_DEMAND                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0064,2,4,0)                    ///<  VA          |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_MAXIMUM_TOTAL_SYSTEM_VA_DEMAND            = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0066,2,4,0)                    ///<  VA          |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_NEUTRAL_CURRENT_DEMAND                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0068,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_MAXIMUM_NEUTRAL_CURRENT                   = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x006A,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_REACTIVE_POWER_DEMAND                     = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x006C,2,4,0)                    ///<  VAr         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_MAXIMUM_REACTIVE_POWER_DEMAND             = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x006E,2,4,0)                    ///<  VAr         |    1    |         |         |         |         |         |         |

	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00C0,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00C2,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00C4,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00C6,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_LINE_1_TO_LINE_2_VOLTS                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00C8,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_LINE_2_TO_LINE_3_VOLTS                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00CA,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_LINE_3_TO_LINE_1_VOLTS                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00CC,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_AVERAGE_LINE_TO_LINE_VOLTS                = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00CE,2,4,0)                    ///<  V           |    1    |         |         |         |         |         |    1    |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_NEUTRAL_CURRENT                           = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00E0,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |    1    |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00E2,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00E4,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00E6,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00E8,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_1_LN_VOLTS_THD                      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00EA,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_2_LN_VOLTS_THD                      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00EC,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_3_LN_VOLTS_THD                      = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00EE,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_1_CURRENT_THD                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00F0,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_2_CURRENT_THD                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00F2,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_3_CURRENT_THD                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00F4,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00F6,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_AVERAGE_LINE_TO_NEUTRAL_VOLTS_THD         = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00F8,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_AVERAGE_LINE_CURRENT_THD                  = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00FA,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00FC,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_TOTAL_SYSTEM_POWER_FACTOR_INV             = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x00FE,2,4,0)                    ///<              |    1    |         |         |         |         |         |         |

	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0100,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_1_CURRENT_DEMAND                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0102,2,4,0)                    ///<  A           |    1    |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_2_CURRENT_DEMAND                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0104,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PHASE_3_CURRENT_DEMAND                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0106,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_MAXIMUM_PHASE_1_CURRENT_DEMAND            = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0108,2,4,0)                    ///<  A           |    1    |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_MAXIMUM_PHASE_2_CURRENT_DEMAND            = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x010A,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_MAXIMUM_PHASE_3_CURRENT_DEMAND            = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x010C,2,4,0)                    ///<  A           |    1    |         |         |         |         |         |         |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x010E,2,4,0)

	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0140,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0142,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0144,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0146,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0148,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x014A,2,4,0)
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x014C,2,4,0)
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_LINE_1_TO_LINE_2_VOLTS_THD                = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x014E,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_LINE_2_TO_LINE_3_VOLTS_THD                = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0150,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_LINE_3_TO_LINE_1_VOLTS_THD                = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0152,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_AVERAGE_LINE_TO_LINE_VOLTS_THD            = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0154,2,4,0)                    ///<  %           |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_TOTAL_ACTIVE_ENERGY                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0156,2,4,0)                    ///<  kWh         |    1    |    1    |    1    |    1    |    1    |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_TOTAL_REACTIVE_ENERGY                     = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0158,2,4,0)                    ///<  kVArh       |    1    |    1    |    1    |    1    |    1    |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L1_IMPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x015A,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L2_IMPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x015C,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L3_IMPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x015E,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L1_EXPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0160,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L2_EXPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0162,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L3_EXPORT_ACTIVE_ENERGY                   = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0164,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L1_TOTAL_ACTIVE_ENERGY                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0166,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L2_TOTAL_ACTIVE_ENERGY                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0168,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L3_TOTAL_ACTIVE_ENERGY                    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x016A,2,4,0)                    ///<  kWh         |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L1_IMPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x016C,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L2_IMPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x016E,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L3_IMPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0170,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L1_EXPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0172,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L2_EXPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0174,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L3_EXPORT_REACTIVE_ENERGY                 = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0176,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L1_TOTAL_REACTIVE_ENERGY                  = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0178,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L2_TOTAL_REACTIVE_ENERGY                  = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x017A,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_L3_TOTAL_REACTIVE_ENERGY                  = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x017C,2,4,0)                    ///<  kVArh       |    1    |         |         |         |         |         |         |
	//,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SPACE                                       = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x017E,2,4,0)

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_CURRENT_RESETTABLE_TOTAL_ACTIVE_ENERGY    = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0180,2,4,0)                    ///<  kWh         |         |    1    |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_CURRENT_RESETTABLE_TOTAL_REACTIVE_ENERGY  = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0182,2,4,0)                    ///<  kVArh       |         |    1    |         |         |         |         |         |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_CURRENT_RESETTABLE_IMPORT_ENERGY          = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0184,2,4,0)                    ///<  kWh         |         |         |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_CURRENT_RESETTABLE_EXPORT_ENERGY          = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0186,2,4,0)                    ///<  kWh         |         |         |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_CURRENT_RESETTABLE_IMPORT_REACTIVE_ENERGY = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0188,2,4,0)                    ///<  kVArh       |         |         |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_CURRENT_RESETTABLE_EXPORT_REACTIVE_ENERGY = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x018A,2,4,0)                    ///<  kVArh       |         |         |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_NET_KWH                                   = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x018C,2,4,0)                    ///<  kWh         |         |         |         |         |         |         |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_NET_KVARH                                 = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x018E,2,4,0)                    ///<  kVArh       |         |         |         |         |         |         |    1    |

	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_IMPORT_POWER                              = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0500,2,4,0)                    ///<  W           |         |         |         |         |         |    1    |    1    |
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_EXPORT_POWER                              = ZRTOS_VFS_MODULE_SDM630__SET(0x04,0x0502,2,4,0)                    ///<  W  


	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_DEMAND_PERIOD                             = ZRTOS_VFS_MODULE_SDM630__SET(0x10,0x0002,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_SYSTEM_TYPE                               = ZRTOS_VFS_MODULE_SDM630__SET(0x10,0x000A,2,4,1)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PULSE1_WIDTH                              = ZRTOS_VFS_MODULE_SDM630__SET(0x10,0x000C,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PASSWORD_LOCK                             = ZRTOS_VFS_MODULE_SDM630__SET(0x03,0x000E,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_NETWORK_PARITY_STOP                       = ZRTOS_VFS_MODULE_SDM630__SET(0x10,0x0012,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_NETWORK_NODE                              = ZRTOS_VFS_MODULE_SDM630__SET(0x10,0x0014,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PULSE1_DIVIDSOR1                          = ZRTOS_VFS_MODULE_SDM630__SET(0x10,0x0016,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PASSWORD                                  = ZRTOS_VFS_MODULE_SDM630__SET(0x10,0x0018,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_NETWORK_BAUD_RATE                         = ZRTOS_VFS_MODULE_SDM630__SET(0x10,0x001C,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_PULSE1_ENERGY_TYPE                        = ZRTOS_VFS_MODULE_SDM630__SET(0x10,0x0056,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_RESET                                     = ZRTOS_VFS_MODULE_SDM630__SET(0x10,0xFC10,2,4,0)                    ///<  W  
	,ZRTOS_VFS_MODULE_SDM630_ADDRESS__SET_SERIAL_NUMBER                             = ZRTOS_VFS_MODULE_SDM630__SET(0x03,0xFC00,2,4,0)                    ///<  W  
}zrtos_vfs_module_sdm630_address_t;

#undef ZRTOS_VFS_MODULE_SDM630__GET
#undef ZRTOS_VFS_MODULE_SDM630__SET


size_t zrtos_vfs_module_sdm630_address__get_function(zrtos_vfs_module_sdm630_address_t thiz){
	return (thiz >> 24);
}

size_t zrtos_vfs_module_sdm630_address__get_addr(zrtos_vfs_module_sdm630_address_t thiz){
	return (thiz >> 8);
}

size_t zrtos_vfs_module_sdm630_address__get_length(zrtos_vfs_module_sdm630_address_t thiz){
	return (thiz >> 2) & 0xF;
}

size_t zrtos_vfs_module_sdm630_address__get_password(zrtos_vfs_module_sdm630_address_t thiz){
	return (thiz >> 1) & 0x1 > 0;
}

bool zrtos_vfs_module_sdm630_address__is_write_op(zrtos_vfs_module_sdm630_address_t thiz){
	return (thiz & 0x1) > 0;
}

zrtos_error_t zrtos_vfs_module_sdm630_data__get_offset_ex(size_t fn,size_t addr,size_t *offset){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;

	size_t x = addr;
	if(0){
	}else if(fn == 0x04){
		if(0){
		}else if(x >= 0x0000 && x <= 0x002A){	x -= 0x0000; x += 0;   //22
		}else if(x >= 0x002E && x <= 0x0030){	x -= 0x002E; x += 22*4;//2
		}else if(x >= 0x0034 && x <= 0x0034){	x -= 0x0034; x += 24*4;//1
		}else if(x >= 0x0038 && x <= 0x0038){	x -= 0x0038; x += 25*4;//1
		}else if(x >= 0x003C && x <= 0x003E){	x -= 0x003C; x += 26*4;//2
		}else if(x >= 0x0042 && x <= 0x0042){	x -= 0x0042; x += 28*4;//1
		}else if(x >= 0x0046 && x <= 0x005E){	x -= 0x0046; x += 29*4;//13
		}else if(x >= 0x0064 && x <= 0x006E){	x -= 0x0064; x += 42*4;//6
		}else if(x >= 0x00C8 && x <= 0x00E0){	x -= 0x00C8; x += 48*4;//13
		}else if(x >= 0x00EA && x <= 0x00F4){	x -= 0x00EA; x += 61*4;//6
		}else if(x >= 0x00F8 && x <= 0x00FA){	x -= 0x00F8; x += 67*4;//2
		}else if(x >= 0x00FE && x <= 0x00FE){	x -= 0x00FE; x += 69*4;//1
		}else if(x >= 0x0102 && x <= 0x010C){	x -= 0x0102; x += 70*4;//6
		}else if(x >= 0x014E && x <= 0x017C){	x -= 0x014E; x += 76*4;//24
		}else if(x >= 0x0180 && x <= 0x018E){	x -= 0x0180; x += 100*4;//8
		}else if(x >= 0x0500 && x <= 0x0502){	x -= 0x0500; x += 108*4;//2
		}else{
			ret = ZRTOS_ERROR__INVAL;
		}
	}else if(fn == 0x03 || fn == 0x10){
		if(0){
		}else if(x >= 0x0002 && x <= 0x0002){	x -= 0x0002; x += 110*4;//1
		}else if(x >= 0x000A && x <= 0x000C){	x -= 0x000A; x += 111*4;//3
		}else if(x >= 0x0012 && x <= 0x0018){	x -= 0x0012; x += 114*4;//4
		}else if(x >= 0x001C && x <= 0x001C){	x -= 0x001C; x += 118*4;//1
		}else if(x >= 0x0056 && x <= 0x0056){	x -= 0x0056; x += 119*4;//1
		}else if(fn == 0x03){
			if(0){
			}else if(x >= 0x000E && x <= 0x000E){	x -= 0x000A; x += 111*4;//3
			}else if(x >= 0xFC00 && x <= 0xFC00){	x -= 0xFC00; x += 120*4;//1
			}else{
				ret = ZRTOS_ERROR__INVAL;
			}
		}else if(fn == 0x10){
			if(0){
			}else if(x >= 0xFC10 && x <= 0xFC10){	x -= 0xFC10; x += 121*4;//1
			}else{
				ret = ZRTOS_ERROR__INVAL;
			}
		}else{
			ret = ZRTOS_ERROR__INVAL;
		}
	}else{
		ret = ZRTOS_ERROR__INVAL;
	}
	*offset = x;

	return ret;
}

zrtos_error_t zrtos_vfs_module_sdm630_data__get_offset(
	 zrtos_vfs_module_sdm630_address_t thiz
	,size_t *offset
){
	return zrtos_vfs_module_sdm630_data__get_offset_ex(
		 zrtos_vfs_module_sdm630_address__get_function(thiz)
		,zrtos_vfs_module_sdm630_address__get_addr(thiz)
		,offset
	);
}

zrtos_error_t zrtos_vfs_module_sdm630__rw(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
	,bool is_write_op
){
	zrtos_error_t ret;
	zrtos_vfs_module_sdm630_inode_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_sdm630_inode_t *
		,zrtos_vfs_file__get_inode_data(
			thiz
		)
	);
	zrtos_vfs_module_sdm630_address_t req = ZRTOS_CAST__REINTERPRET(
		 zrtos_vfs_module_sdm630_address_t
		,offset
	);
	size_t addr = zrtos_vfs_module_sdm630_address__get_addr(req);
	size_t tmp_offset;

	if(offset <= ZRTOS_TYPES__SIZE_MAX
	&& zrtos_error__is_success((ret = zrtos_vfs_module_sdm630_data__get_offset_ex(
		 0x4
		,addr
		,&tmp_offset
	)))){
		ret = zrtos_mem__cpy_address_range(
			 mod->data.data
			,zrtos_types__ptr_add(
				 mod->data.data
				,ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(mod->data.data)
			)
			,ZRTOS_CAST(uint8_t *,buf)
			,len
			,tmp_offset
			,out
			,is_write_op
		);
	}else{
		ret = ZRTOS_ERROR__INVAL;
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_sdm630__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	return zrtos_vfs_module_sdm630__rw(
		 thiz
		,path
		,buf
		,len
		,offset
		,out
		,false
	);
}

zrtos_error_t zrtos_vfs_module_sdm630__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	return zrtos_vfs_module_sdm630__rw(
		 thiz
		,path
		,buf
		,len
		,offset
		,out
		,true
	);
}

zrtos_error_t zrtos_vfs_module_sdm630__on_ioctl(
	 zrtos_vfs_file_t *thiz
	,char *path
	,int request
	,va_list args
){
	zrtos_vfs_module_sdm630_inode_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_sdm630_inode_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	ZRTOS_ASSERT__STATIC(sizeof(int) >= sizeof(zrtos_vfs_module_sdm630_address_t));
	zrtos_vfs_module_sdm630_address_t req = ZRTOS_CAST__REINTERPRET(
		 zrtos_vfs_module_sdm630_address_t
		,request
	);
	size_t fn = zrtos_vfs_module_sdm630_address__get_function(req);
	size_t addr = zrtos_vfs_module_sdm630_address__get_addr(req);
	size_t length = zrtos_vfs_module_sdm630_address__get_length(req);
	bool is_write_op = zrtos_vfs_module_sdm630_address__is_write_op(req);
	void *value = zrtos_va__arg_ptr(
		 args
		,void*
	);
	size_t value_length = zrtos_va__arg(
		 args
		,size_t
	);
	size_t offset;

	if(zrtos_error__is_success((ret = zrtos_vfs_module_sdm630_data__get_offset(
		 req
		,&offset
	)))
	&& zrtos_types__ptr_is_valid_address_range(
		 inode_data->data.data
		,zrtos_types__ptr_add(
			 inode_data->data.data
			,ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(inode_data->data.data)
		)
		,offset
		,&value_length
	)
	&& length == value_length
	){
		void *data = zrtos_types__ptr_add(
			 inode_data->data.data
			,offset
		);

		if(is_write_op){
			ZRTOS_TYPES__SWAP(value,data);
		}

		zrtos_mem__cpy(value,data,length);
	}else{
		ret = ZRTOS_ERROR__INVAL;
	}

	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(sdm630,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_sdm630__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_sdm630__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL(zrtos_vfs_module_sdm630__on_ioctl)
);

#ifdef __cplusplus
}
#endif
#endif