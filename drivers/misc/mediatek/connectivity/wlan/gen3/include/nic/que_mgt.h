/*
** Id: //Department/DaVinci/BRANCHES/MT6620_WIFI_DRIVER_V2_3/include/nic/que_mgt.h#2
*/

/*! \file   "que_mgt.h"
 *  \brief  TX/RX queues management header file
 *
 *  The main tasks of queue management include TC-based HIF TX flow control,
 *  adaptive TC quota adjustment, HIF TX grant scheduling, Power-Save
 *  forwarding control, RX packet reordering, and RX BA agreement management.
 */

/*
** Log: que_mgt.h
**
** 07 25 2014 eason.tsai
** AOSP
**
** 08 23 2013 terry.wu
** [BORA00002207] [MT6630 Wi-Fi] TXM & MQM Implementation
** 1. Reset MSDU_INFO for data packet to avoid unexpected Tx status
** 2. Drop Tx packet to non-associated STA in driver
**
** 08 19 2013 terry.wu
** [BORA00002207] [MT6630 Wi-Fi] TXM & MQM Implementation
** 1. Enable TC resource adjust feature
** 2. Set Non-QoS data frame to TC5
**
** 07 26 2013 terry.wu
** [BORA00002207] [MT6630 Wi-Fi] TXM & MQM Implementation
** 1. Reduce extra Tx frame header parsing
** 2. Add TX port control
** 3. Add net interface to BSS binding
**
** 07 18 2013 terry.wu
** [BORA00002207] [MT6630 Wi-Fi] TXM & MQM Implementation
** 1. Update TxDesc PF bit setting rule
** 2. Remove unnecessary QM function
**
** 06 25 2013 terry.wu
** [BORA00002207] [MT6630 Wi-Fi] TXM & MQM Implementation
** Update for 1st connection
**
** 03 13 2013 terry.wu
** [BORA00002207] [MT6630 Wi-Fi] TXM & MQM Implementation
** .
**
** 03 12 2013 terry.wu
** [BORA00002207] [MT6630 Wi-Fi] TXM & MQM Implementation
** Update Tx utility function for management frame
**
** 01 28 2013 cm.chang
** [BORA00002149] [MT6630 Wi-Fi] Initial software development
** Sync CMD format
**
** 01 21 2013 terry.wu
** [BORA00002207] [MT6630 Wi-Fi] TXM & MQM Implementation
** Update TX path based on new ucBssIndex modifications.
**
** 01 17 2013 cm.chang
** [BORA00002149] [MT6630 Wi-Fi] Initial software development
** Use ucBssIndex to replace eNetworkTypeIndex
**
** 12 27 2012 terry.wu
** [BORA00002207] [MT6630 Wi-Fi] TXM & MQM Implementation
** Update MQM index mapping mechanism
** 1. TID to ACI
** 2. ACI to SW TxQ
** 3. ACI to network TC resource
**
** 12 18 2012 terry.wu
** [BORA00002207] [MT6630 Wi-Fi] TXM & MQM Implementation
** Page count resource management.
**
** 09 17 2012 cm.chang
** [BORA00002149] [MT6630 Wi-Fi] Initial software development
** Duplicate source from MT6620 v2.3 driver branch
** (Davinci label: MT6620_WIFI_Driver_V2_3_120913_1942_As_MT6630_Base)
*
* 08 15 2011 cp.wu
* [WCXRP00000851] [MT6628 Wi-Fi][Driver] Add HIFSYS related definition to driver source tree
* add MT6628-specific definitions.
*
* 07 26 2011 eddie.chen
* [WCXRP00000874] [MT5931][DRV] API for query the RX reorder queued packets counter
* API for query the RX reorder queued packets counter.
*
* 06 14 2011 eddie.chen
* [WCXRP00000753] [MT5931 Wi-Fi][DRV] Adjust QM for MT5931
* Change the parameter for WMM pass.
*
* 05 31 2011 eddie.chen
* [WCXRP00000753] [MT5931 Wi-Fi][DRV] Adjust QM for MT5931
* Fix the QM quota in MT5931.
*
* 05 09 2011 eddie.chen
* [WCXRP00000709] [MT6620 Wi-Fi][Driver] Check free number before copying broadcast packet
* Check free number before copying broadcast packet.
*
* 04 14 2011 eddie.chen
* [WCXRP00000603] [MT6620 Wi-Fi][DRV] Fix Klocwork warning
* Check the SW RFB free. Fix the compile warning..
*
* 04 08 2011 eddie.chen
* [WCXRP00000617] [MT6620 Wi-Fi][DRV/FW] Fix for sigma
* Fix for sigma
*
* 03 28 2011 eddie.chen
* [WCXRP00000602] [MT6620 Wi-Fi][DRV] Fix wmm parameters in beacon for BOW
* Fix wmm parameters in beacon for BOW.
*
* 03 15 2011 eddie.chen
* [WCXRP00000554] [MT6620 Wi-Fi][DRV] Add sw control debug counter
* Add sw debug counter for QM.
*
* 02 17 2011 eddie.chen
* [WCXRP00000458] [MT6620 Wi-Fi][Driver] BOW Concurrent - ProbeResp was exist in other channel
* 1) Chnange GetFrameAction decision when BSS is absent.
* 2) Check channel and resource in processing ProbeRequest
*
* 01 12 2011 eddie.chen
* [WCXRP00000322] Add WMM IE in beacon,
*
*  Add per station flow control when STA is in PS
*
*
* 1) Check Bss if support QoS before adding WMMIE
* 2) Check if support prAdapter->rWifiVar QoS and uapsd in flow control
*
* 12 29 2010 eddie.chen
* [WCXRP00000322] Add WMM IE in beacon,
*
*  Add per station flow control when STA is in PS
*
*
* 1) PS flow control event
*
* 2) WMM IE in beacon, assoc resp, probe resp
*
* 12 23 2010 george.huang
* [WCXRP00000152] [MT6620 Wi-Fi] AP mode power saving function
* 1. update WMM IE parsing, with ASSOC REQ handling
* 2. extend U-APSD parameter passing from driver to FW
*
* 10 04 2010 cp.wu
* [WCXRP00000077] [MT6620 Wi-Fi][Driver][FW] Eliminate use of ENUM_NETWORK_TYPE_T and replaced by
*ENUM_NETWORK_TYPE_INDEX_T only
* remove ENUM_NETWORK_TYPE_T definitions
*
* 09 21 2010 kevin.huang
* [WCXRP00000052] [MT6620 Wi-Fi][Driver] Eliminate Linux Compile Warning
* Eliminate Linux Compile Warning
*
* 08 04 2010 yarco.yang
* NULL
* Add TX_AMPDU and ADDBA_REJECT command
*
* 07 22 2010 george.huang
*
* Update fgIsQoS information in BSS INFO by CMD
*
* 07 16 2010 yarco.yang
*
* 1. Support BSS Absence/Presence Event
* 2. Support STA change PS mode Event
* 3. Support BMC forwarding for AP mode.
*
* 07 14 2010 yarco.yang
*
* 1. Remove CFG_MQM_MIGRATION
* 2. Add CMD_UPDATE_WMM_PARMS command
*
* 07 13 2010 yarco.yang
*
* [WPD00003849]
* [MT6620 and MT5931] SW Migration, add qmGetFrameAction() API for CMD Queue Processing
*
* 07 09 2010 yarco.yang
*
* [MT6620 and MT5931] SW Migration: Add ADDBA support
*
* 07 08 2010 cp.wu
*
* [WPD00003833] [MT6620 and MT5931] Driver migration - move to new repository.
*
* 06 29 2010 yarco.yang
* [WPD00003837][MT6620]Data Path Refine
* replace g_rQM with Adpater->rQM
*
* 06 25 2010 cp.wu
* [WPD00003833][MT6620 and MT5931] Driver migration
* add API in que_mgt to retrieve sta-rec index for security frames.
*
* 06 23 2010 yarco.yang
* [WPD00003837][MT6620]Data Path Refine
* Merge g_arStaRec[] into adapter->arStaRec[]
*
* 06 21 2010 yarco.yang
* [WPD00003837][MT6620]Data Path Refine
* Support CFG_MQM_MIGRATION flag
*
* 06 18 2010 cm.chang
* [WPD00003841][LITE Driver] Migrate RLM/CNM to host driver
* Provide cnmMgtPktAlloc() and alloc/free function of msg/buf
*
* 06 08 2010 cp.wu
* [WPD00003833][MT6620 and MT5931] Driver migration
* add hem_mbox.c and cnm_mem.h (but disabled some feature) for further migration
*
* 06 06 2010 kevin.huang
* [WPD00003832][MT6620 5931] Create driver base
* [MT6620 5931] Create driver base
*
* 03 30 2010 tehuang.liu
* [WPD00001943]Create WiFi test driver framework on WinXP
* Enabled adaptive TC resource control
*
* 03 24 2010 jeffrey.chang
* [WPD00003826]Initial import for Linux port
* initial import for Linux port
*
* 03 19 2010 tehuang.liu
* [WPD00001943]Create WiFi test driver framework on WinXP
* By default enabling dynamic STA_REC activation and decactivation
*
* 03 17 2010 tehuang.liu
* [WPD00001943]Create WiFi test driver framework on WinXP
* Changed STA_REC index determination rules (DA=BMCAST always --> STA_REC_INDEX_BMCAST)
*
* 03 11 2010 tehuang.liu
* [WPD00001943]Create WiFi test driver framework on WinXP
* Fixed buffer leak when processing BAR frames
*
* 02 25 2010 tehuang.liu
* [WPD00001943]Create WiFi test driver framework on WinXP
* Enabled multi-STA TX path with fairness
*
* 02 24 2010 tehuang.liu
* [WPD00001943]Create WiFi test driver framework on WinXP
* Enabled dynamically activating and deactivating STA_RECs
*
* 02 24 2010 tehuang.liu
* [WPD00001943]Create WiFi test driver framework on WinXP
* Added code for dynamic activating and deactivating STA_RECs.
*
* 01 13 2010 tehuang.liu
* [WPD00001943]Create WiFi test driver framework on WinXP
* Enabled the Burst_End Indication mechanism
**  \main\maintrunk.MT6620WiFiDriver_Prj\3 2009-12-09 14:04:53 GMT MTK02468
**  Added RX buffer reordering function prototypes
**  \main\maintrunk.MT6620WiFiDriver_Prj\2 2009-12-02 22:08:44 GMT MTK02468
**  Added macro QM_INIT_STA_REC for initialize a STA_REC
**  \main\maintrunk.MT6620WiFiDriver_Prj\1 2009-11-23 21:58:43 GMT mtk02468
**  Initial version
**
*/

#ifndef _QUE_MGT_H
#define _QUE_MGT_H

/*******************************************************************************
 *                         C O M P I L E R   F L A G S
 ********************************************************************************
 */

/*******************************************************************************
 *                    E X T E R N A L   R E F E R E N C E S
 ********************************************************************************
 */
extern UINT_8 g_arTdlsLink[MAXNUM_TDLS_PEER];
/*******************************************************************************
 *                              C O N S T A N T S
 ********************************************************************************
 */

/* Queue Manager Features */
#define QM_BURST_END_INFO_ENABLED       0	/* 1: Indicate the last TX packet to the FW for each burst */
#define QM_FORWARDING_FAIRNESS          1	/* 1: To fairly share TX resource among active STAs */
#define QM_ADAPTIVE_TC_RESOURCE_CTRL    1	/* 1: To adaptively adjust resource for each TC */
#define QM_FAST_TC_RESOURCE_CTRL        1	/* 1: To fast adjust resource for EMPTY TC (assigned resource is 0) */
#define QM_PRINT_TC_RESOURCE_CTRL       0	/* 1: To print TC resource adjustment results */
#define QM_RX_WIN_SSN_AUTO_ADVANCING    1	/* 1: If pkt with SSN is missing, auto advance the RX reordering window
						 **/
#define QM_RX_INIT_FALL_BEHIND_PASS     1	/* 1: Indicate the packets falling behind to OS before the frame with
						 *SSN is received */
#define QM_TC_RESOURCE_EMPTY_COUNTER    1	/* 1: Count times of TC resource empty happened */

/* Parameters */
#define QM_INIT_TIME_TO_UPDATE_QUE_LEN  60	/* p: Update queue lengths when p TX packets are enqueued */
#define QM_INIT_TIME_TO_ADJUST_TC_RSC   3	/* s: Adjust the TC resource every s updates of queue lengths  */
#define QM_QUE_LEN_MOVING_AVE_FACTOR    3	/* Factor for Que Len averaging */

#define QM_MIN_RESERVED_TC0_RESOURCE    0
#define QM_MIN_RESERVED_TC1_RESOURCE    1
#define QM_MIN_RESERVED_TC2_RESOURCE    0
#define QM_MIN_RESERVED_TC3_RESOURCE    0
#define QM_MIN_RESERVED_TC4_RESOURCE    2	/* Resource for TC4 is not adjustable */
#define QM_MIN_RESERVED_TC5_RESOURCE    0

#define QM_GUARANTEED_TC0_RESOURCE      4
#define QM_GUARANTEED_TC1_RESOURCE      4
#define QM_GUARANTEED_TC2_RESOURCE      9
#define QM_GUARANTEED_TC3_RESOURCE      11
#define QM_GUARANTEED_TC4_RESOURCE      2	/* Resource for TC4 is not adjustable */
#define QM_GUARANTEED_TC5_RESOURCE      4

#define QM_EXTRA_RESERVED_RESOURCE_WHEN_BUSY    0

#define QM_AVERAGE_TC_RESOURCE          6

#define QM_ACTIVE_TC_NUM                    TC_NUM

#define QM_MGMT_QUEUED_THRESHOLD            6
#define QM_CMD_RESERVED_THRESHOLD           4
#define QM_MGMT_QUEUED_TIMEOUT              1000	/* ms */

#define QM_TEST_MODE                        0
#define QM_TEST_TRIGGER_TX_COUNT            50
#define QM_TEST_STA_REC_DETERMINATION       0
#define QM_TEST_STA_REC_DEACTIVATION        0
#define QM_TEST_FAIR_FORWARDING             0

#define QM_DEBUG_COUNTER                    0

/* Per-STA Queues: [0] AC0, [1] AC1, [2] AC2, [3] AC3, [4] MGMT, [5] non-QoS */
/* Per-Type Queues: [0] BMCAST */
#define NUM_OF_PER_STA_TX_QUEUES    6
#define NUM_OF_PER_TYPE_TX_QUEUES   1

/* TX Queue Index */
/* Per-Type */
#define TX_QUEUE_INDEX_BMCAST       0
#define TX_QUEUE_INDEX_NO_STA_REC   0

/* Per-STA */
#define TX_QUEUE_INDEX_AC0          0
#define TX_QUEUE_INDEX_AC1          1
#define TX_QUEUE_INDEX_AC2          2
#define TX_QUEUE_INDEX_AC3          3
#define TX_QUEUE_INDEX_MGMT         4
#define TX_QUEUE_INDEX_NON_QOS      5

#define QM_DEFAULT_USER_PRIORITY    0

#define QM_STA_FORWARD_COUNT_UNLIMITED      0xFFFFFFFF
#define QM_FWD_PKT_QUE_THRESHOLD            128

/* 1 WMM-related */
/* WMM FLAGS */
#define WMM_FLAG_SUPPORT_WMM                BIT(0)
#define WMM_FLAG_SUPPORT_WMMSA              BIT(1)
#define WMM_FLAG_AC_PARAM_PRESENT           BIT(2)
#define WMM_FLAG_SUPPORT_UAPSD              BIT(3)

/* WMM Admission Control Mandatory FLAGS */
#define ACM_FLAG_ADM_NOT_REQUIRED           0
#define ACM_FLAG_ADM_GRANTED                BIT(0)
#define ACM_FLAG_ADM_REQUIRED               BIT(1)

/* WMM Power Saving FLAGS */
#define AC_FLAG_TRIGGER_ENABLED             BIT(1)
#define AC_FLAG_DELIVERY_ENABLED            BIT(2)

/* WMM-2.2.1 WMM Information Element */
#define ELEM_MAX_LEN_WMM_INFO               7

/* WMM-2.2.2 WMM Parameter Element */
#define ELEM_MAX_LEN_WMM_PARAM              24

/* WMM-2.2.1 WMM QoS Info field */
#define WMM_QOS_INFO_PARAM_SET_CNT          BITS(0, 3)	/* Sent by AP */
#define WMM_QOS_INFO_UAPSD                  BIT(7)

#define WMM_QOS_INFO_VO_UAPSD               BIT(0)	/* Sent by non-AP STA */
#define WMM_QOS_INFO_VI_UAPSD               BIT(1)
#define WMM_QOS_INFO_BK_UAPSD               BIT(2)
#define WMM_QOS_INFO_BE_UAPSD               BIT(3)
#define WMM_QOS_INFO_MAX_SP_LEN_MASK        BITS(5, 6)
#define WMM_QOS_INFO_MAX_SP_ALL             0
#define WMM_QOS_INFO_MAX_SP_2               BIT(5)
#define WMM_QOS_INFO_MAX_SP_4               BIT(6)
#define WMM_QOS_INFO_MAX_SP_6               BITS(5, 6)

/* -- definitions for Max SP length field */
#define WMM_MAX_SP_LENGTH_ALL               0
#define WMM_MAX_SP_LENGTH_2                 2
#define WMM_MAX_SP_LENGTH_4                 4
#define WMM_MAX_SP_LENGTH_6                 6

/* WMM-2.2.2 WMM ACI/AIFSN field */
/* -- subfields in the ACI/AIFSN field */
#define WMM_ACIAIFSN_AIFSN                  BITS(0, 3)
#define WMM_ACIAIFSN_ACM                    BIT(4)
#define WMM_ACIAIFSN_ACI                    BITS(5, 6)
#define WMM_ACIAIFSN_ACI_OFFSET             5

/* -- definitions for ACI field */
#define WMM_ACI_AC_BE                       0
#define WMM_ACI_AC_BK                       BIT(5)
#define WMM_ACI_AC_VI                       BIT(6)
#define WMM_ACI_AC_VO                       BITS(5, 6)

#define WMM_ACI(_AC)                        (_AC << WMM_ACIAIFSN_ACI_OFFSET)

/* -- definitions for ECWmin/ECWmax field */
#define WMM_ECW_WMIN_MASK                   BITS(0, 3)
#define WMM_ECW_WMAX_MASK                   BITS(4, 7)
#define WMM_ECW_WMAX_OFFSET                 4

#define TXM_DEFAULT_FLUSH_QUEUE_GUARD_TIME              0	/* Unit: 64 us */

#define QM_RX_BA_ENTRY_MISS_TIMEOUT_MS      (200)

#if CFG_RX_BA_REORDERING_ENHANCEMENT
#define QM_RX_MAX_FW_DROP_SSN_SIZE	8
#define QM_SSN_MASK	0xFFF0
#endif

#if CFG_M0VE_BA_TO_DRIVER
/* MQM internal control bitmap per-bit usage (for operations on g_prMqm->u4FlagBitmap) */
#define MQM_FLAG_TSPEC_NEGO_ADD_IN_PROGRESS 0
#define MQM_FLAG_IDLE_TX_BA_TIMER_STARTED   1
#define MQM_FLAG_IDLE_RX_BA_TIMER_STARTED   2

#define MQM_IDLE_RX_BA_DETECTION			0
#define MQM_IDLE_RX_BA_CHECK_INTERVAL       5000	/* in msec */
#define MQM_DEL_IDLE_RXBA_THRESHOLD_BK      6
#define MQM_DEL_IDLE_RXBA_THRESHOLD_BE      12
#define MQM_DEL_IDLE_RXBA_THRESHOLD_VI      6
#define MQM_DEL_IDLE_RXBA_THRESHOLD_VO      6

/* For indicating whether the role when generating a DELBA message */
#define DELBA_ROLE_INITIATOR			TRUE
#define DELBA_ROLE_RECIPIENT			FALSE

#define MQM_SET_FLAG(_Bitmap, _flag)	{ (_Bitmap) |= (BIT((_flag))); }
#define MQM_CLEAR_FLAG(_Bitmap, _flag)	{ (_Bitmap) &= (~BIT((_flag))); }
#define MQM_CHECK_FLAG(_Bitmap, _flag)	((_Bitmap) & (BIT((_flag))))

typedef enum _ENUM_BA_RESET_SEL_T {
	MAC_ADDR_TID_MATCH = 0,
	MAC_ADDR_MATCH,
	ALWAYS_MATCH,
	MATCH_NUM
} ENUM_BA_RESET_SEL_T;

#endif

/*******************************************************************************
 *                             D A T A   T Y P E S
 ********************************************************************************
 */

enum {
	QM_DBG_CNT_00 = 0,
	QM_DBG_CNT_01,
	QM_DBG_CNT_02,
	QM_DBG_CNT_03,
	QM_DBG_CNT_04,
	QM_DBG_CNT_05,
	QM_DBG_CNT_06,
	QM_DBG_CNT_07,
	QM_DBG_CNT_08,
	QM_DBG_CNT_09,
	QM_DBG_CNT_10,
	QM_DBG_CNT_11,
	QM_DBG_CNT_12,
	QM_DBG_CNT_13,
	QM_DBG_CNT_14,
	QM_DBG_CNT_15,
	QM_DBG_CNT_16,
	QM_DBG_CNT_17,
	QM_DBG_CNT_18,
	QM_DBG_CNT_19,
	QM_DBG_CNT_20,
	QM_DBG_CNT_21,
	QM_DBG_CNT_22,
	QM_DBG_CNT_23,
	QM_DBG_CNT_24,
	QM_DBG_CNT_25,
	QM_DBG_CNT_26,
	QM_DBG_CNT_27,
	QM_DBG_CNT_28,
	QM_DBG_CNT_29,
	QM_DBG_CNT_30,
	QM_DBG_CNT_31,
	QM_DBG_CNT_NUM
};

/* Used for MAC TX */
typedef enum _ENUM_MAC_TX_QUEUE_INDEX_T {
	MAC_TX_QUEUE_AC0_INDEX = 0,
	MAC_TX_QUEUE_AC1_INDEX,
	MAC_TX_QUEUE_AC2_INDEX,
	MAC_TX_QUEUE_AC3_INDEX,
	MAC_TX_QUEUE_AC4_INDEX,
	MAC_TX_QUEUE_AC5_INDEX,
	MAC_TX_QUEUE_AC6_INDEX,
	MAC_TX_QUEUE_BCN_INDEX,
	MAC_TX_QUEUE_BMC_INDEX,
	MAC_TX_QUEUE_NUM
} ENUM_MAC_TX_QUEUE_INDEX_T;

typedef struct _RX_BA_ENTRY_T {
	BOOLEAN fgIsValid;
	QUE_T rReOrderQue;
#if CFG_RX_BA_REORDERING_ENHANCEMENT
	QUE_T rNoNeedWaitQue;
#endif
	UINT_16 u2WinStart;
	UINT_16 u2WinEnd;
	UINT_16 u2WinSize;

	/* For identifying the RX BA agreement */
	UINT_8 ucStaRecIdx;
	UINT_8 ucTid;

	BOOLEAN fgIsWaitingForPktWithSsn;

	TIMER_T rReorderBubbleTimer;
	UINT_16 u2FirstBubbleSn;
	BOOLEAN fgHasBubble;

#if CFG_M0VE_BA_TO_DRIVER
	UINT_8 ucStatus;
	UINT_8 ucIdleCount;
	UINT_16 u2SnapShotSN;
#endif
	/* UINT_8                  ucTxBufferSize; */
	/* BOOL                    fgIsAcConstrain; */
	/* BOOL                    fgIsBaEnabled; */
} RX_BA_ENTRY_T, *P_RX_BA_ENTRY_T;

typedef UINT_32(*PFN_DEQUEUE_FUNCTION) (IN P_ADAPTER_T prAdapter, OUT P_QUE_T prQue, IN UINT_8 ucTC, IN UINT_32
					u4CurrentQuota, IN UINT_32 u4TotalQuota);

/* The mailbox message (could be used for Host-To-Device or Device-To-Host Mailbox) */
typedef struct _MAILBOX_MSG_T {
	UINT_32 u4Msg[2];	/* [0]: D2HRM0R or H2DRM0R, [1]: D2HRM1R or H2DRM1R */
} MAILBOX_MSG_T, *P_MAILBOX_MSG_T;

/* Used for adaptively adjusting TC resources */
typedef struct _TC_RESOURCE_CTRL_T {
	/* TC0, TC1, TC2, TC3, TC5 */
	UINT_32 au4AverageQueLen[TC_NUM - 1];
} TC_RESOURCE_CTRL_T, *P_TC_RESOURCE_CTRL_T;

typedef struct _QUE_MGT_T {	/* Queue Management Control Info */
	/* Per-Type Queues: [0] BMCAST or UNKNOWN-STA packets */
	QUE_T arTxQueue[NUM_OF_PER_TYPE_TX_QUEUES];

#if 0
	/* For TX Scheduling */
	UINT_8 arRemainingTxOppt[NUM_OF_PER_STA_TX_QUEUES];
	UINT_8 arCurrentTxStaIndex[NUM_OF_PER_STA_TX_QUEUES];

#endif

	/* Reordering Queue Parameters */
	RX_BA_ENTRY_T arRxBaTable[CFG_NUM_OF_RX_BA_AGREEMENTS];

	/* Current number of activated RX BA agreements <= CFG_NUM_OF_RX_BA_AGREEMENTS */
	UINT_8 ucRxBaCount;

#if QM_TEST_MODE
	UINT_32 u4PktCount;
	P_ADAPTER_T prAdapter;

#if QM_TEST_FAIR_FORWARDING
	UINT_32 u4CurrentStaRecIndexToEnqueue;
#endif

#endif

#if QM_FORWARDING_FAIRNESS
	/* The current resource used count for a STA with respect to a TC index */
	UINT_32 au4ResourceUsedCount[NUM_OF_PER_STA_TX_QUEUES];

	/* The current serving STA with respect to a TC index */
	UINT_32 au4HeadStaRecIndex[NUM_OF_PER_STA_TX_QUEUES];

	/* For TC5 only */
	BOOLEAN fgGlobalQFirst;
	UINT_32 u4GlobalResourceUsedCount;
#endif

#if QM_ADAPTIVE_TC_RESOURCE_CTRL
	UINT_32 au4AverageQueLen[TC_NUM];
	UINT_32 au4CurrentTcResource[TC_NUM];
	UINT_32 au4MinReservedTcResource[TC_NUM];	/* The minimum amount of resource no matter busy or idle */
	UINT_32 au4GuaranteedTcResource[TC_NUM];	/* The minimum amount of resource when extremely busy */

	UINT_32 u4TimeToAdjustTcResource;
	UINT_32 u4TimeToUpdateQueLen;

	UINT_32 u4QueLenMovingAverage;
	UINT_32 u4ExtraReservedTcResource;
	UINT_32 u4ResidualTcResource;

	/* Set to TRUE if the last TC adjustment has not been completely applied (i.e., waiting more TX-Done events
	 * to align the TC quotas to the TC resource assignment) */
	BOOLEAN fgTcResourcePostAnnealing;

#if QM_FAST_TC_RESOURCE_CTRL
	BOOLEAN fgTcResourceFastReaction;
#endif

#endif

#if QM_DEBUG_COUNTER
	UINT_32 au4QmDebugCounters[QM_DBG_CNT_NUM];
#endif

	UINT_32 u4TxAllowedStaCount;

#if QM_TC_RESOURCE_EMPTY_COUNTER
	UINT_32 au4QmTcResourceEmptyCounter[MAX_BSS_INDEX + 1][TC_NUM];
	UINT_32 au4DequeueNoTcResourceCounter[TC_NUM];
	/*
	 * how many page count back during statistics intervals
	 */
	UINT_32 au4QmTcResourceBackCounter[TC_NUM];
	/*
	 * how many page count used to TX frame during statistics intervals
	 */
	UINT_32 au4QmTcUsedPageCounter[TC_NUM];
	UINT_32 au4QmTcWantedPageCounter[TC_NUM];

	UINT_32 u4EnqueueCounter;
	UINT_32 u4DequeueCounter;
#endif

	UINT_32 u4MaxForwardBufferCount;

	OS_SYSTIME rLastTxPktDumpTime;
} QUE_MGT_T, *P_QUE_MGT_T;

typedef struct _EVENT_RX_ADDBA_T {
	/* Event header */
	UINT_16 u2Length;
	UINT_16 u2Reserved1;	/* Must be filled with 0x0001 (EVENT Packet) */
	UINT_8 ucEID;
	UINT_8 ucSeqNum;
	UINT_8 aucReserved2[2];

	/* Fields not present in the received ADDBA_REQ */
	UINT_8 ucStaRecIdx;

	/* Fields that are present in the received ADDBA_REQ */
	UINT_8 ucDialogToken;	/* Dialog Token chosen by the sender */
	UINT_16 u2BAParameterSet;	/* BA policy, TID, buffer size */
	UINT_16 u2BATimeoutValue;
	UINT_16 u2BAStartSeqCtrl;	/* SSN */
} EVENT_RX_ADDBA_T, *P_EVENT_RX_ADDBA_T;

typedef struct _EVENT_RX_DELBA_T {
	/* Event header */
	UINT_16 u2Length;
	UINT_16 u2Reserved1;	/* Must be filled with 0x0001 (EVENT Packet) */
	UINT_8 ucEID;
	UINT_8 ucSeqNum;
	UINT_8 aucReserved2[2];

	/* Fields not present in the received ADDBA_REQ */
	UINT_8 ucStaRecIdx;
	UINT_8 ucTid;
} EVENT_RX_DELBA_T, *P_EVENT_RX_DELBA_T;

typedef struct _EVENT_BSS_ABSENCE_PRESENCE_T {
	/* Event header */
	UINT_16 u2Length;
	UINT_16 u2Reserved1;	/* Must be filled with 0x0001 (EVENT Packet) */
	UINT_8 ucEID;
	UINT_8 ucSeqNum;
	UINT_8 aucReserved2[2];

	/* Event Body */
	UINT_8 ucBssIndex;
	UINT_8 ucIsAbsent;
	UINT_8 ucBssFreeQuota;
	UINT_8 aucReserved[1];
} EVENT_BSS_ABSENCE_PRESENCE_T, *P_EVENT_BSS_ABSENCE_PRESENCE_T;

typedef struct _EVENT_STA_CHANGE_PS_MODE_T {
	/* Event header */
	UINT_16 u2Length;
	UINT_16 u2Reserved1;	/* Must be filled with 0x0001 (EVENT Packet) */
	UINT_8 ucEID;
	UINT_8 ucSeqNum;
	UINT_8 aucReserved2[2];

	/* Event Body */
	UINT_8 ucStaRecIdx;
	UINT_8 ucIsInPs;
	UINT_8 ucUpdateMode;
	UINT_8 ucFreeQuota;
} EVENT_STA_CHANGE_PS_MODE_T, *P_EVENT_STA_CHANGE_PS_MODE_T;

/* The free quota is used by PS only now */
/* The event may be used by per STA flow conttrol in general */
typedef struct _EVENT_STA_UPDATE_FREE_QUOTA_T {
	/* Event header */
	UINT_16 u2Length;
	UINT_16 u2Reserved1;	/* Must be filled with 0x0001 (EVENT Packet) */
	UINT_8 ucEID;
	UINT_8 ucSeqNum;
	UINT_8 aucReserved2[2];

	/* Event Body */
	UINT_8 ucStaRecIdx;
	UINT_8 ucUpdateMode;
	UINT_8 ucFreeQuota;
	UINT_8 aucReserved[1];
} EVENT_STA_UPDATE_FREE_QUOTA_T, *P_EVENT_STA_UPDATE_FREE_QUOTA_T;

typedef struct _EVENT_CHECK_REORDER_BUBBLE_T {
	/* Event header */
	UINT_16 u2Length;
	UINT_16 u2Reserved1;	/* Must be filled with 0x0001 (EVENT Packet) */
	UINT_8 ucEID;
	UINT_8 ucSeqNum;
	UINT_8 aucReserved2[2];

	/* Event Body */
	UINT_8 ucStaRecIdx;
	UINT_8 ucTid;
} EVENT_CHECK_REORDER_BUBBLE_T, *P_EVENT_CHECK_REORDER_BUBBLE_T;

/* WMM-2.2.1 WMM Information Element */
typedef struct _IE_WMM_INFO_T {
	UINT_8 ucId;		/* Element ID */
	UINT_8 ucLength;	/* Length */
	UINT_8 aucOui[3];	/* OUI */
	UINT_8 ucOuiType;	/* OUI Type */
	UINT_8 ucOuiSubtype;	/* OUI Subtype */
	UINT_8 ucVersion;	/* Version */
	UINT_8 ucQosInfo;	/* QoS Info field */
	UINT_8 ucDummy[3];	/* Dummy for pack */
} IE_WMM_INFO_T, *P_IE_WMM_INFO_T;

typedef struct _WMM_AC_PARAM_T {
	UINT_8 ucAciAifsn;
	UINT_8 ucEcw;
	UINT_16 u2TxopLimit;
} WMM_AC_PARAM_T, *P_WMM_AC_PARAM_T;

/* WMM-2.2.2 WMM Parameter Element */
typedef struct _IE_WMM_PARAM_T {
	UINT_8 ucId;		/* Element ID */
	UINT_8 ucLength;	/* Length */

	/* IE Body */
	UINT_8 aucOui[3];	/* OUI */
	UINT_8 ucOuiType;	/* OUI Type */
	UINT_8 ucOuiSubtype;	/* OUI Subtype */
	UINT_8 ucVersion;	/* Version */

	/* WMM IE Body */
	UINT_8 ucQosInfo;	/* QoS Info field */
	UINT_8 ucReserved;

	/* AC Parameters */
#if 1
	WMM_AC_PARAM_T arAcParam[4];
#else
	UINT_8 ucAciAifsn_BE;
	UINT_8 ucEcw_BE;
	UINT_8 aucTxopLimit_BE[2];

	UINT_8 ucAciAifsn_BG;
	UINT_8 ucEcw_BG;
	UINT_8 aucTxopLimit_BG[2];

	UINT_8 ucAciAifsn_VI;
	UINT_8 ucEcw_VI;
	UINT_8 aucTxopLimit_VI[2];

	UINT_8 ucAciAifsn_VO;
	UINT_8 ucEcw_VO;
	UINT_8 aucTxopLimit_VO[2];
#endif
} IE_WMM_PARAM_T, *P_IE_WMM_PARAM_T;

typedef struct _IE_WMM_TSPEC_T {
	UINT_8 ucId;		/* Element ID */
	UINT_8 ucLength;	/* Length */
	UINT_8 aucOui[3];	/* OUI */
	UINT_8 ucOuiType;	/* OUI Type */
	UINT_8 ucOuiSubtype;	/* OUI Subtype */
	UINT_8 ucVersion;	/* Version */
	/* WMM TSPEC body */
	UINT_8 aucTsInfo[3];	/* TS Info */
	UINT_8 aucTspecBodyPart[1];	/* Note: Utilize PARAM_QOS_TSPEC to fill (memory copy) */
} IE_WMM_TSPEC_T, *P_IE_WMM_TSPEC_T;

typedef struct _IE_WMM_HDR_T {
	UINT_8 ucId;		/* Element ID */
	UINT_8 ucLength;	/* Length */
	UINT_8 aucOui[3];	/* OUI */
	UINT_8 ucOuiType;	/* OUI Type */
	UINT_8 ucOuiSubtype;	/* OUI Subtype */
	UINT_8 ucVersion;	/* Version */
	UINT_8 aucBody[1];	/* IE body */
} IE_WMM_HDR_T, *P_IE_WMM_HDR_T;

typedef struct _AC_QUE_PARMS_T {
	UINT_16 u2CWmin;	/*!< CWmin */
	UINT_16 u2CWmax;	/*!< CWmax */
	UINT_16 u2TxopLimit;	/*!< TXOP limit */
	UINT_16 u2Aifsn;	/*!< AIFSN */
	UINT_8 ucGuradTime;	/*!< GuardTime for STOP/FLUSH. */
	UINT_8 ucIsACMSet;
} AC_QUE_PARMS_T, *P_AC_QUE_PARMS_T;

/* WMM ACI (AC index) */
typedef enum _ENUM_WMM_ACI_T {
	WMM_AC_BE_INDEX = 0,
	WMM_AC_BK_INDEX,
	WMM_AC_VI_INDEX,
	WMM_AC_VO_INDEX,
	WMM_AC_INDEX_NUM
} ENUM_WMM_ACI_T, *P_ENUM_WMM_ACI_T;

/* Used for CMD Queue Operation */
typedef enum _ENUM_FRAME_ACTION_T {
	FRAME_ACTION_DROP_PKT = 0,
	FRAME_ACTION_QUEUE_PKT,
	FRAME_ACTION_TX_PKT,
	FRAME_ACTION_NUM
} ENUM_FRAME_ACTION_T;

typedef enum _ENUM_FRAME_TYPE_IN_CMD_Q_T {
	FRAME_TYPE_802_1X = 0,
	FRAME_TYPE_MMPDU,
	FRAME_TYPE_NUM
} ENUM_FRAME_TYPE_IN_CMD_Q_T;

typedef enum _ENUM_FREE_QUOTA_MODET_T {
	FREE_QUOTA_UPDATE_MODE_INIT = 0,
	FREE_QUOTA_UPDATE_MODE_OVERWRITE,
	FREE_QUOTA_UPDATE_MODE_INCREASE,
	FREE_QUOTA_UPDATE_MODE_DECREASE
} ENUM_FREE_QUOTA_MODET_T, *P_ENUM_FREE_QUOTA_MODET_T;

typedef struct _CMD_UPDATE_WMM_PARMS_T {
	AC_QUE_PARMS_T arACQueParms[AC_NUM];
	UINT_8 ucBssIndex;
	UINT_8 fgIsQBSS;
	UINT_8 aucReserved[2];
} CMD_UPDATE_WMM_PARMS_T, *P_CMD_UPDATE_WMM_PARMS_T;

typedef struct _CMD_TX_AMPDU_T {
	BOOLEAN fgEnable;
	UINT_8 aucReserved[3];
} CMD_TX_AMPDU_T, *P_CMD_TX_AMPDU_T;

typedef struct _CMD_ADDBA_REJECT {
	BOOLEAN fgEnable;
	UINT_8 aucReserved[3];
} CMD_ADDBA_REJECT_T, *P_CMD_ADDBA_REJECT_T;

#if CFG_M0VE_BA_TO_DRIVER
/* The status of an TX/RX BA entry in FW (NEGO means the negotiation process is in progress) */
typedef enum _ENUM_BA_ENTRY_STATUS_T {
	BA_ENTRY_STATUS_INVALID = 0,
	BA_ENTRY_STATUS_NEGO,
	BA_ENTRY_STATUS_ACTIVE,
	BA_ENTRY_STATUS_DELETING
} ENUM_BA_ENTRY_STATUS_T, *P_ENUM_BA_ENTRY_STATUS_T;
#endif

#if CFG_RX_BA_REORDERING_ENHANCEMENT
typedef enum _ENUM_NO_NEED_WATIT_DROP_REASON_T {
	PACKET_DROP_BY_FW = 0,
	PACKET_DROP_BY_DRIVER,
	PACKET_DROP_BY_INDEPENDENT_PKT
} ENUM_NO_NEED_WATIT_DROP_REASON_T, *P_ENUM_NO_NEED_WATIT_DROP_REASON_T;

typedef struct _NO_NEED_WAIT_PKT_T {
	QUE_ENTRY_T rQueEntry;
	UINT_16 u2SSN;
	ENUM_NO_NEED_WATIT_DROP_REASON_T eDropReason;
} NO_NEED_WAIT_PKT_T, *P_NO_NEED_WAIT_PKT_T;

typedef struct _EVENT_PACKET_DROP_BY_FW_T {
	/* Event header */
	UINT_16 u2Length;
	UINT_16 u2Reserved1;	/* Must be filled with 0x0001 (EVENT Packet) */
	UINT_8 ucEID;
	UINT_8 ucSeqNum;
	UINT_8 aucReserved2[2];

	/* Event Body */
	UINT_8 ucStaRecIdx;
	UINT_8 ucTid;
	UINT_16 u2StartSSN;
	UINT_8 au1BitmapSSN[QM_RX_MAX_FW_DROP_SSN_SIZE];
} EVENT_PACKET_DROP_BY_FW_T, *P_EVENT_PACKET_DROP_BY_FW_T;
#endif

/*******************************************************************************
 *                            P U B L I C   D A T A
 ********************************************************************************
 */

/*******************************************************************************
 *                           P R I V A T E   D A T A
 ********************************************************************************
 */

/*******************************************************************************
 *                                 M A C R O S
 ********************************************************************************
 */

#define QM_TX_SET_NEXT_MSDU_INFO(_prMsduInfoPreceding, _prMsduInfoNext) \
	((((_prMsduInfoPreceding)->rQueEntry).prNext) = (P_QUE_ENTRY_T)(_prMsduInfoNext))

#define QM_TX_SET_NEXT_SW_RFB(_prSwRfbPreceding, _prSwRfbNext) \
	((((_prSwRfbPreceding)->rQueEntry).prNext) = (P_QUE_ENTRY_T)(_prSwRfbNext))

#define QM_TX_GET_NEXT_MSDU_INFO(_prMsduInfo) \
	((P_MSDU_INFO_T)(((_prMsduInfo)->rQueEntry).prNext))

#define QM_RX_SET_NEXT_SW_RFB(_prSwRfbPreceding, _prSwRfbNext) \
	((((_prSwRfbPreceding)->rQueEntry).prNext) = (P_QUE_ENTRY_T)(_prSwRfbNext))

#define QM_RX_GET_NEXT_SW_RFB(_prSwRfb) \
	((P_SW_RFB_T)(((_prSwRfb)->rQueEntry).prNext))

#if 0
#define QM_GET_STA_REC_PTR_FROM_INDEX(_prAdapter, _ucIndex) \
	((((_ucIndex) != STA_REC_INDEX_BMCAST) && ((_ucIndex) != STA_REC_INDEX_NOT_FOUND)) ? \
	 &(_prAdapter->arStaRec[_ucIndex]) : NULL)
#endif

#define QM_GET_STA_REC_PTR_FROM_INDEX(_prAdapter, _ucIndex) \
	cnmGetStaRecByIndex(_prAdapter, _ucIndex)

#if 0
#define QM_TX_SET_MSDU_INFO_FOR_DATA_PACKET( \
		_prMsduInfo, \
		_ucTC, \
		_ucPacketType, \
		_ucFormatID, \
		_fgIs802_1x, \
		_fgIs802_11, \
		_u2PalLLH, \
		_u2AclSN, \
		_ucPsForwardingType, \
		_ucPsSessionID \
					) \
	{ \
		ASSERT(_prMsduInfo); \
		(_prMsduInfo)->ucTC = (_ucTC); \
		(_prMsduInfo)->ucPacketType = (_ucPacketType); \
		(_prMsduInfo)->ucFormatID = (_ucFormatID); \
		(_prMsduInfo)->fgIs802_1x = (_fgIs802_1x); \
		(_prMsduInfo)->fgIs802_11 = (_fgIs802_11); \
		(_prMsduInfo)->u2PalLLH = (_u2PalLLH); \
		(_prMsduInfo)->u2AclSN = (_u2AclSN); \
		(_prMsduInfo)->ucPsForwardingType = (_ucPsForwardingType); \
		(_prMsduInfo)->ucPsSessionID = (_ucPsSessionID); \
		(_prMsduInfo)->fgIsBurstEnd = (FALSE); \
	}
#else
#define QM_TX_SET_MSDU_INFO_FOR_DATA_PACKET( \
		_prMsduInfo, \
		_ucTC, \
		_ucPacketType, \
		_ucFormatID, \
		_fgIs802_1x, \
		_fgIs802_11, \
		_ucPsForwardingType \
					) \
	{ \
		ASSERT(_prMsduInfo); \
		(_prMsduInfo)->ucTC = (_ucTC); \
		(_prMsduInfo)->ucPacketType = (_ucPacketType); \
		(_prMsduInfo)->ucFormatID = (_ucFormatID); \
		(_prMsduInfo)->fgIs802_1x = (_fgIs802_1x); \
		(_prMsduInfo)->fgIs802_11 = (_fgIs802_11); \
		(_prMsduInfo)->ucPsForwardingType = (_ucPsForwardingType); \
	}
#endif

#define QM_INIT_STA_REC( \
		_prStaRec, \
		_fgIsValid, \
		_fgIsQoS, \
		_pucMacAddr \
		) \
	{ \
		ASSERT(_prStaRec); \
		(_prStaRec)->fgIsValid = (_fgIsValid); \
		(_prStaRec)->fgIsQoS = (_fgIsQoS); \
		(_prStaRec)->fgIsInPS = FALSE; \
		(_prStaRec)->ucPsSessionID = 0xFF; \
		COPY_MAC_ADDR((_prStaRec)->aucMacAddr, (_pucMacAddr)); \
	}

#if QM_ADAPTIVE_TC_RESOURCE_CTRL
#define QM_GET_TX_QUEUE_LEN(_prAdapter, _u4QueIdx) \
	(((_prAdapter)->rQM.au4AverageQueLen[(_u4QueIdx)] >> (_prAdapter)->rQM.u4QueLenMovingAverage))
#endif

#define WMM_IE_OUI_TYPE(fp)      (((P_IE_WMM_HDR_T)(fp))->ucOuiType)
#define WMM_IE_OUI_SUBTYPE(fp)   (((P_IE_WMM_HDR_T)(fp))->ucOuiSubtype)
#define WMM_IE_OUI(fp)           (((P_IE_WMM_HDR_T)(fp))->aucOui)

#if QM_DEBUG_COUNTER
#define QM_DBG_CNT_INC(_prQM, _index) { (_prQM)->au4QmDebugCounters[(_index)]++; }
#else
#define QM_DBG_CNT_INC(_prQM, _index) {}
#endif

#if CFG_RX_BA_REORDERING_ENHANCEMENT
#define QM_GET_PREVIOUS_SSN(_u2CurrSSN) \
	((UINT_16) (_u2CurrSSN == 0 ? (MAX_SEQ_NO_COUNT - 1) : (_u2CurrSSN - 1)))
#define QM_GET_DROP_BY_FW_SSN(_u2SSN) \
	((UINT_16) (_u2SSN >>= 4))
#endif


/*******************************************************************************
 *                   F U N C T I O N   D E C L A R A T I O N S
 ********************************************************************************
 */
/*----------------------------------------------------------------------------*/
/* Queue Management and STA_REC Initialization                                */
/*----------------------------------------------------------------------------*/

VOID qmInit(IN P_ADAPTER_T prAdapter);

#if QM_TEST_MODE
VOID qmTestCases(IN P_ADAPTER_T prAdapter);
#endif

VOID qmActivateStaRec(IN P_ADAPTER_T prAdapter, IN P_STA_RECORD_T prStaRec);

VOID qmDeactivateStaRec(IN P_ADAPTER_T prAdapter, IN P_STA_RECORD_T prStaRec);

VOID qmUpdateStaRec(IN P_ADAPTER_T prAdapter, IN P_STA_RECORD_T prStaRec);

/*----------------------------------------------------------------------------*/
/* TX-Related Queue Management                                                */
/*----------------------------------------------------------------------------*/

P_MSDU_INFO_T qmFlushTxQueues(IN P_ADAPTER_T prAdapter);

P_MSDU_INFO_T qmFlushStaTxQueues(IN P_ADAPTER_T prAdapter, IN UINT_32 u4StaRecIdx);

P_MSDU_INFO_T qmEnqueueTxPackets(IN P_ADAPTER_T prAdapter, IN P_MSDU_INFO_T prMsduInfoListHead);

P_MSDU_INFO_T qmDequeueTxPackets(IN P_ADAPTER_T prAdapter, IN P_TX_TCQ_STATUS_T prTcqStatus);

#if CFG_SUPPORT_MULTITHREAD
P_MSDU_INFO_T qmDequeueTxPacketsMthread(IN P_ADAPTER_T prAdapter, IN P_TX_TCQ_STATUS_T prTcqStatus);

BOOLEAN
qmAdjustTcQuotasMthread(IN P_ADAPTER_T prAdapter, OUT P_TX_TCQ_ADJUST_T prTcqAdjust, IN P_TX_TCQ_STATUS_T prTcqStatus);
#endif

BOOLEAN qmAdjustTcQuotas(IN P_ADAPTER_T prAdapter, OUT P_TX_TCQ_ADJUST_T prTcqAdjust, IN P_TX_TCQ_STATUS_T prTcqStatus);

#if QM_ADAPTIVE_TC_RESOURCE_CTRL
VOID qmReassignTcResource(IN P_ADAPTER_T prAdapter);

VOID qmUpdateAverageTxQueLen(IN P_ADAPTER_T prAdapter);

VOID qmDoAdaptiveTcResourceCtrl(IN P_ADAPTER_T prAdapter);

VOID qmCheckForFastTcResourceCtrl(IN P_ADAPTER_T prAdapter, IN UINT_8 ucTc);

#endif

VOID qmDetermineStaRecIndex(IN P_ADAPTER_T prAdapter, IN P_MSDU_INFO_T prMsduInfo);

UINT_32
qmDequeueTxPacketsFromPerStaQueues(IN P_ADAPTER_T prAdapter, OUT P_QUE_T prQue, IN UINT_8 ucTC, IN UINT_32
				   u4CurrentQuota, IN UINT_32 u4TotalQuota);

VOID
qmDequeueTxPacketsFromPerTypeQueues(IN P_ADAPTER_T prAdapter, OUT P_QUE_T prQue, IN UINT_8 ucTC, IN UINT_32
				    u4CurrentQuota, IN UINT_32 u4TotalQuota);

UINT_32
qmDequeueTxPacketsFromGlobalQueue(IN P_ADAPTER_T prAdapter, OUT P_QUE_T prQue, IN UINT_8 ucTC, IN UINT_32
				  u4CurrentQuota, IN UINT_32 u4TotalQuota);

VOID
qmSetStaRecTxAllowed(IN P_ADAPTER_T prAdapter, IN P_STA_RECORD_T prStaRec, IN BOOLEAN fgIsTxAllowed);

/*----------------------------------------------------------------------------*/
/* RX-Related Queue Management                                                */
/*----------------------------------------------------------------------------*/

VOID qmInitRxQueues(IN P_ADAPTER_T prAdapter);

P_SW_RFB_T qmFlushRxQueues(IN P_ADAPTER_T prAdapter);

P_SW_RFB_T qmHandleRxPackets(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfbListHead);

VOID qmProcessPktWithReordering(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb, OUT P_QUE_T prReturnedQue);

VOID qmProcessBarFrame(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb, OUT P_QUE_T prReturnedQue);

VOID
qmInsertFallWithinReorderPkt(IN P_SW_RFB_T prSwRfb, IN P_RX_BA_ENTRY_T prReorderQueParm, OUT P_QUE_T prReturnedQue);

VOID qmInsertFallAheadReorderPkt(IN P_SW_RFB_T prSwRfb, IN P_RX_BA_ENTRY_T prReorderQueParm, OUT P_QUE_T prReturnedQue);

VOID qmPopOutDueToFallWithin(IN P_ADAPTER_T prAdapter, IN P_RX_BA_ENTRY_T prReorderQueParm, OUT P_QUE_T prReturnedQue);

VOID qmPopOutDueToFallAhead(IN P_ADAPTER_T prAdapter, IN P_RX_BA_ENTRY_T prReorderQueParm, OUT P_QUE_T prReturnedQue);

VOID qmHandleReorderBubbleTimeout(IN P_ADAPTER_T prAdapter, IN ULONG ulParamPtr);

VOID qmHandleEventCheckReorderBubble(IN P_ADAPTER_T prAdapter, IN P_WIFI_EVENT_T prEvent);

VOID qmHandleMailboxRxMessage(IN MAILBOX_MSG_T prMailboxRxMsg);

BOOLEAN qmCompareSnIsLessThan(IN UINT_32 u4SnLess, IN UINT_32 u4SnGreater);

VOID qmHandleEventRxAddBa(IN P_ADAPTER_T prAdapter, IN P_WIFI_EVENT_T prEvent);

VOID qmHandleEventRxDelBa(IN P_ADAPTER_T prAdapter, IN P_WIFI_EVENT_T prEvent);

P_RX_BA_ENTRY_T qmLookupRxBaEntry(IN P_ADAPTER_T prAdapter, IN UINT_8 ucStaRecIdx, IN UINT_8 ucTid);

BOOL
qmAddRxBaEntry(IN P_ADAPTER_T prAdapter, IN UINT_8 ucStaRecIdx, IN UINT_8 ucTid, IN UINT_16 u2WinStart, IN UINT_16
	       u2WinSize);

VOID qmDelRxBaEntry(IN P_ADAPTER_T prAdapter, IN UINT_8 ucStaRecIdx, IN UINT_8 ucTid, IN BOOLEAN fgFlushToHost);

#if CFG_RX_BA_REORDERING_ENHANCEMENT
VOID qmInsertNoNeedWaitPkt(IN P_SW_RFB_T prSwRfb, IN ENUM_NO_NEED_WATIT_DROP_REASON_T eDropReason);
VOID qmHandleEventDropByFW(IN P_ADAPTER_T prAdapter, IN P_WIFI_EVENT_T prEvent);
VOID qmHandleNoNeedWaitPktList(IN P_RX_BA_ENTRY_T prReorderQueParm);
P_NO_NEED_WAIT_PKT_T qmSearchNoNeedWaitPktBySSN(IN P_RX_BA_ENTRY_T prReorderQueParm, IN UINT_32 u2SSN);
BOOLEAN qmIsIndependentPkt(IN P_SW_RFB_T prSwRfb);
VOID qmRemoveAllNoNeedWaitPkt(IN P_RX_BA_ENTRY_T prReorderQueParm);
VOID qmDumpNoNeedWaitPkt(IN P_RX_BA_ENTRY_T prReorderQueParm);
#endif

VOID mqmProcessAssocRsp(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb, IN PUINT_8 pucIE, IN UINT_16 u2IELength);

VOID mqmProcessBcn(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb, IN PUINT_8 pucIE, IN UINT_16 u2IELength);

BOOLEAN
mqmParseEdcaParameters(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb, IN PUINT_8 pucIE, IN UINT_16 u2IELength, IN
		       BOOLEAN fgForceOverride);

BOOLEAN mqmCompareEdcaParameters(IN P_IE_WMM_PARAM_T prIeWmmParam, IN P_BSS_INFO_T prBssInfo);

VOID mqmFillAcQueParam(IN P_IE_WMM_PARAM_T prIeWmmParam, IN UINT_32 u4AcOffset, OUT P_AC_QUE_PARMS_T prAcQueParams);

VOID mqmProcessScanResult(IN P_ADAPTER_T prAdapter, IN P_BSS_DESC_T prScanResult, OUT P_STA_RECORD_T prStaRec);

UINT_32
mqmFillWmmInfoIE(P_UINT_8 pucOutBuf, BOOLEAN fgSupportUAPSD, UINT_8 ucBmpDeliveryAC, UINT_8 ucBmpTriggerAC, UINT_8
		 ucUapsdSp);

UINT_32
mqmGenerateWmmInfoIEByStaRec(P_ADAPTER_T prAdapter, P_BSS_INFO_T prBssInfo, P_STA_RECORD_T prStaRec, P_UINT_8
			     pucOutBuf);

VOID mqmGenerateWmmInfoIE(IN P_ADAPTER_T prAdapter, IN P_MSDU_INFO_T prMsduInfo);

VOID mqmGenerateWmmParamIE(IN P_ADAPTER_T prAdapter, IN P_MSDU_INFO_T prMsduInfo);

#if CFG_SUPPORT_TDLS

UINT_32 mqmGenerateWmmParamIEByParam(P_ADAPTER_T prAdapter, P_BSS_INFO_T prBssInfo, PUINT_8 pOutBuf);
#endif

ENUM_FRAME_ACTION_T qmGetFrameAction(IN P_ADAPTER_T prAdapter,
				     IN UINT_8 ucBssIndex, IN UINT_8 ucStaRecIdx, IN P_MSDU_INFO_T prMsduInfo,
				     IN ENUM_FRAME_TYPE_IN_CMD_Q_T eFrameType, IN UINT_16 u2FrameLength);

VOID qmHandleEventBssAbsencePresence(IN P_ADAPTER_T prAdapter, IN P_WIFI_EVENT_T prEvent);

VOID qmHandleEventStaChangePsMode(IN P_ADAPTER_T prAdapter, IN P_WIFI_EVENT_T prEvent);

VOID mqmProcessAssocReq(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb, IN PUINT_8 pucIE, IN UINT_16 u2IELength);

VOID qmHandleEventStaUpdateFreeQuota(IN P_ADAPTER_T prAdapter, IN P_WIFI_EVENT_T prEvent);

VOID
qmUpdateFreeQuota(IN P_ADAPTER_T prAdapter, IN P_STA_RECORD_T prStaRec, IN UINT_8 ucUpdateMode, IN UINT_8 ucFreeQuota);

VOID qmFreeAllByBssIdx(IN P_ADAPTER_T prAdapter, IN UINT_8 ucBssIndex);

UINT_32 qmGetRxReorderQueuedBufferCount(IN P_ADAPTER_T prAdapter);

VOID qmDumpQueueStatus(IN P_ADAPTER_T prAdapter);

#if CFG_M0VE_BA_TO_DRIVER
VOID
mqmSendDelBaFrame(IN P_ADAPTER_T prAdapter, IN BOOLEAN fgIsInitiator, IN P_STA_RECORD_T prStaRec, IN UINT_32 u4Tid, IN
		  UINT_32 u4ReasonCode);

WLAN_STATUS
mqmCallbackAddBaRspSent(IN P_ADAPTER_T prAdapter, IN P_MSDU_INFO_T prMsduInfo, IN ENUM_TX_RESULT_CODE_T rTxDoneStatus);

VOID mqmTimeoutCheckIdleRxBa(IN P_ADAPTER_T prAdapter, IN ULONG ulParamPtr);

VOID
mqmRxModifyBaEntryStatus(IN P_ADAPTER_T prAdapter, IN P_RX_BA_ENTRY_T prRxBaEntry, IN ENUM_BA_ENTRY_STATUS_T eStatus);

VOID mqmHandleAddBaReq(IN P_ADAPTER_T prAdapter, IN P_SW_RFB_T prSwRfb);

VOID mqmHandleBaActionFrame(P_ADAPTER_T prAdapter, P_SW_RFB_T prSwRfb);
#endif

#if ARP_MONITER_ENABLE
VOID qmDetectArpNoResponse(P_ADAPTER_T prAdapter, P_MSDU_INFO_T prMsduInfo);
VOID qmResetArpDetect(VOID);
VOID qmHandleRxArpPackets(P_ADAPTER_T prAdapter, P_SW_RFB_T prSwRfb);
#endif

/*******************************************************************************
 *                              F U N C T I O N S
 ********************************************************************************
 */

#if QM_TEST_MODE
extern QUE_MGT_T g_rQM;
#endif
extern const UINT_8 aucTid2ACI[TX_DESC_TID_NUM];
extern const UINT_8 arNetwork2TcResource[HW_BSSID_NUM + 1][NET_TC_NUM];

#endif /* _QUE_MGT_H */
