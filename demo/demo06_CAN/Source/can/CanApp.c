/****************************************Copyright (c)**************************************************
**                               ������������Ƭ����չ���޹�˾
**                                     ��    ��    ��
**                                        ��Ʒһ�� 
**                                 http://www.zlgmcu.com
**-----------------------------------------------------------�ļ���Ϣ--------------------------------------------------------------------------------
**	��   ��  	��:	CANAPP.C
** 	��  		��:	v1.0
** 	��		��:	2004��2��23��
**	��		��:	CANģ��Ӧ�ýӿں���˵���ļ������ļ��еĺ���������û����ر����Ҫ�����Խ����޸ġ�
********************************************************************************************************/
#define		_CANAPP_GLOBAL_
#include    "..\config.h"
#include	"IncludeCan.H"
/*
**************************************************************************************
**	���岢��ʼ�����չ���ID����
**************************************************************************************
*/
#if AF_REG_ENABLE
	#if SFF_INDV_nCell
	stcAF_SFF_CELL	sffIndvTab[] = {};
	#endif
	
	#if SFF_GRP_nCell			   
	stcAF_SFF_CELL 	sffGrpTab[] = {};
	#endif
	
	#if EFF_INDV_nCell
	stcAF_EFF_CELL	effIndvTab[]= {};
	#endif
	
	#if EFF_GRP_nCell
	stcAF_EFF_CELL	effGrpTab[] = {};
	#endif
#endif
/*
********************************************************************************************
**����ԭ��	:  	void	CANIntPrg(void)
**����˵��	:  	��
**����ֵ		:	��	
**˵	��		:	CAN�������жϴ�����
******************************************************************************************/
void __irq CANIntPrg(void)
{
	INT32U 	j;
	uCANICR k;
	if(_CANLUTerr.Word != 0 )	//�����˲�������������
	{
		//����û�����
		j=_CANLUTerrAd.Word;	
	}
	for(j=0;j<CAN_MAX_NUM;j++)
	{
		k=CANICR(j);
		if(k.Bits.RI != 0)		//�����ж�
		{
			ReadCanRxBuf(j,&CANRcvCyBufApp[j]);
		}
		
		if(k.Bits.TI1 != 0)		//��һ���ͻ�������������ж�
		{
		}
		
		if(k.Bits.TI2 != 0)		//�ڶ����ͻ�������������ж�
		{
		}
		
		if(k.Bits.TI3 != 0)		//�������ͻ�������������ж�
		{
		}
		
		if(k.Bits.BEI != 0)		//���ߴ����ж�
		{
			//����û�����
			CanBufOffLinePrg(j);//���߹رմ���
		}
		
		if(k.Bits.ALI != 0)		//�ٲö�ʧ�ж�
		{
		}
		
		if(k.Bits.EPI != 0)		//�����Ͽ��ж�
		{
		}
		if(k.Bits.WUI != 0)		//�����ж�
		{
		}
		if(k.Bits.DOI != 0)
		{
			//����û�����
			ClrCanDataOver(j);	//�ͷŽ��ջ�����
		}
	}
	VICVectAddr = 0;
}

/*
***********************************************************************************************************
**����ԭ��		:  	void	CANRxtoTxDataConvertion (void *desBuf, void *srcBuf )
**����˵��		:  	desBuf ->Ŀ������
					srcBuf  ->Դ����
**����ֵ		:	
**˵	��		:	
***********************************************************************************************************
*/
void	CANRxtoTxDataConvertion (stcTxBUF *desBuf,const  stcRxBUF *srcBuf )
{
	desBuf->TxFrameInfo.Bits.DLC = srcBuf->CANRcvFS.Bits.DLC;
	desBuf->TxFrameInfo.Bits.RTR = srcBuf->CANRcvFS.Bits.RTR;
	desBuf->TxFrameInfo.Bits.FF = srcBuf->CANRcvFS.Bits.FF;
	//��ȡ֡ID
	desBuf->TxCANID.Bits.ID = srcBuf->RxCANID.Bits.ID;	
	//��ȡ֡����
	desBuf->TDA.Word = srcBuf->RDA.Word;
	desBuf->TDB.Word = srcBuf->RDB.Word;
}
/*
***********************************************************************************************************
**����ԭ��		:  	INT32U	WriteCanTxBuf(eCANNUM CanNum,INT32U TxBufNum,
										INT32U TPM,P_stcTxBUF Buf) ;
**����˵��		:  	CanNum		-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
					TxBufNum	-->>	ѡ���ͻ�����
					TPM			-->>	�������ȼ�ģʽ
					Buf			-->>	���͵����ߵ�����
**����ֵ		:	=0;�ɹ�������д�뷢�ͻ�����
					!=0;д���ͻ���������ʧ��	
**˵	��		:	������������CAN���ͻ�����TxBUFд�뷢������
***********************************************************************************************************
*/

void	WriteCanTxBuf(eCANNUM CanNum,INT32U TxBufNum,INT32U TPM,stcTxBUF *Buf)
{
		INT32U	status=0;
		status = status;
		switch(TxBufNum)
		{
			case	TX_BUF1:
				TxBUF1(CanNum) = *Buf;
				break;
			case	TX_BUF2:
				TxBUF2(CanNum) = *Buf;
				break;
			case	TX_BUF3:
				TxBUF3(CanNum) = *Buf;
				break;
			default:
				status = 0x01;
				break;
		}
	if(TPM == 1)
		CANMOD(CanNum).Bits.TPM =1;	//�������ȼ���֡�����ȼ������
}

/*
***********************************************************************************************************
**����ԭ��		:  	void	ReadCanRxBuf(eCANNUM CanNum,stcRcvCANCyBuf *RcvCyBuf)
**����˵��		:  	CanNum	-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**					RcvCyBuf-->>	Ŀ�껷�λ�����ָ��
**����ֵ		:		
**˵	��		:	�����������������յ���CAN����д�뻷�λ�����Buf->CANRcvFS 	=CANRFS(CanNum);
************************************************************************************************************/
INT32U	ReadCanRxBuf(eCANNUM CanNum,stcRcvCANCyBuf *RcvCyBuf)
{
	INT32U	PointTemp = 0;
	INT32U	Statue = 0;
	PointTemp = RcvCyBuf->WritePoint;
	if((0 == RcvCyBuf->FullFlag))
	{
		RcvCyBuf->RcvBuf[PointTemp].CANRcvFS = RxBUF(CanNum).CANRcvFS;
		RcvCyBuf->RcvBuf[PointTemp].RxCANID = RxBUF(CanNum).RxCANID;
		RcvCyBuf->RcvBuf[PointTemp].RDA = RxBUF(CanNum).RDA;
		RcvCyBuf->RcvBuf[PointTemp].RDB = RxBUF(CanNum).RDB;
		if(++RcvCyBuf->WritePoint >= USE_CAN_cycRCV_BUF_SIZE)
			RcvCyBuf->WritePoint=0;
		if(RcvCyBuf->WritePoint == RcvCyBuf->ReadPoint)
			RcvCyBuf->FullFlag =1;
	}
	else
		Statue = 1;
	RelCanRecBuf(CanNum);
	return Statue;
}

/*
***********************************************************************************************************
**����ԭ��	:  	INT32U	CANSendData(eCANNUM CanNum,INT32U Cmd,P_stcTxBUF Buf)
**����˵��	:  	CanNum	-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
				Cmd		-->	����������
				Buf		-->	Ҫ���͵�����
**����ֵ		:	��	
**˵	��		:	���������ڽ����ݷ��͵�CAN����
************************************************************************************************************/
INT32U		CANSendData(eCANNUM CanNum,INT32U Cmd, stcRxBUF *RxBuf)
{
	INT32U TxBufNum,status =0;
	stcTxBUF	TxBuf ;
	if((0== CANSR(CanNum).Bits.TS1)&&(0 != CANSR(CanNum).Bits.TBS1))
	{
		TxBufNum=TX_BUF1;
	}
	else if((0== CANSR(CanNum).Bits.TS2)&&(0 != CANSR(CanNum).Bits.TBS2))
	{
		TxBufNum=TX_BUF2;
	}
	else if((0== CANSR(CanNum).Bits.TS3)&&(0 != CANSR(CanNum).Bits.TBS3))
	{
		TxBufNum=TX_BUF3;
	}
	else
	{
		TxBufNum=0xFF;
		status = 1;
	}
	if (0xFF != TxBufNum)
	{
		CANRxtoTxDataConvertion (&TxBuf, RxBuf);
		WriteCanTxBuf(CanNum, TxBufNum ,  USE_TPM_CAN[CanNum], & TxBuf);
		CanSendCmd(CanNum,Cmd,TxBufNum);
		status = 0;
	}
	return status;
}
/*
***********************************************************************************************************
**����ԭ��	:  	void	ConfigAFReg ()
**����˵��	:  	
**����ֵ		:		
**˵	��		��	�����������������չ�����
************************************************************************************************************
*/
void	ConfigAFReg (void)
{
	//�������չ�����
	#if AF_REG_ENABLE
	INT32U	state;
	//��ʼ������ַ	
	AFBuildLUT(0,SFF_INDV_nCell,SFF_GRP_nCell,EFF_INDV_nCell,EFF_GRP_nCell);
		/*��ʼ����׼֡�������*/
		#if	SFF_INDV_nCell
			state = AFInitSFFIndvTab(sffIndvTab,sizeof(sffIndvTab)/sizeof(stcAF_SFF_CELL));
			/*����û�����*/
		#endif
		/*��ʼ����׼֡��Χ���*/
		#if SFF_GRP_nCell
			state = AFInitSFFGrpTab(sffGrpTab,sizeof(sffGrpTab)/sizeof(stcAF_SFF_CELL));
			/*����û�����*/
		#endif
		/*��ʼ����չ֡�������*/
		#if	EFF_INDV_nCell
			state = AFInitEFFIndvTab(effIndvTab,sizeof(effIndvTab)/sizeof(stcAF_EFF_CELL));
			/*����û�����*/
		#endif
		/*��ʼ����չ֡��Χ���*/
		#if	EFF_GRP_nCell
			state = AFInitEFFGrpTab(effGrpTab,sizeof(effGrpTab)/sizeof(stcAF_EFF_CELL));
			/*����û�����*/
		#endif
		/*�������չ���ģʽ*/
		AFSetMode(Normal);
	#else
		AFSetMode (Bypass);
	#endif
}
/*
***********************************************************************************************************
**����ԭ��	:  	void	InitCAN(eCANNUM CanNum)
**����˵��	:  	CanNum	-->>	CAN��������ֵ���ܴ���CAN_MAX_NUM �涨��ֵ
**����ֵ		:	��	
**˵	��		��	���������ڳ�ʼ��CAN������
************************************************************************************************************/

void	InitCAN(eCANNUM CanNum)
{	
	/*Ӳ��ʹ��CAN������*/
	HwEnCAN(CanNum);
	/*�����λCAN������	*/																								
	while (SoftRstCAN(CanNum));
	/*���ô��󾯸�Ĵ���*/																
	while (SetErWarmVal (CanNum,USE_EWL_CAN[CanNum]));										
	//��ʼ��������
	while (SetCANBaudRate (CanNum,USE_BTR_CAN[CanNum]));											
	/*��ʼ���ж�*/
	VICDefVectAddr=(INT32U)CANIntPrg;
	VICIntEnable |= (1 << 19) | ( 1 << (20+ CAN1)) | (1 << (26+ CAN1));
	CANIER(CanNum).Word= USE_INT_CAN[CanNum];												
	/*��ʼ��ģʽ*/
	while (SetTPMMOD(CanNum,USE_TPM_CAN[CanNum]));	//���÷�������ģʽ�Ĵ���									
	while (SetLOMMOD(CanNum,USE_LOM_CAN[CanNum]));	//����ֻ��ģʽ�Ĵ���
	/********* �����������ʼ������ ***********/
	CANRcvCyBufApp[CanNum].FullFlag = 0;			//��ʼ�����ջ��λ�����
	CANRcvCyBufApp[CanNum].ReadPoint = 0;
	CANRcvCyBufApp[CanNum].WritePoint = 0;
	/*�������CAN*/
	SoftEnCAN(CanNum);
}


/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
