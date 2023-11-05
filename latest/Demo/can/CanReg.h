/****************************************Copyright (c)**************************************************
**                               ������������Ƭ����չ���޹�˾
**                                     ��    ��    ��
**                                        ��Ʒһ�� 
**                                 http://www.zlgmcu.com
**-------------------------------------�ļ���Ϣ--------------------------------------------------------
**	��   ��  	��:	CANREG.H
** 	��  		��:	v1.0
** 	��		��:	2004��2��23��
**	��		��:	CANģ��Ĵ������Ͷ��塢��ַ����ͷ�ļ�
********************************************************************************************************/
#ifndef	_CANREG_H_
#define	_CANREG_H_
/*
**********************************************************************************************************************
**   �����˲���RAM�׵�ַ
**********************************************************************************************************************
*/
#define	CANAFRAM_BADR				0xE0038000
/*
**********************************************************************************************************************
**  CAN�Ĵ�������ַ����
**********************************************************************************************************************
*/
#define 	CANMOD_BADR				0xE0044000     		//ģʽ�Ĵ���
#define 	CANCMR_BADR				0xE0044004      	//����Ĵ���
#define 	CANGSR_BADR				0xE0044008      	//ȫ��״̬�Ĵ���
#define 	CANICR_BADR				0xE004400C     		//�жϼ�����Ĵ���
#define 	CANIER_BADR				0xE0044010      	//�ж�ʹ�ܼĴ���
#define 	CANBTR_BADR				0xE0044014      	//����ʱ��Ĵ���
#define 	CANEWL_BADR				0xE0044018      	//�������ƼĴ���
#define 	CANSR_BADR  			0xE004401C      	//״̬�Ĵ���
#define 	CANRFS_BADR				0xE0044020      	//����֡��Ϣ�Ĵ���
#define		CANRID_BADR				0xE0044024      	//���ձ���ID�Ĵ���

#define 	CANRDA_BADR				0xE0044028      	//��������1~4
#define 	CANRDB_BADR 			0xE004402C      	//��������5��8
#define 	CANTFI1_BADR			0xE0044030      	//CAN���ͻ�����1֡��Ϣ�Ĵ���
#define 	CANTID1_BADR			0xE0044034      	// CAN���ͻ�����1����ID�Ĵ���
#define 	CANTDA1_BADR			0xE0044038      	// CAN���ͻ�����1��������1��4�Ĵ���
#define 	CANTDB1_BADR			0xE004403C      	// CAN���ͻ�����1��������5��8�Ĵ���
#define 	CANTFI2_BADR			0xE0044040      	// CAN���ͻ�����2֡��Ϣ�Ĵ���
#define 	CANTID2_BADR			0xE0044044      	// CAN���ͻ�����2����ID�Ĵ���
#define 	CANTDA2_BADR			0xE0044048     		// CAN���ͻ�����2��������1��4�Ĵ���
#define 	CANTDB2_BADR			0xE004404C      	// CAN���ͻ�����2��������5��8�Ĵ���
#define 	CANTFI3_BADR			0xE0044050      	// CAN���ͻ�����3֡��Ϣ�Ĵ���
#define 	CANTID3_BADR			0xE0044054      	// CAN���ͻ�����3����ID�Ĵ���
#define 	CANTDA3_BADR			0xE0044058      	// CAN���ͻ�����3��������1��4�Ĵ���
#define 	CANTDB3_BADR			0xE004405C      	// CAN���ͻ�����3��������5��8�Ĵ���
/*
**********************************************************************************************************************
**  ����RxBUF�Ļ���ַ
**********************************************************************************************************************
*/
#define	RxBUF_BADR					0xE0044020
/*
**********************************************************************************************************************
**  ����TxBUF�Ļ���ַ
**********************************************************************************************************************
*/
#define	TxBUF1_BADR					0xE0044030			// CAN���ͻ�����1�׵�ַ
#define	TxBUF2_BADR					0xE0044040			// CAN���ͻ�����2�׵�ַ
#define	TxBUF3_BADR					0xE0044050			// CAN���ͻ�����3�׵�ַ
/*
**********************************************************************************************************************
**  ����ȫ��Ӧ�õļĴ���
**********************************************************************************************************************
*/
#define 	CANTxSR_GADR   			0xE0040000      	//����״̬�Ĵ���
#define 	CANRxSR_GADR      		0xE0040004      	//����״̬�Ĵ���
#define 	CANMSR_GADR       		0xE0040008      	//����״̬�Ĵ���
#define 	CANAFMR_GADR      		0xE003C000      	//�����˲�����
#define 	CANSFF_sa_GADR      	0xE003C004      	//��׼֡���
#define 	CANSFF_GRP_sa_GADR 		0xE003C008      	//��׼֡����
#define 	CANEFF_sa_GADR      	0xE003C00C      	//��չ֡���
#define 	CANEFF_GRP_sa_GADR 		0xE003C010      	//��չ֡����
#define 	CANENDofTable_GADR  	0xE003C014      	//��������ַ
#define 	CANLUTerrAd_GADR   		0xE003C018      	//LUT�����ַ��ַ�Ĵ���
#define 	CANLUTerr_GADR      	0xE003C01C			//LUT����Ĵ���
/*
**********************************************************************************************************************
**  CAN������ͨ������
**********************************************************************************************************************
*/
typedef 	enum		_cannum_				
{ 
#if		CAN_MAX_NUM  == 4			//΢�������к���4·CAN
	CAN1 = 0, 						//CAN1ģ��
	CAN2,							//CAN2ģ��
	CAN3,							//CAN3ģ��
	CAN4							//CAN4ģ��
#elif	CAN_MAX_NUM  == 2			//΢�������к���2·CAN
	CAN1 = 0, 						//CAN1ģ��
	CAN2							//CAN2ģ��
#endif
} eCANNUM;		

//#define REGAFRAM         (*((volatile INT32U *) 0xE0038000))      /* lpc2119\lpc2129\lpc2292\lpc2294 only */

/*
*********************************************************************************************************************
**   ���� CANMOD �Ĵ���:
1.This register controls the basic operating mode of the CAN Controller. 
2.Bits not listed read as 0 and should be written as 0.
*********************************************************************************************************************
*/
typedef	union		_canmod_
{
	INT32U	Word;
	struct	{
		INT32U	RM 		:1;		//����RMλ(��λλ)
		INT32U	LOM 	:1;		//����LOMλ(ֻ��ģʽλ)
		
		INT32U	STM		:1;		//����STMλ "0"���͵���Ϣ���뱻Ӧ��ű��Ͽ�
									//			"1"�Բ���ģʽ,CANCMR��SRRλһ��ʹ�ã����Դﵽ�Է����յ�Ч��
									
		INT32U	TPM 	:1;		//����TPMλ "0"3�����ͻ����������ȼ��ɸ��Ե�CAN ID����
									//			"1"3�����ͻ����������ȼ��ɸ��Ե�Tx���ȼ������
									
		INT32U	SM 		:1;		//����SMλ(˯��ģʽλ)
		
		INT32U	RPM 	:1;		//����RPMλ "0"��������������λ��Rx��Tx��Ϊ�͵�ƽ
									//			"1"��ת����ģʽ--��������������λ��Rx��Ϊ�ߵ�ƽ
									
		INT32U	RSV1 	:1;		//����λ
		INT32U	TM 		:1;		//����TMλ(����ģʽ)
		INT32U	RSV24	:24;	//����λ
	}Bits;
}uCANMod,*P_uCANMod;

#define 	CANMOD(CanNum)		(*((volatile P_uCANMod)(CANMOD_BADR+CanNum* CAN_OFFSET_ADR)))

/*
**********************************************************************************************************************
**   ���� CANCMR �Ĵ���:
1.Writing to this write-only register initiates an action. 
2.Bits not listed should be written as 0. Reading this register yields zeroes.
**********************************************************************************************************************
*/
typedef	union		_cancmr_
{
	INT32U	Word;
	struct	
	{
		INT32U	TR 		:1;		//����TRλ(��������)
		INT32U	AT 		:1;		//����ATλ(������ֹ)
		INT32U	RRB 	:1;		//����RRBλ(���ջ������ͷ�)
		INT32U	CDO 	:1;		//����������λ
		INT32U	SRR 	:1;		//����SRRλ(�Խ�������)
		INT32U	STB1 	:1;		//����SEND TxBUF1λ(ѡ��BUF1����)
		INT32U	STB2 	:1;		//����SEND TxBUF2λ(ѡ��BUF2����)
		INT32U	STB3 	:1;		//����SEND TxBUF3λ(ѡ��BUF3����)
		INT32U	RSV24	:24;	//����λ
	}Bits;
}uCANCMR,*P_uCANCMR;

#define 	CANCMR(CanNum)		(*((volatile P_uCANCMR)(CANCMR_BADR+CanNum* CAN_OFFSET_ADR )))
/*
************************************************************************************************************************
**   ���� CANGSR �Ĵ���:
1.This register is read-only, except that the Error Counters can be written when the RM bit in the CANMOD register is 1.
2.Bits not listed read as 0 and should be written as 0.
************************************************************************************************************************
*/
typedef	union		_cangsr_
{
	INT32U	Word;				//�ֲ�������
	struct	
	{
		INT32U	RBS 	:1;	//���ջ�����״̬λ
		INT32U	DOS 	:1; //�������״̬λ
		INT32U	TBS 	:1;	//���ͻ�����״̬����λ
		INT32U	TCS 	:1;	//�������״̬λ
		INT32U	RS 		:1;	//���ڽ���״̬
		INT32U	TS 		:1;	//���ڷ���״̬
		INT32U	ES	 	:1;	//����״̬
		INT32U	BS 		:1;	//���߹ر�
		INT32U	RSV8	:8;	//����λ
		INT32U	RXERR 	:8;	//���մ������
		INT32U	TXERR 	:8;	//���ʹ������
	}Bits;
}uCANGSR,*P_uCANGSR;

#define 	CANGSR(CanNum)		(*((volatile P_uCANGSR)( CANGSR_BADR+CanNum* CAN_OFFSET_ADR ))) 
/*
**********************************************************************************************************************
**   ���� CANICR �Ĵ���:
1.Bits in this register indicate information about events on the CAN bus. This register is read-only.
2.Bits not listed read as 0 and should be written as 0.
3.The clearing of bits 1-9 and the releasing of bits 16-23 and 24-31 all occur on any read from CANICR,
  regardless of whether part or all of the register is read.This means that software should always read CANICR as a word,
  and and process and deal with all bits of the register as appropriate for the application.
**********************************************************************************************************************
*/
typedef	union		_canicr_
{
	INT32U	Word;				//�ֲ�������
	struct	
	{
		INT32U	RI 		:1;	//�����ж�λ
		INT32U	TI1 	:1;	//TxBUF1���ͳɹ��ж�λ
		INT32U	EI 		:1;	//���󱨾��ж�λ
		INT32U	DOI 	:1;	//��������ж�λ
		INT32U	WUI 	:1;	//˯�߻����ж�λ
		INT32U	EPI 	:1;	//�����Ͽ��ж�λ
		INT32U	ALI 	:1;	//�ٲô����ж�λ
		INT32U	BEI 	:1;	//���ߴ����ж�
		INT32U	IDI 	:1;	//���յ�CAN��ʶ���ж�λ
		INT32U	TI2 	:1;	// TxBUF2���ͳɹ��ж�λ
		INT32U	TI3 	:1;	// TxBUF3���ͳɹ��ж�λ
		INT32U	RSV5	:5;	//����λ
		INT32U	ERRBIT 	:5;	//������벶��
		INT32U	ERRDIR 	:1;	//������
		INT32U	ERRC 	:2;	//��������
		INT32U	ALCBIT 	:5;	//�ٲô�����벶��
		INT32U	RSV3	:3;	//����
	}Bits;
}uCANICR,*P_uCANICR;

#define 	CANICR(CanNum)		(*((volatile P_uCANICR)( CANICR_BADR+CanNum* CAN_OFFSET_ADR ))) 
/*
**********************************************************************************************************************
**   ���� CANIER �Ĵ���:
1.This read/write register controls whether various events on the CAN controller will result in an interrupt.
2.Bits 7:0 in this register correspond 1-to-1 with bits 7:0 in the CANICR register.
**********************************************************************************************************************
*/
typedef	union		_canier_
{
	INT32U	Word;			//�ֲ�������
	struct	
	{
		INT32U	RIE 	:1;	//�����ж�ʹ��λ
		INT32U	TIE1 	:1;	//TxBUF1��������ж�ʹ��λ
		INT32U	EIE 	:1;	//���󱨾��ж�ʹ��λ
		INT32U	DOIE 	:1;	//��������ж�ʹ��λ
		INT32U	WUIE 	:1;	//˯��ģʽ�����ж�ʹ��λ
		INT32U	EPIE 	:1;	//�����Ͽ��ж�ʹ��λ
		INT32U	ALIE 	:1;	//�ٲö�ʧ�ж�ʹ��λ
		INT32U	BEIE 	:1;	//���ߴ����ж�ʹ��λ
		INT32U	IDIE	:1;	//���յ�CAN��ʶ���ж�ʹ��λ
		INT32U	TIE2 	:1;	//TxBUF2��������ж�ʹ��λ
		INT32U	TIE3	:1;	//TxBUF3��������ж�ʹ��λ
		INT32U	RSV21	:21;//����λ
	}Bits;
}uCANIER,*P_uCANIER;

#define 	CANIER(CanNum)		(*((volatile P_uCANIER)( CANIER_BADR+CanNum* CAN_OFFSET_ADR )))
/*
**********************************************************************************************************************
**   ���� CANBTR �Ĵ���:
1.This register controls how various CAN timings are derived from the VPB clock.
2.It can be read at any time, but can only be written if the RM bit in CANmod is 1.
**********************************************************************************************************************
*/
typedef	union		_canbtr_
{
	INT32U	Word;					//�ֲ�������
	struct	
	{
		INT32U	BRP 	:10;	//Ԥ��Ƶλ��϶���
		INT32U	RSV4	:4;		//����λ
		INT32U	SJW 	:2;		//ͬ����ת���
		INT32U	TSEG1 	:4;		//ʱ���1
		INT32U	TSEG2 	:3;		//ʱ���2
		INT32U	SAM 	:1;		//����ģʽλ
		INT32U	RSV8	:8;		//����
	}Bits;
}uCANBTR,*P_uCANBTR;

#define 	CANBTR(CanNum)		(*((volatile P_uCANBTR)( CANBTR_BADR+CanNum* CAN_OFFSET_ADR )))
/*
**********************************************************************************************************************
**   ���� CANEWL �Ĵ���:
1.This register sets a limit on Tx or Rx errors at which an interrupt can occur.
2.It can be read at any time, but can only be written if the RM bit in CANmod is 1.
**********************************************************************************************************************
*/
typedef	union	_canewl_
{
	INT32U	Word;					//�ֲ�������
	struct	
	{
		INT32U	EWL 	:8;		///���������ֵ
		INT32U	RSV24	:24;	//����λ
	}Bits;
}uCANEWL,*P_uCANEWL;

#define 	CANEWL(CanNum)		(*((volatile P_uCANEWL)( CANEWL_BADR+CanNum* CAN_OFFSET_ADR )))
/*
**********************************************************************************************************************
**   ���� CANSR �Ĵ���:
1.This register contains three status bytes, in which the bits not related to tranmission are identical to the 
  corresponding bits in the Global Status Register, while those relating to transmission reflect the status of 
  each of the 3 Tx Buffers.
**********************************************************************************************************************
*/
typedef	union	_cansr_
{
	INT32U	Word;					//�ֲ�������
	struct	
	{
		INT32U	RBS1 	:1;		//���ջ�������Ч
		INT32U	DOS1 	:1;		//�������
		INT32U	TBS1 	:1;		//TxBUF1����λ  "0":����
		INT32U	TCS1 	:1;		//TxBUF1�����ݷ������ 
		INT32U	RS1 	:1;		//���ڽ���
		INT32U	TS1 	:1;		//TxBUF1���������ڷ��� "1"���ڷ���
		INT32U	ES1 	:1;		//�����Ͽ�
		INT32U	BS1 	:1;		//���ߴ���
		INT32U	RBS2 	:1;		//
		INT32U	DOS2 	:1;		//
		INT32U	TBS2 	:1;		// TxBUF2����
		INT32U	TCS2 	:1;		// TxBUF2�����ݷ������
		INT32U	RS2 	:1;		//
		INT32U	TS2 	:1;		// TxBUF2���������ڷ���
		INT32U	ES2 	:1;		//
		INT32U	BS2 	:1;		//
		INT32U	RBS3 	:1;		//
		INT32U	DOS3 	:1;		//
		INT32U	TBS3 	:1;		// TxBUF3����
		INT32U	TCS3 	:1;		// TxBUF3�����ݷ������
		INT32U	RS3 	:1;		//
		INT32U	TS3 	:1;		// TxBUF3���������ڷ���
		INT32U	ES3 	:1;		//
		INT32U	BS3 	:1;		//
		INT32U	RSV8	:8;		//
	}Bits;
}uCANSR,*P_uCANSR;

#define 	CANSR(CanNum)		(*((volatile P_uCANSR)( CANSR_BADR+CanNum* CAN_OFFSET_ADR )))
/*
**********************************************************************************************************************
**   ���� CANRFS �Ĵ���:
1.This register defines the characteristics of the current received message. 
2.It is read-only in normal operation, but can be written for testing purposes if the RM bit in CANMOD is 1.
**********************************************************************************************************************
*/
typedef	union		_canrfs_
{
	INT32U		Word;				//�ֲ�������
	struct	
	{
		INT32U	IDIN 	:10;	//ID����ֵ
		INT32U	BP 		:1;		//BP
		INT32U	RSV5 	:5;		//����
		INT32U	DLC 	:4;		//���ݳ���
		INT32U	RSV10	:10;	//����
		INT32U	RTR 	:1;		//Զ��֡������֡ʶ��λ
		INT32U	FF 		:1;		//��չ֡����׼֡ʶ��λ
	}Bits;
}uCANRFS,*P_uCANRFS;

#define 	CANRFS(CanNum)		(*((volatile P_uCANRFS)( CANRFS_BADR+CanNum* CAN_OFFSET_ADR )))
/*
**********************************************************************************************************************
**   ���� CANRID �Ĵ���:
1.This register contains the Identifier field of the current received message. 
2.It is read-only in normal operation, but can be written for testing purposes if the RM bit in CANmod is 1.
3.It has two different formats depending on the FF bit in CANRFS.	FF=0 (11 Bits  10:0)
																	FF=1 (29 Bits  28:0)	
**********************************************************************************************************************
*/
typedef	union		_canrid_
{
	INT32U		Word;					//�ֲ�������
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
**   ���� CANRDx �Ĵ���:
1.This register contains the Data bytes of the current received message. 
2.It is read-only in normal operation, but can be written for testing purposes if the RM bit in CANMOD is 1.
**********************************************************************************************************************
*/
typedef	union		_canrdx_
{
	INT32U		Word;					//�ֲ�������
	struct	
	{
		INT32U	Data1 	:8;			//�����ֽ�
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
**   ���� CANTFIx �Ĵ���:
1.When the corresponding TBS bit in CANSR is 1, software can write to one of these registers to define the format of 
  the next transmit message for that Tx buffer.
2.Bits not listed read as 0 and should be written as 0.
**********************************************************************************************************************
*/
typedef	union		_cantfix_
{
	INT32U		Word;				//�ֽڲ�������
	struct	
	{
		INT32U	PRIO 	:8;		//���������ݷ������ȼ���ֵ
		INT32U	RSV8	:8;						
		INT32U	DLC 	:4;		//�������ݳ���
		INT32U	RSV10	:10;
		INT32U	RTR 	:1;		//Զ��֡������֡���λ
		INT32U	FF 		:1;		//��չ֡����׼֡���λ
	}Bits;
}uCANTFIx,*P_uCANTFIx;

#define CANTFI1(CanNum)		(*((volatile P_uCANTFIx)(CANTFI1_BADR+CanNum*CAN_OFFSET_ADR)))
#define CANTFI2(CanNum)		(*((volatile P_uCANTFIx)(CANTFI2_BADR+CanNum*CAN_OFFSET_ADR)))
#define CANTFI3(CanNum)		(*((volatile P_uCANTFIx)(CANTFI3_BADR+CanNum*CAN_OFFSET_ADR)))
/*
**********************************************************************************************************************
**   ���巢��֡�Ľṹ
**********************************************************************************************************************
*/
typedef	struct		_stcTXBUF_
{
	uCANTFIx		TxFrameInfo;	//����֡��Ϣ�ṹ
	uCANRID			TxCANID;		//����֡��ϢID
	uCANRDx		TDA;			//��������1��4�ֽ�
	uCANRDx		TDB;			//��������5��8�ֽ�
}*P_stcTxBUF,stcTxBUF;

#define	TxBUF1(CanNum)		(*((volatile P_stcTxBUF)( TxBUF1_BADR+CanNum*CAN_OFFSET_ADR)))
#define	TxBUF2(CanNum)		(*((volatile P_stcTxBUF)( TxBUF2_BADR+CanNum*CAN_OFFSET_ADR)))
#define	TxBUF3(CanNum)		(*((volatile P_stcTxBUF)( TxBUF3_BADR+CanNum*CAN_OFFSET_ADR)))
/*
**********************************************************************************************************************
**   ���� CANTxSR �Ĵ���:
**********************************************************************************************************************
*/
typedef	union		_uCANTxSR_
{
	INT32U		Word;				//�ֲ�������
	struct	
	{
		INT32U	TS1 	:1;		//CAN1���ڷ���״̬
		INT32U	TS2 	:1;		//CAN2���ڷ���״̬
		INT32U	TS3 	:1;		//CAN3���ڷ���״̬
		INT32U	TS4 	:1;		//CAN4���ڷ���״̬
		INT32U	RSV1	:4;		//����
		INT32U	TBS1 	:1;		//CAN1���ͻ���������״̬
		INT32U	TBS2 	:1;		//CAN2���ͻ���������״̬
		INT32U	TBS3 	:1;		//CAN3���ͻ���������״̬
		INT32U	TBS4 	:1;		//CAN4���ͻ���������״̬
		INT32U	RSV2 	:4;		// 
		INT32U	TCS1 	:1;		//CAN1�������״̬
		INT32U	TCS2 	:1;		//CAN2�������״̬
		INT32U	TCS3 	:1;		//CAN3�������״̬
		INT32U	TCS4 	:1;		//CAN4�������״̬
		INT32U	RSV12	:12;	//����
	}Bits;
}*P_uCANTxSR,uCANTxSR;

#define 	_CANTxSR				(*((volatile P_uCANTxSR) CANTxSR_GADR))
/*
**********************************************************************************************************************
**   ���� CANRxSR �Ĵ���:
**********************************************************************************************************************
*/
typedef	union		_uCANRxSR_
{
	INT32U		Word;				//�ֲ�������
	struct	
	{
		INT32U	RS1 	:1;		//CAN1���ڽ���״̬
		INT32U	RS2 	:1;		//CAN2���ڽ���״̬
		INT32U	RS3 	:1;		//CAN3���ڽ���״̬
		INT32U	RS4 	:1;		//CAN4���ڽ���״̬
		INT32U	RSV1	:4;		//����
		INT32U	RBS1 	:1;		//CAN1���ջ�������Ч
		INT32U	RBS2 	:1;		//CAN2���ջ�������Ч
		INT32U	RBS3 	:1;		//CAN3���ջ�������Ч
		INT32U	RBS4 	:1;		//CAN4���ջ�������Ч
		INT32U	RSV2 	:4;		// 
		INT32U	DOS1 	:1;		//CAN1���ջ��������
		INT32U	DOS2 	:1;		//CAN2���ջ��������
		INT32U	DOS3 	:1;		//CAN3���ջ��������
		INT32U	DOS4 	:1;		//CAN4���ջ��������
		INT32U	RSV12	:12;	//����
	}Bits;
}*P_uCANRxSR, uCANRxSR;

#define 	_CANRxSR				(*((volatile P_uCANRxSR) CANRxSR_GADR))
/*
**********************************************************************************************************************
**   �������֡�Ľṹ
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
**   ���� CANMSR �Ĵ���:
**********************************************************************************************************************
*/
typedef	union		_uCANMSR_
{
	INT32U		Word;				//�ֲ�������
	struct	
	{
		INT32U	ES1 		:1;		//CAN1���󱨾�
		INT32U	ES2 		:1;		//CAN2���󱨾�
		INT32U	ES3 		:1;		//CAN3���󱨾�
		INT32U	ES4 		:1;		//CAN4���󱨾�
		INT32U	RSV1		:4;		//����
		INT32U	BS1 		:1;		//CAN1��������
		INT32U	BS2 		:1;		//CAN2��������
		INT32U	BS3 		:1;		//CAN3��������
		INT32U	BS4 		:1;		//CAN4��������
		INT32U	RSV20		:20;	//����
	}Bits;
}*P_uCANMSR, uCANMSR;

#define 	_CANMSR				(*((volatile P_uCANMSR) CANMSR_GADR))
/*
**********************************************************************************************************************
**   ���� CANAFMR �Ĵ���:
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
**  FullCAN�˲����ͱ�׼֡����������Ͷ���
**********************************************************************************************************************
*/
typedef	struct _AF_SFF_CELL_
{
	INT32U UpId		:11;	// 11bit ID1
	INT32U UpRsv	:1;		//
	INT32U UpDis	:1;		// ����λ
	INT32U UpCh		:3;		// CAN��������
	
	INT32U LoId		:11;	// 11bit ID0
	INT32U LoRsv	:1;		//
	INT32U LoDis	:1;		// ����λ
	INT32U LoCh		:3;		// CAN��������
}stcAF_SFF_CELL,*P_stcAF_SFF_CELL;
/*
************************************************************************************
**  CAN�˲�����չ֡����������Ͷ���
************************************************************************************
*/
typedef	struct	_AF_EFF_CELL_
{
	INT32U Id		:29;	// 29bit EFF ID
	INT32U Ch		:3;		// CAN��������
}stcAF_EFF_CELL,*P_stcAF_EFF_CELL;
/*
***************************************************************************************
**	FullCANģʽ���Զ����յ�֡�Ľṹ
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
**   ���� SFF_sa �Ĵ���:
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
**   ���� SFF_GRP_sa �Ĵ���:
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
**   ���� LUTerr �Ĵ���:
**1-This read-only bit is set to 1 if the Acceptance Filter encounters an error in the content of the
	tables in AF RAM. It is cleared when software reads the LUTerrAd register. This condition
	is ORed with the ��other CAN�� interrupts from the CAN controllers, to produce the request for
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

