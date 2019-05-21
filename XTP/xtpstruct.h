#pragma once
#include"..\sdk\include\xoms_api_fund_struct.h"

using namespace System;
using namespace::Runtime::InteropServices;
namespace XTP {
	namespace API {

		/// ��Ű汾�ŵ��ַ�������
		#define VERSION_LEN 16
		/// �汾������
		typedef char VersionType[VERSION_LEN];
		/// �ɽ������ַ�������
		#define TRADING_DAY_LEN 9
			/// ���֤ȯ������ַ�������
		#define TICKER_LEN 16
			/// ���֤ȯ���Ƶ��ַ�������
		#define TICKER_NAME_LEN 64
			/// ���ر�����ŵ��ַ�������
		#define LOCAL_ORDER_LEN         11
			/// ���������ŵ��ַ�������
		#define ORDER_EXCH_LEN          17
			/// �ɽ�ִ�б�ŵ��ַ�������
		#define EXEC_ID_LEN             18
			/// ����������Ա�����ַ�������
		#define BRANCH_PBU_LEN          7
			/// �û��ʽ��˻����ַ�������
		#define ACCOUNT_NAME_LEN        16
			///������Ϣ���ַ�������
		#define ERR_MSG_LEN  124
			/// �û��ʽ��˻����ַ�������
		#define ACCOUNT_NAME_LEN        16

			/// �û��ʽ��˻�������ַ�������
		#define ACCOUNT_PASSWORD_LEN 64
#pragma region basic struct

		/// <summary>
		/// XTP_PROTOCOL_TYPE ��һ��ͨѶ����Э�鷽ʽ
		/// </summary>
		public enum class PROTOCOL_TYPE
		{
			XTP_PROTOCOL_TCP = 1,	///<����TCP��ʽ����
			XTP_PROTOCOL_UDP		///<����UDP��ʽ����
		};

		///��־�����������
		public enum class LOG_LEVEL {
			XTP_LOG_LEVEL_FATAL, ///<���ش��󼶱�
			XTP_LOG_LEVEL_ERROR, ///<���󼶱�
			XTP_LOG_LEVEL_WARNING, ///<���漶��
			XTP_LOG_LEVEL_INFO,   ///<info����
			XTP_LOG_LEVEL_DEBUG,  ///<debug����
			XTP_LOG_LEVEL_TRACE   ///<trace����
		};

		[StructLayout(LayoutKind::Sequential)]
		public ref struct  RspInfoStruct
		{
			///�������
			Int32	error_id;
			///������Ϣ
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = ERR_MSG_LEN)]
			String^	error_msg;
		};

		/// <summary>
		/// EXCHANGE_TYPE �ǽ���������
		/// </summary>
		public enum class EXCHANGE_TYPE
		{
			XTP_EXCHANGE_SH = 1,	///<��֤
			XTP_EXCHANGE_SZ,		///<��֤
			XTP_EXCHANGE_MAX	///<�����ڵĽ���������
		};

		//////////////////////////////////////////////////////////////////////////
		///@brief ETF_REPLACE_TYPE�ֽ������ʶ����
		//////////////////////////////////////////////////////////////////////////
		public enum class ETF_REPLACE_TYPE
		{
			ERT_CASH_FORBIDDEN = 0,             ///<��ֹ�ֽ����
			ERT_CASH_OPTIONAL,                  ///<�����ֽ����
			ERT_CASH_MUST,                      ///<�����ֽ����
			ERT_CASH_RECOMPUTE_INTER_SZ,        ///<�����˲��ֽ����
			ERT_CASH_MUST_INTER_SZ,             ///<���б����ֽ����
			ERT_CASH_RECOMPUTE_INTER_OTHER,     ///<�ǻ����г��ɷ�֤ȯ�˲��ֽ����
			ERT_CASH_MUST_INTER_OTHER,          ///<��ʾ�ǻ����г��ɷ�֤ȯ�����ֽ����
			EPT_INVALID                         ///<��Чֵ
		};
		///ָ���ĺ�Լ
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  SpecificTickerStruct
		{
			///����������
			EXCHANGE_TYPE exchange_id;
			///��Լ���루��������������Ϣ������"600000  "
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^	ticker;
		};


		/// <summary>
		///ҵ������
		/// </summary>
		public enum class BUSINESS_TYPE
		{
			XTP_BUSINESS_TYPE_CASH = 0,            ///<��ͨ��Ʊҵ�񣨹�Ʊ������ETF�����ȣ�
			XTP_BUSINESS_TYPE_IPOS,                ///<�¹��깺ҵ�񣨶�Ӧ��price type��ѡ���޼����ͣ�
			XTP_BUSINESS_TYPE_REPO,                ///<�ع�ҵ�� ( ��Ӧ��price type��Ϊ�޼ۣ�side��Ϊ�� )
			XTP_BUSINESS_TYPE_ETF,                 ///<ETF����ҵ��
			XTP_BUSINESS_TYPE_MARGIN,              ///<������ȯҵ����δ֧�֣�
			XTP_BUSINESS_TYPE_DESIGNATION,         ///<ת�йܣ�δ֧�֣�
			XTP_BUSINESS_TYPE_ALLOTMENT,		   ///<���ҵ�񣨶�Ӧ��price type��ѡ���޼�����,side��Ϊ��
			XTP_BUSINESS_TYPE_STRUCTURED_FUND_PURCHASE_REDEMPTION,	   ///<�ּ���������ҵ��
			XTP_BUSINESS_TYPE_STRUCTURED_FUND_SPLIT_MERGE,	   ///<�ּ������ֺϲ�ҵ��
			XTP_BUSINESS_TYPE_MONEY_FUND,		   ///<���һ���ҵ����δ֧�֣�
			XTP_BUSINESS_TYPE_OPTION,              ///<��Ȩҵ��
			XTP_BUSINESS_TYPE_EXECUTE,             ///<��Ȩ
			XTP_BUSINESS_TYPE_FREEZE,              ///<�����������ݲ�֧��
			XTP_BUSINESS_TYPE_UNKNOWN              ///<δ֪����
		};

		/////////////////////////////////////////////////////////////////////////
		///@brief XTP_TBT_TYPE��һ����ʻر�����
		/////////////////////////////////////////////////////////////////////////
		public enum class TBT_TYPE {
			XTP_TBT_ENTRUST = 1,	///<���ί��
			XTP_TBT_TRADE = 2,		///<��ʳɽ�
		};

		/////////////////////////////////////////////////////////////////////////
		///@brief XTP_OPT_CALL_OR_PUT_TYPE��һ���Ϲ����Ϲ�����
		/////////////////////////////////////////////////////////////////////////
		public enum class OPT_CALL_OR_PUT_TYPE {
			XTP_OPT_CALL = 1,	    ///<�Ϲ�
			XTP_OPT_PUT = 2,		///<�Ϲ�
		};

		/////////////////////////////////////////////////////////////////////////
		///@brief XTP_OPT_EXERCISE_TYPE_TYPE��һ����Ȩ��ʽ����
		/////////////////////////////////////////////////////////////////////////
		public enum class OPT_EXERCISE_TYPE_TYPE {
			XTP_OPT_EXERCISE_TYPE_EUR = 1,	    ///<ŷʽ
			XTP_OPT_EXERCISE_TYPE_AME = 2,		///<��ʽ
		};

		/////////////////////////////////////////////////////////////////////////
		///@brief XTP_POSITION_DIRECTION_TYPE��һ���ֲַ�������
		/////////////////////////////////////////////////////////////////////////
		public enum class POSITION_DIRECTION_TYPE {
			XTP_POSITION_DIRECTION_NET = 0,	    ///<��
			XTP_POSITION_DIRECTION_LONG,		///<�ࣨ��Ȩ��ΪȨ������
			XTP_POSITION_DIRECTION_SHORT,       ///<�գ���Ȩ��Ϊ���񷽣�
			XTP_POSITION_DIRECTION_COVERED,     ///<���ң���Ȩ��Ϊ�������񷽣�
		};

		/////////////////////////////////////////////////////////////////////////
		///@brief XTP_CRD_CASH_REPAY_STATUS��һ��������ȯֱ�ӻ���״̬����
		/////////////////////////////////////////////////////////////////////////
		public enum class CRD_CR_STATUS {
			XTP_CRD_CR_INIT = 0,        ///< ��ʼ��δ����״̬
			XTP_CRD_CR_SUCCESS,         ///< �ѳɹ�����״̬
			XTP_CRD_CR_FAILED,          ///< ����ʧ��״̬
		};
#pragma endregion


#pragma region api data struct
		//////////////////////////////////////////////////////////////////////////
		///@brief XTP_ACCOUNT_TYPE�˻�����
		//////////////////////////////////////////////////////////////////////////
		public enum class ACCOUNT_TYPE
		{
			XTP_ACCOUNT_NORMAL = 0,	///<��ͨ�˻�
			XTP_ACCOUNT_CREDIT,		///<�����˻�
			XTP_ACCOUNT_DERIVE,		///<����Ʒ�˻�
			XTP_ACCOUNT_UNKNOWN		///<δ֪�˻�����
		};
		/////////////////////////////////////////////////////////////////////////
		///@brief XTP_FUND_TRANSFER_TYPE���ʽ���ת��������
		/////////////////////////////////////////////////////////////////////////
		public enum class FUND_TRANSFER_TYPE
		{
			XTP_FUND_TRANSFER_OUT = 0,		///<ת�� ��XTPת������̨
			XTP_FUND_TRANSFER_IN,	        ///<ת�� �ӹ�̨ת��XTP
			XTP_FUND_INTER_TRANSFER_OUT,    ///<��ڵ�ת�� �ӱ�XTP�ڵ�1��ת�����Զ�XTP�ڵ�2��XTP������֮�仮����ֻ�ܿ��˻��û�ʹ��
			XTP_FUND_INTER_TRANSFER_IN,     ///<��ڵ�ת�� �ӶԶ�XTP�ڵ�2��ת�뵽��XTP�ڵ�1��XTP������֮�仮����ֻ�ܿ��˻��û�ʹ��
			XTP_FUND_TRANSFER_UNKNOWN		///<δ֪����
		};

		/////////////////////////////////////////////////////////////////////////
		///@brief XTP_FUND_OPER_STATUS��̨�ʽ�������
		/////////////////////////////////////////////////////////////////////////
		public enum class FUND_OPER_STATUS {
			XTP_FUND_OPER_PROCESSING = 0,	///<XTP���յ������ڴ�����
			XTP_FUND_OPER_SUCCESS,			///<�ɹ�
			XTP_FUND_OPER_FAILED,			///<ʧ��
			XTP_FUND_OPER_SUBMITTED,		///<���ύ�����й�̨����
			XTP_FUND_OPER_UNKNOWN			///<δ֪
		};
		/////////////////////////////////////////////////////////////////////////
		///@brief SPLIT_MERGE_STATUS��һ���������ֺϲ�״̬����
		/////////////////////////////////////////////////////////////////////////
		public enum class SPLIT_MERGE_STATUS {
			XTP_SPLIT_MERGE_STATUS_ALLOW = 0,	///<�����ֺͺϲ�
			XTP_SPLIT_MERGE_STATUS_ONLY_SPLIT,	///<ֻ�����֣�������ϲ�
			XTP_SPLIT_MERGE_STATUS_ONLY_MERGE,	///<ֻ����ϲ�����������
			XTP_SPLIT_MERGE_STATUS_FORBIDDEN	///<�������ֺϲ�
		};


		//////////////////////////////////////////////////////////////////////////
		///�г�����
		//////////////////////////////////////////////////////////////////////////
		public enum class MARKET_TYPE
		{
			XTP_MKT_INIT = 0,///<��ʼ��ֵ����δ֪
			XTP_MKT_SZ_A = 1,///<����A��
			XTP_MKT_SH_A,    ///<�Ϻ�A��
							 /*
							 XTP_MKT_SZ_B,    ///<����B��
							 XTP_MKT_SH_B,    ///<�Ϻ�B��*/
			XTP_MKT_MAX  ///<�г����͸���
		};

		/////////////////////////////////////////////////////////////////////////
		///TXTPTradeTypeType�ǳɽ���������
		/////////////////////////////////////////////////////////////////////////
		public enum struct TradeTypeType :Byte
		{
			COMMON = '0',//��ͨ�ɽ�
			CASH = '1',//�ֽ����
			PRIMARY = '2'//һ���г��ɽ�
		};


		//////////////////////////////////////////////////////////////////////////
		///@brief TICKER_TYPE֤ȯ����
		//////////////////////////////////////////////////////////////////////////
		public enum struct TICKER_TYPE
		{
			XTP_TICKER_TYPE_STOCK = 0,            ///<��ͨ��Ʊ
			XTP_TICKER_TYPE_INDEX,                ///<ָ��
			XTP_TICKER_TYPE_FUND,                 ///<����
			XTP_TICKER_TYPE_BOND,                 ///<ծȯ
			XTP_TICKER_TYPE_OPTION,               ///<��Ȩ
			XTP_TICKER_TYPE_UNKNOWN               ///<δ֪����
		};

		
		/// <summary>
		/// ������������
		/// </summary>
		public enum class SIDE_TYPE
		{
			BUY = 1,	///<���¹��깺��ETF��ȣ�
			SELL = 2,		///<������ع���
			///�깺
			PURCHASE = 7,
			///���
			REDEMPTION = 8,
			///���
			SPLIT = 9,
			///�ϲ�
			MERGE = 10,
			///�İ�֮���side�ı��ң��ݲ�֧��
			COVER = 11,
			///�İ�֮���side��������Ӧ��ƽ��ʶΪ����/��������Ӧ��ƽ��ʶΪƽ��
			FREEZE = 12,
			/// ��������
			TRADE = 21,
			/// ��ȯ����
			SHORT_SELL = 22,
			/// ��ȯ����
			REPAY_MARGIN = 23,
			/// ��ȯ��ȯ
			REPAY_STOCK = 24,
			/// �ֽ𻹿��������ͨ����Э�飬�������Ͳ�ѯЭ�飩
			CASH_REPAY_MARGIN = 25,
			/// ��ȯ��ȯ
			STOCK_REPAY_STOCK = 26,
			/// ��ȯ��ת
			SURSTK_TRANS = 27,
			/// ����Ʒת��
			GRTSTK_TRANSIN = 28,
			/// ����Ʒת��
			GRTSTK_TRANSOUT = 29,
			UNKNOWN,	///<δ֪������Ч��������
		};

		////////////////////////////////////////////////////////////////////////
///@brief XTP_POSITION_EFFECT_TYPE�ǿ�ƽ��ʶ����
/////////////////////////////////////////////////////////////////////////
		public enum class POSITION_EFFECT_TYPE
		{
			/// ��ʼֵ��δֵ֪��ƽ��ʶ���ֻ�����
			INIT = 0,
			/// ��
			OPEN = 1,
			/// ƽ
			CLOSE = 2,
			/// ǿƽ
			FORCECLOSE = 3,
			/// ƽ��
			CLOSETODAY = 4,
			/// ƽ��
			CLOSEYESTERDAY = 5,
			/// ǿ��
			FORCEOFF = 6,
			/// ����ǿƽ
			LOCALFORCECLOSE = 7,
			/// ����ҵ��׷��ǿƽ
			CREDIT_FORCE_COVER = 8,
			/// ����ҵ���峥ǿƽ
			CREDIT_FORCE_CLEAR = 9,
			/// ����ҵ���Լ����ǿƽ
			CREDIT_FORCE_DEBT = 10,
			/// ����ҵ��������ǿƽ
			CREDIT_FORCE_UNCOND = 11,
			/// δ֪�Ŀ�ƽ��ʶ����
			UNKNOWN = 12
		};
		/////////////////////////////////////////////////////////////////////////
		///TXTPOrderTypeType��һ��������������
		/////////////////////////////////////////////////////////////////////////
		public enum class TOrderTypeType
		{
			Normal = '0',	///����
			DeriveFromQuote = '1',		///��������
			DeriveFromCombination = '2',		///�������
			Combination = '3',		///��ϱ���
			ConditionalOrder = '4',		///������
			Swap = '5',		///������
		};
		/////////////////////////////////////////////////////////////////////////
		///TXTPTradeTypeType��һ���ɽ���������
		/////////////////////////////////////////////////////////////////////////
		public enum class TTradeTypeType
		{
			XTP_TRDT_Common = '0',	///��ͨ�ɽ�
			XTP_TRDT_OptionsExecution = '1',		///��Ȩִ��
			XTP_TRDT_OTC = '2',		///OTC�ɽ�
			XTP_TRDT_EFPDerived = '3',		///��ת�������ɽ�
			XTP_TRDT_CombinationDerived = '4',		///��������ɽ�
			XTP_TRDT_EFTPurchase = '5',		///ETF�깺
			XTP_TRDT_EFTRedem = '6'		///ETF���
		};


		/////////////////////////////////////////////////////////////////////////
		///@enum XTP_TE_RESUME_TYPE ��һ��˽�����ش���ʽ
		/////////////////////////////////////////////////////////////////////////
		public enum class TE_RESUME_TYPE
		{
			XTP_TERT_RESTART = 0,	///<�ӱ������տ�ʼ�ش�
			XTP_TERT_RESUME,		///<�Ӵ��ϴ��յ�������
			XTP_TERT_QUICK			///<ֻ���͵�¼��˽����������
		};

		/////////////////////////////////////////////////////////////////////////
		///XTP_ORDER_SUBMIT_STATUS_TYPE��һ�������ύ״̬����
		/////////////////////////////////////////////////////////////////////////
		public enum class ORDER_SUBMIT_STATUS_TYPE
		{
			XTP_ORDER_SUBMIT_STATUS_INSERT_SUBMITTED = 1, ///<�����Ѿ��ύ
			XTP_ORDER_SUBMIT_STATUS_INSERT_ACCEPTED,///<�����Ѿ�������
			XTP_ORDER_SUBMIT_STATUS_INSERT_REJECTED,///<�����Ѿ����ܾ�
			XTP_ORDER_SUBMIT_STATUS_CANCEL_SUBMITTED,///<�����Ѿ��ύ
			XTP_ORDER_SUBMIT_STATUS_CANCEL_REJECTED,///<�����Ѿ����ܾ�
			XTP_ORDER_SUBMIT_STATUS_CANCEL_ACCEPTED ///<�����Ѿ�������
		};

		/////////////////////////////////////////////////////////////////////////
		///@enum XTP_ORDER_ACTION_STATUS_TYPE ��һ����������״̬����
		/////////////////////////////////////////////////////////////////////////
		public enum class ORDER_ACTION_STATUS_TYPE
		{
			XTP_ORDER_ACTION_STATUS_SUBMITTED = 1,	///<�Ѿ��ύ
			XTP_ORDER_ACTION_STATUS_ACCEPTED,		///<�Ѿ�����
			XTP_ORDER_ACTION_STATUS_REJECTED		///<�Ѿ����ܾ�
		};

		/////////////////////////////////////////////////////////////////////////
		///XTP_ORDER_STATUS_TYPE��һ������״̬����
		/////////////////////////////////////////////////////////////////////////
		public enum class ORDER_STATUS_TYPE
		{
			XTP_ORDER_STATUS_INIT = 0,///<��ʼ��
			XTP_ORDER_STATUS_ALLTRADED = 1,           ///<ȫ���ɽ�
			XTP_ORDER_STATUS_PARTTRADEDQUEUEING,  ///<���ֳɽ�
			XTP_ORDER_STATUS_PARTTRADEDNOTQUEUEING, ///<���ֳ���
			XTP_ORDER_STATUS_NOTRADEQUEUEING,   ///<δ�ɽ�
			XTP_ORDER_STATUS_CANCELED,  ///<�ѳ���
			XTP_ORDER_STATUS_REJECTED,  ///<�Ѿܾ�
			XTP_ORDER_STATUS_UNKNOWN  ///<δ֪
		};
		/////////////////////////////////////////////////////////////////////////
		///@enum XTP_PRICE_TYPE ��һ���۸�����
		/////////////////////////////////////////////////////////////////////////
		public enum class PRICE_TYPE
		{
			XTP_PRICE_LIMIT = 1,           ///<�޼۵�-��/�� / ����Ȩ������ͨ��Ʊҵ���⣬����ҵ���ʹ�ô������ͣ�
			XTP_PRICE_BEST_OR_CANCEL,      ///<��ʱ�ɽ�ʣ��ת�������м۵�-�� /����Ȩ
			XTP_PRICE_BEST5_OR_LIMIT,      ///<�����嵵��ʱ�ɽ�ʣ��ת�޼ۣ��м۵�-��
			XTP_PRICE_BEST5_OR_CANCEL,     ///<����5����ʱ�ɽ�ʣ��ת�������м۵�-����
			XTP_PRICE_ALL_OR_CANCEL,       ///<ȫ���ɽ�����,�м۵�-��/����Ȩ
			XTP_PRICE_FORWARD_BEST,        ///<�������ţ��м۵�-��
			XTP_PRICE_REVERSE_BEST_LIMIT,  ///<�Է�����ʣ��ת�޼ۣ��м۵�-��/����Ȩ
			XTP_PRICE_LIMIT_OR_CANCEL,	   ///<��Ȩ�޼��걨FOK
			XTP_PRICE_TYPE_UNKNOWN,		   ///<δ֪������Ч�۸�����
		};

		///��ѯ�ּ�������Ϣ�ṹ��
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryStructuredFundInfoReq
		{
			EXCHANGE_TYPE   exchange_id;  ///<���������룬����Ϊ��
										  ///<�ּ�����ĸ������룬����Ϊ�գ����Ϊ�գ���Ĭ�ϲ�ѯ���еķּ�����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                sf_ticker;
		};

		//////////////////////////////////////////////////////////////////////////
		///��ѯ�ּ�������Ϣ��Ӧ�ṹ��
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  StructuredFundInfo
		{
			///<����������
			EXCHANGE_TYPE   exchange_id;
			///<�ּ�����ĸ�������
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                sf_ticker;
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_NAME_LEN)]
			String^                 sf_ticker_name; ///<�ּ�����ĸ��������
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                 ticker;   ///<�ּ������ӻ������
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_NAME_LEN)]
			String^                 ticker_name; ///<�ּ������ӻ�������
			SPLIT_MERGE_STATUS	split_merge_status;   ///<���������ֺϲ�״̬
			UInt32            ratio; ///<��ֺϲ�����
			UInt32            min_split_qty;///<��С�������
			UInt32            min_merge_qty; ///<��С�ϲ�����
			double              net_price;///<����ֵ
		};

		//////////////////////////////////////////////////////////////////////////
		///��ѯ��ƱETF��Լ�������--����ṹ��,
		///�������Ϊ����������:1,�����򷵻������г���ETF��Լ��Ϣ��
		///                  2,ֻ��дmarket,���ظý����г��½��
		///                   3,��дmarket��ticker����,ֻ���ظ�etf��Ϣ��
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryETFBaseReq
		{
			///�����г�
			MARKET_TYPE    market;
			///ETF��������
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^               ticker;
		};


		//////////////////////////////////////////////////////////////////////////
		///��ѯ��ƱETF��Լ�������--��Ӧ�ṹ��
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryETFBaseRsp
		{
			MARKET_TYPE     market;                             ///<�����г�
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                etf;                ///<etf����,����,����ͳһʹ�øô���
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                subscribe_redemption_ticker;    ///<etf�깺��ش���
			Int32             unit;                               ///<��С�깺��ص�λ��Ӧ��ETF����,������֤"50ETF"����900000
			Int32             subscribe_status;                   ///<�Ƿ������깺,1-����,0-��ֹ
			Int32             redemption_status;                  ///<�Ƿ��������,1-����,0-��ֹ
			double              max_cash_ratio;                     ///<����ֽ��������,С��1����ֵ   TODO �Ƿ����double
			double              estimate_amount;                    ///<T��Ԥ�����
			double              cash_component;                     ///<T-X���ֽ���
			double              net_value;                          ///<����λ��ֵ
			double              total_amount;                       ///<��С���굥λ��ֵ�ܽ��=net_value*unit
		};



		//////////////////////////////////////////////////////////////////////////
		///��ѯ��ƱETF��Լ�ɷֹ���Ϣ--����ṹ��,�������Ϊ:�����г�+ETF��������
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryETFComponentReq
		{
			///�����г�
			MARKET_TYPE     market;
			///ETF��������
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                ticker;
		};


		//////////////////////////////////////////////////////////////////////////
		///��ѯ��ƱETF��Լ�ɷֹ���Ϣ--��Ӧ�ṹ��
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryETFComponentRsp
		{
			///�����г�
			MARKET_TYPE     market;
			///ETF����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                ticker;
			///�ɷݹɴ���
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                component_ticker;
			///�ɷݹ�����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_NAME_LEN)]
			String^                component_name;
			///�ɷݹ�����
			Int64             quantity;
			///�ɷݹɽ����г�
			MARKET_TYPE     component_market;
			///�ɷݹ������ʶ
			ETF_REPLACE_TYPE    replace_type;
			///��۱���
			double              premium_ratio;
			///�ɷֹ������ʶΪ�����ֽ����ʱ����ܽ��
			double              amount;

		};

		//////////////////////////////////////////////////////////////////////////
		///��ѯ���տ��깺�¹���Ϣ
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryIPOTickerRsp {
			///�����г�
			MARKET_TYPE     market;
			///�깺����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                ticker;
			///�깺��Ʊ����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_NAME_LEN)]
			String^                ticker_name;
			///�깺�۸�
			double              price;
			///�깺��Ԫ         
			Int32             unit;
			///��������깺����
			Int32             qty_upper_limit;
		};


		//////////////////////////////////////////////////////////////////////////
		///��ѯ�û��깺���
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryIPOQuotaRsp {
			///�����г�
			MARKET_TYPE     market;
			///���깺���
			Int32             quantity;
		};

		//////////////////////////////////////////////////////////////////////////
///��ѯ��Ȩ���۽���ҵ��ο���Ϣ--����ṹ��,�������Ϊ:�����г�+8λ��Ȩ����
//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryOptionAuctionInfoReq {
			///�����г�
			MARKET_TYPE     market;
			///8λ��Ȩ��Լ����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                                ticker;
		};

		//////////////////////////////////////////////////////////////////////////
		///��ѯ��Ȩ���۽���ҵ��ο���Ϣ
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryOptionAuctionInfoRsp {
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                                ticker;             ///<��Լ���룬����ticker���ñ��ֶ�
			MARKET_TYPE     security_id_source;                 ///<֤ȯ����Դ
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_NAME_LEN)]
			String^                                symbol;        ///<��Լ���
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_NAME_LEN)]
			String^                                contract_id;   ///<��Լ���״���
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                                underlying_security_id; ///<����֤ȯ����
			MARKET_TYPE     underlying_security_id_source;      ///<����֤ȯ����Դ

			UInt32            list_date;                          ///<�������ڣ���ʽΪYYYYMMDD
			UInt32            last_trade_date;                    ///<������գ���ʽΪYYYYMMDD
			TICKER_TYPE     ticker_type;                        ///<֤ȯ���
			Int32             day_trading;                        ///<�Ƿ�֧�ֵ��ջ�ת���ף�1-����0-������

			OPT_CALL_OR_PUT_TYPE    call_or_put;                ///<�Ϲ����Ϲ�
			UInt32            delivery_day;                       ///<��Ȩ�����գ���ʽΪYYYYMMDD
			UInt32            delivery_month;                     ///<�����·ݣ���ʽΪYYYYMM

			OPT_EXERCISE_TYPE_TYPE  exercise_type;              ///<��Ȩ��ʽ
			UInt32            exercise_begin_date;                ///<��Ȩ��ʼ���ڣ���ʽΪYYYYMMDD
			UInt32            exercise_end_date;                  ///<��Ȩ�������ڣ���ʽΪYYYYMMDD
			double              exercise_price;                     ///<��Ȩ�۸�

			Int64             qty_unit;                           ///<������λ������ĳһ֤ȯ�걨��ί�У���ί�������ֶα���Ϊ��֤ȯ������λ��������
			Int64             contract_unit;                      ///<��Լ��λ
			Int64             contract_position;                  ///<��Լ�ֲ���

			double              prev_close_price;                   ///<��Լǰ���̼�
			double              prev_clearing_price;                ///<��Լǰ�����

			Int64             lmt_buy_max_qty;                    ///<�޼��������
			Int64             lmt_buy_min_qty;                    ///<�޼�����С��
			Int64             lmt_sell_max_qty;                   ///<�޼��������
			Int64             lmt_sell_min_qty;                   ///<�޼�����С��
			Int64             mkt_buy_max_qty;                    ///<�м��������
			Int64             mkt_buy_min_qty;                    ///<�м�����С��
			Int64             mkt_sell_max_qty;                   ///<�м��������
			Int64             mkt_sell_min_qty;                   ///<�м�����С��

			double              price_tick;                         ///<��С���۵�λ
			double              upper_limit_price;                  ///<��ͣ��
			double              lower_limit_price;                  ///<��ͣ��
			double              sell_margin;                        ///<������ÿ�ű�֤��
			double              margin_ratio_param1;                ///<��������֤������������һ
			double              margin_ratio_param2;                ///<��������֤��������������

			[MarshalAs(UnmanagedType::ByValArray, SizeConst = 20)]
			array<UInt64>^ unknown;                        ///<�������ֶΣ�
		};


		//////////////////////////////////////////////////////////////////////////
		///������ȯֱ�ӻ�����Ӧ��Ϣ
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  CrdCashRepayRsp
		{
			Int64 xtp_id;             ///< ֱ�ӻ��������XTPID
			double  request_amount;     ///< ֱ�ӻ����������
			double  cash_repay_amount;  ///< ʵ�ʻ���ʹ�ý��
		};

		//////////////////////////////////////////////////////////////////////////
		///����������ȯֱ�ӻ����¼��Ϣ
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  CrdCashRepayInfo
		{
			Int64                     xtp_id;             ///< ֱ�ӻ��������XTPID
			CRD_CR_STATUS           status;             ///< ֱ�ӻ����״̬
			double                      request_amount;     ///< ֱ�ӻ����������
			double                      cash_repay_amount;  ///< ʵ�ʻ���ʹ�ý��
			POSITION_EFFECT_TYPE    position_effect;    ///< ǿƽ��־
		};

		//////////////////////////////////////////////////////////////////////////
		///����������ȯ��ծ��¼��Ϣ
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  CrdDebtInfo
		{
			Int32             debt_type;              ///< ��ծ��Լ����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = 33)]
			String^                                debt_id;            ///< ��ծ��Լ���
			Int64             position_id;            ///< ��ծ��Ӧ����ͷ����
			UInt64            order_xtp_id;           ///< ���ɸ�ծ�Ķ�����ţ��ǵ��ո�ծ�޴���
			Int32             debt_status;            ///< ��ծ��Լ״̬
			MARKET_TYPE     market;                 ///< �г�
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                                ticker; ///< ֤ȯ����
			UInt64            order_date;             ///< ί������
			UInt64            end_date;               ///< ��ծ��ֹ����
			UInt64            orig_end_date;          ///< ��ծԭʼ��ֹ����
			bool                is_extended;            ///< �����Ƿ���յ�չ������
			double              remain_amt;             ///< δ�������
			Int64             remain_qty;             ///< δ��������
			double              remain_principal;       ///< δ����������
		};

		//////////////////////////////////////////////////////////////////////////
		///������ȯ�����ʻ�����
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  CrdFundInfo
		{
			double maintenance_ratio;       ///< ά�ֵ���Ʒ����
			double line_of_credit;          ///< �������Ŷ��
			double guaranty;                ///< ���ڱ�֤�������
			double position_amount;         ///< ����ͷ����ý��ڲ��ӿڣ���ʽ�汾��Ҫɾ��
		};

		//////////////////////////////////////////////////////////////////////////
		///������ȯָ��֤ȯ�ϵĸ�ծδ������
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  ClientQueryCrdDebtStockReq
		{
			MARKET_TYPE market;                 ///< �г�
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                            ticker; ///< ֤ȯ����
		};

		[StructLayout(LayoutKind::Sequential)]
		public ref struct  CrdDebtStockInfo
		{
			MARKET_TYPE market;                     ///< �г�
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                            ticker;     ///< ֤ȯ����
			Int64         remain_quantity;            ///< ��ծδ������
			Int64         order_withhold_quantity;    ///< �ҵ�δ�ɻ�ȯ����
		};

		//////////////////////////////////////////////////////////////////////////
		///��ȯͷ��֤ȯ��ѯ
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  ClientQueryCrdPositionStockReq
		{
			MARKET_TYPE market;                 ///< ֤ȯ�г�
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                            ticker; ///< ֤ȯ����
		};

		[StructLayout(LayoutKind::Sequential)]
		public ref struct  ClientQueryCrdPositionStkInfo {

			MARKET_TYPE market;                 ///< ֤ȯ�г�
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                            ticker; ///< ֤ȯ����
			Int64         limit_qty;              ///< ��ȯ����
			Int64         yesterday_qty;          ///< ��������ȯ����
			Int64         left_qty;               ///< ʣ�����ȯ����
			Int64         frozen_qty;             ///< ������ȯ����
		};


#pragma endregion

#pragma region quote struct

		public	enum class MARKETDATA_TYPE {
			XTP_MARKETDATA_ACTUAL = 0, // �ֻ�(��Ʊ/����/ծȯ��)
			XTP_MARKETDATA_OPTION = 1, // ��Ȩ
		};

		///��Ʊ������ծȯ�ȶ�������
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  MarketDataStockExData {
			///ί����������(SH,SZ)
			Int64 total_bid_qty;
			///ί����������(SH,SZ)
			Int64 total_ask_qty;
			///��Ȩƽ��ί��۸�(SH,SZ)
			double ma_bid_price;
			///��Ȩƽ��ί���۸�(SH,SZ)
			double ma_ask_price;
			///ծȯ��Ȩƽ��ί��۸�(SH)
			double ma_bond_bid_price;
			///ծȯ��Ȩƽ��ί���۸�(SH)
			double ma_bond_ask_price;
			///ծȯ����������(SH)
			double yield_to_maturity;
			///����ʵʱ�ο���ֵ(SH,SZ)
			double iopv;
			///ETF�깺����(SH)
			Int32 etf_buy_count;
			///ETF��ر���(SH)
			Int32 etf_sell_count;
			///ETF�깺����(SH)
			double etf_buy_qty;
			///ETF�깺���(SH)
			double etf_buy_money;
			///ETF�������(SH)
			double etf_sell_qty;
			///ETF��ؽ��(SH)
			double etf_sell_money;
			///Ȩִ֤�е�������(SH)
			double total_warrant_exec_qty;
			///Ȩ֤��ͣ�۸�Ԫ��(SH)
			double warrant_lower_price;
			///Ȩ֤��ͣ�۸�Ԫ��(SH)
			double warrant_upper_price;
			///���볷������(SH)
			Int32 cancel_buy_count;
			///������������(SH)
			Int32 cancel_sell_count;
			///���볷������(SH)
			double cancel_buy_qty;
			///������������(SH)
			double cancel_sell_qty;
			///���볷�����(SH)
			double cancel_buy_money;
			///�����������(SH)
			double cancel_sell_money;
			///�����ܱ���(SH)
			Int64 total_buy_count;
			///�����ܱ���(SH)
			Int64 total_sell_count;
			///����ί�гɽ����ȴ�ʱ��(SH)
			Int32 duration_after_buy;
			///����ί�гɽ����ȴ�ʱ��(SH)
			Int32 duration_after_sell;
			///��ί�м�λ��(SH)
			Int32 num_bid_orders;
			///����ί�м�λ��(SH)
			Int32 num_ask_orders;

			///����T-1�վ�ֵ(SZ)
			double pre_iopv;
			///Ԥ��
			Int64 r1;
			///Ԥ��
			Int64 r2;
		};

		// ��Ȩ��������
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  MarketDataOptionExData {
			///�������жϲο���(SH)
			double  auction_price;
			///�������жϼ��Ͼ�������ƥ����(SH)
			Int64 auction_qty;
			///���ѯ��ʱ��(SH)
			Int64 last_enquiry_time;
		};
		///����
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  MarketDataStruct
		{
			// ����
			///����������
			EXCHANGE_TYPE exchange_id;
			///��Լ���루��������������Ϣ��
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^	ticker;

			// ��Ʊ�ȼ۸�
			///���¼�
			double	last_price;
			///������
			double	pre_close_price;
			///����
			double	open_price;
			///��߼�
			double	high_price;
			///��ͼ�
			double	low_price;
			///������
			double	close_price;

			// ��Ȩ������
			Int64 pre_total_long_positon;
			///�ֲ���(��)
			Int64	total_long_positon;
			///���ս����
			double	pre_settl_price;
			///���ս����
			double	settl_price;

			// �ǵ�ͣ
			///��ͣ��
			double	upper_limit_price;
			///��ͣ��
			double	lower_limit_price;
			///Ԥ��
			double	pre_delta;
			///Ԥ��
			double	curr_delta;

			/// ʱ����
			Int64 data_time;

			// ��������
			///����
			Int64	qty;
			///�ɽ����
			double	turnover;
			///���վ���
			double	avg_price;

			// ������
			///ʮ�������
			array<double>^ bid;
			///ʮ��������
			array<double>^	ask;
			///ʮ��������
			array<Int64>^	bid_qty;
			///ʮ��������
			array<Int64>^	ask_qty;

			// ltsû�а��������ݣ�Ŀǰδ��д��
			///�ɽ�����
			Int64 trades_count;
			///��ǰ����״̬˵��
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = 8)]
			String^ ticker_status;
			MarketDataStockExData stk;
			MarketDataOptionExData opt;
			///������union��������������
			MARKETDATA_TYPE data_type;
			///Ԥ��
			Int32 r4;
		};

		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QuoteStaticInfoStruct {
			///����������
			EXCHANGE_TYPE exchange_id;
			///��Լ���루��������������Ϣ���������ո���'\0'��β
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^ ticker;
			/// ��Լ����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_NAME_LEN)]
			String^ ticker_name;
			/// ��Լ����
			TICKER_TYPE ticker_type;
			///������
			double  pre_close_price;
			///��ͣ���
			double  upper_limit_price;
			///��ͣ���
			double  lower_limit_price;
			///��С�䶯��λ
			double  price_tick;
			/// ��Լ��С������(��)
			Int32  buy_qty_unit;
			/// ��Լ��С������(��)
			Int32 sell_qty_unit;
		};
		///������
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  OrderBook {
			///����������
			EXCHANGE_TYPE exchange_id;
			///��Լ���루��������������Ϣ���������ո���'\0'��β
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^    ticker;

			///���¼�
			double last_price;
			///������Ϊ�ܳɽ���
			Int64 qty;
			///�ɽ���Ϊ�ܳɽ����
			double  turnover;
			///�ɽ�����
			Int64 trades_count;

			// ������
			///ʮ�������
			[MarshalAs(UnmanagedType::ByValArray, SizeConst = 10)]
			array<Double>^ bid;
			//double bid[10];
			///ʮ��������
			[MarshalAs(UnmanagedType::ByValArray, SizeConst = 10)]
			array<Double>^  ask;
			///ʮ��������
			[MarshalAs(UnmanagedType::ByValArray, SizeConst = 10)]
			array<Int64>^ bid_qty;
			///ʮ��������
			[MarshalAs(UnmanagedType::ByValArray, SizeConst = 10)]
			array<Int64>^ ask_qty;
			/// ʱ����
			Int64 data_time;
		};

		///���ί��(���������)
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  TickByTickEntrust {
			///Ƶ������
			Int32 channel_no;
			///ί�����(��ͬһ��channel_no��Ψһ����1��ʼ����)
			Int64 seq;
			///ί�м۸�
			double  price;
			///ί������
			Int64 qty;
			///'1':��; '2':��; 'G':����; 'F':����
			char  side;
			///�������: '1': �м�; '2': �޼�; 'U': ��������
			char ord_type;
		};

		///��ʳɽ�
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  TickByTickTrade {
			///Ƶ������
			Int32 channel_no;
			///ί�����(��ͬһ��channel_no��Ψһ����1��ʼ����)
			Int64 seq;
			///�ɽ��۸�
			double price;
			///�ɽ���
			Int64 qty;
			///�ɽ����(�������Ͻ���)
			double money;
			///�򷽶�����
			Int64 bid_no;
			///����������
			Int64 ask_no;
			/// SH: �����̱�ʶ('B':������; 'S':������; 'N':δ֪)
			/// SZ: �ɽ���ʶ('4':��; 'F':�ɽ�)
			char trade_flag;
		};

		///���������Ϣ
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  TickByTickStruct {
			///����������
			EXCHANGE_TYPE exchange_id;
			///��Լ���루��������������Ϣ���������ո���'\0'��β
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^ ticker;
			///Ԥ��
			Int64 seq;
			///ί��ʱ�� or �ɽ�ʱ��
			Int64 data_time;
			///ί�� or �ɽ�
			//TBT_TYPE type;
			//TODO:define XTPTickByTickStruct
			TickByTickEntrust entrust;
			TickByTickTrade     trade;

			/*union {
				TickByTickEntrust entrust;
				TickByTickTrade     trade;
			};*/
		};


		///����ѯ��������Ϣ
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  TickerPriceInfo {
			///����������
			EXCHANGE_TYPE exchange_id;
			///��Լ���루��������������Ϣ���������ո���'\0'��β
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^ ticker;
			///���¼�
			double last_price;
		};

#pragma endregion


#pragma region trade struct

		
		/// <summary>
		///������Ϣ
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  OrderInsertInfo
		{
			///XTPϵͳ����ID�������û���д
			UInt64                order_xtp_id;
			///�������ã��ɿͻ��Զ��壬С��1000000
			UInt32	            order_client_id;
			///��Լ���� �ͻ������󲻴��ո���'\0'��β
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                    ticker;
			///�����г�
			MARKET_TYPE         market;
			///�۸�
			double                  price;
			///ֹ��ۣ������ֶΣ�
			double                  stop_price;
			///����
			Int64                 quantity;
			///�����۸�
			PRICE_TYPE          price_type;
			///��������
			SIDE_TYPE           side;
			///ҵ������
			BUSINESS_TYPE       business_type;
		};

		//////////////////////////////////////////////////////////////////////////
		///������ѯ
		//////////////////////////////////////////////////////////////////////////
		///������ѯ����-������ѯ
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryOrderReq
		{
			///֤ȯ���룬����Ϊ�գ����Ϊ�գ���Ĭ�ϲ�ѯʱ����ڵ����гɽ��ر�
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^    ticker;
			///��ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰ������0��
			UInt64   begin_time;
			///��ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰʱ��
			UInt64   end_time;
		};

		///��ѯ�ɽ��ر�����-��ѯ����(��֮ǰ��ʵһ����
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryTraderReq
		{
			///֤ȯ���룬����Ϊ�գ����Ϊ�գ���Ĭ�ϲ�ѯʱ����ڵ����гɽ��ر�
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^    ticker;
			///��ʼʱ�䣬��ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰ������0��
			Int64   begin_time;
			///����ʱ�䣬��ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰʱ��
			Int64   end_time;
		};

		//////////////////////////////////////////////////////////////////////////
		///�˻��ʽ��ѯ��Ӧ�ṹ��
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryAssetRspStruct
		{
			///���ʲ�
			double total_asset;
			///�����ʽ�
			double buying_power;
			///֤ȯ�ʲ�
			double security_asset;
			///�ۼ�����ɽ�֤ȯռ���ʽ𣨱����ֶΣ�
			double fund_buy_amount;
			///�ۼ�����ɽ����׷��ã������ֶΣ�
			double fund_buy_fee;
			///�ۼ������ɽ�֤ȯ�����ʽ𣨱����ֶΣ�
			double fund_sell_amount;
			///�ۼ������ɽ����׷��ã������ֶΣ�
			double fund_sell_fee;
			//XTPϵͳԤ�۵��ʽ𣨰�����������ƱʱԤ�۵Ľ����ʽ�+Ԥ�������ѣ�
			double withholding_amount;
			///�˻�����
			ACCOUNT_TYPE account_type;

			//UInt64 unknown[43];
			[MarshalAs(UnmanagedType::ByValArray, SizeConst = 43)]
			array<UInt64>^ unknown;
		};


		///������Ӧ�ṹ��
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  OrderInfoStruct
		{
			///XTPϵͳ����ID
			UInt64                order_xtp_id;
			///�������ã��û��Զ��壬С��1000000
			UInt32	            order_client_id;
			///�����������ã��û��Զ��壬С��1000000
			UInt32                order_cancel_client_id;
			///������XTPϵͳ�е�id
			UInt64                order_cancel_xtp_id;
			///��Լ����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                    ticker;
			///�����г�
			MARKET_TYPE         market;
			///�۸�
			double                  price;
			///����
			Int64                 quantity;
			///�����۸�����
			PRICE_TYPE          price_type;
			///��������
			SIDE_TYPE           side;
			///ҵ������
			BUSINESS_TYPE       business_type;
			///��ɽ�����
			Int64                 qty_traded;
			///ʣ���������������ɹ�ʱ����ʾ��������
			Int64                 qty_left;
			///ί��ʱ��
			Int64                 insert_time;
			///����޸�ʱ��
			Int64                 update_time;
			///����ʱ��
			Int64                 cancel_time;
			///�ɽ����
			double                  trade_amount;
			///���ر������ OMS���ɵĵ���
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = LOCAL_ORDER_LEN)]
			String^                    order_local_id;
			///����״̬
			ORDER_STATUS_TYPE   order_status;
			///�����ύ״̬
			ORDER_SUBMIT_STATUS_TYPE   order_submit_status;
			///TODO:��������
			TOrderTypeType       order_type;
		};

		///����ʧ����Ӧ��Ϣ
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  OrderCancelInfoStruct
		{
			///����XTPID
			UInt64                 order_cancel_xtp_id;
			///ԭʼ����XTPID
			UInt64                 order_xtp_id;
		};

		///�����ɽ��ṹ��
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  TradeReportStruct
		{
			///XTPϵͳ����ID
			UInt64                 order_xtp_id;
			///�������ã�С��1000000
			UInt32                order_client_id;
			///��Լ����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^                     ticker;
			///�����г�
			MARKET_TYPE          market;
			///������
			UInt64                 local_order_id;
			///�ɽ���ţ����Ψһ���Ͻ���ÿ�ʽ���Ψһ
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = EXEC_ID_LEN)]
			String^                    exec_id;
			///�۸�
			double                   price;
			///����
			Int64                  quantity;
			///�ɽ�ʱ��
			Int64                  trade_time;
			///�ɽ����
			double                   trade_amount;
			///�ɽ���� --�ر���¼�ţ�ÿ��������Ψһ
			UInt64                 report_index;
			///������� --����������
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = ORDER_EXCH_LEN)]
			String^                     order_exch_id;
			///�ɽ�����  --�ɽ��ر��е�ִ������
			TTradeTypeType        trade_type;
			///��������
			SIDE_TYPE            side;
			///����������Ա���� 
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = BRANCH_PBU_LEN)]
			String^                    branch_pbu;
		};


		//////////////////////////////////////////////////////////////////////////
		///��ѯ��Ʊ�ֲ����
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  QueryStkPositionStruct
		{
			///֤ȯ����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_LEN)]
			String^	 ticker;
			///֤ȯ����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = TICKER_NAME_LEN)]
			String^		ticker_name;
			///�����г�
			MARKET_TYPE     market;
			///��ǰ�ֲ�
			Int64             total_qty;
			///���ùɷ���
			Int64             sellable_qty;
			///�ֲֳɱ�
			double              avg_price;
			///����ӯ��
			double              unrealized_pnl;
			///���ճֲ�
			Int64             yesterday_position;
			///�����깺����������깺���������������ͬʱ���ڣ���˿��Թ���һ���ֶΣ�
			Int64				purchase_redeemable_qty;
			///(�����ֶ�)
			[MarshalAs(UnmanagedType::ByValArray, SizeConst = 50)]
			array<UInt64>^ unknown;
		};

		/////////////////////////////////////////////////////////////////////////
		///�ʽ���ת��ˮ֪ͨ
		/////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  FundTransferNotice
		{
			///�ʽ���ת���
			UInt64	            serial_id;
			///��ת����
			FUND_TRANSFER_TYPE	transfer_type;
			///���
			double	                amount;
			///������� 
			FUND_OPER_STATUS    oper_status;
			///����ʱ��
			UInt64	            transfer_time;
		};

		/////////////////////////////////////////////////////////////////////////
		///�û��ʽ�����
		/////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  FundTransferReq
		{
			///�ʽ���ת��ţ������û���д��������xtp_id
			UInt64	serial_id;
			///�ʽ��˻�����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = ACCOUNT_NAME_LEN)]
			String^        fund_account;
			///�ʽ��˻�����
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = ACCOUNT_PASSWORD_LEN)]
			String^	    password;
			///���
			double	    amount;
			///��ת����
			FUND_TRANSFER_TYPE	transfer_type;
		};
		/////////////////////////////////////////////////////////////////////////
		///�ʽ���ת��ˮ��ѯ��������Ӧ
		/////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)]
		public ref struct QueryFundTransferLogReq {
			///�ʽ���ת���
			UInt64	serial_id;
		};

#pragma endregion

	}
}
