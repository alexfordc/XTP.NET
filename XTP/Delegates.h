/*
*/
#pragma once
#include"utils.h"
#include"xtpstruct.h"
namespace XTP
{
	namespace API
	{
		//common delegates

		public delegate void OnErrorDelegate(RspInfoStruct^);

		//quote delegates

		public delegate void OnQuoterDisconnectedDelegate(int);
		public delegate void OnSubMarketDataDelegate(RspInfoStruct^, SpecificTickerStruct^, bool);
		public delegate void OnUnSubMarketDataDelegate(RspInfoStruct^, SpecificTickerStruct^, bool);
		
		public delegate void OnDepthMarketDataDelegate(MarketDataStruct^, array<Int64>^, Int32, Int32, array<Int64>^, Int32, Int32);
		public delegate void OnQueryAllTickersDelegate(RspInfoStruct^, QuoteStaticInfoStruct^, bool);

		///�������鶩����Ӧ��
		///@param ticker ��ϸ�ĺ�Լ�������
		///@param error_info ���ĺ�Լ��������ʱ�Ĵ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param is_last �Ƿ�˴ζ��ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ÿ�����ĵĺ�Լ����Ӧһ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void  OnSubOrderBookDelegate(SpecificTickerStruct^ ticker, RspInfoStruct^ error_info, bool is_last) ;

		///�˶����鶩����Ӧ��
		///@param ticker ��ϸ�ĺ�Լȡ���������
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param is_last �Ƿ�˴�ȡ�����ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ÿ��ȡ�����ĵĺ�Լ����Ӧһ��ȡ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void OnUnSubOrderBookDelegate(SpecificTickerStruct^  ticker, RspInfoStruct^ error_info, bool is_last) ;

		///���鶩����֪ͨ
		///@param order_book ���鶩�������ݣ���Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void OnOrderBookDelegate(OrderBook^ order_book) ;

		///�����������Ӧ��
		///@param ticker ��ϸ�ĺ�Լ�������
		///@param error_info ���ĺ�Լ��������ʱ�Ĵ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param is_last �Ƿ�˴ζ��ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ÿ�����ĵĺ�Լ����Ӧһ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void OnSubTickByTickDelegate(SpecificTickerStruct^  ticker, RspInfoStruct^ error_info, bool is_last) ;

		///�˶��������Ӧ��
		///@param ticker ��ϸ�ĺ�Լȡ���������
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param is_last �Ƿ�˴�ȡ�����ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ÿ��ȡ�����ĵĺ�Լ����Ӧһ��ȡ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void OnUnSubTickByTickDelegate(SpecificTickerStruct^  ticker, RspInfoStruct^ error_info, bool is_last) ;

		///�������֪ͨ
		///@param tbt_data ����������ݣ��������ί�к���ʳɽ�����Ϊ���ýṹ�壬��Ҫ����type�����������ί�л�����ʳɽ�����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void OnTickByTickDelegate(TickByTickStruct^ tbt_data) ;

		///����ȫ�г�������Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		public delegate void OnSubscribeAllMarketDataDelegate(RspInfoStruct^ error_info) ;

		///�˶�ȫ�г�������Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		public delegate void OnUnSubscribeAllMarketDataDelegate(RspInfoStruct^ error_info) ;

		///����ȫ�г������鶩����Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		public delegate void OnSubscribeAllOrderBookDelegate(RspInfoStruct^ error_info) ;

		///�˶�ȫ�г������鶩����Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		public delegate void OnUnSubscribeAllOrderBookDelegate(RspInfoStruct^ error_info) ;

		///����ȫ�г����������Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		public delegate void OnSubscribeAllTickByTickDelegate(RspInfoStruct^ error_info) ;

		///�˶�ȫ�г����������Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		public delegate void OnUnSubscribeAllTickByTickDelegate(RspInfoStruct^ error_info) ;


		///��ѯ�ɽ��׺�Լ��Ӧ��
		///@param ticker_info �ɽ��׺�Լ��Ϣ
		///@param error_info ��ѯ�ɽ��׺�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param is_last �Ƿ�˴β�ѯ�ɽ��׺�Լ�����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		public delegate void OnQueryAllTickers(QuoteStaticInfoStruct^ ticker_info, RspInfoStruct^ error_info, bool is_last) ;

		///��ѯ��Լ�����¼۸���ϢӦ��
		///@param ticker_info ��Լ�����¼۸���Ϣ
		///@param error_info ��ѯ��Լ�����¼۸���Ϣʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param is_last �Ƿ�˴β�ѯ�����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		public delegate void OnQueryTickersPriceInfo(TickerPriceInfo^ ticker_info, RspInfoStruct^ error_info, bool is_last) ;


		//trader delegates
		public delegate void OnTraderDisconnectedDelegate(UInt64, int);
		public delegate void OnOrderDelegate(RspInfoStruct^, OrderInfoStruct^,UInt64);
		public delegate void OnQueryOrderDelegate(RspInfoStruct^, OrderInfoStruct^, int, bool, UInt64);
		public delegate void OnOrderCancelDelegate(RspInfoStruct^, OrderCancelInfoStruct^, UInt64);
		public delegate void OnTradeDelegate(TradeReportStruct^, UInt64);
		public delegate void OnQueryTradeDelegate(RspInfoStruct^, TradeReportStruct^, int, bool, UInt64);
		public delegate void OnQueryAssetDelegate( QueryAssetRspStruct^, RspInfoStruct^, int, bool, UInt64);
		public delegate void OnQueryPositionDelegate(QueryStkPositionStruct^, RspInfoStruct^, int, bool, UInt64);

		///�����ѯ�ּ�������Ϣ��Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param fund_info ��ѯ���ķּ��������
		///@param error_info ��ѯ�ּ�����������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void  OnQueryStructuredFundDelegate(StructuredFundInfo^ fund_info, RspInfoStruct^ error_info, int request_id, bool is_last, UInt64 session_id) ;

		///�����ѯ�ʽ𻮲�������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param fund_transfer_info ��ѯ�����ʽ��˻����
		///@param error_info ��ѯ�ʽ��˻���������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void  OnQueryFundTransferDelegate(FundTransferNotice ^ fund_transfer_info, RspInfoStruct^ error_info, int request_id, bool is_last, UInt64 session_id) ;

		///�ʽ𻮲�֪ͨ
		///@param fund_transfer_info �ʽ𻮲�֪ͨ�ľ�����Ϣ���û�����ͨ��fund_transfer_info.serial_id����������ͨ��GetClientIDByXTPID() == client_id�������Լ��Ķ�����
		///@param error_info �ʽ𻮲��������ܾ����߷�������ʱ�������ʹ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ���ʽ𻮲�������״̬�仯��ʱ�򣬻ᱻ���ã���Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ�����ߡ����е�¼�˴��û��Ŀͻ��˶����յ����û����ʽ𻮲�֪ͨ��
		public delegate void  OnFundTransferDelegate(FundTransferNotice^ fund_transfer_info, RspInfoStruct^ error_info, UInt64 session_id) ;

		///�����ѯETF�嵥�ļ�����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param etf_info ��ѯ����ETF�嵥�ļ����
		///@param error_info ��ѯETF�嵥�ļ���������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void  OnQueryETFDelegate(QueryETFBaseRsp^ etf_info, RspInfoStruct^ error_info, int request_id, bool is_last, UInt64 session_id) ;

		///�����ѯETF��Ʊ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param etf_component_info ��ѯ����ETF��Լ����سɷֹ���Ϣ
		///@param error_info ��ѯETF��Ʊ����������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void  OnQueryETFBasketDelegate(QueryETFComponentRsp^ etf_component_info, RspInfoStruct^ error_info, int request_id, bool is_last, UInt64 session_id) ;

		///�����ѯ�����¹��깺��Ϣ�б����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param ipo_info ��ѯ���Ľ����¹��깺��һֻ��Ʊ��Ϣ
		///@param error_info ��ѯ�����¹��깺��Ϣ�б�������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void  OnQueryIPOInfoListDelegate(QueryIPOTickerRsp^ ipo_info, RspInfoStruct^ error_info, int request_id, bool is_last, UInt64 session_id) ;

		///�����ѯ�û��¹��깺�����Ϣ����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param quota_info ��ѯ�����û�ĳ���г��Ľ����¹��깺�����Ϣ
		///@param error_info ���ѯ�û��¹��깺�����Ϣ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		public delegate void  OnQueryIPOQuotaInfoDelegate(QueryIPOQuotaRsp^ quota_info, RspInfoStruct^ error_info, int request_id, bool is_last, UInt64 session_id) ;
	}
}