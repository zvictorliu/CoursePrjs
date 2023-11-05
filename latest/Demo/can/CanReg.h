/****************************************Copyright (c)**************************************************
**                               广州周立功单片机发展有限公司
**                                     研    究    所
**                                        产品一部 
**                                 http://www.zlgmcu.com
**-------------------------------------文件信息--------------------------------------------------------
**	文   件  	名:	CANREG.H
** 	版  		本:	v1.0
** 	日		期:	2004年2月23日
**	描		述:	CAN模块寄存器类型定义、地址定义头文件
********************************************************************************************************/
#ifndef	_CANREG_H_
#define	_CANREG_H_
/*
**********************************************************************************************************************
**   验收滤波器RAM首地址
**********************************************************************************************************************
*/
#define	CANAFRAM_BADR				0xE0038000
/*
**********************************************************************************************************************
**  CAN寄存器基地址定义
**********************************************************************************************************************
*/
#define 	CANMOD_BADR				0xE0044000     		//模式寄存器
#define 	CANCMR_BADR				0xE0044004      	//命令寄存器
#define 	CANGSR_BADR				0xE0044008      	//全局状态寄存器
#define 	CANICR_BADR				0xE004400C     		//中断及捕获寄存器
#define 	CANIER_BADR				0xE0044010      	//中断使能寄存器
#define 	CANBTR_BADR				0xE0044014      	//总线时序寄存器
#define 	CANEWL_BADR				0xE0044018      	//报警限制寄存器
#define 	CANSR_BADR  			0xE004401C      	//状态寄存器
#define 	CANRFS_BADR				0xE0044020      	//接收帧信息寄存器
#define		CANRID_BADR				0xE0044024      	//接收报文ID寄存器

#define 	CANRDA_BADR				0xE0044028      	//接收数据1~4
#define 	CANRDB_BADR 			0xE004402C      	//接收数据5～8
#define 	CANTFI1_BADR			0xE0044030      	//CAN发送缓冲区1帧信息寄存器
#define 	CANTID1_BADR			0xE0044034      	// CAN发送缓冲区1报文ID寄存器
#define 	CANTDA1_BADR			0xE0044038      	// CAN发送缓冲区1发送数据1～4寄存器
#define 	CANTDB1_BADR			0xE004403C      	// CAN发送缓冲区1发送数据5～8寄存器
#define 	CANTFI2_BADR			0xE0044040      	// CAN发送缓冲区2帧信息寄存器
#define 	CANTID2_BADR			0xE0044044      	// CAN发送缓冲区2报文ID寄存器
#define 	CANTDA2_BADR			0xE0044048     		// CAN发送缓冲区2发送数据1～4寄存器
#define 	CANTDB2_BADR			0xE004404C      	// CAN发送缓冲区2发送数据5～8寄存器
#define 	CANTFI3_BADR			0xE0044050      	// CAN发送缓冲区3帧信息寄存器
#define 	CANTID3_BADR			0xE0044054      	// CAN发送缓冲区3报文ID寄存器
#define 	CANTDA3_BADR			0xE0044058      	// CAN发送缓冲区3发送数据1～4寄存器
#define 	CANTDB3_BADR			0xE004405C      	// CAN发送缓冲区3发送数据5～8寄存器
/*
**********************************************************************************************************************
**  定义RxBUF的基地址
**********************************************************************************************************************
*/
#define	RxBUF_BADR					0xE0044020
/*
**********************************************************************************************************************
**  定义TxBUF的基地址
**********************************************************************************************************************
*/
#define	TxBUF1_BADR					0xE0044030			// CAN发送缓冲区1首地址
#define	TxBUF2_BADR					0xE0044040			// CAN发送缓冲区2首地址
#define	TxBUF3_BADR					0xE0044050			// CAN发送缓冲区3首地址
/*
**********************************************************************************************************************
**  定义全局应用的寄存器
**********************************************************************************************************************
*/
#define 	CANTxSR_GADR   			0xE0040000      	//发送状态寄存器
#define 	CANRxSR_GADR      		0xE0040004      	//接收状态寄存器
#define 	CANMSR_GADR       		0xE0040008      	//错误状态寄存器
#define 	CANAFMR_GADR      		0xE003C000      	//验收滤波控制
#define 	CANSFF_sa_GADR      	0xE003C004      	//标准帧表格
#define 	CANSFF_GRP_sa_GADR 		0xE003C008      	//标准帧组表格
#define 	CANEFF_sa_GADR      	0xE003C00C      	//扩展帧表格
#define 	CANEFF_GRP_sa_GADR 		0xE003C010      	//扩展帧组表格
#define 	CANENDofTable_GADR  	0xE003C014      	//表格结束地址
#define 	CANLUTerrAd_GADR   		0xE003C018      	//LUT错误地址地址寄存器
#define 	CANLUTerr_GADR      	0xE003C01C			//LUT错误寄存器
/*
**********************************************************************************************************************
**  CAN控制器通道定义
**********************************************************************************************************************
*/
typedef 	enum		_cannum_				
{ 
#if		CAN_MAX_NUM  == 4			//微处理器中含有4路CAN
	CAN1 = 0, 						//CAN1模块
	CAN2,							//CAN2模块
	CAN3,							//CAN3模块
	CAN4							//CAN4模块
#elif	CAN_MAX_NUM  == 2			//微处理器中含有2路CAN
	CAN1 = 0, 						//CAN1模块
	CAN2							//CAN2模块
#endif
} eCANNUM;		

//#define REGAFRAM         (*((volatile INT32U *) 0xE0038000))      /* lpc2119\lpc2129\lpc2292\lpc2294 only */

/*
*********************************************************************************************************************
**   定义 CANMOD 寄存器:
1.This register controls the basic operating mode of the CAN Controller. 
2.Bits not listed read as 0 and should be written as 0.
*********************************************************************************************************************
*/
typedef	union		_canmod_
{
	INT32U	Word;
	struct	{
		INT32U	RM 		:1;		//定义RM位(复位位)
		INT32U	LOM 	:1;		//定义LOM位(只听模式位)
		
		INT32U	STM		:1;		//定义STM位 "0"发送的信息必须被应答才被认可
									//			"1"自测试模式,CANCMR的SRR位一起使用，可以达到自发自收的效果
									
		INT32U	TPM 	:1;		//定义TPM位 "0"3个发送缓冲区的优先级由各自的CAN ID决定
									//			"1"3个发送缓冲区的优先级由各自的Tx优先级域决定
									
		INT32U	SM 		:1;		//定义SM位(睡眠模式位)
		
		INT32U	RPM 	:1;		//定义RPM位 "0"如果传输的是显性位，Rx和Tx脚为低电平
									//			"1"翻转极性模式--如果传输的是显性位，Rx脚为高电平
									
		INT32U	RSV1 	:1;		//保留位
		INT32U	TM 		:1;		//定义TM位(测试模式)
		INT32U	RSV24	:24;	//保留位
	}Bits;
}uCANMod,*P_uCANMod;

#define 	CANMOD(CanNum)		(*((volatile P_uCANMod)(CANMOD_BADR+CanNum* CAN_OFFSET_ADR)))

/*
**********************************************************************************************************************
**   定义 CANCMR 寄存器:
1.Writing to this write-only register initiates an action. 
2.Bits not listed should be written as 0. Reading this register yields zeroes.
**********************************************************************************************************************
*/
typedef	union		_cancmr_
{
	INT32U	Word;
	struct	
	{
		INT32U	TR 		:1;		//定义TR位(发送请求)
		INT32U	AT 		:1;		//定义AT位(发送中止)
		INT32U	RRB 	:1;		//定义RRB位(接收缓冲区释放)
		INT32U	CDO 	:1;		//清除数据溢出位
		INT32U	SRR 	:1;		//定义SRR位(自接收请求)
		INT32U	STB1 	:1;		//定义SEND TxBUF1位(选择BUF1发送)
		INT32U	STB2 	:1;		//定义SEND TxBUF2位(选择BUF2发送)
		INT32U	STB3 	:1;		//定义SEND TxBUF3位(选择BUF3发送)
		INT32U	RSV24	:24;	//保留位
	}Bits;
}uCANCMR,*P_uCANCMR;

#define 	CANCMR(CanNum)		(*((volatile P_uCANCMR)(CANCMR_BADR+CanNum* CAN_OFFSET_ADR )))
/*
************************************************************************************************************************
**   定义 CANGSR 寄存器:
1.This register is read-only, except that the Error Counters can be written when the RM bit in the CANMOD register is 1.
2.Bits not listed read as 0 and should be written as 0.
************************************************************************************************************************
*/
typedef	union		_cangsr_
{
	INT32U	Word;				//字操作定义
	struct	
	{
		INT32U	RBS 	:1;	//接收缓冲区状态位
		INT32U	DOS 	:1; //数据溢出状态位
		INT32U	TBS 	:1;	//发送缓冲区状态锁定位
		INT32U	TCS 	:1;	//发送完成状态位
		INT32U	RS 		:1;	//正在接收状态
		INT32U	TS 		:1;	//正在发送状态
		INT32U	ES	 	:1;	//错误状态
		INT32U	BS 		:1;	//总线关闭
		INT32U	RSV8	:8;	//保留位
		INT32U	RXERR 	:8;	//接收错误计数
		INT32U	TXERR 	:8;	//发送错误计数
	}Bits;
}uCANGSR,*P_uCANGSR;

#define 	CANGSR(CanNum)		(*((volatile P_uCANGSR)( CANGSR_BADR+CanNum* CAN_OFFSET_ADR ))) 
/*
**********************************************************************************************************************
**   定义 CANICR 寄存器:
1.Bits in this register indicate information about events on the CAN bus. This register is read-only.
2.Bits not listed read as 0 and should be written as 0.
3.The clearing of bits 1-9 and the releasing of bits 16-23 and 24-31 all occur on any read from CANICR,
  regardless of whether part or all of the register is read.This means that software should always read CANICR as a word,
  and and process and deal with all bits of the register as appropriate for the application.
**********************************************************************************************************************
*/
typedef	union		_canicr_
{
	INT32U	Word;				//字操作定义
	struct	
	{
		INT32U	RI 		:1;	//接收中断位
		INT32U	TI1 	:1;	//TxBUF1发送成功中断位
		INT32U	EI 		:1;	//错误报警中断位
		INT32U	DOI 	:1;	//数据溢出中断位
		INT32U	WUI 	:1;	//睡眠唤醒中断位
		INT32U	EPI 	:1;	//错误认可中断位
		INT32U	ALI 	:1;	//仲裁错误中断位
		INT32U	BEI 	:1;	//总线错误中断
		INT32U	IDI 	:1;	//接收到CAN标识符中断位
		INT32U	TI2 	:1;	// TxBUF2发送成功中断位
		INT32U	TI3 	:1;	// TxBUF3发送成功中断位
		INT32U	RSV5	:5;	//保留位
		INT32U	ERRBIT 	:5;	//错误代码捕获
		INT32U	ERRDIR 	:1;	//错误方向
		INT32U	ERRC 	:2;	//错误类型
		INT32U	ALCBIT 	:5;	//仲裁错误代码捕获
		INT32U	RSV3	:3;	//保留
	}Bits;
}uCANICR,*P_uCANICR;

#define 	CANICR(CanNum)		(*((volatile P_uCANICR)( CANICR_BADR+CanNum* CAN_OFFSET_ADR ))) 
/*
**********************************************************************************************************************
**   定义 CANIER 寄存器:
1.This read/write register controls whether various events on the CAN controller will result in an interrupt.
2.Bits 7:0 in this register correspond 1-to-1 with bits 7:0 in the CANICR register.
**********************************************************************************************************************
*/
typedef	union		_canier_
{
	INT32U	Word;			//字操作定义
	struct	
	{
		INT32U	RIE 	:1;	//接收中断使能位
		INT32U	TIE1 	:1;	//TxBUF1发送完成中断使能位
		INT32U	EIE 	:1;	//错误报警中断使能位
		INT32U	DOIE 	:1;	//数据溢出中断使能位
		INT32U	WUIE 	:1;	//睡眠模式唤醒中断使能位
		INT32U	EPIE 	:1;	//错误认可中断使能位
		INT32U	ALIE 	:1;	//仲裁丢失中断使能位
		INT32U	BEIE 	:1;	//总线错误中断使能位
		INT32U	IDIE	:1;	//接收到CAN标识符中断使能位
		INT32U	TIE2 	:1;	//TxBUF2发送完成中断使能位
		INT32U	TIE3	:1;	//TxBUF3发送完成中断使能位
		INT32U	RSV21	:21;//保留位
	}Bits;
}uCANIER,*P_uCANIER;

#define 	CANIER(CanNum)		(*((volatile P_uCANIER)( CANIER_BADR+CanNum* CAN_OFFSET_ADR )))
/*
**********************************************************************************************************************
**   定义 CANBTR 寄存器:
1.This register controls how various CAN timings are derived from the VPB clock.
2.It can be read at any time, but can only be written if the RM bit in CANmod is 1.
**********************************************************************************************************************
*/
typedef	union		_canbtr_
{
	INT32U	Word;					//字操作定义
	struct	
	{
		INT32U	BRP 	:10;	//预分频位组合定义
		INT32U	RSV4	:4;		//保留位
		INT32U	SJW 	:2;		//同步跳转宽度
		INT32U	TSEG1 	:4;		//时间段1
		INT32U	TSEG2 	:3;		//时间段2
		INT32U	SAM 	:1;		//采样模式位
		INT32U	RSV8	:8;		//保留
	}Bits;
}uCANBTR,*P_uCANBTR;

#define 	CANBTR(CanNum)		(*((volatile P_uCANBTR)( CANBTR_BADR+CanNum* CAN_OFFSET_ADR )))
/*
**********************************************************************************************************************
**   定义 CANEWL 寄存器:
1.This register sets a limit on Tx or Rx errors at which an interrupt can occur.
2.It can be read at any time, but can only be written if the RM bit in CANmod is 1.
**********************************************************************************************************************
*/
typedef	union	_canewl_
{
	INT32U	Word;					//字操作定义
	struct	
	{
		INT32U	EWL 	:8;		///出错警告界限值
		INT32U	RSV24	:24;	//保留位
	}Bits;
}uCANEWL,*P_uCANEWL;

#define 	CANEWL(CanNum)		(*((volatile P_uCANEWL)( CANEWL_BADR+CanNum* CAN_OFFSET_ADR )))
/*
**********************************************************************************************************************
**   定义 CANSR 寄存器:
1.This register contains three status bytes, in which the bits not related to tranmission are identical to the 
  corresponding bits in the Global Status Register, while those relating to transmission reflect the status of 
  each of the 3 Tx Buffers.
**********************************************************************************************************************
*/
typedef	union	_cansr_
{
	INT32U	Word;					//字操作定义
	struct	
	{
		INT32U	RBS1 	:1;		//接收缓冲区有效
		INT32U	DOS1 	:1;		//数据溢出
		INT32U	TBS1 	:1;		//TxBUF1锁定位  "0":锁定
		INT32U	TCS1 	:1;		//TxBUF1的数据发送完成 
		INT32U	RS1 	:1;		//正在接收
		INT32U	TS1 	:1;		//TxBUF1的数据正在发送 "1"正在发送
		INT32U	ES1 	:1;		//错误认可
		INT32U	BS1 	:1;		//总线错误
		INT32U	RBS2 	:1;		//
		INT32U	DOS2 	:1;		//
		INT32U	TBS2 	:1;		// TxBUF2锁定
		INT32U	TCS2 	:1;		// TxBUF2的数据发送完成
		INT32U	RS2 	:1;		//
		INT32U	TS2 	:1;		// TxBUF2的数据正在发送
		INT32U	ES2 	:1;		//
		INT32U	BS2 	:1;		//
		INT32U	RBS3 	:1;		//
		INT32U	DOS3 	:1;		//
		INT32U	TBS3 	:1;		// TxBUF3锁定
		INT32U	TCS3 	:1;		// TxBUF3的数据发送完成
		INT32U	RS3 	:1;		//
		INT32U	TS3 	:1;		// TxBUF3的数据正在发送
		INT32U	ES3 	:1;		//
		INT32U	BS3 	:1;		//
		INT32U	RSV8	:8;		//
	}Bits;
}uCANSR,*P_uCANSR;

#define 	CANSR(CanNum)		(*((volatile P_uCANSR)( CANSR_BADR+CanNum* CAN_OFFSET_ADR )))
/*
**********************************************************************************************************************
**   定义 CANRFS 寄存器:
1.This register defines the characteristics of the current received message. 
2.It is read-only in normal operation, but can be written for testing purposes if the RM bit in CANMOD is 1.
**********************************************************************************************************************
*/
typedef	union		_canrfs_
{
	INT32U		Word;				//字操作定义
	struct	
	{
		INT32U	IDIN 	:10;	//ID索引值
		INT32U	BP 		:1;		//BP
		INT32U	RSV5 	:5;		//保留
		INT32U	DLC 	:4;		//数据长度
		INT32U	RSV10	:10;	//保留
		INT32U	RTR 	:1;		//远程帧、数据帧识别位
		INT32U	FF 		:1;		//扩展帧、标准帧识别位
	}Bits;
}uCANRFS,*P_uCANRFS;

#define 	CANRFS(CanNum)		(*((volatile P_uCANRFS)( CANRFS_BADR+CanNum* CAN_OFFSET_ADR )))
/*
**********************************************************************************************************************
**   定义 CANRID 寄存器:
1.This register contains the Identifier field of the current received message. 
2.It is read-only in normal operation, but can be written for testing purposes if the RM bit in CANmod is 1.
3.It has two different formats depending on the FF bit in CANRFS.	FF=0 (11 Bits  10:0)
																	FF=1 (29 Bits  28:0)	
**********************************************************************************************************************
*/
typedef	union		_canrid_
{
	INT32U		Word;					//字操作定义
	struct
	{
		INT32U	ID 		:29;
		INT32U	RSV3 	:3;
	}Bits;
}uCANRID,*P_uCANRID;

#define 	CANRID(CanNum)		(*((volatile P_uCANRID)(CANRID_BADR+CanNum* CAN_OFFSET_ADR)))
#define		CANTID1(CanNum)		(*((volatile P_uCANRID)(CANTID1_BADR+CanNum*CAN_OFFSET_ADR)))
#define		CANTID2(CanNum)		(*((volatile P_uCANRID)(CANTID2_BADR+CanNum*CAN_OFFSET_ADR)))
#define		CANTID3(CanNum)		(*((volatile P_uCANRID)(CANTID3_BADR+CanNum*CAN_OFFSET_ADR)))
/*
**********************************************************************************************************************
**   定义 CANRDx 寄存器:
1.This register contains the Data bytes of the current received message. 
2.It is read-only in normal operation, but can be written for testing purposes if the RM bit in CANMOD is 1.
**********************************************************************************************************************
*/
typedef	union		_canrdx_
{
	INT32U		Word;					//字操作定义
	struct	
	{
		INT32U	Data1 	:8;			//数据字节
		INT32U	Data2 	:8;	
		INT32U	Data3 	:8;	
		INT32U	Data4 	:8;	
	}Bits;
}uCANRDx,*P_uCANRDx;

#define 	CANRDA(CanNum)		(*((volatile P_uCANRDx)(CANRDA_BADR+CanNum* CAN_OFFSET_ADR)))	//1-4 Data bytes
#define 	CANRDB(CanNum)		(*((volatile P_uCANRDx)(CANRDB_BADR+CanNum* CAN_OFFSET_ADR)))	//5-8 Data bytes
#define		CANTDA1(CanNum)		(*((volatile P_uCANRDx)(CANTDA1_BADR+CanNum*CAN_OFFSET_ADR)))   
#define		CANTDB1(CanNum)		(*((volatile P_uCANRDx)(CANTDB1_BADR+CanNum*CAN_OFFSET_ADR)))
#define		CANTDA2(CanNum)		(*((volatile P_uCANRDx)(CANTDA2_BADR+CanNum*CAN_OFFSET_ADR)))
#define		CANTDB2(CanNum)		(*((volatile P_uCANRDx)(CANTDB2_BADR+CanNum*CAN_OFFSET_ADR)))
#define		CANTDA3(CanNum)		(*((volatile P_uCANRDx)(CANTDA3_BADR+CanNum*CAN_OFFSET_ADR))) 
#define		CANTDB3(CanNum)		(*((volatile P_uCANRDx)(CANTDB3_BADR+CanNum*CAN_OFFSET_ADR)))

/*
**********************************************************************************************************************
**   定义 CANTFIx 寄存器:
1.When the corresponding TBS bit in CANSR is 1, software can write to one of these registers to define the format of 
  the next transmit message for that Tx buffer.
2.Bits not listed read as 0 and should be written as 0.
**********************************************************************************************************************
*/
typedef	union		_cantfix_
{
	INT32U		Word;				//字节操作定义
	struct	
	{
		INT32U	PRIO 	:8;		//缓冲区数据发送优先级的值
		INT32U	RSV8	:8;						
		INT32U	DLC 	:4;		//发送数据长度
		INT32U	RSV10	:10;
		INT32U	RTR 	:1;		//远程帧、数据帧辨别位
		INT32U	FF 		:1;		//扩展帧、标准帧辨别位
	}Bits;
}uCANTFIx,*P_uCANTFIx;

#define CANTFI1(CanNum)		(*((volatile P_uCANTFIx)(CANTFI1_BADR+CanNum*CAN_OFFSET_ADR)))
#define CANTFI2(CanNum)		(*((volatile P_uCANTFIx)(CANTFI2_BADR+CanNum*CAN_OFFSET_ADR)))
#define CANTFI3(CanNum)		(*((volatile P_uCANTFIx)(CANTFI3_BADR+CanNum*CAN_OFFSET_ADR)))
/*
**********************************************************************************************************************
**   定义发送帧的结构
**********************************************************************************************************************
*/
typedef	struct		_stcTXBUF_
{
	uCANTFIx		TxFrameInfo;	//发送帧信息结构
	uCANRID			TxCANID;		//发送帧信息ID
	uCANRDx		TDA;			//发送数据1～4字节
	uCANRDx		TDB;			//发送数据5～8字节
}*P_stcTxBUF,stcTxBUF;

#define	TxBUF1(CanNum)		(*((volatile P_stcTxBUF)( TxBUF1_BADR+CanNum*CAN_OFFSET_ADR)))
#define	TxBUF2(CanNum)		(*((volatile P_stcTxBUF)( TxBUF2_BADR+CanNum*CAN_OFFSET_ADR)))
#define	TxBUF3(CanNum)		(*((volatile P_stcTxBUF)( TxBUF3_BADR+CanNum*CAN_OFFSET_ADR)))
/*
**********************************************************************************************************************
**   定义 CANTxSR 寄存器:
**********************************************************************************************************************
*/
typedef	union		_uCANTxSR_
{
	INT32U		Word;				//字操作定义
	struct	
	{
		INT32U	TS1 	:1;		//CAN1正在发送状态
		INT32U	TS2 	:1;		//CAN2正在发送状态
		INT32U	TS3 	:1;		//CAN3正在发送状态
		INT32U	TS4 	:1;		//CAN4正在发送状态
		INT32U	RSV1	:4;		//保留
		INT32U	TBS1 	:1;		//CAN1发送缓冲区锁定状态
		INT32U	TBS2 	:1;		//CAN2发送缓冲区锁定状态
		INT32U	TBS3 	:1;		//CAN3发送缓冲区锁定状态
		INT32U	TBS4 	:1;		//CAN4发送缓冲区锁定状态
		INT32U	RSV2 	:4;		// 
		INT32U	TCS1 	:1;		//CAN1发送完成状态
		INT32U	TCS2 	:1;		//CAN2发送完成状态
		INT32U	TCS3 	:1;		//CAN3发送完成状态
		INT32U	TCS4 	:1;		//CAN4发送完成状态
		INT32U	RSV12	:12;	//保留
	}Bits;
}*P_uCANTxSR,uCANTxSR;

#define 	_CANTxSR				(*((volatile P_uCANTxSR) CANTxSR_GADR))
/*
**********************************************************************************************************************
**   定义 CANRxSR 寄存器:
**********************************************************************************************************************
*/
typedef	union		_uCANRxSR_
{
	INT32U		Word;				//字操作定义
	struct	
	{
		INT32U	RS1 	:1;		//CAN1正在接收状态
		INT32U	RS2 	:1;		//CAN2正在接收状态
		INT32U	RS3 	:1;		//CAN3正在接收状态
		INT32U	RS4 	:1;		//CAN4正在接收状态
		INT32U	RSV1	:4;		//保留
		INT32U	RBS1 	:1;		//CAN1接收缓冲区有效
		INT32U	RBS2 	:1;		//CAN2接收缓冲区有效
		INT32U	RBS3 	:1;		//CAN3接收缓冲区有效
		INT32U	RBS4 	:1;		//CAN4接收缓冲区有效
		INT32U	RSV2 	:4;		// 
		INT32U	DOS1 	:1;		//CAN1接收缓冲区溢出
		INT32U	DOS2 	:1;		//CAN2接收缓冲区溢出
		INT32U	DOS3 	:1;		//CAN3接收缓冲区溢出
		INT32U	DOS4 	:1;		//CAN4接收缓冲区溢出
		INT32U	RSV12	:12;	//保留
	}Bits;
}*P_uCANRxSR, uCANRxSR;

#define 	_CANRxSR				(*((volatile P_uCANRxSR) CANRxSR_GADR))
/*
**********************************************************************************************************************
**   定义接收帧的结构
**********************************************************************************************************************
*/
typedef	struct	_stcRXBUF_
{
	uCANRFS	CANRcvFS;
	uCANRID	RxCANID;
	uCANRDx	RDA;
	uCANRDx	RDB;
}*P_stcRxBUF,stcRxBUF;

#define	RxBUF(CanNum)	(*((volatile P_stcRxBUF)( RxBUF_BADR+CanNum*CAN_OFFSET_ADR)))

/*
**********************************************************************************************************************
**   定义 CANMSR 寄存器:
**********************************************************************************************************************
*/
typedef	union		_uCANMSR_
{
	INT32U		Word;				//字操作定义
	struct	
	{
		INT32U	ES1 		:1;		//CAN1错误报警
		INT32U	ES2 		:1;		//CAN2错误报警
		INT32U	ES3 		:1;		//CAN3错误报警
		INT32U	ES4 		:1;		//CAN4错误报警
		INT32U	RSV1		:4;		//保留
		INT32U	BS1 		:1;		//CAN1总线脱离
		INT32U	BS2 		:1;		//CAN2总线脱离
		INT32U	BS3 		:1;		//CAN3总线脱离
		INT32U	BS4 		:1;		//CAN4总线脱离
		INT32U	RSV20		:20;	//保留
	}Bits;
}*P_uCANMSR, uCANMSR;

#define 	_CANMSR				(*((volatile P_uCANMSR) CANMSR_GADR))
/*
**********************************************************************************************************************
**   定义 CANAFMR 寄存器:
**********************************************************************************************************************
*/
typedef	union		_canafmr_
{
	INT32U	Word;
	struct	
	{
		INT32U	AccOff 	:1;	//1-when"1":if AccBP is 0, the Acceptance Filter is not operational.
								//			All Rx messages on all CAN buses are ignored.

		INT32U	AccBP 	:1;	//1-when"1":all Rx messages are accepted on enabled CAN controllers.
								//			Software must set this bit before modifying the contents of any 
								//			of the registers described below
								//2-when"0":When both this bit and AccOff are 0, the Acceptance filter 
								//			operates to screen received CAN Identifiers.

		INT32U	eFCAN 	:1;	//1-when"1":the Acceptance Filter itself will take care of receiving and 
								//			storing messages for selected Standard ID values on selected 
								//			CAN buses.
								//2-when"0":software must read all messages for all enabled IDs on all 
								//			enabled CAN buses,from the receiving CAN controllers.
		INT32U	RSV29 	:29;
	}Bits;
}uCANAFMR,*P_uCANAFMR;

#define 	_CANAFMR			(*((volatile P_uCANAFMR) CANAFMR_GADR))
/*
**********************************************************************************************************************
**  FullCAN滤波器和标准帧表格数据类型定义
**********************************************************************************************************************
*/
typedef	struct _AF_SFF_CELL_
{
	INT32U UpId		:11;	// 11bit ID1
	INT32U UpRsv	:1;		//
	INT32U UpDis	:1;		// 禁能位
	INT32U UpCh		:3;		// CAN控制器号
	
	INT32U LoId		:11;	// 11bit ID0
	INT32U LoRsv	:1;		//
	INT32U LoDis	:1;		// 禁能位
	INT32U LoCh		:3;		// CAN控制器号
}stcAF_SFF_CELL,*P_stcAF_SFF_CELL;
/*
************************************************************************************
**  CAN滤波器扩展帧表格数据类型定义
************************************************************************************
*/
typedef	struct	_AF_EFF_CELL_
{
	INT32U Id		:29;	// 29bit EFF ID
	INT32U Ch		:3;		// CAN控制器号
}stcAF_EFF_CELL,*P_stcAF_EFF_CELL;
/*
***************************************************************************************
**	FullCAN模式下自动接收的帧的结构
***************************************************************************************
*/
typedef struct _AF_AUTOSTORE_MSG
{
	struct tag_Head
	{
		INT32U ID	:11;
		INT32U RSV5	:5;
		INT32U DLC	:4;
		INT32U RSV12:4;
		INT32U SEM	:2;
		INT32U RSV41:4;
		INT32U RTR	:1;
		INT32U FF	:1;	
	}Head;
	uCANRDx 	da;
	uCANRDx 	db;
}stcAF_AUTOSTORE_MSG,*P_stcAF_AUTOSTORE_MSG;
/*
**********************************************************************************************************************
**   定义 SFF_sa 寄存器:
**1-The start address of the table of individual Standard Identifiers in AF Lookup RAM.If the table is empty,
	write the same value in this register and the SFF_GRP_sa register described below.
**2-If the eFCAN bit in the AFMR is 1, this value also indicates the size of the table of Standard IDs which 
	the Acceptance Filter will search and (if found) automatically store received messages in Acceptance Filter RAM.
**********************************************************************************************************************
*/
typedef	union	_canF_sa_
{
	INT32U	Word;
	struct	
	{
		INT32U	RSV2 	:2;
		INT32U	SADR 	:9;	
		INT32U	RSV21 	:21;
	}Bits;
}uCANF_sa,*P_uCANF_sa;

#define 	_CANSFF_sa			(*((volatile P_uCANF_sa)(CANSFF_sa_GADR)))
#define 	_CANEFF_sa			(*((volatile P_uCANF_sa)(CANEFF_sa_GADR)))
#define 	_CANLUTerrAd		(*((volatile P_uCANF_sa)(CANLUTerrAd_GADR)))
/*
**********************************************************************************************************************
**   定义 SFF_GRP_sa 寄存器:
**1-The start address of the table of grouped Standard Identifiers in AF Lookup RAM. If the table is empty,
	write the same value in this register and the EFF_sa register described below.
**2-The largest value that should be written to this register is 0x800, when only the Standard Individual  
	table is used, and the last word (address 0x7FC) in AF Lookup Table RAM is used.
**********************************************************************************************************************
*/
typedef	union	_canGRP_sa_
{
	INT32U	Word;
	struct	
	{
		INT32U	RSV2 	:2;
		INT32U	SADR 	:10;
		INT32U	RSV20 	:20;
	}Bits;
}uCANGRP_sa,*P_uCANGRP_sa;

#define 	_CANSFF_GRP_sa		(*((volatile P_uCANGRP_sa)(CANSFF_GRP_sa_GADR)))
#define 	_CANEFF_GRP_sa		(*((volatile P_uCANGRP_sa)(CANEFF_GRP_sa_GADR)))
#define 	_CANENDofTable		(*((volatile P_uCANGRP_sa)(CANENDofTable_GADR)))
/*
**********************************************************************************************************************
**   定义 LUTerr 寄存器:
**1-This read-only bit is set to 1 if the Acceptance Filter encounters an error in the content of the
	tables in AF RAM. It is cleared when software reads the LUTerrAd register. This condition
	is ORed with the “other CAN” interrupts from the CAN controllers, to produce the request for
	a VIC interrupt channel.
**********************************************************************************************************************
*/
typedef	union	_canLUTerr
{
	INT32U	Word;
	struct	
	{
		INT32U	LERR 	:1;
		INT32U	RSV31 	:31;
	}Bits;
}uCANLUTerr,*P_uCANLUTerr;

#define 	_CANLUTerr			(*((volatile P_uCANLUTerr)( CANLUTerr_GADR)))
/*
*********************************************************************************************************
**                            			End Of File
********************************************************************************************************
*/
#endif

