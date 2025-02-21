/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2022 MediaTek Inc.
 */

#ifndef __DEVAPC_MT6886_H__
#define __DEVAPC_MT6886_H__

#include "devapc-mtk-multi-ao.h"

/******************************************************************************
 * VARIABLE DEFINITION
 ******************************************************************************/
/* dbg status default setting */
#define PLAT_DBG_UT_DEFAULT		false
#define PLAT_DBG_KE_DEFAULT		true
#define PLAT_DBG_AEE_DEFAULT		true
#define PLAT_DBG_WARN_DEFAULT		true
#define PLAT_DBG_DAPC_DEFAULT		false

/******************************************************************************
 * STRUCTURE DEFINITION
 ******************************************************************************/
enum DEVAPC_SLAVE_TYPE {
	SLAVE_TYPE_INFRA = 0,
	SLAVE_TYPE_INFRA1,
	SLAVE_TYPE_PERI_PAR,
	SLAVE_TYPE_VLP,
	SLAVE_TYPE_ADSP,
	SLAVE_TYPE_MMINFRA,
	SLAVE_TYPE_MMUP,
	SLAVE_TYPE_NUM,
};

enum DEVAPC_VIO_MASK_STA_NUM {
	VIO_MASK_STA_NUM_INFRA = 10,
	VIO_MASK_STA_NUM_INFRA1 = 9,
	VIO_MASK_STA_NUM_PERI_PAR = 3,
	VIO_MASK_STA_NUM_VLP = 4,
	VIO_MASK_STA_NUM_ADSP = 3,
	VIO_MASK_STA_NUM_MMINFRA = 12,
	VIO_MASK_STA_NUM_MMUP = 4,
};

enum DEVAPC_PD_OFFSET {
	PD_VIO_MASK_OFFSET = 0x0,
	PD_VIO_STA_OFFSET = 0x400,
	PD_VIO_DBG0_OFFSET = 0x900,
	PD_VIO_DBG1_OFFSET = 0x904,
	PD_VIO_DBG2_OFFSET = 0x908,
	PD_APC_CON_OFFSET = 0xF00,
	PD_SHIFT_STA_OFFSET = 0xF20,
	PD_SHIFT_SEL_OFFSET = 0xF30,
	PD_SHIFT_CON_OFFSET = 0xF10,
	PD_VIO_DBG3_OFFSET = 0x90C,
};

#define SRAMROM_SLAVE_TYPE	SLAVE_TYPE_INFRA	/* Infra */
#define MM2ND_SLAVE_TYPE	SLAVE_TYPE_NUM		/* No MM2ND */

enum OTHER_TYPES_INDEX {
	SRAMROM_VIO_INDEX = 308,
	CONN_VIO_INDEX = 121, /* starts from 0x18 */
	MDP_VIO_INDEX = 0,
	DISP2_VIO_INDEX = 0,
	MMSYS_VIO_INDEX = 0,
};

enum INFRACFG_MM2ND_VIO_NUM {
	INFRACFG_MM_VIO_STA_NUM = 4,
	INFRACFG_MDP_VIO_STA_NUM = 10,
	INFRACFG_DISP2_VIO_STA_NUM = 4,
};

enum INFRACFG_MM2ND_OFFSET {
	INFRACFG_MM_SEC_VIO0_OFFSET = 0xB30,
	INFRACFG_MDP_SEC_VIO0_OFFSET = 0xB40,
	INFRACFG_DISP2_SEC_VIO0_OFFSET = 0xB70,
};

enum BUSID_LENGTH {
	INFRAAXI_MI_BIT_LENGTH = 16,
	ADSPAXI_MI_BIT_LENGTH = 8,
	MMINFRAAXI_MI_BIT_LENGTH = 19,
};

struct INFRAAXI_ID_INFO {
	const char	*master;
	uint8_t		bit[INFRAAXI_MI_BIT_LENGTH];
};

struct ADSPAXI_ID_INFO {
	const char	*master;
	uint8_t		bit[ADSPAXI_MI_BIT_LENGTH];
};

struct MMINFRAAXI_ID_INFO {
	const char	*master;
	uint8_t		bit[MMINFRAAXI_MI_BIT_LENGTH];
};

enum DEVAPC_IRQ_TYPE {
	IRQ_TYPE_INFRA = 0,
	IRQ_TYPE_PERI,
	IRQ_TYPE_VLP,
	IRQ_TYPE_ADSP,
	IRQ_TYPE_MMINFRA,
	IRQ_TYPE_MMUP,
	IRQ_TYPE_GPU,
	IRQ_TYPE_NUM,
};

enum ADSP_MI_SELECT {
	ADSP_MI13 = 0,
	ADSP_MI15
};

/******************************************************************************
 * PLATFORM DEFINATION
 ******************************************************************************/

/* For Infra VIO_DBG */
#define INFRA_VIO_DBG_MSTID			0xFFFFFFFF
#define INFRA_VIO_DBG_MSTID_START_BIT		0
#define INFRA_VIO_DBG_DMNID			0x0000003F
#define INFRA_VIO_DBG_DMNID_START_BIT		0
#define INFRA_VIO_DBG_W_VIO			0x00000040
#define INFRA_VIO_DBG_W_VIO_START_BIT		6
#define INFRA_VIO_DBG_R_VIO			0x00000080
#define INFRA_VIO_DBG_R_VIO_START_BIT		7
#define INFRA_VIO_ADDR_HIGH			0xFFFFFFFF
#define INFRA_VIO_ADDR_HIGH_START_BIT		0

/* For SRAMROM VIO */
#define SRAMROM_SEC_VIO_ID_MASK			0x0001FFFF
#define SRAMROM_SEC_VIO_ID_SHIFT		0
#define SRAMROM_SEC_VIO_DOMAIN_MASK		0x0F000000
#define SRAMROM_SEC_VIO_DOMAIN_SHIFT		24
#define SRAMROM_SEC_VIO_RW_MASK			0x80000000
#define SRAMROM_SEC_VIO_RW_SHIFT		31

/* For MM 2nd VIO */
#define INFRACFG_MM2ND_VIO_DOMAIN_MASK		0x00000030
#define INFRACFG_MM2ND_VIO_DOMAIN_SHIFT		4
#define INFRACFG_MM2ND_VIO_ID_MASK		0x007FFF00
#define INFRACFG_MM2ND_VIO_ID_SHIFT		8
#define INFRACFG_MM2ND_VIO_RW_MASK		0x01000000
#define INFRACFG_MM2ND_VIO_RW_SHIFT		24

#define SRAM_START_ADDR				(0x100000)
#define SRAM_END_ADDR				(0x1FFFFF)

#define L3CACHE_0_START				(0x01000000)
#define L3CACHE_0_END				(0x02FFFFFF)
#define L3CACHE_1_START				(0x0A000000)
#define L3CACHE_1_END				(0x0C1FFFFF)
#define L3CACHE_2_START				(0x0C400000)
#define L3CACHE_2_END				(0x0CFFFFFF)

/* For VLP Bus Parser */
#define VLP_SCP_START_ADDR			(0x1C400000)
#define VLP_SCP_END_ADDR			(0x1C7FFFFF)
#define VLP_INFRA_START				(0x00000000)
#define VLP_INFRA_END				(0x1BFFFFFF)
#define VLP_INFRA_1_START			(0x1D000000)
#define VLP_INFRA_1_END				(0x43FFFFFFF)

/* For ADSP Bus Parser */
#define ADSP_INFRA_START			(0x00000000)
#define ADSP_INFRA_END				(0x1CFFFFFF)
#define ADSP_INFRA_1_START			(0x1E200000)
#define ADSP_INFRA_1_END			(0x4DFFFFFF)
#define ADSP_OTHER_START			(0x1E000000)
#define ADSP_OTHER_END				(0x1E01FFFF)

/* For MMINFRA Bus Parser */
#define DISP_START_ADDR				(0x14000000)
#define DISP_END_ADDR				(0x141FFFFF)
#define IMG_START_ADDR				(0x15000000)
#define IMG_END_ADDR				(0x157FFFFF)
#define VDEC_START_ADDR				(0x16000000)
#define VDEC_END_ADDR				(0x1608FFFF)
#define VENC_START_ADDR				(0x17000000)
#define VENC_END_ADDR				(0x177FFFFF)
#define CAM_START_ADDR				(0x1A000000)
#define CAM_END_ADDR				(0x1A1FFFFF)
#define CCU_START_ADDR				(0x1B000000)
#define CCU_END_ADDR				(0x1BFFFFFF)
#define MMUP_START_ADDR				(0x1EA00000)
#define MMUP_END_ADDR				(0x1ECFFFFF)
#define MML_START_ADDR				(0x1F000000)
#define MML_END_ADDR				(0x1F7FFFFF)

static const struct mtk_device_info mt6886_devices_infra[] = {
	/* sys_idx, ctrl_idx, vio_idx, device, vio_irq */
	/* 0 */
	{0, 0, 0, "APMIXEDSYS_APB_S", true},
	{0, 1, 1, "APMIXEDSYS_APB_S-1", true},
	{0, 2, 2, "RESERVED_APB_S", true},
	{0, 3, 3, "TOPCKGEN_APB_S", true},
	{0, 4, 4, "INFRACFG_AO_APB_S", true},
	{0, 5, 5, "GPIO_APB_S", true},
	{0, 6, 6, "DEVICE_APC_INFRA_AO_APB_S", true},
	{0, 7, 7, "BCRM_INFRA_AO_APB_S", true},
	{0, 8, 8, "DEBUG_CTRL_INFRA_AO_APB_S", true},
	{0, 9, 10, "TOP_MISC_APB_S", true},

	/* 10 */
	{0, 10, 11, "MBIST_AO_APB_S", true},
	{0, 11, 12, "DPMAIF_AO_APB_S", true},
	{0, 12, 13, "INFRA_SECURITY_AO_APB_S", true},
	{0, 13, 14, "TOPCKGEN_INFRA_CFG_APB_S", true},
	{0, 14, 15, "DRM_DEBUG_TOP_APB_S", true},
	{0, 15, 16, "EFUSE_DEBUG_AO_APB_S", true},
	{0, 16, 17, "PMSR_APB_S", true},
	{0, 17, 62, "INFRA2PERI_S", true},
	{0, 18, 63, "INFRA2PERI_S-1", true},
	{0, 19, 64, "INFRA2PERI_S-2", true},

	/* 20 */
	{0, 20, 65, "INFRA2MM_S", true},
	{0, 21, 66, "INFRA2MM_S-1", true},
	{0, 22, 67, "INFRA2MM_S-2", true},
	{0, 23, 68, "INFRA2MM_S-3", true},
	{0, 24, 70, "APU_S_S", true},
	{0, 25, 71, "APU_S_S-1", true},
	{0, 26, 72, "APU_S_S-2", true},
	{0, 27, 73, "APU_S_S-3", true},
	{0, 28, 74, "APU_S_S-4", true},
	{0, 29, 75, "APU_S_S-5", true},

	/* 30 */
	{0, 30, 76, "APU_S_S-6", true},
	{0, 31, 77, "MFG_S_S-0", true},
	{0, 32, 78, "MFG_S_S-2", true},
	{0, 33, 79, "MFG_S_S-3", true},
	{0, 34, 80, "MFG_S_S-4", true},
	{0, 35, 81, "MFG_S_S-5", true},
	{0, 36, 82, "MFG_S_S-7", true},
	{0, 37, 83, "MFG_S_S-8", true},
	{0, 38, 84, "MFG_S_S-9", true},
	{0, 39, 85, "MFG_S_S-10", true},

	/* 40 */
	{0, 40, 86, "MFG_S_S-11", true},
	{0, 41, 87, "MFG_S_S-12", true},
	{0, 42, 88, "MFG_S_S-13", true},
	{0, 43, 89, "MFG_S_S-14", true},
	{0, 44, 90, "MFG_S_S-15", true},
	{0, 45, 91, "MFG_S_S-16", true},
	{0, 46, 92, "MFG_S_S-18", true},
	{0, 47, 93, "MFG_S_S-19", true},
	{0, 48, 94, "MFG_S_S-20", true},
	{0, 49, 95, "MFG_S_S-21", true},

	/* 50 */
	{0, 50, 96, "MFG_S_S-22", true},
	{0, 51, 97, "MFG_S_S-24", true},
	{0, 52, 98, "MFG_S_S-25", true},
	{0, 53, 99, "MFG_S_S-26", true},
	{0, 54, 100, "MFG_S_S-28", true},
	{0, 55, 101, "MFG_S_S-30", true},
	{0, 56, 102, "MFG_S_S-31", true},
	{0, 57, 103, "MFG_S_S-32", true},
	{0, 58, 104, "MFG_S_S-34", true},
	{0, 59, 105, "MFG_S_S-36", true},

	/* 60 */
	{0, 60, 106, "MFG_S_S-37", true},
	{0, 61, 107, "MFG_S_S-38", true},
	{0, 62, 108, "MFG_S_S-39", true},
	{0, 63, 109, "MFG_S_S-40", true},
	{0, 64, 110, "MFG_S_S-41", true},
	{0, 65, 111, "MFG_S_S-42", true},
	{0, 66, 112, "MFG_S_S-43", true},
	{0, 67, 113, "MFG_S_S-44", true},
	{0, 68, 114, "MFG_S_S-45", true},
	{0, 69, 115, "MFG_S_S-47", true},

	/* 70 */
	{0, 70, 116, "MFG_S_S-48", true},
	{0, 71, 117, "MFG_S_S-49", true},
	{0, 72, 118, "MFG_S_S-51", true},
	{0, 73, 119, "MFG_S_S-52", true},
	{0, 74, 120, "MFG_S_S-53", true},
	{0, 75, 121, "MFG_S_S-54", true},
	{0, 76, 122, "L3C_S", true},
	{0, 77, 123, "L3C_S-1", true},
	{0, 78, 124, "L3C_S-20", true},
	{0, 79, 125, "L3C_S-21", true},

	/* 80 */
	{0, 80, 126, "L3C_S-22", true},
	{0, 81, 127, "L3C_S-23", true},
	{0, 82, 128, "L3C_S-24", true},
	{0, 83, 129, "L3C_S-25", true},
	{0, 84, 130, "L3C_S-26", true},
	{0, 85, 131, "L3C_S-27", true},
	{0, 86, 132, "L3C_S-28", true},
	{0, 87, 133, "L3C_S-29", true},
	{0, 88, 134, "L3C_S-30", true},
	{0, 89, 135, "L3C_S-31", true},

	/* 90 */
	{0, 90, 136, "L3C_S-32", true},
	{0, 91, 137, "L3C_S-33", true},
	{0, 92, 138, "L3C_S-34", true},
	{0, 93, 139, "L3C_S-35", true},
	{0, 94, 140, "L3C_S-36", true},
	{0, 95, 141, "L3C_S-37", true},
	{0, 96, 142, "L3C_S-38", true},
	{0, 97, 143, "L3C_S-39", true},
	{0, 98, 144, "L3C_S-40", true},
	{0, 99, 145, "L3C_S-41", true},

	/* 100 */
	{0, 100, 146, "L3C_S-42", true},
	{0, 101, 147, "L3C_S-43", true},
	{0, 102, 148, "L3C_S-44", true},
	{0, 103, 151, "VLPSYS_S", true},
	{0, 104, 160, "DEBUGSYS_APB_S", true},
	{0, 105, 161, "DPMAIF_PDN_APB_S", true},
	{0, 106, 162, "DPMAIF_PDN_APB_S-1", true},
	{0, 107, 163, "DPMAIF_PDN_APB_S-2", true},
	{0, 108, 164, "DPMAIF_PDN_APB_S-3", true},
	{0, 109, 165, "DEVICE_APC_INFRA_PDN_APB_S", true},

	/* 110 */
	{0, 110, 166, "DEBUG_TRACKER_APB_S", true},
	{0, 111, 167, "DEBUG_TRACKER_APB1_S", true},
	{0, 112, 168, "BCRM_INFRA_PDN_APB_S", true},
	{0, 113, 169, "M4_IOMMU0_APB_S", true},
	{0, 114, 170, "M4_IOMMU1_APB_S", true},
	{0, 115, 171, "M4_IOMMU2_APB_S", true},
	{0, 116, 172, "M4_IOMMU3_APB_S", true},
	{0, 117, 173, "M4_IOMMU4_APB_S", true},
	{0, 118, 174, "M6_IOMMU0_APB_S", true},
	{0, 119, 175, "M6_IOMMU1_APB_S", true},

	/* 120 */
	{0, 120, 176, "M6_IOMMU2_APB_S", true},
	{0, 121, 177, "M6_IOMMU3_APB_S", true},
	{0, 122, 178, "M6_IOMMU4_APB_S", true},
	{0, 123, 179, "M7_IOMMU0_APB_S", true},
	{0, 124, 180, "M7_IOMMU1_APB_S", true},
	{0, 125, 181, "M7_IOMMU2_APB_S", true},
	{0, 126, 182, "M7_IOMMU3_APB_S", true},
	{0, 127, 183, "M7_IOMMU4_APB_S", true},
	{0, 128, 184, "PTP_THERM_CTRL_APB_S", true},
	{0, 129, 185, "PTP_THERM_CTRL2_APB_S", true},

	/* 130 */
	{0, 130, 186, "SYS_CIRQ_APB_S", true},
	{0, 131, 187, "CCIF0_AP_APB_S", true},
	{0, 132, 188, "CCIF0_MD_APB_S", true},
	{0, 133, 189, "CCIF1_AP_APB_S", true},
	{0, 134, 190, "CCIF1_MD_APB_S", true},
	{0, 135, 191, "MBIST_PDN_APB_S", true},
	{0, 136, 192, "INFRACFG_PDN_APB_S", true},
	{0, 137, 193, "TRNG_APB_S", true},
	{0, 138, 194, "DX_CC_APB_S", true},
	{0, 139, 195, "CQ_DMA_APB_S", true},

	/* 140 */
	{0, 140, 196, "SRAMROM_APB_S", true},
	{0, 141, 197, "RESERVED_DVFS_PROC_APB_S", true},
	{0, 142, 199, "SYS_CIRQ2_APB_S", true},
	{0, 143, 200, "CCIF2_AP_APB_S", true},
	{0, 144, 201, "CCIF2_MD_APB_S", true},
	{0, 145, 202, "CCIF3_AP_APB_S", true},
	{0, 146, 203, "CCIF3_MD_APB_S", true},
	{0, 147, 204, "CCIF4_AP_APB_S", true},
	{0, 148, 205, "CCIF4_MD_APB_S", true},
	{0, 149, 206, "CCIF5_AP_APB_S", true},

	/* 150 */
	{0, 150, 207, "CCIF5_MD_APB_S", true},
	{0, 151, 208, "HWCCF_APB_S", true},
	{0, 152, 209, "INFRA_BUS_HRE_APB_S", true},
	{0, 153, 210, "IPI_APB_S", true},
	{1, 0, 18, "ADSPSYS_S", true},
	{1, 1, 19, "MD_AP_S", true},
	{1, 2, 20, "MD_AP_S-1", true},
	{1, 3, 21, "MD_AP_S-2", true},
	{1, 4, 22, "MD_AP_S-3", true},
	{1, 5, 23, "MD_AP_S-4", true},

	/* 160 */
	{1, 6, 24, "MD_AP_S-5", true},
	{1, 7, 25, "MD_AP_S-6", true},
	{1, 8, 26, "MD_AP_S-7", true},
	{1, 9, 27, "MD_AP_S-8", true},
	{1, 10, 28, "MD_AP_S-9", true},
	{1, 11, 29, "MD_AP_S-10", true},
	{1, 12, 30, "MD_AP_S-11", true},
	{1, 13, 31, "MD_AP_S-12", true},
	{1, 14, 32, "MD_AP_S-13", true},
	{1, 15, 33, "MD_AP_S-14", true},

	/* 170 */
	{1, 16, 34, "MD_AP_S-15", true},
	{1, 17, 35, "MD_AP_S-16", true},
	{1, 18, 36, "MD_AP_S-17", true},
	{1, 19, 37, "MD_AP_S-18", true},
	{1, 20, 38, "MD_AP_S-19", true},
	{1, 21, 39, "MD_AP_S-20", true},
	{1, 22, 40, "MD_AP_S-21", true},
	{1, 23, 41, "MD_AP_S-22", true},
	{1, 24, 42, "MD_AP_S-23", true},
	{1, 25, 43, "MD_AP_S-24", true},

	/* 180 */
	{1, 26, 44, "MD_AP_S-25", true},
	{1, 27, 45, "MD_AP_S-26", true},
	{1, 28, 46, "MD_AP_S-27", true},
	{1, 29, 47, "MD_AP_S-28", true},
	{1, 30, 48, "MD_AP_S-29", true},
	{1, 31, 49, "MD_AP_S-30", true},
	{1, 32, 50, "MD_AP_S-31", true},
	{1, 33, 51, "MD_AP_S-32", true},
	{1, 34, 52, "MD_AP_S-33", true},
	{1, 35, 53, "MD_AP_S-34", true},

	/* 190 */
	{1, 36, 54, "MD_AP_S-35", true},
	{1, 37, 55, "MD_AP_S-36", true},
	{1, 38, 56, "MD_AP_S-37", true},
	{1, 39, 57, "MD_AP_S-38", true},
	{1, 40, 58, "MD_AP_S-39", true},
	{1, 41, 59, "MD_AP_S-40", true},
	{1, 42, 60, "MD_AP_S-41", true},
	{1, 43, 61, "MD_AP_S-42", true},
	{2, 0, 69, "CONN_S", true},

	{-1, -1, 211, "OOB_way_en", true},
	{-1, -1, 212, "OOB_way_en", true},
	{-1, -1, 213, "OOB_way_en", true},
	{-1, -1, 214, "OOB_way_en", true},
	{-1, -1, 215, "OOB_way_en", true},
	{-1, -1, 216, "OOB_way_en", true},
	{-1, -1, 217, "OOB_way_en", true},
	{-1, -1, 218, "OOB_way_en", true},
	{-1, -1, 219, "OOB_way_en", true},

	{-1, -1, 220, "OOB_way_en", true},
	{-1, -1, 221, "OOB_way_en", true},
	{-1, -1, 222, "OOB_way_en", true},
	{-1, -1, 223, "OOB_way_en", true},
	{-1, -1, 224, "OOB_way_en", true},
	{-1, -1, 225, "OOB_way_en", true},
	{-1, -1, 226, "OOB_way_en", true},
	{-1, -1, 227, "OOB_way_en", true},
	{-1, -1, 228, "OOB_way_en", true},
	{-1, -1, 229, "OOB_way_en", true},

	{-1, -1, 230, "OOB_way_en", true},
	{-1, -1, 231, "OOB_way_en", true},
	{-1, -1, 232, "OOB_way_en", true},
	{-1, -1, 233, "OOB_way_en", true},
	{-1, -1, 234, "OOB_way_en", true},
	{-1, -1, 235, "OOB_way_en", true},
	{-1, -1, 236, "OOB_way_en", true},
	{-1, -1, 237, "OOB_way_en", true},
	{-1, -1, 238, "OOB_way_en", true},
	{-1, -1, 239, "OOB_way_en", true},

	{-1, -1, 240, "OOB_way_en", true},
	{-1, -1, 241, "OOB_way_en", true},
	{-1, -1, 242, "OOB_way_en", true},
	{-1, -1, 243, "OOB_way_en", true},
	{-1, -1, 244, "OOB_way_en", true},
	{-1, -1, 245, "OOB_way_en", true},
	{-1, -1, 246, "OOB_way_en", true},
	{-1, -1, 247, "OOB_way_en", true},
	{-1, -1, 248, "OOB_way_en", true},
	{-1, -1, 249, "OOB_way_en", true},

	{-1, -1, 250, "OOB_way_en", true},
	{-1, -1, 251, "OOB_way_en", true},
	{-1, -1, 252, "OOB_way_en", true},
	{-1, -1, 253, "OOB_way_en", true},
	{-1, -1, 254, "OOB_way_en", true},
	{-1, -1, 255, "OOB_way_en", true},
	{-1, -1, 256, "OOB_way_en", true},
	{-1, -1, 257, "OOB_way_en", true},
	{-1, -1, 258, "OOB_way_en", true},
	{-1, -1, 259, "OOB_way_en", true},

	{-1, -1, 260, "OOB_way_en", true},
	{-1, -1, 261, "OOB_way_en", true},
	{-1, -1, 262, "OOB_way_en", true},
	{-1, -1, 263, "OOB_way_en", true},
	{-1, -1, 264, "OOB_way_en", true},
	{-1, -1, 265, "OOB_way_en", true},
	{-1, -1, 266, "OOB_way_en", true},
	{-1, -1, 267, "OOB_way_en", true},
	{-1, -1, 268, "OOB_way_en", true},
	{-1, -1, 269, "OOB_way_en", true},

	{-1, -1, 270, "OOB_way_en", true},
	{-1, -1, 271, "OOB_way_en", true},
	{-1, -1, 272, "OOB_way_en", true},
	{-1, -1, 273, "OOB_way_en", true},
	{-1, -1, 274, "OOB_way_en", true},
	{-1, -1, 275, "OOB_way_en", true},
	{-1, -1, 276, "OOB_way_en", true},
	{-1, -1, 277, "OOB_way_en", true},
	{-1, -1, 278, "OOB_way_en", true},
	{-1, -1, 279, "OOB_way_en", true},

	{-1, -1, 280, "OOB_way_en", true},
	{-1, -1, 281, "OOB_way_en", true},
	{-1, -1, 282, "OOB_way_en", true},
	{-1, -1, 283, "OOB_way_en", true},
	{-1, -1, 284, "OOB_way_en", true},
	{-1, -1, 285, "OOB_way_en", true},
	{-1, -1, 286, "OOB_way_en", true},
	{-1, -1, 287, "OOB_way_en", true},
	{-1, -1, 288, "OOB_way_en", true},
	{-1, -1, 289, "OOB_way_en", true},

	{-1, -1, 290, "OOB_way_en", true},
	{-1, -1, 291, "OOB_way_en", true},
	{-1, -1, 292, "OOB_way_en", true},
	{-1, -1, 293, "OOB_way_en", true},
	{-1, -1, 294, "OOB_way_en", true},
	{-1, -1, 295, "OOB_way_en", true},
	{-1, -1, 296, "OOB_way_en", true},
	{-1, -1, 297, "OOB_way_en", true},

	{-1, -1, 298, "Decode_error", true},
	{-1, -1, 299, "Decode_error", true},
	{-1, -1, 300, "Decode_error", true},
	{-1, -1, 301, "Decode_error", true},
	{-1, -1, 302, "Decode_error", true},
	{-1, -1, 303, "Decode_error", true},

	{-1, -1, 304, "reserve", false},
	{-1, -1, 305, "reserve", false},
	{-1, -1, 306, "reserve", false},
	{-1, -1, 307, "CQ_DMA", false},
	{-1, -1, 308, "SRAMROM", true},
	{-1, -1, 309, "DEVICE_APC_INFRA_AO", false},
	{-1, -1, 310, "DEVICE_APC_INFRA_PDN", false},
};

static const struct mtk_device_info mt6886_devices_infra1[] = {
	/* sys_idx, ctrl_idx, vio_idx, device, vio_irq */
	/* 0 */
	{0, 0, 0, "DRAMC_MD32_S0_APB_S", true},
	{0, 1, 1, "DRAMC_MD32_S0_APB_S-1", true},
	{0, 2, 2, "DRAMC_MD32_S1_APB_S", true},
	{0, 3, 3, "DRAMC_MD32_S1_APB_S-1", true},
	{0, 4, 4, "DRAMC_MD32_S2_APB_S", true},
	{0, 5, 5, "DRAMC_MD32_S2_APB_S-1", true},
	{0, 6, 6, "DRAMC_MD32_S3_APB_S", true},
	{0, 7, 7, "DRAMC_MD32_S3_APB_S-1", true},
	{0, 8, 8, "BND_EAST_APB0_S", true},
	{0, 9, 9, "BND_EAST_APB1_S", true},

	/* 10 */
	{0, 10, 10, "BND_EAST_APB2_S", true},
	{0, 11, 11, "BND_EAST_APB3_S", true},
	{0, 12, 12, "BND_EAST_APB4_S", true},
	{0, 13, 13, "BND_EAST_APB5_S", true},
	{0, 14, 14, "BND_EAST_APB6_S", true},
	{0, 15, 15, "BND_EAST_APB7_S", true},
	{0, 16, 16, "BND_EAST_APB8_S", true},
	{0, 17, 17, "BND_EAST_APB9_S", true},
	{0, 18, 18, "BND_EAST_APB10_S", true},
	{0, 19, 19, "BND_EAST_APB11_S", true},

	/* 20 */
	{0, 20, 20, "BND_EAST_APB12_S", true},
	{0, 21, 21, "BND_EAST_APB13_S", true},
	{0, 22, 22, "BND_EAST_APB14_S", true},
	{0, 23, 23, "BND_EAST_APB15_S", true},
	{0, 24, 24, "BND_WEST_APB0_S", true},
	{0, 25, 25, "BND_WEST_APB1_S", true},
	{0, 26, 26, "BND_WEST_APB2_S", true},
	{0, 27, 27, "BND_WEST_APB3_S", true},
	{0, 28, 28, "BND_WEST_APB4_S", true},
	{0, 29, 29, "BND_WEST_APB5_S", true},

	/* 30 */
	{0, 30, 30, "BND_WEST_APB6_S", true},
	{0, 31, 31, "BND_WEST_APB7_S", true},
	{0, 32, 32, "BND_NORTH_APB0_S", true},
	{0, 33, 33, "BND_NORTH_APB1_S", true},
	{0, 34, 34, "BND_NORTH_APB2_S", true},
	{0, 35, 35, "BND_NORTH_APB3_S", true},
	{0, 36, 36, "BND_NORTH_APB4_S", true},
	{0, 37, 37, "BND_NORTH_APB5_S", true},
	{0, 38, 38, "BND_NORTH_APB6_S", true},
	{0, 39, 39, "BND_NORTH_APB7_S", true},

	/* 40 */
	{0, 40, 40, "BND_NORTH_APB8_S", true},
	{0, 41, 41, "BND_NORTH_APB9_S", true},
	{0, 42, 42, "BND_NORTH_APB10_S", true},
	{0, 43, 43, "BND_NORTH_APB11_S", true},
	{0, 44, 44, "BND_NORTH_APB12_S", true},
	{0, 45, 45, "BND_NORTH_APB13_S", true},
	{0, 46, 46, "BND_NORTH_APB14_S", true},
	{0, 47, 47, "BND_NORTH_APB15_S", true},
	{0, 48, 48, "BND_SOUTH_APB0_S", true},
	{0, 49, 49, "BND_SOUTH_APB1_S", true},

	/* 50 */
	{0, 50, 50, "BND_SOUTH_APB2_S", true},
	{0, 51, 51, "BND_SOUTH_APB3_S", true},
	{0, 52, 52, "BND_SOUTH_APB4_S", true},
	{0, 53, 53, "BND_SOUTH_APB5_S", true},
	{0, 54, 54, "BND_SOUTH_APB6_S", true},
	{0, 55, 55, "BND_SOUTH_APB7_S", true},
	{0, 56, 56, "BND_SOUTH_APB8_S", true},
	{0, 57, 57, "BND_SOUTH_APB9_S", true},
	{0, 58, 58, "BND_SOUTH_APB10_S", true},
	{0, 59, 59, "BND_SOUTH_APB11_S", true},

	/* 60 */
	{0, 60, 60, "BND_SOUTH_APB12_S", true},
	{0, 61, 61, "BND_SOUTH_APB13_S", true},
	{0, 62, 62, "BND_SOUTH_APB14_S", true},
	{0, 63, 63, "BND_SOUTH_APB15_S", true},
	{0, 64, 64, "BND_EAST_NORTH_APB0_S", true},
	{0, 65, 65, "BND_EAST_NORTH_APB1_S", true},
	{0, 66, 66, "BND_EAST_NORTH_APB2_S", true},
	{0, 67, 67, "BND_EAST_NORTH_APB3_S", true},
	{0, 68, 68, "BND_EAST_NORTH_APB4_S", true},
	{0, 69, 69, "BND_EAST_NORTH_APB5_S", true},

	/* 70 */
	{0, 70, 70, "BND_EAST_NORTH_APB6_S", true},
	{0, 71, 71, "BND_EAST_NORTH_APB7_S", true},
	{0, 72, 72, "DRAMC_CH0_TOP0_APB_S", true},
	{0, 73, 73, "DRAMC_CH0_TOP1_APB_S", true},
	{0, 74, 74, "DRAMC_CH0_TOP2_APB_S", true},
	{0, 75, 75, "DRAMC_CH0_TOP3_APB_S", true},
	{0, 76, 76, "DRAMC_CH0_TOP4_APB_S", true},
	{0, 77, 77, "DRAMC_CH0_TOP5_APB_S", true},
	{0, 78, 78, "DRAMC_CH0_TOP6_APB_S", true},
	{0, 79, 79, "DRAMC_CH1_TOP0_APB_S", true},

	/* 80 */
	{0, 80, 80, "DRAMC_CH1_TOP1_APB_S", true},
	{0, 81, 81, "DRAMC_CH1_TOP2_APB_S", true},
	{0, 82, 82, "DRAMC_CH1_TOP3_APB_S", true},
	{0, 83, 83, "DRAMC_CH1_TOP4_APB_S", true},
	{0, 84, 84, "DRAMC_CH1_TOP5_APB_S", true},
	{0, 85, 85, "DRAMC_CH1_TOP6_APB_S", true},
	{0, 86, 86, "DRAMC_CH2_TOP0_APB_S", true},
	{0, 87, 87, "DRAMC_CH2_TOP1_APB_S", true},
	{0, 88, 88, "DRAMC_CH2_TOP2_APB_S", true},
	{0, 89, 89, "DRAMC_CH2_TOP3_APB_S", true},

	/* 90 */
	{0, 90, 90, "DRAMC_CH2_TOP4_APB_S", true},
	{0, 91, 91, "DRAMC_CH2_TOP5_APB_S", true},
	{0, 92, 92, "DRAMC_CH2_TOP6_APB_S", true},
	{0, 93, 93, "DRAMC_CH3_TOP0_APB_S", true},
	{0, 94, 94, "DRAMC_CH3_TOP1_APB_S", true},
	{0, 95, 95, "DRAMC_CH3_TOP2_APB_S", true},
	{0, 96, 96, "DRAMC_CH3_TOP3_APB_S", true},
	{0, 97, 97, "DRAMC_CH3_TOP4_APB_S", true},
	{0, 98, 98, "DRAMC_CH3_TOP5_APB_S", true},
	{0, 99, 99, "DRAMC_CH3_TOP6_APB_S", true},

	/* 100 */
	{0, 100, 104, "NEMI_MBIST_PDN_APB_S", true},
	{0, 101, 105, "NEMI_CFG_APB_S", true},
	{0, 102, 106, "NEMI_APB_S", true},
	{0, 103, 107, "NEMI_MPU_APB_S", true},
	{0, 104, 108, "NEMI_RSV0_PDN_APB_S", true},
	{0, 105, 109, "NEMI_BCRM_PDN_APB_S", true},
	{0, 106, 110, "NEMI_FAKE_ENGINE_1_S", true},
	{0, 107, 111, "NEMI_FAKE_ENGINE_0_S", true},
	{0, 108, 112, "NEMI_SSC_APB0_S", true},
	{0, 109, 113, "NEMI_SSC_APB1_S", true},

	/* 110 */
	{0, 110, 114, "NEMI_SSC_APB2_S", true},
	{0, 111, 115, "NEMI_CFG_AO_APB_S", true},
	{0, 112, 116, "NEMI_DEBUG_CTRL_AO_APB_S", true},
	{0, 113, 117, "NEMI_BCRM_AO_APB_S", true},
	{0, 114, 118, "NEMI_RSI_APB_S", true},
	{0, 115, 119, "NEMI_RSV1_PDN_APB_S", true},
	{0, 116, 120, "NEMI_HRE_EMI_APB_S", true},
	{0, 117, 121, "NEMI_HRE_EMI_MPU_APB_S", true},
	{0, 118, 122, "NEMI_HRE_EMI_SLB_APB_S", true},
	{0, 119, 123, "NEMI_SMPU0_APB_S", true},

	/* 120 */
	{0, 120, 124, "NEMI_SMPU1_APB_S", true},
	{0, 121, 125, "NEMI_SMPU2_APB_S", true},
	{0, 122, 126, "NEMI_SLB_APB_S", true},
	{0, 123, 127, "NEMI_HRE_SMPU_APB_S", true},
	{0, 124, 128, "NEMI_RSV0_AO_APB_S", true},
	{0, 125, 129, "NEMI_RSV1_AO_APB_S", true},
	{0, 126, 130, "NEMI_RSV2_AO_APB_S", true},
	{0, 127, 131, "BCRM_INFRA_PDN1_APB_S", true},
	{0, 128, 132, "DEVICE_APC_INFRA_PDN1_APB_S", true},
	{0, 129, 133, "BCRM_INFRA_AO1_APB_S", true},

	/* 130 */
	{0, 130, 134, "DEVICE_APC_INFRA_AO1_APB_S", true},
	{0, 131, 135, "DEBUG_CTRL_INFRA_AO1_APB_S", true},

	{-1, -1, 136, "OOB_way_en", true},
	{-1, -1, 137, "OOB_way_en", true},
	{-1, -1, 138, "OOB_way_en", true},
	{-1, -1, 139, "OOB_way_en", true},

	{-1, -1, 140, "OOB_way_en", true},
	{-1, -1, 141, "OOB_way_en", true},
	{-1, -1, 142, "OOB_way_en", true},
	{-1, -1, 143, "OOB_way_en", true},
	{-1, -1, 144, "OOB_way_en", true},
	{-1, -1, 145, "OOB_way_en", true},
	{-1, -1, 146, "OOB_way_en", true},
	{-1, -1, 147, "OOB_way_en", true},
	{-1, -1, 148, "OOB_way_en", true},
	{-1, -1, 149, "OOB_way_en", true},

	{-1, -1, 150, "OOB_way_en", true},
	{-1, -1, 151, "OOB_way_en", true},
	{-1, -1, 152, "OOB_way_en", true},
	{-1, -1, 153, "OOB_way_en", true},
	{-1, -1, 154, "OOB_way_en", true},
	{-1, -1, 155, "OOB_way_en", true},
	{-1, -1, 156, "OOB_way_en", true},
	{-1, -1, 157, "OOB_way_en", true},
	{-1, -1, 158, "OOB_way_en", true},
	{-1, -1, 159, "OOB_way_en", true},

	{-1, -1, 160, "OOB_way_en", true},
	{-1, -1, 161, "OOB_way_en", true},
	{-1, -1, 162, "OOB_way_en", true},
	{-1, -1, 163, "OOB_way_en", true},
	{-1, -1, 164, "OOB_way_en", true},
	{-1, -1, 165, "OOB_way_en", true},
	{-1, -1, 166, "OOB_way_en", true},
	{-1, -1, 167, "OOB_way_en", true},
	{-1, -1, 168, "OOB_way_en", true},
	{-1, -1, 169, "OOB_way_en", true},

	{-1, -1, 170, "OOB_way_en", true},
	{-1, -1, 171, "OOB_way_en", true},
	{-1, -1, 172, "OOB_way_en", true},
	{-1, -1, 173, "OOB_way_en", true},
	{-1, -1, 174, "OOB_way_en", true},
	{-1, -1, 175, "OOB_way_en", true},
	{-1, -1, 176, "OOB_way_en", true},
	{-1, -1, 177, "OOB_way_en", true},
	{-1, -1, 178, "OOB_way_en", true},
	{-1, -1, 179, "OOB_way_en", true},

	{-1, -1, 180, "OOB_way_en", true},
	{-1, -1, 181, "OOB_way_en", true},
	{-1, -1, 182, "OOB_way_en", true},
	{-1, -1, 183, "OOB_way_en", true},
	{-1, -1, 184, "OOB_way_en", true},
	{-1, -1, 185, "OOB_way_en", true},
	{-1, -1, 186, "OOB_way_en", true},
	{-1, -1, 187, "OOB_way_en", true},
	{-1, -1, 188, "OOB_way_en", true},
	{-1, -1, 189, "OOB_way_en", true},

	{-1, -1, 190, "OOB_way_en", true},
	{-1, -1, 191, "OOB_way_en", true},
	{-1, -1, 192, "OOB_way_en", true},
	{-1, -1, 193, "OOB_way_en", true},
	{-1, -1, 194, "OOB_way_en", true},
	{-1, -1, 195, "OOB_way_en", true},
	{-1, -1, 196, "OOB_way_en", true},
	{-1, -1, 197, "OOB_way_en", true},
	{-1, -1, 198, "OOB_way_en", true},
	{-1, -1, 199, "OOB_way_en", true},

	{-1, -1, 200, "OOB_way_en", true},
	{-1, -1, 201, "OOB_way_en", true},
	{-1, -1, 202, "OOB_way_en", true},
	{-1, -1, 203, "OOB_way_en", true},
	{-1, -1, 204, "OOB_way_en", true},
	{-1, -1, 205, "OOB_way_en", true},
	{-1, -1, 206, "OOB_way_en", true},
	{-1, -1, 207, "OOB_way_en", true},
	{-1, -1, 208, "OOB_way_en", true},
	{-1, -1, 209, "OOB_way_en", true},

	{-1, -1, 210, "OOB_way_en", true},
	{-1, -1, 211, "OOB_way_en", true},
	{-1, -1, 212, "OOB_way_en", true},
	{-1, -1, 213, "OOB_way_en", true},
	{-1, -1, 214, "OOB_way_en", true},
	{-1, -1, 215, "OOB_way_en", true},
	{-1, -1, 216, "OOB_way_en", true},
	{-1, -1, 217, "OOB_way_en", true},
	{-1, -1, 218, "OOB_way_en", true},
	{-1, -1, 219, "OOB_way_en", true},

	{-1, -1, 220, "OOB_way_en", true},
	{-1, -1, 221, "OOB_way_en", true},
	{-1, -1, 222, "OOB_way_en", true},
	{-1, -1, 223, "OOB_way_en", true},
	{-1, -1, 224, "OOB_way_en", true},
	{-1, -1, 225, "OOB_way_en", true},
	{-1, -1, 226, "OOB_way_en", true},
	{-1, -1, 227, "OOB_way_en", true},
	{-1, -1, 228, "OOB_way_en", true},
	{-1, -1, 229, "OOB_way_en", true},

	{-1, -1, 230, "OOB_way_en", true},
	{-1, -1, 231, "OOB_way_en", true},
	{-1, -1, 232, "OOB_way_en", true},
	{-1, -1, 233, "OOB_way_en", true},
	{-1, -1, 234, "OOB_way_en", true},
	{-1, -1, 235, "OOB_way_en", true},
	{-1, -1, 236, "OOB_way_en", true},
	{-1, -1, 237, "OOB_way_en", true},
	{-1, -1, 238, "OOB_way_en", true},
	{-1, -1, 239, "OOB_way_en", true},

	{-1, -1, 240, "OOB_way_en", true},
	{-1, -1, 241, "OOB_way_en", true},
	{-1, -1, 242, "OOB_way_en", true},
	{-1, -1, 243, "OOB_way_en", true},
	{-1, -1, 244, "OOB_way_en", true},
	{-1, -1, 245, "OOB_way_en", true},
	{-1, -1, 246, "OOB_way_en", true},
	{-1, -1, 247, "OOB_way_en", true},
	{-1, -1, 248, "OOB_way_en", true},
	{-1, -1, 249, "OOB_way_en", true},

	{-1, -1, 250, "OOB_way_en", true},
	{-1, -1, 251, "OOB_way_en", true},
	{-1, -1, 252, "OOB_way_en", true},
	{-1, -1, 253, "OOB_way_en", true},
	{-1, -1, 254, "OOB_way_en", true},
	{-1, -1, 255, "OOB_way_en", true},
	{-1, -1, 256, "OOB_way_en", true},
	{-1, -1, 257, "OOB_way_en", true},
	{-1, -1, 258, "OOB_way_en", true},
	{-1, -1, 259, "OOB_way_en", true},

	{-1, -1, 260, "OOB_way_en", true},
	{-1, -1, 261, "OOB_way_en", true},
	{-1, -1, 262, "OOB_way_en", true},
	{-1, -1, 263, "OOB_way_en", true},
	{-1, -1, 264, "OOB_way_en", true},
	{-1, -1, 265, "OOB_way_en", true},
	{-1, -1, 266, "OOB_way_en", true},
	{-1, -1, 267, "OOB_way_en", true},
	{-1, -1, 268, "OOB_way_en", true},
	{-1, -1, 269, "OOB_way_en", true},

	{-1, -1, 270, "OOB_way_en", true},
	{-1, -1, 271, "OOB_way_en", true},
	{-1, -1, 272, "OOB_way_en", true},

	{-1, -1, 273, "Decode_error", true},
	{-1, -1, 274, "Decode_error", true},
	{-1, -1, 275, "Decode_error", true},
	{-1, -1, 276, "Decode_error", true},
	{-1, -1, 277, "Decode_error", true},
	{-1, -1, 278, "Decode_error", true},
	{-1, -1, 279, "Decode_error", true},
	{-1, -1, 280, "Decode_error", true},
	{-1, -1, 281, "Decode_error", true},

	{-1, -1, 282, "North EMI", false},
	{-1, -1, 283, "North EMI MPU", false},
	{-1, -1, 284, "DEVICE_APC_INFRA_AO1", false},
	{-1, -1, 285, "DEVICE_APC_INFRA_PDN1", false},
};

static const struct mtk_device_info mt6886_devices_peri_par[] = {
	/* sys_idx, ctrl_idx, vio_idx, device, vio_irq */
	/* 0 */
	{0, 0, 0, "UART0_APB_S", true},
	{0, 1, 1, "UART1_APB_S", true},
	{0, 2, 2, "PWM_PERI_APB_S", true},
	{0, 3, 3, "BTIF_APB_S", true},
	{0, 4, 4, "DISP_PWM0_APB_S", true},
	{0, 5, 5, "SPI0_APB_S", true},
	{0, 6, 6, "SPI1_APB_S", true},
	{0, 7, 7, "SPI2_APB_S", true},
	{0, 8, 8, "SPI3_APB_S", true},
	{0, 9, 9, "SPI4_APB_S", true},

	/* 10 */
	{0, 10, 10, "SPI5_APB_S", true},
	{0, 11, 11, "SPI6_APB_S", true},
	{0, 12, 12, "SPI7_APB_S", true},
	{0, 13, 13, "DEVICE_APC_PERI_PAR_PDN_APB_S", true},
	{0, 14, 14, "PERI_MBIST_PDN_APB_S", true},
	{0, 15, 15, "BCRM_PERI_PAR_PDN_APB_S", true},
	{0, 16, 16, "IIC_P2P_REMAP_APB_S", true},
	{0, 17, 17, "APDMA_APB_S", true},
	{0, 18, 18, "SSUSB_S", true},
	{0, 19, 19, "SSUSB_S-1", true},

	/* 20 */
	{0, 20, 20, "SSUSB_S-2", true},
	{0, 21, 21, "AUDIO_S-1", true},
	{0, 22, 22, "AUDIO_S-2", true},
	{0, 23, 23, "MSDC1_S-1", true},
	{0, 24, 24, "MSDC1_S-2", true},
	{0, 25, 25, "UFS0_S", true},
	{0, 26, 26, "UFS0_S-1", true},
	{0, 27, 27, "UFS0_S-2", true},
	{0, 28, 28, "UFS0_S-3", true},
	{0, 29, 29, "UFS0_S-4", true},

	/* 30 */
	{0, 30, 30, "UFS0_S-5", true},
	{0, 31, 31, "UFS0_S-6", true},
	{0, 32, 32, "UFS0_S-7", true},
	{0, 33, 33, "UFS0_S-8", true},
	{0, 34, 34, "DEVICE_APC_PERI_PAR_AO_APB_S", true},
	{0, 35, 35, "MBIST_AO_APB_S", true},
	{0, 36, 36, "BCRM_PERI_PAR_AO_APB_S", true},
	{0, 37, 37, "PERICFG_AO_APB_S", true},
	{0, 38, 38, "DEBUG_CTRL_PERI_PAR_AO_APB_S", true},

	{-1, -1, 39, "OOB_way_en", true},

	{-1, -1, 40, "OOB_way_en", true},
	{-1, -1, 41, "OOB_way_en", true},
	{-1, -1, 42, "OOB_way_en", true},
	{-1, -1, 43, "OOB_way_en", true},
	{-1, -1, 44, "OOB_way_en", true},
	{-1, -1, 45, "OOB_way_en", true},
	{-1, -1, 46, "OOB_way_en", true},
	{-1, -1, 47, "OOB_way_en", true},
	{-1, -1, 48, "OOB_way_en", true},
	{-1, -1, 49, "OOB_way_en", true},
	{-1, -1, 50, "OOB_way_en", true},

	{-1, -1, 51, "OOB_way_en", true},
	{-1, -1, 52, "OOB_way_en", true},
	{-1, -1, 53, "OOB_way_en", true},
	{-1, -1, 54, "OOB_way_en", true},
	{-1, -1, 55, "OOB_way_en", true},
	{-1, -1, 56, "OOB_way_en", true},
	{-1, -1, 57, "OOB_way_en", true},
	{-1, -1, 58, "OOB_way_en", true},
	{-1, -1, 59, "OOB_way_en", true},

	{-1, -1, 60, "OOB_way_en", true},
	{-1, -1, 61, "OOB_way_en", true},
	{-1, -1, 62, "OOB_way_en", true},
	{-1, -1, 63, "OOB_way_en", true},

	{-1, -1, 64, "Decode_error", true},
	{-1, -1, 65, "Decode_error", true},

	{-1, -1, 66, "APDMA", false},
	{-1, -1, 67, "IIC_P2P_REMAP", false},
	{-1, -1, 68, "DEVICE_APC_PERI_AO", false},
	{-1, -1, 69, "DEVICE_APC_PERI_PDN", false},
};

static const struct mtk_device_info mt6886_devices_vlp[] = {
	/* sys_idx, ctrl_idx, vio_idx, device, vio_irq */
	/* 0 */
	{0, 0, 0, "INFRA_S0_S", true},
	{0, 1, 1, "INFRA_S0_S-1", true},
	{0, 2, 2, "INFRA_S0_S-2", true},
	{0, 3, 3, "SCP_S", true},
	{0, 4, 4, "SCP_S-1", true},
	{0, 5, 5, "SCP_S-2", true},
	{0, 6, 6, "SCP_S-3", true},
	{0, 7, 7, "SCP_S-4", true},
	{0, 8, 8, "SCP_S-5", true},
	{0, 9, 9, "SPM_APB_S", true},

	/* 10 */
	{0, 10, 10, "SPM_APB_S-1", true},
	{0, 11, 11, "SPM_APB_S-2", true},
	{0, 12, 12, "SPM_APB_S-3", true},
	{0, 13, 13, "SPM_APB_S-4", true},
	{0, 14, 14, "SPM_APB_S-5", true},
	{0, 15, 15, "SPM_APB_S-6", true},
	{0, 16, 16, "SPM_APB_S-7", true},
	{0, 17, 17, "SPM_APB_S-8", true},
	{0, 18, 18, "SPM_APB_S-9", true},
	{0, 19, 19, "SPM_APB_S-10", true},

	/* 20 */
	{0, 20, 20, "SPM_APB_S-11", true},
	{0, 21, 21, "SPM_APB_S-12", true},
	{0, 22, 22, "SPM_APB_S-13", true},
	{0, 23, 23, "SSPM_S", true},
	{0, 24, 24, "SSPM_S-1", true},
	{0, 25, 25, "SSPM_S-2", true},
	{0, 26, 26, "SSPM_S-3", true},
	{0, 27, 27, "SSPM_S-4", true},
	{0, 28, 28, "SSPM_S-5", true},
	{0, 29, 29, "SSPM_S-6", true},

	/* 30 */
	{0, 30, 30, "SSPM_S-7", true},
	{0, 31, 31, "SSPM_S-8", true},
	{0, 32, 32, "SSPM_S-9", true},
	{0, 33, 33, "SSPM_S-10", true},
	{0, 34, 34, "SSPM_S-11", true},
	{0, 35, 35, "SSPM_S-12", true},
	{0, 36, 36, "VLPCFG_AO_APB_S", true},
	{0, 37, 38, "SRCLKEN_RC_APB_S", true},
	{0, 38, 39, "TOPRGU_APB_S", true},
	{0, 39, 40, "APXGPT_APB_S", true},

	/* 40 */
	{0, 40, 41, "KP_APB_S", true},
	{0, 41, 42, "DVFSRC_APB_S", true},
	{0, 42, 43, "MBIST_APB_S", true},
	{0, 43, 44, "SYS_TIMER_APB_S", true},
	{0, 44, 45, "VLP_CKSYS_APB_S", true},
	{0, 45, 46, "PMIF1_APB_S", true},
	{0, 46, 47, "PMIF2_APB_S", true},
	{0, 47, 49, "PWM_VLP_APB_S", true},
	{0, 48, 50, "SEJ_APB_S", true},
	{0, 49, 51, "AES_TOP0_APB_S", true},

	/* 50 */
	{0, 50, 52, "SECURITY_AO_APB_S", true},
	{0, 51, 53, "DEVICE_APC_VLP_AO_APB_S", true},
	{0, 52, 54, "DEVICE_APC_VLP_APB_S", true},
	{0, 53, 55, "BCRM_VLP_AO_APB_S", true},
	{0, 54, 56, "DEBUG_CTRL_VLP_AO_APB_S", true},
	{0, 55, 57, "VLPCFG_APB_S", true},
	{0, 56, 58, "SPMI_P_MST_APB_S", true},
	{0, 57, 59, "SPMI_M_MST_APB_S", true},
	{0, 58, 60, "EFUSE_DEBUG_AO_APB_S", true},
	{0, 59, 61, "MD_BUCK_CTRL_SEQUENCER_APB_S", true},

	/* 60 */
	{0, 60, 62, "AP_CIRQ_EINT_APB_S", true},
	{0, 61, 63, "SRAMRC_APB_S", true},
	{0, 62, 64, "TRNG_APB_S", true},
	{0, 63, 65, "DX_CC_APB_S", true},
	{0, 64, 66, "IPS_APB_S", true},

	{-1, -1, 67, "OOB_way_en", true},
	{-1, -1, 68, "OOB_way_en", true},
	{-1, -1, 69, "OOB_way_en", true},

	{-1, -1, 70, "OOB_way_en", true},
	{-1, -1, 71, "OOB_way_en", true},
	{-1, -1, 72, "OOB_way_en", true},
	{-1, -1, 73, "OOB_way_en", true},
	{-1, -1, 74, "OOB_way_en", true},
	{-1, -1, 75, "OOB_way_en", true},
	{-1, -1, 76, "OOB_way_en", true},
	{-1, -1, 77, "OOB_way_en", true},
	{-1, -1, 78, "OOB_way_en", true},
	{-1, -1, 79, "OOB_way_en", true},

	{-1, -1, 80, "OOB_way_en", true},
	{-1, -1, 81, "OOB_way_en", true},
	{-1, -1, 82, "OOB_way_en", true},
	{-1, -1, 83, "OOB_way_en", true},
	{-1, -1, 84, "OOB_way_en", true},
	{-1, -1, 85, "OOB_way_en", true},
	{-1, -1, 86, "OOB_way_en", true},
	{-1, -1, 87, "OOB_way_en", true},
	{-1, -1, 88, "OOB_way_en", true},
	{-1, -1, 89, "OOB_way_en", true},

	{-1, -1, 90, "OOB_way_en", true},
	{-1, -1, 91, "OOB_way_en", true},
	{-1, -1, 92, "OOB_way_en", true},
	{-1, -1, 93, "OOB_way_en", true},
	{-1, -1, 94, "OOB_way_en", true},
	{-1, -1, 95, "OOB_way_en", true},
	{-1, -1, 96, "OOB_way_en", true},
	{-1, -1, 97, "OOB_way_en", true},
	{-1, -1, 98, "OOB_way_en", true},
	{-1, -1, 99, "OOB_way_en", true},

	{-1, -1, 100, "OOB_way_en", true},

	{-1, -1, 101, "Decode_error", true},

	{-1, -1, 102, "PMIF1", false},
	{-1, -1, 103, "PMIF2", false},
	{-1, -1, 104, "DEVICE_APC_VLP_AO", false},
	{-1, -1, 105, "DEVICE_APC_VLP_PDN", false},
};

static const struct mtk_device_info mt6886_devices_adsp[] = {
	/* sys_idx, ctrl_idx, vio_idx, device, vio_irq */
	/* 0 */
	{0, 0, 0, "INFRA_S", true},
	{0, 1, 1, "INFRA_S-1", true},
	{0, 2, 2, "INFRA_S-2", true},
	{0, 3, 3, "EMI_S", true},
	{0, 4, 4, "AFE_S", true},
	{0, 5, 5, "AFE_S-1", true},
	{0, 6, 6, "DSP1_S", true},
	{0, 7, 7, "DSP1_S-1", true},
	{0, 8, 8, "DSP2_S", true},
	{0, 9, 9, "DSP2_S-1", true},

	/* 10 */
	{0, 10, 10, "DSPCFG_0_S", true},
	{0, 11, 11, "DSPCKCTL_S", true},
	{0, 12, 12, "DMA_0_CFG_S", true},
	{0, 13, 13, "DSP_TIMER_0_S", true},
	{0, 14, 14, "DSP_UART_S", true},
	{0, 15, 15, "BUSMON_DRAM_S", true},
	{0, 16, 16, "DSPMBOX_0_S", true},
	{0, 17, 17, "DSPMBOX_1_S", true},
	{0, 18, 18, "DSPMBOX_2_S", true},
	{0, 19, 19, "DSPMBOX_3_S", true},

	/* 20 */
	{0, 20, 20, "DSPMBOX_4_S", true},
	{0, 21, 21, "DSPCFG_SEC_S", true},
	{0, 22, 22, "BUSMON_INFRA_S", true},
	{0, 23, 23, "DMA_1_CFG_S", true},
	{0, 24, 24, "ADSP_RSV_S", true},
	{0, 25, 25, "HRE_S", true},
	{0, 26, 26, "ADSP_BUSCFG_S", true},
	{0, 27, 27, "ADSP_TMBIST_S", true},
	{0, 28, 28, "BCRM_S", true},
	{0, 29, 29, "BUS_DEBUG_S", true},

	/* 30 */
	{0, 30, 30, "SYSCFG_AO_S", true},
	{0, 31, 31, "DBG_TRACKER_EMI_APB_S", true},
	{0, 32, 32, "DBG_TRACKER_INFRA_APB_S", true},
	{0, 33, 33, "DAPC_AO_S", true},
	{0, 34, 34, "K_BCRM_S", true},
	{0, 35, 35, "DAPC_S", true},

	{-1, -1, 36, "OOB_way_en", true},
	{-1, -1, 37, "OOB_way_en", true},
	{-1, -1, 38, "OOB_way_en", true},
	{-1, -1, 39, "OOB_way_en", true},

	{-1, -1, 40, "OOB_way_en", true},
	{-1, -1, 41, "OOB_way_en", true},
	{-1, -1, 42, "OOB_way_en", true},
	{-1, -1, 43, "OOB_way_en", true},
	{-1, -1, 44, "OOB_way_en", true},
	{-1, -1, 45, "OOB_way_en", true},
	{-1, -1, 46, "OOB_way_en", true},
	{-1, -1, 47, "OOB_way_en", true},
	{-1, -1, 48, "OOB_way_en", true},
	{-1, -1, 49, "OOB_way_en", true},

	{-1, -1, 50, "OOB_way_en", true},
	{-1, -1, 51, "OOB_way_en", true},
	{-1, -1, 52, "OOB_way_en", true},
	{-1, -1, 53, "OOB_way_en", true},
	{-1, -1, 54, "OOB_way_en", true},
	{-1, -1, 55, "OOB_way_en", true},
	{-1, -1, 56, "OOB_way_en", true},
	{-1, -1, 57, "OOB_way_en", true},
	{-1, -1, 58, "OOB_way_en", true},
	{-1, -1, 59, "OOB_way_en", true},

	{-1, -1, 60, "OOB_way_en", true},
	{-1, -1, 61, "OOB_way_en", true},
	{-1, -1, 62, "OOB_way_en", true},
	{-1, -1, 63, "OOB_way_en", true},
	{-1, -1, 64, "OOB_way_en", true},
	{-1, -1, 65, "OOB_way_en", true},
	{-1, -1, 66, "OOB_way_en", true},
	{-1, -1, 67, "OOB_way_en", true},

	{-1, -1, 68, "Decode_error", true},

	{-1, -1, 69, "DEVICE_APC_AO_AUD_BUS_AO_PD", false},
	{-1, -1, 70, "DEVICE_APC_AUD_BUS_AO_PDN", false},
};

static const struct mtk_device_info mt6886_devices_mminfra[] = {
	/* sys_idx, ctrl_idx, vio_idx, device, vio_irq */
	/* 0 */
	{0, 69, 69, "VDEC_APB_S-10", true},
	{0, 70, 70, "CCU_APB_S", true},
	{0, 71, 71, "CCU_APB_S-1", true},
	{0, 72, 72, "CCU_APB_S-2", true},
	{0, 73, 73, "CCU_APB_S-3", true},
	{0, 74, 74, "CCU_APB_S-4", true},
	{0, 75, 75, "CCU_APB_S-5", true},
	{0, 76, 76, "CCU_APB_S-6", true},
	{0, 77, 77, "CCU_APB_S-7", true},
	{0, 78, 78, "CCU_APB_S-8", true},

	/* 10 */
	{0, 79, 79, "CCU_APB_S-9", true},
	{0, 80, 80, "CCU_APB_S-10", true},
	{0, 81, 81, "CCU_APB_S-11", true},
	{0, 82, 82, "CCU_APB_S-12", true},
	{0, 83, 83, "CCU_APB_S-13", true},
	{0, 84, 84, "CCU_APB_S-14", true},
	{0, 85, 85, "CCU_APB_S-15", true},
	{0, 86, 86, "CCU_APB_S-16", true},
	{0, 87, 87, "CCU_APB_S-17", true},
	{0, 88, 88, "CCU_APB_S-18", true},

	/* 20 */
	{0, 89, 89, "CCU_APB_S-19", true},
	{0, 90, 90, "IMG_APB_S", true},
	{0, 91, 91, "IMG_APB_S-1", true},
	{0, 92, 92, "IMG_APB_S-2", true},
	{0, 93, 93, "IMG_APB_S-3", true},
	{0, 94, 94, "IMG_APB_S-4", true},
	{0, 95, 95, "IMG_APB_S-5", true},
	{0, 96, 96, "IMG_APB_S-6", true},
	{0, 97, 97, "IMG_APB_S-7", true},
	{0, 98, 98, "IMG_APB_S-8", true},

	/* 30 */
	{0, 99, 99, "IMG_APB_S-9", true},
	{0, 100, 100, "IMG_APB_S-10", true},
	{0, 101, 101, "IMG_APB_S-11", true},
	{0, 102, 102, "IMG_APB_S-12", true},
	{0, 103, 103, "IMG_APB_S-13", true},
	{0, 104, 104, "IMG_APB_S-14", true},
	{0, 105, 105, "IMG_APB_S-15", true},
	{0, 106, 106, "IMG_APB_S-16", true},
	{0, 107, 107, "IMG_APB_S-17", true},
	{0, 108, 108, "IMG_APB_S-18", true},

	/* 40 */
	{0, 109, 109, "IMG_APB_S-19", true},
	{0, 110, 110, "IMG_APB_S-20", true},
	{0, 111, 111, "IMG_APB_S-21", true},
	{0, 112, 112, "IMG_APB_S-22", true},
	{0, 113, 113, "IMG_APB_S-23", true},
	{0, 114, 114, "IMG_APB_S-24", true},
	{0, 115, 115, "IMG_APB_S-25", true},
	{0, 116, 116, "IMG_APB_S-26", true},
	{0, 117, 117, "IMG_APB_S-27", true},
	{0, 118, 118, "IMG_APB_S-28", true},

	/* 50 */
	{0, 119, 119, "IMG_APB_S-29", true},
	{0, 120, 120, "IMG_APB_S-30", true},
	{0, 121, 121, "IMG_APB_S-31", true},
	{0, 122, 122, "IMG_APB_S-32", true},
	{0, 123, 123, "IMG_APB_S-33", true},
	{0, 124, 124, "IMG_APB_S-34", true},
	{0, 125, 125, "IMG_APB_S-35", true},
	{0, 126, 126, "IMG_APB_S-36", true},
	{0, 127, 127, "IMG_APB_S-37", true},
	{0, 128, 128, "IMG_APB_S-38", true},

	/* 60 */
	{0, 129, 129, "IMG_APB_S-39", true},
	{0, 130, 130, "IMG_APB_S-40", true},
	{0, 131, 131, "IMG_APB_S-41", true},
	{0, 132, 132, "IMG_APB_S-42", true},
	{0, 133, 133, "IMG_APB_S-43", true},
	{0, 134, 134, "IMG_APB_S-44", true},
	{0, 135, 135, "IMG_APB_S-45", true},
	{0, 136, 136, "IMG_APB_S-46", true},
	{0, 137, 137, "IMG_APB_S-47", true},
	{0, 138, 138, "IMG_APB_S-48", true},

	/* 70 */
	{0, 139, 139, "IMG_APB_S-49", true},
	{0, 140, 140, "IMG_APB_S-50", true},
	{0, 141, 141, "IMG_APB_S-51", true},
	{0, 142, 142, "CAM_APB_S", true},
	{0, 143, 143, "CAM_APB_S-1", true},
	{0, 144, 144, "CAM_APB_S-2", true},
	{0, 145, 145, "CAM_APB_S-3", true},
	{0, 146, 146, "CAM_APB_S-4", true},
	{0, 147, 147, "CAM_APB_S-5", true},
	{0, 148, 148, "CAM_APB_S-6", true},

	/* 80 */
	{0, 149, 149, "CAM_APB_S-7", true},
	{0, 150, 150, "CAM_APB_S-8", true},
	{0, 151, 151, "CAM_APB_S-9", true},
	{0, 152, 152, "CAM_APB_S-10", true},
	{0, 153, 153, "CAM_APB_S-11", true},
	{0, 154, 154, "CAM_APB_S-12", true},
	{0, 155, 155, "CAM_APB_S-13", true},
	{0, 156, 156, "CAM_APB_S-14", true},
	{0, 157, 157, "CAM_APB_S-15", true},
	{0, 158, 158, "CAM_APB_S-16", true},

	/* 90 */
	{0, 159, 159, "CAM_APB_S-17", true},
	{0, 160, 160, "CAM_APB_S-18", true},
	{0, 161, 161, "CAM_APB_S-19", true},
	{0, 162, 162, "CAM_APB_S-20", true},
	{0, 163, 163, "CAM_APB_S-21", true},
	{0, 164, 164, "CAM_APB_S-22", true},
	{0, 165, 165, "CAM_APB_S-23", true},
	{0, 166, 166, "CAM_APB_S-24", true},
	{0, 167, 167, "CAM_APB_S-25", true},
	{0, 168, 168, "CAM_APB_S-26", true},

	/* 100 */
	{0, 169, 169, "CAM_APB_S-27", true},
	{0, 170, 170, "CAM_APB_S-28", true},
	{0, 171, 171, "CAM_APB_S-29", true},
	{0, 172, 172, "CAM_APB_S-30", true},
	{0, 173, 173, "CAM_APB_S-31", true},
	{0, 174, 174, "CAM_APB_S-32", true},
	{0, 175, 175, "CAM_APB_S-33", true},
	{0, 176, 176, "CAM_APB_S-34", true},
	{0, 177, 177, "CAM_APB_S-35", true},
	{0, 178, 178, "CAM_APB_S-36", true},

	/* 110 */
	{0, 179, 179, "CAM_APB_S-37", true},
	{0, 180, 180, "CAM_APB_S-38", true},
	{0, 181, 181, "CAM_APB_S-39", true},
	{0, 182, 182, "CAM_APB_S-40", true},
	{0, 183, 183, "CAM_APB_S-41", true},
	{0, 184, 184, "CAM_APB_S-42", true},
	{0, 185, 185, "CAM_APB_S-43", true},
	{0, 186, 186, "CAM_APB_S-44", true},
	{0, 187, 187, "CAM_APB_S-45", true},
	{0, 188, 188, "CAM_APB_S-46", true},

	/* 120 */
	{0, 189, 189, "CAM_APB_S-47", true},
	{0, 190, 190, "CAM_APB_S-48", true},
	{0, 191, 191, "CAM_APB_S-49", true},
	{0, 192, 192, "CAM_APB_S-50", true},
	{0, 193, 193, "CAM_APB_S-51", true},
	{0, 194, 194, "CAM_APB_S-52", true},
	{0, 195, 195, "CAM_APB_S-53", true},
	{0, 196, 196, "CAM_APB_S-54", true},
	{0, 197, 197, "CAM_APB_S-55", true},
	{0, 198, 198, "CAM_APB_S-56", true},

	/* 130 */
	{0, 199, 199, "CAM_APB_S-57", true},
	{0, 200, 200, "CAM_APB_S-58", true},
	{0, 201, 201, "CAM_APB_S-59", true},
	{0, 202, 202, "CAM_APB_S-60", true},
	{0, 203, 203, "CAM_APB_S-61", true},
	{0, 204, 204, "CAM_APB_S-62", true},
	{0, 205, 205, "CAM_APB_S-63", true},
	{0, 206, 206, "CAM_APB_S-64", true},
	{0, 207, 207, "CAM_APB_S-65", true},
	{0, 208, 208, "CAM_APB_S-66", true},

	/* 140 */
	{0, 209, 209, "CAM_APB_S-67", true},
	{0, 210, 210, "CAM_APB_S-68", true},
	{0, 211, 211, "CAM_APB_S-69", true},
	{0, 212, 212, "CAM_APB_S-70", true},
	{0, 213, 213, "CAM_APB_S-71", true},
	{0, 214, 214, "CAM_APB_S-72", true},
	{0, 215, 215, "CAM_APB_S-73", true},
	{0, 216, 216, "CAM_APB_S-74", true},
	{0, 217, 217, "CAM_APB_S-75", true},
	{0, 218, 218, "CAM_APB_S-76", true},

	/* 150 */
	{0, 219, 219, "CAM_APB_S-77", true},
	{0, 220, 220, "CAM_APB_S-78", true},
	{0, 221, 221, "CAM_APB_S-79", true},
	{0, 222, 222, "CAM_APB_S-80", true},
	{0, 223, 223, "CAM_APB_S-81", true},
	{0, 224, 224, "CAM_APB_S-82", true},
	{0, 225, 225, "CAM_APB_S-83", true},
	{0, 226, 226, "CAM_APB_S-84", true},
	{0, 227, 227, "CAM_APB_S-85", true},
	{0, 228, 228, "CAM_APB_S-86", true},

	/* 160 */
	{0, 229, 229, "CAM_APB_S-87", true},
	{0, 230, 230, "CAM_APB_S-88", true},
	{0, 231, 231, "CAM_APB_S-89", true},
	{0, 232, 232, "CAM_APB_S-90", true},
	{0, 233, 233, "CAM_APB_S-91", true},
	{0, 234, 234, "CAM_APB_S-92", true},
	{0, 235, 235, "CAM_APB_S-93", true},
	{0, 236, 236, "CAM_APB_S-94", true},
	{0, 237, 237, "CAM_APB_S-95", true},
	{0, 238, 238, "CAM_APB_S-96", true},

	/* 170 */
	{0, 239, 239, "CAM_APB_S-97", true},
	{0, 240, 240, "CAM_APB_S-98", true},
	{0, 241, 241, "CAM_APB_S-99", true},
	{0, 242, 242, "CAM_APB_S-100", true},
	{0, 243, 243, "CAM_APB_S-101", true},
	{0, 244, 244, "CAM_APB_S-102", true},
	{0, 245, 245, "CAM_APB_S-103", true},
	{0, 246, 246, "CAM_APB_S-104", true},
	{0, 247, 247, "CAM_APB_S-105", true},
	{0, 248, 248, "CAM_APB_S-106", true},

	/* 180 */
	{0, 249, 249, "CAM_APB_S-107", true},
	{0, 250, 250, "CAM_APB_S-108", true},
	{0, 251, 251, "CAM_APB_S-109", true},
	{0, 252, 252, "CAM_APB_S-110", true},
	{0, 253, 253, "CAM_APB_S-111", true},
	{0, 254, 254, "CAM_APB_S-112", true},
	{0, 255, 255, "CAM_APB_S-113", true},
	{1, 0, 256, "CAM_APB_S-114", true},
	{1, 1, 257, "CAM_APB_S-115", true},
	{1, 2, 258, "CAM_APB_S-116", true},

	/* 190 */
	{1, 3, 259, "CAM_APB_S-117", true},
	{1, 4, 260, "CAM_APB_S-118", true},
	{1, 5, 261, "CAM_APB_S-119", true},
	{1, 6, 262, "CAM_APB_S-120", true},
	{1, 7, 263, "CAM_APB_S-121", true},
	{1, 8, 264, "CAM_APB_S-122", true},
	{1, 9, 265, "CAM_APB_S-123", true},
	{1, 10, 266, "DISP_APB_S", true},
	{1, 11, 267, "DISP_APB_S-1", true},
	{1, 12, 268, "DISP_APB_S-2", true},

	/* 200 */
	{1, 13, 269, "DISP_APB_S-3", true},
	{1, 14, 270, "DISP_APB_S-4", true},
	{1, 15, 271, "DISP_APB_S-5", true},
	{1, 16, 272, "DISP_APB_S-6", true},
	{1, 17, 273, "DISP_APB_S-7", true},
	{1, 18, 274, "DISP_APB_S-8", true},
	{1, 19, 275, "DISP_APB_S-9", true},
	{1, 20, 276, "DISP_APB_S-10", true},
	{1, 21, 277, "DISP_APB_S-11", true},
	{1, 22, 278, "DISP_APB_S-12", true},

	/* 210 */
	{1, 23, 279, "DISP_APB_S-13", true},
	{1, 24, 280, "DISP_APB_S-14", true},
	{1, 25, 281, "DISP_APB_S-15", true},
	{1, 26, 282, "DISP_APB_S-16", true},
	{1, 27, 283, "DISP_APB_S-17", true},
	{1, 28, 284, "DISP_APB_S-18", true},
	{1, 29, 285, "DISP_APB_S-19", true},
	{1, 30, 286, "DISP_APB_S-20", true},
	{1, 31, 287, "DISP_APB_S-21", true},
	{1, 32, 288, "DISP_APB_S-22", true},

	/* 220 */
	{1, 33, 289, "DISP_APB_S-23", true},
	{1, 34, 290, "DISP_APB_S-24", true},
	{1, 35, 291, "DISP_APB_S-25", true},
	{1, 36, 292, "DISP_APB_S-26", true},
	{1, 37, 293, "DISP_APB_S-27", true},
	{1, 38, 294, "DISP_APB_S-28", true},
	{1, 39, 295, "DISP_APB_S-29", true},
	{1, 40, 296, "DISP_APB_S-30", true},
	{1, 41, 297, "DISP_APB_S-31", true},
	{1, 42, 298, "DISP_APB_S-32", true},

	/* 230 */
	{1, 43, 299, "DISP_APB_S-33", true},
	{1, 44, 300, "DISP_APB_S-34", true},
	{1, 45, 301, "DISP_APB_S-35", true},
	{1, 46, 302, "DISP_APB_S-36", true},
	{1, 47, 303, "DISP_APB_S-37", true},
	{1, 48, 304, "DISP_APB_S-38", true},
	{1, 49, 305, "DISP_APB_S-39", true},
	{1, 50, 306, "DISP_APB_S-40", true},
	{1, 51, 307, "DISP_APB_S-41", true},
	{1, 52, 308, "DISP_APB_S-42", true},

	/* 240 */
	{1, 53, 309, "DISP_APB_S-43", true},
	{1, 54, 310, "DISP_APB_S-44", true},
	{1, 55, 311, "MDP_APB_S", true},
	{1, 56, 312, "MDP_APB_S-1", true},
	{1, 57, 313, "MDP_APB_S-2", true},
	{1, 58, 314, "MDP_APB_S-3", true},
	{1, 59, 315, "MDP_APB_S-4", true},
	{1, 60, 316, "MDP_APB_S-5", true},
	{1, 61, 317, "MDP_APB_S-6", true},
	{1, 62, 318, "MDP_APB_S-7", true},

	/* 250 */
	{1, 63, 319, "MDP_APB_S-8", true},
	{1, 64, 320, "MDP_APB_S-9", true},
	{1, 65, 321, "MDP_APB_S-10", true},
	{1, 66, 322, "MDP_APB_S-11", true},
	{1, 67, 323, "MDP_APB_S-12", true},
	{1, 68, 324, "MDP_APB_S-13", true},
	{1, 69, 325, "MDP_APB_S-14", true},
	{1, 70, 326, "MDP_APB_S-15", true},
	{1, 71, 327, "MDP_APB_S-16", true},
	{1, 72, 328, "MDP_APB_S-17", true},

	/* 260 */
	{1, 73, 329, "MDP_APB_S-18", true},
	{1, 74, 330, "MDP_APB_S-19", true},
	{1, 75, 331, "MDP_APB_S-20", true},
	{1, 76, 332, "MDP_APB_S-21", true},
	{1, 77, 333, "MDP_APB_S-22", true},
	{1, 78, 334, "MDP_APB_S-23", true},
	{1, 79, 335, "MDP_APB_S-24", true},
	{1, 80, 336, "HRE_APB_S", true},
	{1, 81, 340, "DAPC_AO_S", true},
	{1, 82, 341, "BCRM_AO_S", true},

	/* 270 */
	{1, 83, 342, "DEBUG_CTL_AO_S", true},

	{-1, -1, 343, "OOB_way_en", true},
	{-1, -1, 344, "OOB_way_en", true},
	{-1, -1, 345, "OOB_way_en", true},
	{-1, -1, 346, "OOB_way_en", true},
	{-1, -1, 347, "OOB_way_en", true},
	{-1, -1, 348, "OOB_way_en", true},
	{-1, -1, 349, "OOB_way_en", true},

	{-1, -1, 350, "OOB_way_en", true},
	{-1, -1, 351, "OOB_way_en", true},
	{-1, -1, 352, "OOB_way_en", true},
	{-1, -1, 353, "OOB_way_en", true},
	{-1, -1, 354, "OOB_way_en", true},
	{-1, -1, 355, "OOB_way_en", true},
	{-1, -1, 356, "OOB_way_en", true},

	{-1, -1, 357, "Decode_error", true},
	{-1, -1, 358, "Decode_error", true},
	{-1, -1, 359, "Decode_error", true},
	{-1, -1, 360, "Decode_error", true},

	{-1, -1, 361, "GCE_D", false},
	{-1, -1, 362, "GCE_M", false},
	{-1, -1, 363, "DEVICE_APC_MM_AO", false},
	{-1, -1, 363, "DEVICE_APC_MM_PDN", false},
};

static const struct mtk_device_info mt6886_devices_mmup[] = {
	/* sys_idx, ctrl_idx, vio_idx, device, vio_irq */
	/* 0 */
	{0, 0, 0, "p_main_BCRM", true},
	{0, 1, 1, "p_main_DEBUG", true},
	{0, 2, 2, "p_main_DEVAPCAO", true},
	{0, 3, 3, "p_main_DEVAPC", true},
	{0, 4, 4, "p_par_top", true},
	{0, 5, 5, "pslv_clk_ctrl", true},
	{0, 6, 6, "pslv_cfgreg", true},
	{0, 7, 7, "pslv_uart", true},
	{0, 8, 8, "pslv_uart1", true},
	{0, 9, 9, "pslv_cfg_core0", true},

	/* 10 */
	{0, 10, 10, "pslv_dma_core0", true},
	{0, 11, 11, "pslv_irq_core0", true},
	{0, 12, 12, "pslv_tmr_core0", true},
	{0, 13, 13, "pslv_dbg_core0", true},
	{0, 14, 14, "pbus_tracker", true},
	{0, 15, 15, "pCACHE0", true},
	{0, 16, 16, "pslv_cfgreg_sec", true},
	{0, 17, 17, "p_mbox0", true},
	{0, 18, 18, "p_mbox1", true},
	{0, 19, 19, "p_mbox2", true},

	/* 20 */
	{0, 20, 20, "p_mbox3", true},
	{0, 21, 21, "p_mbox4", true},
	{0, 22, 22, "pslv_rsv00", true},
	{0, 23, 23, "pslv_rsv01", true},

	{-1, -1, 24, "OOB_way_en", true},
	{-1, -1, 25, "OOB_way_en", true},
	{-1, -1, 26, "OOB_way_en", true},
	{-1, -1, 27, "OOB_way_en", true},
	{-1, -1, 28, "OOB_way_en", true},
	{-1, -1, 29, "OOB_way_en", true},

	{-1, -1, 30, "OOB_way_en", true},
	{-1, -1, 31, "OOB_way_en", true},
	{-1, -1, 32, "OOB_way_en", true},
	{-1, -1, 33, "OOB_way_en", true},
	{-1, -1, 34, "OOB_way_en", true},
	{-1, -1, 35, "OOB_way_en", true},
	{-1, -1, 36, "OOB_way_en", true},
	{-1, -1, 37, "OOB_way_en", true},
	{-1, -1, 38, "OOB_way_en", true},
	{-1, -1, 39, "OOB_way_en", true},

	{-1, -1, 40, "OOB_way_en", true},
	{-1, -1, 41, "OOB_way_en", true},
	{-1, -1, 42, "OOB_way_en", true},
	{-1, -1, 43, "OOB_way_en", true},
	{-1, -1, 44, "OOB_way_en", true},
	{-1, -1, 45, "OOB_way_en", true},
	{-1, -1, 46, "OOB_way_en", true},
	{-1, -1, 47, "OOB_way_en", true},
	{-1, -1, 48, "OOB_way_en", true},
	{-1, -1, 49, "OOB_way_en", true},

	{-1, -1, 50, "Decode_error", true},
	{-1, -1, 51, "Decode_error", true},

	{-1, -1, 52, "DEVICE_APC_MMUP_AO", false},
	{-1, -1, 53, "DEVICE_APC_MMUP_PDN", false},
};

enum DEVAPC_VIO_SLAVE_NUM {
	VIO_SLAVE_NUM_INFRA = ARRAY_SIZE(mt6886_devices_infra),
	VIO_SLAVE_NUM_INFRA1 = ARRAY_SIZE(mt6886_devices_infra1),
	VIO_SLAVE_NUM_PERI_PAR = ARRAY_SIZE(mt6886_devices_peri_par),
	VIO_SLAVE_NUM_VLP = ARRAY_SIZE(mt6886_devices_vlp),
	VIO_SLAVE_NUM_ADSP = ARRAY_SIZE(mt6886_devices_adsp),
	VIO_SLAVE_NUM_MMINFRA = ARRAY_SIZE(mt6886_devices_mminfra),
	VIO_SLAVE_NUM_MMUP = ARRAY_SIZE(mt6886_devices_mmup),
};

#endif /* __DEVAPC_MT6886_H__ */
