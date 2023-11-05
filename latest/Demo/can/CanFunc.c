/****************************************Copyright (c)**************************************************
**                               广州周立功单片机发展有限公司
**                                     研    究    所
**                                        产品一部 
**                                 http://www.zlgmcu.com
**--------------------------------------------文件信息-------------------------------------------------
**	文   件  	名:	CANFUNC.C
** 	版  		本:	v1.0
** 	日		期:	2004年2月23日
**	描		述:	CAN模块功能操作函数说明文件
********************************************************************************************************/
#define	_CANFUNC_GLOBAL_
#include "config.h"
#include "IncludeCan.H"
/*
***************************************************************
**		应用常量定义
***************************************************************
*/

//使用工作模式
const 	INT32U	USE_LOM_CAN[2] = 
{
	USE_LOM_CAN1,
	USE_LOM_CAN2,
};
//使用睡眠模式
const 	INT32U	USE_SLP_MOD_CAN[2] = 
{
	USE_SLP_MOD_CAN1,
	USE_SLP_MOD_CAN2,
};
//使用波特率
const 	INT32U	USE_BTR_CAN[2] = 
{
	USE_BTR_CAN1,
	USE_BTR_CAN2,
};
//使用发送缓冲区发送优先级模式选择
const 	INT32U	USE_TPM_CAN[2] = 
{
	USE_TPM_CAN1,
	USE_TPM_CAN2,
};
//应用中断
const 	INT32U	USE_INT_CAN[2] = 
{
	USE_INT_CAN1,
	USE_INT_CAN2,
};
//应用报警限制
const	INT32U	USE_EWL_CAN[2] = 
{
	USE_EWL_CAN1,
	USE_EWL_CAN2,
};
/*
********************************************************************************************************
**函数原型		:  	void	HwRstCAN (eCANNUM CanNum)
**参数说明		:  	CanNum		-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**返回值		:	无	
**说	明		:	本函数用于硬件复位CAN控制器，主要是CAN模块掉电，用于省电处理
*********************************************************************************************************/
void HwRstCAN(eCANNUM CanNum)
{
	PCONP &= ~((INT32U)0x01 << (13+CanNum));
}
/*
*********************************************************************************************************
**函数原型		:  	void	HwEnCAN (eCANNUM CanNum)
**参数说明		:  	CanNum		-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**返回值		:	无	
**说	明		:	本函数用于硬件使能CAN控制器
*********************************************************************************************************/
void		HwEnCAN(eCANNUM CanNum)
{
	_CANAFMR.Bits.AccBP =1;
	PCONP |= ((INT32U)0x01 << (13+CanNum));
	switch(CanNum)
	{
		
		case	CAN1:
			PINSEL1 &=  ~((INT32U)0x03 << 18);
			PINSEL1 |=  ((INT32U)0x01 << 18);
			break;
		case	CAN2:
			PINSEL1 &=  ~((INT32U)0x0F << 14);
			PINSEL1 |=  ((INT32U)0x05 << 14);
			break;
		default:
			break;	
	}
}
/*
***********************************************************************************************************
**函数原型		:  	INT32U	SoftRstCAN (eCANNUM CanNum)
**参数说明		:  	CanNum		-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**返回值		:	＝0，表示复位成功； ＝0，复位不成功；	
**说	明		:	本函数用于软件复位CAN控制器
************************************************************************************************************/
INT32U		SoftRstCAN(eCANNUM CanNum)
{
	CANMOD(CanNum).Bits.RM =1;
	return(!CANMOD(CanNum).Bits.RM );
}
/*
***********************************************************************************************************
**函数原型		:  	INT32U	SoftEnCAN (eCANNUM CanNum)
**参数说明		:  	CanNum		-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**返回值		:	＝0，表示成功使CAN控制器进入工作模式；!＝0，不成功；	
**说	明		:	本函数用于软件使能CAN控制器
************************************************************************************************************/
INT32U		SoftEnCAN(eCANNUM CanNum)
{
	INT32U	i = 0x100;
	CANMOD(CanNum).Bits.RM =0;
	while (i-- > 0);
	return(CANMOD(CanNum).Bits.RM );
}
/*
***********************************************************************************************************
**函数原型		:  	SetCANBaudRate (eCANNUM CanNum);
**参数说明		:  	CanNum	-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**				:	Val 	-->>	总线定时器的设定参数值
**返回值		:	＝0，表示成功使CAN控制器设置波特率； !＝0，不成功；	
**说	明		:	本函数用于设置CAN的波特率(只有在RM ＝ 1时才可写入)
************************************************************************************************************/
INT32U		SetCANBaudRate (eCANNUM CanNum,INT32U Val)
{
	INT32U	statue = 0;
	if (CANMOD(CanNum).Bits.RM)
	{
		CANBTR(CanNum).Word = Val;
		if (CANBTR(CanNum).Word != Val)
		{
			statue = 1;
		}
	}
	else
	{
		statue = 1;
	}
	return statue;
}
/*
***********************************************************************************************************
**函数原型		:  	SetErWarmVal (eCANNUM CanNum)
**参数说明		:  	CanNum	-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**				:	Val		-->>	错误警告寄存器的设定值
**返回值		:	＝0，表示成功使CAN控制器错误警告寄存器； ！＝0，不成功；	
**说	明		:	本函数用于设置CAN的错误警告寄存器(只有在RM ＝ 1时才可写入)
************************************************************************************************************/
INT32U		SetErWarmVal (const eCANNUM CanNum, INT32U Val)
{
	INT32U	statue = 0;
	if (CANMOD(CanNum).Bits.RM)
	{
		CANEWL(CanNum).Bits.EWL = Val;
		if (CANEWL(CanNum).Bits.EWL != Val)
		{
			statue = 1;
		}
	}
	else
	{
		statue = 1;
	}
	return statue;
}
/*
***********************************************************************************************************
**函数原型		:  	SetTPMMOD	 (eCANNUM CanNum)
**参数说明		:  	CanNum	-->> CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**				:	Val     -->> 0:各自的CAN ID决定;1:由发送缓冲区的优先级域决定
**返回值		:	＝0，表示成功设置CAN的发送优先级模式位； ！＝0，不成功；	
**说	明		:	本函数用于设置CAN的发送优先级模式
************************************************************************************************************/
INT32U		SetTPMMOD	 (eCANNUM CanNum, INT32U Val)
{
	CANMOD(CanNum).Bits.TPM = Val;
	if (CANMOD(CanNum).Bits.TPM == Val)
		return 0;
	else
		return 1;
}
/*
***********************************************************************************************************
**函数原型		:  	INT32U		SetLOMMOD	 (eCANNUM CanNum)
**参数说明		:  	CanNum		-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**				:	Val			-->>    只听模式选择 0;正常，1:只听
**返回值		:	＝0，表示成功设置CAN的只听模式； ！＝0，不成功；	
**说	明		:	本函数用于设置CAN只听模式(只有在RM ＝ 1时才可写入)
************************************************************************************************************/
INT32U		SetLOMMOD	 (eCANNUM CanNum, INT32U Val)
{
	INT32U	statue = 0;
	if (CANMOD(CanNum).Bits.RM)
	{
		CANMOD(CanNum).Bits.LOM = Val;
		if (CANMOD(CanNum).Bits.LOM != Val)
		{
			statue = 1;
		}
	}
	else
	{
		statue = 1;
	}
	return statue;
}
/*
***********************************************************************************************************
**函数原型		:  	void	CanSendCmd(eCANNUM CanNum,INT32U Cmd,INT32U TxBufNum)
**参数说明		:  	CanNum		-->> CAN控制器，值不能大于CAN_MAX_NUM 规定的值
					Cmd	-->> 发送命令字:1--单次发送,
									     2--自发自收,
									     3--单次自发自收,
									     其他--正常发送
					TxBufNum	-->> 选择发送缓冲区
**返回值		:		
**说	明		:	本函数用于发送命令处理(只写寄存器)
************************************************************************************************************/
void	CanSendCmd(eCANNUM CanNum,INT32U Cmd,INT32U TxBufNum)
{
	uCANCMR Temp;
	Temp.Word =0;
	Temp.Bits.STB1 = TxBufNum & 0x00000001;
	Temp.Bits.STB2 = (TxBufNum & 0x00000002)>>1;
	Temp.Bits.STB3 = (TxBufNum & 0x00000004)>>2;
	switch(Cmd)
	{
		case	1:
			if (CANMOD(CanNum).Bits.STM != 0)
			{
				while (!CANMOD(CanNum).Bits.RM)
					CANMOD(CanNum).Bits.RM = 1;
				/*****************************/	
				while (CANMOD(CanNum).Bits.STM)
					CANMOD(CanNum).Bits.STM = 0;
				/******************************/
				while (CANMOD(CanNum).Bits.RM)
					CANMOD(CanNum).Bits.RM = 0;
			}
			Temp.Bits.AT =1;						//单次发送
			Temp.Bits.TR =1;
			break;
		case	2:
		case	3:									//自发自收
			if (CANMOD(CanNum).Bits.STM != 1)
			{
				while (!CANMOD(CanNum).Bits.RM)
					CANMOD(CanNum).Bits.RM = 1;
				/******************************/	
				while (!CANMOD(CanNum).Bits.STM)
					CANMOD(CanNum).Bits.STM = 1;
				/*****************************/
				while (CANMOD(CanNum).Bits.RM)
					CANMOD(CanNum).Bits.RM = 0;
			}
			Temp.Bits.SRR =1;
			if(Cmd == 3)							//单次自发自收
			{
				Temp.Bits.AT =1;
			}
			break;
		case 	0:
		default:									//正常发送
			if (CANMOD(CanNum).Bits.STM != 0)
			{
				while (!CANMOD(CanNum).Bits.RM)
					CANMOD(CanNum).Bits.RM = 1;
				/*****************************/	
				while (CANMOD(CanNum).Bits.STM)
					CANMOD(CanNum).Bits.STM = 0;
				/******************************/
				while (CANMOD(CanNum).Bits.RM)
					CANMOD(CanNum).Bits.RM = 0;
			}
			Temp.Bits.TR =1;
			break;
	}
	CANCMR(CanNum) = Temp;
}
/*
***********************************************************************************************************
**函数原型		:  	void	RelCanRecBuf (eCANNUM CanNum)
**参数说明		:  	CanNum		-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**返回值		:		
**说	明		:	本函数用于释放接收缓冲区
************************************************************************************************************/
void	RelCanRecBuf (eCANNUM CanNum)
{
	uCANCMR Temp;
	Temp.Word =0;
	Temp.Bits.RRB=1;
	CANCMR(CanNum) = Temp;
}
/*
***********************************************************************************************************
**函数原型		:  	ClrCanDataOver (eCANNUM CanNum)
**参数说明		:  	CanNum		-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**返回值		:		
**说	明		:	本函数用于清除数据溢出
************************************************************************************************************/
void	ClrCanDataOver (eCANNUM CanNum)
{
	uCANCMR Temp;
	Temp.Word =0;
	Temp.Bits.CDO=1;
	CANCMR(CanNum) = Temp;
}

/*
***********************************************************************************************************
**函数原型		:  	INT32U 	CanEntrySM(CanNum)
**参数说明		:  	CanNum	-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**返回值		:	=0;成功进入睡眠状态;
					!=0;不能进入睡眠状态;	
**说	明		:	本函数用于使CAN控制器进入休眠模式
***********************************************************************************************************
*/
INT32U	CanEntrySM(eCANNUM	CanNum)
{
	CANMOD(CanNum).Bits.SM = 1;	
	return(!CANMOD(CanNum).Bits.SM);
}
/*
***********************************************************************************************************
**函数原型		:  	INT32U CanQuitSM(eCANNUM	CanNum)
**参数说明		:  	CanNum		-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**返回值		:	=0;成功退出睡眠状态;
					!=0;不能退出睡眠状态;	
**说	明		:	本函数用于使CAN控制器退出休眠模式
***********************************************************************************************************
*/
INT32U CanQuitSM(eCANNUM CanNum)	
{
	uCANMod		i;
	i=CANMOD(CanNum);
	CANMOD(CanNum).Bits.RM=1; 
	CANMOD(CanNum).Bits.SM = 0;	
	CANMOD(CanNum).Bits.RM=i.Bits.RM; 
	return(CANMOD(CanNum).Bits.SM);
}
/*
*********************************************************************************************************
**函数原型	;	void AFSetMode(INT32U mode)
**参数说明	;	mode -->> 验收过滤控制器的模式
**							Bypass =  1
**							normal =  2
**							fullCAN = 3
**							Ignored = 4
**返回值	:	
**
**说明		:	验收控制寄存器的设置函数						  
*********************************************************************************************************
*/
void AFSetMode(INT32U mode)
{
	uCANAFMR afmr;
	afmr.Word = 0;					// initial value!!!

	switch(mode)
	{
	case 1:
		afmr.Bits.AccBP = 1;	// Bypass mode
		break;
	case 2:
		//..						// normal filter
		break;
	case 3:
		afmr.Bits.eFCAN = 1;	// fullCAN mode
		break;
	default:
		afmr.Bits.AccBP = 0;
		afmr.Bits.AccOff = 1;	// all message on CAN buses are ignored
		break;
	}

	CANAFMR = afmr.Word;
}
/*
************************************************************************************************************
**函数原型	:	INT32U AFBuildLUT (INT32U FCAN_nCell,
**								   INT32U SFF_INDV_nCell,
**								   INT32U SFF_GRP_nCell,
**								   INT32U EFF_INDV_nCell,
**								   INT32U EFF_GRP_nCell)
**参数说明	:	FCAN_nCell_Num -->>	FullCAN标准帧滤波单元个数
**				SFF_INDV_nCell_Num -->>	单个标准帧滤波单元个数
**				SFF_GRP_nCell_Num -->>	标准帧范围滤波单元个数
**				EFF_INDV_nCell_Num -->> 单个扩展帧滤波单元个数
**				EFF_GRP_nCell_Num -->>	扩展帧范围滤波单元个数
**
**返回值	:   LUT_SETTING_OK 			= 0,
**				TOTAL_SIZE_TOO_LARGE 	= 1,
**				EFF_GRP_SIZE_INVALID	= 3,
**				FCAN_STORE_SIZE_INVALID = 4,
**
**说明		:	验收过滤寄存器的初始化函数
************************************************************************************************************
*/
INT32U AFBuildLUT( INT32U FCAN_nCell_Num,INT32U SFF_INDV_nCell_Num,
				   INT32U SFF_GRP_nCell_Num,INT32U EFF_INDV_nCell_Num,
				   INT32U EFF_GRP_nCell_Num)
{
	INT32U	i;
	uCANAFMR afmr;
	INT32U tmpREGSFF_sa,tmpREGSFF_GRP_sa,tmpREGEFF_sa;
	INT32U tmpREGEFF_GRP_sa,tmpREGENDofTable;
	INT32U *pU32 = (INT32U *)(CANAFRAM_BADR);
	
	if(4 * (FCAN_nCell_Num + SFF_INDV_nCell_Num + SFF_GRP_nCell_Num + EFF_INDV_nCell_Num + EFF_GRP_nCell_Num) > 0x800)
		return TOTAL_SIZE_TOO_LARGE;

	if((EFF_GRP_nCell_Num % 2) != 0)
		return EFF_GRP_SIZE_INVALID;
	
	tmpREGSFF_sa 		= FCAN_nCell_Num * 4; 
	tmpREGSFF_GRP_sa 	= tmpREGSFF_sa + (SFF_INDV_nCell_Num * 4);
	tmpREGEFF_sa 		= tmpREGSFF_GRP_sa + (SFF_GRP_nCell_Num * 4);
	tmpREGEFF_GRP_sa 	= tmpREGEFF_sa + (EFF_INDV_nCell_Num * 4);
	tmpREGENDofTable 	= tmpREGEFF_GRP_sa + (EFF_GRP_nCell_Num * 4);
	
	afmr.Word = 0;
	afmr.Bits.AccBP = 1;
	CANAFMR = afmr.Word;

	if((0x800 - tmpREGSFF_sa * 6) < tmpREGENDofTable)
	{
		return FCAN_STORE_SIZE_INVALID;
	}

	
	for(i=0;i<(0x800/4);i++)
	{
		*(pU32 + i) = -1;		// disable all AF cell
	}
	CANSFF_sa		= tmpREGSFF_sa;
	CANSFF_GRP_sa	= tmpREGSFF_GRP_sa;
	CANEFF_sa		= tmpREGEFF_sa;
	CANEFF_GRP_sa 	= tmpREGEFF_GRP_sa;
	CANENDofTable 	= tmpREGENDofTable;
	
	return LUT_SETTING_OK;
}
/*
*********************************************************************************************************
**函数原型	;	INT32U AFInitFCANTab(stcAF_SFF_CELL *pTab,INT32U nCell)
**参数说明	;	pTab -->>	FullCAN 标准帧ID结构数组
**			:	nCell -->>	Cell的个数
**
**返回值	:	LUT_SETTING_OK 	= 0,
**				TABLE_CELL_TOO_LARGE	= 5,
**
**说明		:	FullCAN标准帧表格的初始化
*********************************************************************************************************
*/
INT32U AFInitFCANTab(stcAF_SFF_CELL *pTab,INT32U nCell)
{
	uCANAFMR afmr;
	INT32U bakAfmr;
	INT32U i;
	
	stcAF_SFF_CELL mask = {-1,-1,-1,-1,-1,-1,-1,-1};
	stcAF_SFF_CELL *pU32 = (stcAF_SFF_CELL *)(CANAFRAM_BADR);
	
	if(nCell > (CANSFF_sa / 4))
		return TABLE_CELL_TOO_LARGE;

	afmr.Word = CANAFMR;
	bakAfmr = afmr.Word;
	afmr.Bits.AccBP = 1;
	CANAFMR = afmr.Word;

	
	for(i=0;i<(CANSFF_GRP_sa/4);i++)
	{
		*(pU32 + i) = mask;			// disable all AF cell
	}

	for(i=0;i<nCell;i++)
	{
		*(pU32 + i) = *(pTab+i);	// set filter cell
	}
	
	CANAFMR = bakAfmr;
	
	return LUT_SETTING_OK;
}
/*
*********************************************************************************************************
**函数原型	;	INT32U AFInitSFFIndvTab(stcAF_SFF_CELL *pTab,INT32U nCell)
**参数说明	;	pTab -->>	标准帧ID结构数组
**			:	nCell -->>	Cell的个数
**
**返回值	:	LUT_SETTING_OK 	= 0,
**				TABLE_CELL_TOO_LARGE	= 5,
**
**说明		:	单独标准帧表格的初始化
*********************************************************************************************************
*/
INT32U AFInitSFFIndvTab(stcAF_SFF_CELL *pTab,INT32U nCell)
{
	INT32U i;
	uCANAFMR afmr;
	INT32U bakAfmr;
	stcAF_SFF_CELL *pU32 = (stcAF_SFF_CELL *)((INT32U)CANAFRAM_BADR + (INT32U)(CANSFF_sa));
	stcAF_SFF_CELL mask = {-1,-1,-1,-1,-1,-1,-1,-1};
	
	if(nCell > ((CANSFF_GRP_sa-CANSFF_sa) / 4))
		return TABLE_CELL_TOO_LARGE;

	afmr.Word = CANAFMR;
	bakAfmr = afmr.Word;
	afmr.Bits.AccBP = 1;
	CANAFMR = afmr.Word;

	for(i=0;i<((CANSFF_GRP_sa-CANSFF_sa)/4);i++)
	{
		*(pU32 + i) = mask;			// disable all AF cell
	}

	for(i=0;i<nCell;i++)
	{
		*(pU32 + i) = *(pTab+i);	// set filter cell
	}
	
	CANAFMR = bakAfmr;
	
	return LUT_SETTING_OK;
}
/*
*********************************************************************************************************
**函数原型	;	INT32U AFInitSFFGrpTab(_AF_SFF_CELL *pTab,UINT32 nCell)
**参数说明	;	pTab -->>	标准帧ID结构数组
**			:	nCell -->>	Cell的个数
**
**返回值	:	LUT_SETTING_OK 	= 0,
**				TABLE_CELL_TOO_LARGE	= 5,
**
**说明		:	标准帧范围表格的初始化
*********************************************************************************************************
*/
INT32U AFInitSFFGrpTab(stcAF_SFF_CELL *pTab,INT32U nCell)
{
	INT32U	i;
	uCANAFMR afmr;
	INT32U bakAfmr;
	stcAF_SFF_CELL mask = {-1,-1,-1,-1,-1,-1,-1,-1};
	stcAF_SFF_CELL *pU32 = (stcAF_SFF_CELL *)((INT32U)CANAFRAM_BADR + (INT32U)(CANSFF_GRP_sa));
	
	if(nCell > ((CANEFF_sa - CANSFF_GRP_sa) / 4))
		return TABLE_CELL_TOO_LARGE;

	afmr.Word = CANAFMR;
	bakAfmr = afmr.Word;
	afmr.Bits.AccBP = 1;
	CANAFMR = afmr.Word;

	for(i=0;i<((CANEFF_sa - CANSFF_GRP_sa)/4);i++)
	{
		*(pU32 + i) = mask;			// disable all AF cell
	}

	for(i=0;i<nCell;i++)
	{
		*(pU32 + i) = *(pTab+i);	// set filter cell
	}
	
	CANAFMR = bakAfmr;
	return LUT_SETTING_OK;
}
/*
*********************************************************************************************************
**函数原型	;	INT32U AFInitEFFIndvTab(stcAF_EFF_CELL *pTab,INT32U nCell)
**参数说明	;	pTab -->>	扩展帧ID结构数组
**			:	nCell -->>	Cell的个数
**
**返回值	:	LUT_SETTING_OK 	= 0,
**				TABLE_CELL_TOO_LARGE	= 5,
**
**说明		:	单独扩展帧表格的初始化
*********************************************************************************************************
*/
INT32U AFInitEFFIndvTab(stcAF_EFF_CELL *pTab,INT32U nCell)
{
	INT32U		i;
	uCANAFMR	afmr;
	INT32U		bakAfmr;
	stcAF_EFF_CELL mask = {-1,-1};
	stcAF_EFF_CELL *pU32 = (stcAF_EFF_CELL *)((INT32U)CANAFRAM_BADR + (INT32U)(CANEFF_sa));
	
	if(nCell > ((CANEFF_GRP_sa-CANEFF_sa) / 4))
		return TABLE_CELL_TOO_LARGE;
	afmr.Word = CANAFMR;
	bakAfmr = afmr.Word;
	afmr.Bits.AccBP = 1;
	CANAFMR = afmr.Word;

	for(i=0;i<((CANEFF_GRP_sa-CANEFF_sa)/4);i++)
	{
		*(pU32 + i) = mask;			// disable all AF cell
	}

	for(i=0;i<nCell;i++)
	{
		*(pU32 + i) = *(pTab+i);	// set filter cell
	}
	
	CANAFMR = bakAfmr;
	
	return LUT_SETTING_OK;
}
/*
*********************************************************************************************************
**函数原型	;	INT32U AFInitEFFGrpTab(stcAF_EFF_CELL *pTab,INT32U nCell)
**参数说明	;	pTab -->>	扩展帧ID结构数组
**			:	nCell -->>	Cell的个数
**
**返回值	:	LUT_SETTING_OK 	= 0,
**				TABLE_CELL_TOO_LARGE	= 5,
**				CELL_NUM_INVALID		= 6,
**
**说明		:	扩展帧范围表格的初始化
*********************************************************************************************************
*/
INT32U AFInitEFFGrpTab(stcAF_EFF_CELL *pTab,INT32U nCell)
{
	INT32U		i;
	uCANAFMR 	afmr;
	INT32U 		bakAfmr;
	stcAF_EFF_CELL mask = {-1,-1};
	stcAF_EFF_CELL *pU32 = (stcAF_EFF_CELL *)((INT32U)CANAFRAM_BADR + (INT32U)(CANEFF_GRP_sa));
	
	if((nCell % 2) != 0)
		return CELL_NUM_INVALID;
	if(nCell > ((CANENDofTable- CANEFF_GRP_sa) / 4))
		return TABLE_CELL_TOO_LARGE;
	afmr.Word = CANAFMR;
	bakAfmr = afmr.Word;
	afmr.Bits.AccBP = 1;
	CANAFMR = afmr.Word;
	
	for(i=0;i<((CANENDofTable- CANEFF_GRP_sa)/4);i++)
	{
		*(pU32 + i) = mask;			// disable all AF cell
	}

	for(i=0;i<nCell;i++)
	{
		*(pU32 + i) = *(pTab+i);	// set filter cell
	}
	
	CANAFMR = bakAfmr;
	
	return LUT_SETTING_OK;
}
/*
*********************************************************************************************************
**函数原型	;	INT32U AFReadFCANRxResurt(_AF_AUTOSTORE_MSG *pMsg,UINT32 IdIndex)
**参数说明	;	pMsg -->>	FullCAN中自动保存的信息的ID结构
**			:	nCell -->>	FullCAN自动接收完毕后生成的索引		  
*********************************************************************************************************
*/
INT32U AFReadFCANRxResurt(stcAF_AUTOSTORE_MSG *pMsg,INT32U IdIndex)
{
	INT32U state = -1;
	stcAF_AUTOSTORE_MSG *pTmp;
	pTmp = (stcAF_AUTOSTORE_MSG *)((INT32U)CANAFRAM_BADR + (INT32U)CANENDofTable + (INT32U)(IdIndex * 12));

	if(pTmp->Head.SEM == 0x03)		//SEM = 11(b)
	{
		pTmp->Head.SEM = 0x00;		// set flag to begin read message...
		*pMsg = *pTmp;
		if(pTmp->Head.SEM != 0x00)	// flag check...
			state = 1;	//update continue...
		else
			state = 2;	//get a correct message!
	}
	else
		state = 0;		//not any update after last access.
	return state;
}

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
