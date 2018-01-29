#pragma once
#include"..\sdk\include\xoms_api_fund_struct.h"

using namespace System;
using namespace::Runtime::InteropServices;
namespace XTP
{
	namespace API {

		/// ��Ű汾�ŵ��ַ�������
#define XTP_VERSION_LEN 16
	/// �汾������
		typedef char XTPVersionType[XTP_VERSION_LEN];
		/// �ɽ������ַ�������
#define XTP_TRADING_DAY_LEN 9
	/// ���֤ȯ������ַ�������
#define XTP_TICKER_LEN 16
	/// ���֤ȯ���Ƶ��ַ�������
#define XTP_TICKER_NAME_LEN 64
	/// ���ر�����ŵ��ַ�������
#define XTP_LOCAL_ORDER_LEN         11
	/// ���������ŵ��ַ�������
#define XTP_ORDER_EXCH_LEN          17
	/// �ɽ�ִ�б�ŵ��ַ�������
#define XTP_EXEC_ID_LEN             18
	/// ����������Ա�����ַ�������
#define XTP_BRANCH_PBU_LEN          7
	/// �û��ʽ��˻����ַ�������
#define XTP_ACCOUNT_NAME_LEN        16
	///������Ϣ���ַ�������
#define XTP_ERR_MSG_LEN  124
#pragma region basic struct

	/// <summary>
	/// XTP_PROTOCOL_TYPE ��һ��ͨѶ����Э�鷽ʽ
	/// </summary>
		public enum class PROTOCOL_TYPE
		{
			XTP_PROTOCOL_TCP = 1,	///<����TCP��ʽ����
			XTP_PROTOCOL_UDP		///<����UDP��ʽ����
		};

		[StructLayout(LayoutKind::Sequential)] 
		public ref struct  RspInfoStruct
		{
			///�������
			Int32	error_id;
			///������Ϣ
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = XTP_ERR_MSG_LEN)]
			String^	error_msg;
		};

		///ָ���ĺ�Լ
		[StructLayout(LayoutKind::Sequential)]
		public ref struct  SpecificTickerStruct
		{
			///����������
			int exchange_id;
			///��Լ���루��������������Ϣ������"600000  "
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = XTP_TICKER_LEN)]
			String^	ticker;
		};
#pragma endregion


#pragma region api data struct
		//////////////////////////////////////////////////////////////////////////
		///@brief XTP_ACCOUNT_TYPE�˻�����
		//////////////////////////////////////////////////////////////////////////
		public enum ACCOUNT_TYPE
		{
			XTP_ACCOUNT_NORMAL = 0,	///<��ͨ�˻�
			XTP_ACCOUNT_CREDIT,		///<�����˻�
			XTP_ACCOUNT_DERIVE,		///<����Ʒ�˻�
			XTP_ACCOUNT_UNKNOWN		///<δ֪�˻�����
		};

		/// <summary>
		/// XTP_EXCHANGE_TYPE �ǽ���������
		/// </summary>
		public enum class EXCHANGE_TYPE
		{
			XTP_EXCHANGE_SH = 1,	///<��֤
			XTP_EXCHANGE_SZ,		///<��֤
			XTP_EXCHANGE_MAX	///<�����ڵĽ���������
		};
		/////////////////////////////////////////////////////////////////////////
		///@brief SPLIT_MERGE_STATUS��һ���������ֺϲ�״̬����
		/////////////////////////////////////////////////////////////////////////
		public enum SPLIT_MERGE_STATUS {
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
		public enum struct TradeTypeType:Byte
		{			
			COMMON = '0',//��ͨ�ɽ�
			CASH = '1',//�ֽ����
			PRIMARY ='2'//һ���г��ɽ�
		};
		///��ѯ�ּ�������Ϣ�ṹ��
		[StructLayout(LayoutKind::Sequential)] public ref struct  QueryStructuredFundInfoReq
		{
			EXCHANGE_TYPE   exchange_id;  ///<���������룬����Ϊ��
										  ///<�ּ�����ĸ������룬����Ϊ�գ����Ϊ�գ���Ĭ�ϲ�ѯ���еķּ�����
			String^                sf_ticker;
		};

		//////////////////////////////////////////////////////////////////////////
		///��ѯ�ּ�������Ϣ��Ӧ�ṹ��
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)] public ref struct  StructuredFundInfo
		{
			///<����������
			EXCHANGE_TYPE   exchange_id;
			///<�ּ�����ĸ�������
			String^                sf_ticker;
			String^                 sf_ticker_name; ///<�ּ�����ĸ��������
			String^                 ticker;   ///<�ּ������ӻ������
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
		[StructLayout(LayoutKind::Sequential)] public ref struct  QueryETFBaseReq
		{
			///�����г�
			MARKET_TYPE    market;
			///ETF��������
			String^               ticker;
		};


		//////////////////////////////////////////////////////////////////////////
		///��ѯ��ƱETF��Լ�������--��Ӧ�ṹ��
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)] public ref struct  QueryETFBaseRsp
		{
			MARKET_TYPE     market;                             ///<�����г�
			String^                etf;                ///<etf����,����,����ͳһʹ�øô���
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
		[StructLayout(LayoutKind::Sequential)] public ref struct  QueryETFComponentReq
		{
			///�����г�
			MARKET_TYPE     market;
			///ETF��������
			String^                ticker;
		};


		//////////////////////////////////////////////////////////////////////////
		///��ѯ��ƱETF��Լ�ɷֹ���Ϣ--��Ӧ�ṹ��
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)] public ref struct  QueryETFComponentRsp
		{
			///�����г�
			MARKET_TYPE     market;
			///ETF����
			String^                ticker;
			///�ɷݹɴ���
			String^                component_ticker;
			///�ɷݹ�����
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
		[StructLayout(LayoutKind::Sequential)] public ref struct  QueryIPOTickerRsp {
			///�����г�
			MARKET_TYPE     market;
			///�깺����
			String^                ticker;
			///�깺��Ʊ����
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
		[StructLayout(LayoutKind::Sequential)] public ref struct  QueryIPOQuotaRsp {
			///�����г�
			MARKET_TYPE     market;
			///���깺���
			Int32             quantity;
		};

		


		//////////////////////////////////////////////////////////////////////////
		///@brief XTP_TICKER_TYPE֤ȯ����
		//////////////////////////////////////////////////////////////////////////
		public enum TICKER_TYPE
		{
			XTP_TICKER_TYPE_BOND,                 ///<ծȯ

		};


		public enum BUSINESS_TYPE
		{
			XTP_BUSINESS_TYPE_CASH = 0,            ///<��ͨ��Ʊҵ�񣨹�Ʊ������ETF�����ȣ�
			XTP_BUSINESS_TYPE_IPOS,                ///<�¹��깺ҵ�񣨶�Ӧ��price type��ѡ���޼����ͣ�
			XTP_BUSINESS_TYPE_REPO,                ///<�ع�ҵ�� ( ��Ӧ��price type��Ϊ�޼ۣ�side��Ϊ�� )
			XTP_BUSINESS_TYPE_ETF,                 ///<ETF����ҵ����δ֧�֣�
			XTP_BUSINESS_TYPE_MARGIN,              ///<������ȯҵ����δ֧�֣�
			XTP_BUSINESS_TYPE_DESIGNATION,         ///<ת�йܣ�δ֧�֣�
			XTP_BUSINESS_TYPE_ALLOTMENT,		   ///<���ҵ�񣨶�Ӧ��price type��ѡ���޼�����,side��Ϊ��
			XTP_BUSINESS_TYPE_STRUCTURED_FUND_PURCHASE_REDEMPTION,	   ///<�ּ���������ҵ��
			XTP_BUSINESS_TYPE_STRUCTURED_FUND_SPLIT_MERGE,	   ///<�ּ������ֺϲ�ҵ��
			XTP_BUSINESS_TYPE_MONEY_FUND,		   ///<���һ���ҵ����δ֧�֣�
			XTP_BUSINESS_TYPE_UNKNOWN              ///<δ֪����

		};

		/////////////////////////////////////////////////////////////////////////
		///@brief XTP_TBT_TYPE��һ����ʻر�����
		/////////////////////////////////////////////////////////////////////////
		public enum TBT_TYPE {
			XTP_TBT_ENTRUST = 1,	///<���ί��
			XTP_TBT_TRADE = 2,		///<��ʳɽ�
		};

		#pragma endregion

		#pragma region quote struct


		///����
		[StructLayout(LayoutKind::Sequential)] 
		public ref struct  MarketDataStruct
		{
			// ����
			///����������
			int exchange_id;
			///��Լ���루��������������Ϣ��
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = XTP_TICKER_LEN)]
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

			// �ڻ�������
			///��ֲ�����Ŀǰδ��д��
			double	pre_open_interest;
			///�ֲ�����Ŀǰδ��д��
			double	open_interest;
			///�ϴν���ۣ�Ŀǰδ��д��
			double	pre_settlement_price;
			///���ν���ۣ�Ŀǰδ��д��
			double	settlement_price;

			///��ͣ��ۣ�Ŀǰδ��д��
			double	upper_limit_price;
			///��ͣ��ۣ�Ŀǰδ��д��
			double	lower_limit_price;
			///����ʵ�ȣ�Ŀǰδ��д��
			double	pre_delta;
			///����ʵ�ȣ�Ŀǰδ��д��
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
			String^ ticker_status;
			///ί����������
			Int64 total_bid_qty;
			///ί����������
			Int64 total_ask_qty;
			///��Ȩƽ��ί��۸�
			double ma_bid_price;
			///��Ȩƽ��ί���۸�
			double ma_ask_price;
			///ծȯ��Ȩƽ��ί��۸�
			double ma_bond_bid_price;
			///ծȯ��Ȩƽ��ί���۸�
			double ma_bond_ask_price;
			///ծȯ����������
			double yield_to_maturity;
			///ETF��ֵ��ֵ
			double iopv;
			///ETF�깺����
			Int32 etf_buy_count;
			///ETF��ر���
			Int32 etf_sell_count;
			///ETF�깺����
			double etf_buy_qty;
			///ETF�깺���
			double etf_buy_money;
			///ETF�������
			double etf_sell_qty;
			///ETF��ؽ��
			double etf_sell_money;
			///Ȩִ֤�е�������
			double total_warrant_exec_qty;
			///Ȩ֤��ͣ�۸�Ԫ��
			double warrant_lower_price;
			///Ȩ֤��ͣ�۸�Ԫ��
			double warrant_upper_price;
			///���볷������
			Int32 cancel_buy_count;
			///������������
			Int32 cancel_sell_count;
			///���볷������
			double cancel_buy_qty;
			///������������
			double cancel_sell_qty;
			///���볷�����
			double cancel_buy_money;
			///�����������
			double cancel_sell_money;
			///�����ܱ���
			Int64 total_buy_count;
			///�����ܱ���
			Int64 total_sell_count;
			///����ί�гɽ����ȴ�ʱ��
			Int32 duration_after_buy;
			///����ί�гɽ����ȴ�ʱ��
			Int32 duration_after_sell;
			///��ί�м�λ��
			Int32 num_bid_orders;
			///����ί�м�λ��
			Int32 num_ask_orders;
			///�ɽ�ʱ�䣨UA3113��
			Int32 exec_time;
			///���б�־��UA103/UA104��
			String^ is_market_closed;
			///��Լ�ֲ�����UA103��
			double total_position;
			///��ӯ��1��UA103��
			double pe_ratio1;
			///��ӯ��2��UA103��
			double pe_ratio2;
		};

		[StructLayout(LayoutKind::Sequential)] public ref struct  QuoteStaticInfoStruct {
			///����������
			int exchange_id;
			///��Լ���루��������������Ϣ���������ո���'\0'��β
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = XTP_TICKER_LEN)]
			String^ ticker;
			/// ��Լ����
			String^ ticker_name;
			/// ��Լ����
			int ticker_type;
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
		[StructLayout(LayoutKind::Sequential)] public ref struct  OrderBook {
			///����������
			EXCHANGE_TYPE exchange_id;
			///��Լ���루��������������Ϣ���������ո���'\0'��β
			[MarshalAs(UnmanagedType::ByValTStr, SizeConst = XTP_TICKER_LEN)]
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
		[StructLayout(LayoutKind::Sequential)] public ref struct  TickByTickEntrust {
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
			///�������: '1': �м�; '2': �޼�; '3': ��������
			char ord_type;
		};

		///��ʳɽ�
		[StructLayout(LayoutKind::Sequential)] public ref struct  TickByTickTrade {
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
		public ref struct  XTPTickByTickStruct {
			///����������
			EXCHANGE_TYPE exchange_id;
			///��Լ���루��������������Ϣ���������ո���'\0'��β
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
		[StructLayout(LayoutKind::Sequential)] public ref struct  XTPTickerPriceInfo {
			///����������
			EXCHANGE_TYPE exchange_id;
			///��Լ���루��������������Ϣ���������ո���'\0'��β
			String^ ticker;
			///���¼�
			double last_price;
		};

#pragma endregion


#pragma region trade struct



		/////////////////////////////////////////////////////////////////////////
		///@enum XTP_SIDE_TYPE ��һ��������������
		/////////////////////////////////////////////////////////////////////////
		public enum class SIDE_TYPE
		{
			XTP_SIDE_BUY = 1,	///<��
			XTP_SIDE_SELL,		///<��
			XTP_SIDE_BUY_OPEN,		///<��
			XTP_SIDE_SELL_OPEN,		///<����
			XTP_SIDE_BUY_CLOSE,		///<��ƽ
			XTP_SIDE_SELL_CLOSE		///<��ƽ
		};


		/////////////////////////////////////////////////////////////////////////
		///TXTPOrderTypeType��һ��������������
		/////////////////////////////////////////////////////////////////////////
		public enum class TOrderTypeType
		{
			Normal = '0',	///����
			DeriveFromQuote= '1',		///��������
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
			XTP_PRICE_LIMIT = 1,           ///<�޼۵�
			XTP_PRICE_BEST_OR_CANCEL,      ///<��ʱ�ɽ�ʣ��ת�������м۵�
			XTP_PRICE_BEST5_OR_LIMIT,      ///<�����嵵��ʱ�ɽ�ʣ��ת�޼ۣ��м۵�
			XTP_PRICE_BEST5_OR_CANCEL,     ///<����5����ʱ�ɽ�ʣ��ת�������м۵�
			XTP_PRICE_ALL_OR_CANCEL,       ///<ȫ���ɽ�����,�м۵�
			XTP_PRICE_FORWARD_BEST,        ///<�������ţ��м۵�
			XTP_PRICE_REVERSE_BEST_LIMIT,  ///<�Է�����ʣ��ת�޼ۣ��м۵�
			XTP_PRICE_TYPE_MAX,			///<�۸����͸���
		};

		[StructLayout(LayoutKind::Sequential)] public ref struct  XTPOrderInsert
		{
			///XTPϵͳ����ID�������û���д
			UInt64                order_xtp_id;
			///�������ã��ɿͻ��Զ��壬С��1000000
			UInt32	            order_client_id;
			///��Լ���� �ͻ������󲻴��ո���'\0'��β
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
		};

		//////////////////////////////////////////////////////////////////////////
		///������ѯ
		//////////////////////////////////////////////////////////////////////////
		///������ѯ����-������ѯ
		[StructLayout(LayoutKind::Sequential)] public ref struct  XTPQueryOrder
		{
			///֤ȯ���룬����Ϊ�գ����Ϊ�գ���Ĭ�ϲ�ѯʱ����ڵ����гɽ��ر�
			String^    ticker;
			///��ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰ������0��
			UInt64   begin_time;
			///��ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰʱ��
			UInt64   end_time;
		};

		///��ѯ�ɽ��ر�����-��ѯ����(��֮ǰ��ʵһ����
		[StructLayout(LayoutKind::Sequential)] public ref struct  XTPQueryTrader
		{
			///֤ȯ���룬����Ϊ�գ����Ϊ�գ���Ĭ�ϲ�ѯʱ����ڵ����гɽ��ر�
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
		[StructLayout(LayoutKind::Sequential)] public ref struct  OrderInfoStruct
		{
			///XTPϵͳ����ID
			UInt64                order_xtp_id;
			///�������ã��û��Զ��壬С��1000000
			UInt32	            order_client_id;
			///�����������ã��û��Զ��壬С��1000000
			UInt32                order_cancel_client_id;
			///������XTPϵͳ�е�id
			UInt32                order_cancel_xtp_id;
			///��Լ����
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
			String^                    order_local_id;
			///����״̬
			ORDER_STATUS_TYPE   order_status;
			///�����ύ״̬
			ORDER_SUBMIT_STATUS_TYPE   order_submit_status;
			///TODO:��������
			TOrderTypeType       order_type;
		};

		///����ʧ����Ӧ��Ϣ
		[StructLayout(LayoutKind::Sequential)] public ref struct  OrderCancelInfoStruct
		{
			///����XTPID
			UInt64                 order_cancel_xtp_id;
			///ԭʼ����XTPID
			UInt64                 order_xtp_id;
		};

		///�����ɽ��ṹ��
		[StructLayout(LayoutKind::Sequential)] public ref struct  TradeReportStruct
		{
			///XTPϵͳ����ID
			UInt64                 order_xtp_id;
			///�������ã�С��1000000
			UInt32                order_client_id;
			///��Լ����
			String^                     ticker;
			///�����г�
			MARKET_TYPE          market;
			///������
			UInt64                 local_order_id;
			///�ɽ���ţ����Ψһ���Ͻ���ÿ�ʽ���Ψһ
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
			String^                     order_exch_id;
			///�ɽ�����  --�ɽ��ر��е�ִ������
			TTradeTypeType        trade_type;
			///��������
			SIDE_TYPE            side;
			///����������Ա���� 
			String^                    branch_pbu;
		};


		//////////////////////////////////////////////////////////////////////////
		///��ѯ��Ʊ�ֲ����
		//////////////////////////////////////////////////////////////////////////
		[StructLayout(LayoutKind::Sequential)] public ref struct  QueryStkPositionStruct
		{
			///֤ȯ����
			String^	 ticker;
			///֤ȯ����
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

#pragma endregion

}
}
