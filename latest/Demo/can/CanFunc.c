/****************************************Copyright (c)**************************************************
**                               ������������Ƭ����չ���޹�˾
**                                     ��    ��    ��
**                                        ��Ʒһ�� 
**                                 http://www.zlgmcu.com
**--------------------------------------------�ļ���Ϣ-------------------------------------------------
**	��   ��  	��:	CANFUNC.C
** 	��  		��:	v1.0
** 	��		��:	2004��2��23��
**	��		��:	CANģ�鹦�ܲ�������˵���ļ�
********************************************************************************************************/
#define	_CANFUNC_GLOBAL_
#include "config.h"
#include "IncludeCan.H"
/*
***************************************************************
**		Ӧ�ó�������
***************************************************************
*/

//ʹ�ù���ģʽ
const 	INT32U	USE_LOM_CAN[2] = 
{
	USE_LOM_CAN1,
	USE_LOM_CAN2,
};
//ʹ��˯��ģʽ
const 	INT32U	USE_SLP_MOD_CAN[2] = 
{
	USE_SLP_MOD_CAN1,
	USE_SLP_MOD_CAN2,
};
//ʹ�ò�����
const 	INT32U	USE_BTR_CAN[2] = 
{
	USE_BTR_CAN1,
	USE_BTR_CAN2,
};
//ʹ�÷��ͻ������������ȼ�ģʽѡ��
const 	INT32U	USE_TPM_CAN[2] = 
{
	USE_TPM_CAN1,
	USE_TPM_CAN2,
};
//Ӧ���ж�
const 	INT32U	USE_INT_CAN[2] = 
{
	USE_INT_CAN1,
	USE_INT_CAN2,
};
//Ӧ�ñ�������
const	INT32U	USE_EWL_CAN[2] = 
{
	USE_EWL_CAN1,
	USE_EWL_CAN2,
};
/*
********************************************************************************************************
**����ԭ��		:  	void	HwRstCAN (eCANNUM CanNum)
**����˵��		:  	CanNum		-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**����ֵ		:	��	
**˵	��		:	����������Ӳ����λCAN����������Ҫ��CANģ����磬����ʡ�紦��
*********************************************************************************************************/
void HwRstCAN(eCANNUM CanNum)
{
	PCONP &= ~((INT32U)0x01 << (13+CanNum));
}
/*
*********************************************************************************************************
**����ԭ��		:  	void	HwEnCAN (eCANNUM CanNum)
**����˵��		:  	CanNum		-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**����ֵ		:	��	
**˵	��		:	����������Ӳ��ʹ��CAN������
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
**����ԭ��		:  	INT32U	SoftRstCAN (eCANNUM CanNum)
**����˵��		:  	CanNum		-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**����ֵ		:	��0����ʾ��λ�ɹ��� ��0����λ���ɹ���	
**˵	��		:	���������������λCAN������
************************************************************************************************************/
INT32U		SoftRstCAN(eCANNUM CanNum)
{
	CANMOD(CanNum).Bits.RM =1;
	return(!CANMOD(CanNum).Bits.RM );
}
/*
***********************************************************************************************************
**����ԭ��		:  	INT32U	SoftEnCAN (eCANNUM CanNum)
**����˵��		:  	CanNum		-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**����ֵ		:	��0����ʾ�ɹ�ʹCAN���������빤��ģʽ��!��0�����ɹ���	
**˵	��		:	�������������ʹ��CAN������
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
**����ԭ��		:  	SetCANBaudRate (eCANNUM CanNum);
**����˵��		:  	CanNum	-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**				:	Val 	-->>	���߶�ʱ�����趨����ֵ
**����ֵ		:	��0����ʾ�ɹ�ʹCAN���������ò����ʣ� !��0�����ɹ���	
**˵	��		:	��������������CAN�Ĳ�����(ֻ����RM �� 1ʱ�ſ�д��)
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
**����ԭ��		:  	SetErWarmVal (eCANNUM CanNum)
**����˵��		:  	CanNum	-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**				:	Val		-->>	���󾯸�Ĵ������趨ֵ
**����ֵ		:	��0����ʾ�ɹ�ʹCAN���������󾯸�Ĵ����� ����0�����ɹ���	
**˵	��		:	��������������CAN�Ĵ��󾯸�Ĵ���(ֻ����RM �� 1ʱ�ſ�д��)
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
**����ԭ��		:  	SetTPMMOD	 (eCANNUM CanNum)
**����˵��		:  	CanNum	-->> CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**				:	Val     -->> 0:���Ե�CAN ID����;1:�ɷ��ͻ����������ȼ������
**����ֵ		:	��0����ʾ�ɹ�����CAN�ķ������ȼ�ģʽλ�� ����0�����ɹ���	
**˵	��		:	��������������CAN�ķ������ȼ�ģʽ
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
**����ԭ��		:  	INT32U		SetLOMMOD	 (eCANNUM CanNum)
**����˵��		:  	CanNum		-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**				:	Val			-->>    ֻ��ģʽѡ�� 0;������1:ֻ��
**����ֵ		:	��0����ʾ�ɹ�����CAN��ֻ��ģʽ�� ����0�����ɹ���	
**˵	��		:	��������������CANֻ��ģʽ(ֻ����RM �� 1ʱ�ſ�д��)
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
**����ԭ��		:  	void	CanSendCmd(eCANNUM CanNum,INT32U Cmd,INT32U TxBufNum)
**����˵��		:  	CanNum		-->> CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
					Cmd	-->> ����������:1--���η���,
									     2--�Է�����,
									     3--�����Է�����,
									     ����--��������
					TxBufNum	-->> ѡ���ͻ�����
**����ֵ		:		
**˵	��		:	���������ڷ��������(ֻд�Ĵ���)
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
			Temp.Bits.AT =1;						//���η���
			Temp.Bits.TR =1;
			break;
		case	2:
		case	3:									//�Է�����
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
			if(Cmd == 3)							//�����Է�����
			{
				Temp.Bits.AT =1;
			}
			break;
		case 	0:
		default:									//��������
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
**����ԭ��		:  	void	RelCanRecBuf (eCANNUM CanNum)
**����˵��		:  	CanNum		-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**����ֵ		:		
**˵	��		:	�����������ͷŽ��ջ�����
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
**����ԭ��		:  	ClrCanDataOver (eCANNUM CanNum)
**����˵��		:  	CanNum		-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**����ֵ		:		
**˵	��		:	��������������������
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
**����ԭ��		:  	INT32U 	CanEntrySM(CanNum)
**����˵��		:  	CanNum	-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**����ֵ		:	=0;�ɹ�����˯��״̬;
					!=0;���ܽ���˯��״̬;	
**˵	��		:	����������ʹCAN��������������ģʽ
***********************************************************************************************************
*/
INT32U	CanEntrySM(eCANNUM	CanNum)
{
	CANMOD(CanNum).Bits.SM = 1;	
	return(!CANMOD(CanNum).Bits.SM);
}
/*
***********************************************************************************************************
**����ԭ��		:  	INT32U CanQuitSM(eCANNUM	CanNum)
**����˵��		:  	CanNum		-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**����ֵ		:	=0;�ɹ��˳�˯��״̬;
					!=0;�����˳�˯��״̬;	
**˵	��		:	����������ʹCAN�������˳�����ģʽ
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
**����ԭ��	;	void AFSetMode(INT32U mode)
**����˵��	;	mode -->> ���չ��˿�������ģʽ
**							Bypass =  1
**							normal =  2
**							fullCAN = 3
**							Ignored = 4
**����ֵ	:	
**
**˵��		:	���տ��ƼĴ��������ú���						  
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
**����ԭ��	:	INT32U AFBuildLUT (INT32U FCAN_nCell,
**								   INT32U SFF_INDV_nCell,
**								   INT32U SFF_GRP_nCell,
**								   INT32U EFF_INDV_nCell,
**								   INT32U EFF_GRP_nCell)
**����˵��	:	FCAN_nCell_Num -->>	FullCAN��׼֡�˲���Ԫ����
**				SFF_INDV_nCell_Num -->>	������׼֡�˲���Ԫ����
**				SFF_GRP_nCell_Num -->>	��׼֡��Χ�˲���Ԫ����
**				EFF_INDV_nCell_Num -->> ������չ֡�˲���Ԫ����
**				EFF_GRP_nCell_Num -->>	��չ֡��Χ�˲���Ԫ����
**
**����ֵ	:   LUT_SETTING_OK 			= 0,
**				TOTAL_SIZE_TOO_LARGE 	= 1,
**				EFF_GRP_SIZE_INVALID	= 3,
**				FCAN_STORE_SIZE_INVALID = 4,
**
**˵��		:	���չ��˼Ĵ����ĳ�ʼ������
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
**����ԭ��	;	INT32U AFInitFCANTab(stcAF_SFF_CELL *pTab,INT32U nCell)
**����˵��	;	pTab -->>	FullCAN ��׼֡ID�ṹ����
**			:	nCell -->>	Cell�ĸ���
**
**����ֵ	:	LUT_SETTING_OK 	= 0,
**				TABLE_CELL_TOO_LARGE	= 5,
**
**˵��		:	FullCAN��׼֡���ĳ�ʼ��
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
**����ԭ��	;	INT32U AFInitSFFIndvTab(stcAF_SFF_CELL *pTab,INT32U nCell)
**����˵��	;	pTab -->>	��׼֡ID�ṹ����
**			:	nCell -->>	Cell�ĸ���
**
**����ֵ	:	LUT_SETTING_OK 	= 0,
**				TABLE_CELL_TOO_LARGE	= 5,
**
**˵��		:	������׼֡���ĳ�ʼ��
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
**����ԭ��	;	INT32U AFInitSFFGrpTab(_AF_SFF_CELL *pTab,UINT32 nCell)
**����˵��	;	pTab -->>	��׼֡ID�ṹ����
**			:	nCell -->>	Cell�ĸ���
**
**����ֵ	:	LUT_SETTING_OK 	= 0,
**				TABLE_CELL_TOO_LARGE	= 5,
**
**˵��		:	��׼֡��Χ���ĳ�ʼ��
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
**����ԭ��	;	INT32U AFInitEFFIndvTab(stcAF_EFF_CELL *pTab,INT32U nCell)
**����˵��	;	pTab -->>	��չ֡ID�ṹ����
**			:	nCell -->>	Cell�ĸ���
**
**����ֵ	:	LUT_SETTING_OK 	= 0,
**				TABLE_CELL_TOO_LARGE	= 5,
**
**˵��		:	������չ֡���ĳ�ʼ��
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
**����ԭ��	;	INT32U AFInitEFFGrpTab(stcAF_EFF_CELL *pTab,INT32U nCell)
**����˵��	;	pTab -->>	��չ֡ID�ṹ����
**			:	nCell -->>	Cell�ĸ���
**
**����ֵ	:	LUT_SETTING_OK 	= 0,
**				TABLE_CELL_TOO_LARGE	= 5,
**				CELL_NUM_INVALID		= 6,
**
**˵��		:	��չ֡��Χ���ĳ�ʼ��
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
**����ԭ��	;	INT32U AFReadFCANRxResurt(_AF_AUTOSTORE_MSG *pMsg,UINT32 IdIndex)
**����˵��	;	pMsg -->>	FullCAN���Զ��������Ϣ��ID�ṹ
**			:	nCell -->>	FullCAN�Զ�������Ϻ����ɵ�����		  
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
