/****************************************Copyright (c)**************************************************
**                               广州周立功单片机发展有限公司
**                                     研    究    所
**                                        产品一部 
**                                 http://www.zlgmcu.com
**-----------------------------------------------------------文件信息--------------------------------------------------------------------------------
**	文   件  	名:	CANAPP.C
** 	版  		本:	v1.0
** 	日		期:	2004年2月23日
**	描		述:	CAN模块应用接口函数说明文件。该文件中的函数，如果用户有特别的需要，可以进行修改。
********************************************************************************************************/
#define		_CANAPP_GLOBAL_
#include    "..\config.h"
#include	"IncludeCan.H"
/*
**************************************************************************************
**	定义并初始化验收过滤ID数组
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
**函数原型	:  	void	CANIntPrg(void)
**参数说明	:  	无
**返回值		:	无	
**说	明		:	CAN控制器中断处理函数
******************************************************************************************/
void __irq CANIntPrg(void)
{
	INT32U 	j;
	uCANICR k;
	if(_CANLUTerr.Word != 0 )	//验收滤波器遇到表格错误
	{
		//添加用户代码
		j=_CANLUTerrAd.Word;	
	}
	for(j=0;j<CAN_MAX_NUM;j++)
	{
		k=CANICR(j);
		if(k.Bits.RI != 0)		//接收中断
		{
			ReadCanRxBuf(j,&CANRcvCyBufApp[j]);
		}
		
		if(k.Bits.TI1 != 0)		//第一发送缓冲区发送完成中断
		{
		}
		
		if(k.Bits.TI2 != 0)		//第二发送缓冲区发送完成中断
		{
		}
		
		if(k.Bits.TI3 != 0)		//第三发送缓冲区发送完成中断
		{
		}
		
		if(k.Bits.BEI != 0)		//总线错误中断
		{
			//添加用户代码
			CanBufOffLinePrg(j);//总线关闭处理
		}
		
		if(k.Bits.ALI != 0)		//仲裁丢失中断
		{
		}
		
		if(k.Bits.EPI != 0)		//错误认可中断
		{
		}
		if(k.Bits.WUI != 0)		//唤醒中断
		{
		}
		if(k.Bits.DOI != 0)
		{
			//添加用户代码
			ClrCanDataOver(j);	//释放接收缓冲区
		}
	}
	VICVectAddr = 0;
}

/*
***********************************************************************************************************
**函数原型		:  	void	CANRxtoTxDataConvertion (void *desBuf, void *srcBuf )
**参数说明		:  	desBuf ->目的数据
					srcBuf  ->源数据
**返回值		:	
**说	明		:	
***********************************************************************************************************
*/
void	CANRxtoTxDataConvertion (stcTxBUF *desBuf,const  stcRxBUF *srcBuf )
{
	desBuf->TxFrameInfo.Bits.DLC = srcBuf->CANRcvFS.Bits.DLC;
	desBuf->TxFrameInfo.Bits.RTR = srcBuf->CANRcvFS.Bits.RTR;
	desBuf->TxFrameInfo.Bits.FF = srcBuf->CANRcvFS.Bits.FF;
	//读取帧ID
	desBuf->TxCANID.Bits.ID = srcBuf->RxCANID.Bits.ID;	
	//读取帧数据
	desBuf->TDA.Word = srcBuf->RDA.Word;
	desBuf->TDB.Word = srcBuf->RDB.Word;
}
/*
***********************************************************************************************************
**函数原型		:  	INT32U	WriteCanTxBuf(eCANNUM CanNum,INT32U TxBufNum,
										INT32U TPM,P_stcTxBUF Buf) ;
**参数说明		:  	CanNum		-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
					TxBufNum	-->>	选择发送缓冲区
					TPM			-->>	发送优先级模式
					Buf			-->>	发送到总线的数据
**返回值		:	=0;成功将数据写入发送缓冲区
					!=0;写发送缓冲区操作失败	
**说	明		:	本函数用于向CAN发送缓冲区TxBUF写入发送数据
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
		CANMOD(CanNum).Bits.TPM =1;	//发送优先级由帧的优先级域决定
}

/*
***********************************************************************************************************
**函数原型		:  	void	ReadCanRxBuf(eCANNUM CanNum,stcRcvCANCyBuf *RcvCyBuf)
**参数说明		:  	CanNum	-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**					RcvCyBuf-->>	目标环形缓冲区指针
**返回值		:		
**说	明		:	本函数用于驱动将收到的CAN数据写入环形缓冲区Buf->CANRcvFS 	=CANRFS(CanNum);
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
**函数原型	:  	INT32U	CANSendData(eCANNUM CanNum,INT32U Cmd,P_stcTxBUF Buf)
**参数说明	:  	CanNum	-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
				Cmd		-->	发送命令字
				Buf		-->	要发送的数据
**返回值		:	无	
**说	明		:	本函数用于将数据发送到CAN总线
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
**函数原型	:  	void	ConfigAFReg ()
**参数说明	:  	
**返回值		:		
**说	明		：	本函数用于配置验收过滤器
************************************************************************************************************
*/
void	ConfigAFReg (void)
{
	//配置验收过滤器
	#if AF_REG_ENABLE
	INT32U	state;
	//初始化表格地址	
	AFBuildLUT(0,SFF_INDV_nCell,SFF_GRP_nCell,EFF_INDV_nCell,EFF_GRP_nCell);
		/*初始化标准帧独立表格*/
		#if	SFF_INDV_nCell
			state = AFInitSFFIndvTab(sffIndvTab,sizeof(sffIndvTab)/sizeof(stcAF_SFF_CELL));
			/*添加用户代码*/
		#endif
		/*初始化标准帧范围表格*/
		#if SFF_GRP_nCell
			state = AFInitSFFGrpTab(sffGrpTab,sizeof(sffGrpTab)/sizeof(stcAF_SFF_CELL));
			/*添加用户代码*/
		#endif
		/*初始化扩展帧独立表格*/
		#if	EFF_INDV_nCell
			state = AFInitEFFIndvTab(effIndvTab,sizeof(effIndvTab)/sizeof(stcAF_EFF_CELL));
			/*添加用户代码*/
		#endif
		/*初始化扩展帧范围表格*/
		#if	EFF_GRP_nCell
			state = AFInitEFFGrpTab(effGrpTab,sizeof(effGrpTab)/sizeof(stcAF_EFF_CELL));
			/*添加用户代码*/
		#endif
		/*设置验收过滤模式*/
		AFSetMode(Normal);
	#else
		AFSetMode (Bypass);
	#endif
}
/*
***********************************************************************************************************
**函数原型	:  	void	InitCAN(eCANNUM CanNum)
**参数说明	:  	CanNum	-->>	CAN控制器，值不能大于CAN_MAX_NUM 规定的值
**返回值		:	无	
**说	明		：	本函数用于初始化CAN控制器
************************************************************************************************************/

void	InitCAN(eCANNUM CanNum)
{	
	/*硬件使能CAN控制器*/
	HwEnCAN(CanNum);
	/*软件复位CAN控制器	*/																								
	while (SoftRstCAN(CanNum));
	/*设置错误警告寄存器*/																
	while (SetErWarmVal (CanNum,USE_EWL_CAN[CanNum]));										
	//初始化波特率
	while (SetCANBaudRate (CanNum,USE_BTR_CAN[CanNum]));											
	/*初始化中断*/
	VICDefVectAddr=(INT32U)CANIntPrg;
	VICIntEnable |= (1 << 19) | ( 1 << (20+ CAN1)) | (1 << (26+ CAN1));
	CANIER(CanNum).Word= USE_INT_CAN[CanNum];												
	/*初始化模式*/
	while (SetTPMMOD(CanNum,USE_TPM_CAN[CanNum]));	//设置发送优先模式寄存器									
	while (SetLOMMOD(CanNum,USE_LOM_CAN[CanNum]));	//设置只听模式寄存器
	/********* 添加用其他初始化代码 ***********/
	CANRcvCyBufApp[CanNum].FullFlag = 0;			//初始化接收环形缓冲区
	CANRcvCyBufApp[CanNum].ReadPoint = 0;
	CANRcvCyBufApp[CanNum].WritePoint = 0;
	/*软件启动CAN*/
	SoftEnCAN(CanNum);
}


/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
