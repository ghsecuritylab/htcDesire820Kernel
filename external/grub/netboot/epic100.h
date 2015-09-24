#ifndef	_EPIC100_H_
# define _EPIC100_H_

#ifndef	PCI_VENDOR_SMC
# define PCI_VENDOR_SMC		0x10B8
#endif

#ifndef	PCI_DEVICE_SMC_EPIC100
# define PCI_DEVICE_SMC_EPIC100	0x0005
#endif

#define PCI_DEVICE_ID_NONE	0xFFFF

enum epic100_registers {
    COMMAND= 0,		
    INTSTAT= 4,		
    INTMASK= 8,		
    GENCTL = 0x0C,	
    NVCTL  = 0x10,	
    EECTL  = 0x14,	
    TEST   = 0x1C,	
    CRCCNT = 0x20,	
    ALICNT = 0x24,	
    MPCNT  = 0x28,	
    MMCTL  = 0x30,	
    MMDATA = 0x34,	
    MIICFG = 0x38,	
    IPG    = 0x3C,	
    LAN0   = 0x40,	
    IDCHK  = 0x4C,	
    MC0    = 0x50,	
    RXCON  = 0x60,	
    TXCON  = 0x70,	
    TXSTAT = 0x74,	
    PRCDAR = 0x84,	
    PRSTAT = 0xA4,	
    PRCPTHR= 0xB0,	
    PTCDAR = 0xC4,	
    ETHTHR = 0xDC	
};

#define CR_STOP_RX		(0x00000001)
#define CR_START_RX		(0x00000002)
#define CR_QUEUE_TX		(0x00000004)
#define CR_QUEUE_RX		(0x00000008)
#define CR_NEXTFRAME		(0x00000010)
#define CR_STOP_TX_DMA		(0x00000020)
#define CR_STOP_RX_DMA		(0x00000040)
#define CR_TX_UGO		(0x00000080)


#define	INTR_RX_THR_STA		(0x00400000)	
#define	INTR_RX_BUFF_EMPTY	(0x00200000)	
#define	INTR_TX_IN_PROG		(0x00100000)	
#define	INTR_RX_IN_PROG		(0x00080000)	
#define	INTR_TXIDLE		(0x00040000)	
#define INTR_RXIDLE		(0x00020000)	
#define INTR_INTR_ACTIVE	(0x00010000)	
#define INTR_RX_STATUS_OK	(0x00008000)	
#define INTR_PCI_TGT_ABT	(0x00004000)	
#define INTR_PCI_MASTER_ABT	(0x00002000)	
#define INTR_PCI_PARITY_ERR	(0x00001000)	
#define INTR_PCI_DATA_ERR	(0x00000800)	
#define INTR_RX_THR_CROSSED	(0x00000400)	
#define INTR_CNTFULL		(0x00000200)	
#define INTR_TXUNDERRUN		(0x00000100)	
#define INTR_TXEMPTY		(0x00000080)	
#define INTR_TX_CH_COMPLETE	(0x00000040)	
#define INTR_TXDONE		(0x00000020)	
#define INTR_RXERROR		(0x00000010)	
#define INTR_RXOVERFLOW		(0x00000008)	
#define INTR_RX_QUEUE_EMPTY	(0x00000004)	
#define INTR_RXHEADER		(0x00000002)	
#define INTR_RXDONE		(0x00000001)	

#define INTR_CLEARINTR		(0x00007FFF)
#define INTR_VALIDBITS		(0x007FFFFF)
#define INTR_DISABLE		(0x00000000)
#define INTR_CLEARERRS		(0x00007F18)
#define INTR_ABNINTR		(INTR_CNTFULL | INTR_TXUNDERRUN | INTR_RXOVERFLOW)


#define GC_SOFT_RESET		(0x00000001)
#define GC_INTR_ENABLE		(0x00000002)
#define GC_SOFT_INTR		(0x00000004)
#define GC_POWER_DOWN		(0x00000008)
#define GC_ONE_COPY		(0x00000010)
#define GC_BIG_ENDIAN		(0x00000020)
#define GC_RX_PREEMPT_TX	(0x00000040)
#define GC_TX_PREEMPT_RX	(0x00000080)

#define GC_RX_FIFO_THR_32	(0x00000000)
#define GC_RX_FIFO_THR_64	(0x00000100)
#define GC_RX_FIFO_THR_96	(0x00000200)
#define GC_RX_FIFO_THR_128	(0x00000300)

#define GC_MRC_MEM_READ		(0x00000000)
#define GC_MRC_READ_MULT	(0x00000400)
#define GC_MRC_READ_LINE	(0x00000800)

#define GC_SOFTBIT0		(0x00001000)
#define GC_SOFTBIT1		(0x00002000)
#define GC_RESET_PHY		(0x00004000)


#define RC_SAVE_ERRORED_PKT	(0x00000001)
#define RC_SAVE_RUNT_FRAMES	(0x00000002)
#define RC_RCV_BROADCAST	(0x00000004)
#define RC_RCV_MULTICAST	(0x00000008)
#define RC_RCV_INVERSE_PKT	(0x00000010)
#define RC_PROMISCUOUS_MODE	(0x00000020)
#define RC_MONITOR_MODE		(0x00000040)
#define RC_EARLY_RCV_ENABLE	(0x00000080)

#define RD_FRAGLIST		(0x0001)	
#define RD_LLFORM		(0x0002)	
#define RD_HDR_CPY		(0x0004)	


#define TC_EARLY_TX_ENABLE	(0x00000001)

#define TC_LM_NORMAL		(0x00000000)
#define TC_LM_INTERNAL		(0x00000002)
#define TC_LM_EXTERNAL		(0x00000004)
#define TC_LM_FULL_DPX		(0x00000006)

#define TX_SLOT_TIME		(0x00000078)

#define TX_FIFO_THRESH		128	

#define RRING_PKT_INTACT	(0x0001)
#define RRING_ALIGN_ERR		(0x0002)
#define RRING_CRC_ERR		(0x0004)
#define RRING_MISSED_PKT	(0x0008)
#define RRING_MULTICAST		(0x0010)
#define RRING_BROADCAST		(0x0020)
#define RRING_RECEIVER_DISABLE	(0x0040)
#define RRING_STATUS_VALID	(0x1000)
#define RRING_FRAGLIST_ERR	(0x2000)
#define RRING_HDR_COPIED	(0x4000)
#define RRING_OWN		(0x8000)

#define RRING_ERROR		(RRING_ALIGN_ERR|RRING_CRC_ERR)

#define TRING_PKT_INTACT	(0x0001)	
#define TRING_PKT_NONDEFER	(0x0002)	
#define TRING_COLL		(0x0004)	
#define TRING_CARR		(0x0008)	
#define TRING_UNDERRUN		(0x0010)	
#define TRING_HB_COLL		(0x0020)	
#define TRING_WIN_COLL		(0x0040)	
#define TRING_DEFERRED		(0x0080)	
#define TRING_COLL_COUNT	(0x0F00)	
#define TRING_COLL_EXCESS	(0x1000)	
#define TRING_OWN		(0x8000)	

#define TRING_ABORT	(TRING_COLL_EXCESS|TRING_WIN_COLL|TRING_UNDERRUN)
#define TRING_ERROR	(TRING_DEFERRED|TRING_WIN_COLL|TRING_UNDERRUN|TRING_CARR )

#define TD_FRAGLIST		(0x0001)	
#define TD_LLFORM		(0x0002)	
#define TD_IAF			(0x0004)	
#define TD_NOCRC		(0x0008)	
#define TD_LASTDESC		(0x0010)	

#endif	