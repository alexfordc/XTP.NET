#pragma once
// XTPDll.h
#pragma once
#include "basicDll.h"

using namespace System;

namespace XTP {
	namespace API {


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
			XTP_ORDT_Normal = '0',	///����
			XTP_ORDT_DeriveFromQuote = '1',		///��������
			XTP_ORDT_DeriveFromCombination = '2',		///�������
			XTP_ORDT_Combination = '3',		///��ϱ���
			XTP_ORDT_ConditionalOrder = '4',		///������
			XTP_ORDT_Swap = '5'		///������
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

		public ref struct XTPOrderInsert
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
		public ref struct XTPQueryOrder
		{
			///֤ȯ���룬����Ϊ�գ����Ϊ�գ���Ĭ�ϲ�ѯʱ����ڵ����гɽ��ر�
			String^    ticker;
			///��ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰ������0��
			UInt64   begin_time;
			///��ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰʱ��
			UInt64   end_time;
		};

		///��ѯ�ɽ��ر�����-��ѯ����(��֮ǰ��ʵһ����
		public ref struct XTPQueryTrader
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
		public ref struct QueryAssetRspStruct
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
		};


		///������Ӧ�ṹ��
		public ref struct OrderInfoStruct
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
			///��������
			TOrderTypeType       order_type;
		};

		///����ʧ����Ӧ��Ϣ
		public ref struct OrderCancelInfoStruct
		{
			///����XTPID
			UInt64                 order_cancel_xtp_id;
			///ԭʼ����XTPID
			UInt64                 order_xtp_id;
		};

		///�����ɽ��ṹ��
		public ref struct TradeReportStruct
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
		public ref struct QueryStkPositionStruct
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
		};



	}
}