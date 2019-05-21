#pragma once
#include"utils.h"
#include"../sdk/include/xtp_quote_api.h"
#include"Delegates.h"

namespace XTP
{
	namespace API {
		class XtpQuoteSpi;
	}
}
namespace XTP {
	namespace API
	{
		/// <summary>
		/// �й���,XTP Marcket Data Adapter
		/// </summary>
		public ref class XtpQuoteAdapter
		{
		private:
			QuoteApi * pUserApi;
			XtpQuoteSpi* pUserSpi;
		private:
			~XtpQuoteAdapter(void);
		public:
			bool IsLogin = false;
		public:
			///����QuoteApi
			///@param client_id ���������룩��������ͬһ�û��Ĳ�ͬ�ͻ��ˣ����û��Զ���
			///@param log_path ���������룩����������Ϣ�ļ���Ŀ¼�����趨һ���п�дȨ�޵���ʵ���ڵ�·��
			///@param log_level ��־�������
			///@remark ���һ���˻���Ҫ�ڶ���ͻ��˵�¼����ʹ�ò�ͬ��client_id��ϵͳ����һ���˻�ͬʱ��¼����ͻ��ˣ����Ƕ���ͬһ�˻�����ͬ��client_idֻ�ܱ���һ��session���ӣ�����ĵ�¼��ǰһ��session�����ڼ䣬�޷�����
			XtpQuoteAdapter(int client_id, String ^ log_path, LOG_LEVEL log_level);

		public:
			///�û���¼����
			///@return ��¼�Ƿ�ɹ�����0����ʾ��¼�ɹ�����-1����ʾ���ӷ�����������ʱ�û����Ե���GetApiLastError()����ȡ������룬��-2����ʾ�Ѵ������ӣ��������ظ���¼�������Ҫ����������logout����-3����ʾ�����д���
			///@param ip ������ip��ַ�����ơ�127.0.0.1��
			///@param port �������˿ں�
			///@param user ��½�û���
			///@param password ��½����
			///@param sock_type ��1������TCP����2������UDP
			///@remark �˺���Ϊͬ������ʽ������Ҫ�첽�ȴ���¼�ɹ������������ؼ��ɽ��к�����������apiֻ����һ������
			int Login(String ^ ip, int port, String ^ investor_id, String ^ password, PROTOCOL_TYPE protocal_type);

			String^ GetTradingDay();

			//��ȡAPI�汾��
			String^ GetApiVersion();

			///��ȡAPI��ϵͳ����
			RspInfoStruct^ GetApiLastError();

			//��ѯ���й�Ʊ����
			int QueryAllTickers(EXCHANGE_TYPE exchange);

			///�ǳ�����
			///@return �ǳ��Ƿ�ɹ�����0����ʾ�ǳ��ɹ����ǡ�0����ʾ�ǳ�������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@remark �˺���Ϊͬ������ʽ������Ҫ�첽�ȴ��ǳ������������ؼ��ɽ��к�������
			int Logout();


			///���ò���UDP��ʽ����ʱ�Ľ��ջ�������С
			///@remark ��Ҫ��Login֮ǰ���ã�Ĭ�ϴ�С����С���þ�Ϊ64MB���˻����С��λΪMB��������2�Ĵη���������128MB������128��
			void SetUDPBufferSize(UInt32 buff_size);

			///�����������ʱ��������λΪ��
			///@param interval �������ʱ��������λΪ��
			///@remark �˺���������Login֮ǰ����
			void SetHeartBeatInterval(UInt32 interval);

			///����/�˶����顣������Ʊ��ָ������Ȩ��
			///@return ���Ľӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո� 
			///@param count Ҫ����/�˶�����ĺ�Լ����
			///@param exchange_id ����������
			///@param is_subscribe �Ƿ��Ƕ���
			///@remark ����һ���Զ���ͬһ֤ȯ�������Ķ����Լ�������û���Ϊ����������Ҫ���µ�¼���������������Ҫ���¶�������
			int SubscribeMarketData(array<String^>^ ticker, EXCHANGE_TYPE exchange, bool is_subscribe);

			///����/�˶����鶩������������Ʊ��ָ������Ȩ��
			///@return ����/�˶����鶩�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո� 
			///@param exchange_id ����������
			///@param is_subscribe �Ƿ��Ƕ���
			///@remark ����һ���Զ���ͬһ֤ȯ�������Ķ����Լ�������û���Ϊ����������Ҫ���µ�¼���������������Ҫ���¶�������(�ݲ�֧��)
			int SubscribeOrderBook(array<String^>^ ticker, EXCHANGE_TYPE exchange_id, bool is_subscribe);

			///����/�˶�������顣������Ʊ��ָ������Ȩ��
			///@return ����/�˶��������ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո�  
			///@param exchange_id ����������
			///@param  is_subscribe �Ƿ��Ƕ���
			///@remark ����һ���Զ���ͬһ֤ȯ�������Ķ����Լ�������û���Ϊ����������Ҫ���µ�¼���������������Ҫ���¶�������(�ݲ�֧��)
			int SubscribeTickByTick(array<String^>^ ticker, EXCHANGE_TYPE exchange_id, bool is_subscribe);

			///����/�˶�ȫ�г�������
			///@return ����/�˶�ȫ�г�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param  is_subscribe �Ƿ��Ƕ���
			///@remark ��Ҫ��ȫ�г��˶�����ӿ�����ʹ��
			int SubscribeAllMarketData(EXCHANGE_TYPE exchange_id, bool is_subscribe);

			///����/�˶�ȫ�г��Ĺ�Ʊ���鶩����
			///@return ����/�˶�ȫ�г����鶩�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param  is_subscribe �Ƿ��Ƕ���
			///@remark ��Ҫ��ȫ�г��˶����鶩�����ӿ�����ʹ��
			int SubscribeAllOrderBook(EXCHANGE_TYPE exchange_id, bool is_subscribe);

			///����/�˶�ȫ�г��Ĺ�Ʊ�������
			///@return ����/�˶�ȫ�г��������ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param  is_subscribe �Ƿ��Ƕ���
			///@remark ��Ҫ��ȫ�г��˶��������ӿ�����ʹ��
			int SubscribeAllTickByTick(EXCHANGE_TYPE exchange_id, bool is_subscribe);

			///��ȡ��Լ�����¼۸���Ϣ
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ��ѯ�ɹ����ǡ�0����ʾ��ѯ���ɹ�
			///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո�  
			///@param exchange_id ����������
			int QueryTickersPriceInfo(array<String^>^ ticker, EXCHANGE_TYPE exchange_id);

			///��ȡ���к�Լ�����¼۸���Ϣ
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ��ѯ�ɹ����ǡ�0����ʾ��ѯ���ɹ�
			int QueryAllTickersPriceInfo();

			///����/�˶�ȫ�г�����Ȩ����
			///@return ����/�˶�ȫ����Ȩ������ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param exchange_id ��ʾ��ǰȫ���ĵ��г������ΪXTP_EXCHANGE_UNKNOWN����ʾ����ȫ�г���XTP_EXCHANGE_SH��ʾΪ�Ϻ�ȫ�г���XTP_EXCHANGE_SZ��ʾΪ����ȫ�г�
			///@remark ��Ҫ��ȫ�г��˶���Ȩ����ӿ�����ʹ��
			virtual int SubscribeAllOptionMarketData(EXCHANGE_TYPE exchange_id, bool is_subscribe) ;

		
			///����/�˶�ȫ�г�����Ȩ���鶩����
			///@return ����/�˶�ȫ�г���Ȩ���鶩�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param exchange_id ��ʾ��ǰȫ���ĵ��г������ΪXTP_EXCHANGE_UNKNOWN����ʾ����ȫ�г���XTP_EXCHANGE_SH��ʾΪ�Ϻ�ȫ�г���XTP_EXCHANGE_SZ��ʾΪ����ȫ�г�
			///@remark ��Ҫ��ȫ�г��˶���Ȩ���鶩�����ӿ�����ʹ��
			virtual int SubscribeAllOptionOrderBook(EXCHANGE_TYPE exchange_id, bool is_subscribe);

			///����/�˶�ȫ�г�����Ȩ�������
			///@return ����/�˶�ȫ�г���Ȩ�������ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param exchange_id ��ʾ��ǰȫ���ĵ��г������ΪXTP_EXCHANGE_UNKNOWN����ʾ����ȫ�г���XTP_EXCHANGE_SH��ʾΪ�Ϻ�ȫ�г���XTP_EXCHANGE_SZ��ʾΪ����ȫ�г�
			///@remark ��Ҫ��ȫ�г��˶���Ȩ�������ӿ�����ʹ��
			virtual int SubscribeAllOptionTickByTick(EXCHANGE_TYPE exchange_id, bool is_subscribe) ;

		public:
			event OnQuoterDisconnectedDelegate^ OnDisconnectedEvent
			{
				void add(OnQuoterDisconnectedDelegate^ handler)
				{
					OnDisconnected_delegate += handler;
				}
				void remove(OnQuoterDisconnectedDelegate^ handler)
				{
					OnDisconnected_delegate -= handler;
				}
				void raise(int reason)
				{
					if (OnDisconnected_delegate)
					{
						OnDisconnected_delegate(reason);
					}
				}
			}
			event OnErrorDelegate^ OnErrorEvent {
				void add(OnErrorDelegate^ handler)
				{
					OnError_delegate += handler;
				}
				void remove(OnErrorDelegate^ handler)
				{
					OnError_delegate -= handler;
				}
				void raise(RspInfoStruct^ rsp)
				{
					if (OnError_delegate)
					{
						OnError_delegate(rsp);
					}
				}
			}
			event OnSubMarketDataDelegate^ OnSubMarketDataEvent {
				void add(OnSubMarketDataDelegate^ handler)
				{
					OnSubMarketData_delegate += handler;
				}
				void remove(OnSubMarketDataDelegate^ handler)
				{
					OnSubMarketData_delegate -= handler;
				}
				void raise(RspInfoStruct^ rsp, SpecificTickerStruct^ tick, bool isLast)
				{
					if (OnSubMarketData_delegate)
					{
						OnSubMarketData_delegate(rsp, tick, isLast);
					}
				}
			}
			event OnUnSubMarketDataDelegate^ OnUnSubMarketDataEvent {
				void add(OnUnSubMarketDataDelegate^ handler)
				{
					OnUnSubMarketData_delegate += handler;
				}
				void remove(OnUnSubMarketDataDelegate^ handler)
				{
					OnUnSubMarketData_delegate -= handler;
				}
				void raise(RspInfoStruct^ rsp, SpecificTickerStruct^ tick, bool isLast)
				{
					if (OnUnSubMarketData_delegate)
					{
						OnUnSubMarketData_delegate(rsp, tick, isLast);
					}
				}
			}
			event OnDepthMarketDataDelegate^ OnDepthMarketDataEvent {
				void add(OnDepthMarketDataDelegate^ handler)
				{
					OnDepthMarketData_delegate += handler;
				}
				void remove(OnDepthMarketDataDelegate^ handler)
				{
					OnDepthMarketData_delegate -= handler;
				}
				void raise(MarketDataStruct^ marketdata, array<Int64>^ bid1Qty, Int32 bid1Count, Int32 bid1MaxCount, array<Int64>^ ask1Qty, Int32 ask1Count, Int32 ask1MaxCount)
				{
					if (OnDepthMarketData_delegate)
					{
						OnDepthMarketData_delegate(marketdata, bid1Qty, bid1Count, bid1MaxCount, ask1Qty, ask1Count, ask1MaxCount);
					}
				}
			}

			event OnQueryAllTickersDelegate^ OnQueryAllTickersEvent {
				void add(OnQueryAllTickersDelegate^ handler)
				{
					OnQueryAllTickers_delegate += handler;
				}
				void remove(OnQueryAllTickersDelegate^ handler)
				{
					OnQueryAllTickers_delegate -= handler;
				}
				void raise(RspInfoStruct^ rsp, QuoteStaticInfoStruct^ data, bool is_last)
				{
					if (OnQueryAllTickers_delegate)
					{
						OnQueryAllTickers_delegate(rsp, data, is_last);
					}
				}
			}
			event OnSubOrderBookDelegate^ OnSubOrderBookEvent{
				void add(OnSubOrderBookDelegate^ handler)
				{
					OnSubOrderBook_delegate += handler;
				}
				void remove(OnSubOrderBookDelegate^ handler)
				{
					OnSubOrderBook_delegate -= handler;
				}
				void raise(SpecificTickerStruct^ ticker, RspInfoStruct^ error_info, bool is_last)
				{
					if (OnSubOrderBook_delegate)
					{
						OnSubOrderBook_delegate(ticker, error_info, is_last);
					}
				}
			}

			event OnUnSubOrderBookDelegate^ OnUnSubOrderBookEvent
			{void add(OnUnSubOrderBookDelegate^ handler)
			{
				OnUnSubOrderBook_delegate += handler;
			}
			void remove(OnUnSubOrderBookDelegate^ handler)
			{
				OnUnSubOrderBook_delegate -= handler;
			}
			void raise(SpecificTickerStruct^  ticker, RspInfoStruct^ error_info, bool is_last)
			{
				if (OnUnSubOrderBook_delegate)
				{
					OnUnSubOrderBook_delegate(ticker, error_info, is_last);
				}
			}}
			event OnOrderBookDelegate^ OnOrderBookEvent{void add(OnOrderBookDelegate^ handler)
			{
				OnOrderBook_delegate += handler;
			}
			void remove(OnOrderBookDelegate^ handler)
			{
				OnOrderBook_delegate -= handler;
			}
			void raise(OrderBook^ order_book)
			{
				if (OnOrderBook_delegate)
				{
					OnOrderBook_delegate(order_book);
				}
			}}

			event OnSubTickByTickDelegate^ OnSubTickByTickEvent{void add(OnSubTickByTickDelegate^ handler)
			{
				OnSubTickByTick_delegate += handler;
			}
			void remove(OnSubTickByTickDelegate^ handler)
			{
				OnSubTickByTick_delegate -= handler;
			}
			void raise(SpecificTickerStruct^  ticker, RspInfoStruct^ error_info, bool is_last)
			{
				if (OnSubTickByTick_delegate)
				{
					OnSubTickByTick_delegate(ticker, error_info, is_last);
				}
			}}
			event OnUnSubTickByTickDelegate^ OnUnSubTickByTickEvent{void add(OnUnSubTickByTickDelegate^ handler)
			{
				OnUnSubTickByTick_delegate += handler;
			}
			void remove(OnUnSubTickByTickDelegate^ handler)
			{
				OnUnSubTickByTick_delegate -= handler;
			}
			void raise(SpecificTickerStruct^  ticker, RspInfoStruct^ error_info, bool is_last)
			{
				if (OnUnSubTickByTick_delegate)
				{
					OnUnSubTickByTick_delegate(ticker, error_info, is_last);
				}
			}}
			event OnTickByTickDelegate^ OnTickByTickEvent{void add(OnTickByTickDelegate^ handler)
			{
				OnTickByTick_delegate += handler;
			}
			void remove(OnTickByTickDelegate^ handler)
			{
				OnTickByTick_delegate -= handler;
			}
			void raise(TickByTickStruct^ tbt_data)
			{
				if (OnTickByTick_delegate)
				{
					OnTickByTick_delegate(tbt_data);
				}
			}}
			event OnSubscribeAllMarketDataDelegate^ OnSubscribeAllMarketDataEvent{void add(OnSubscribeAllMarketDataDelegate^ handler)
			{
				OnSubscribeAllMarketData_delegate += handler;
			}
			void remove(OnSubscribeAllMarketDataDelegate^ handler)
			{
				OnSubscribeAllMarketData_delegate -= handler;
			}
			void raise(RspInfoStruct^ rsp)
			{
				if (OnSubscribeAllMarketData_delegate)
				{
					OnSubscribeAllMarketData_delegate(rsp);
				}
			}}
			event OnUnSubscribeAllMarketDataDelegate^ OnUnSubscribeAllMarketDataEvent
			{void add(OnUnSubscribeAllMarketDataDelegate^ handler)
			{
				OnUnSubscribeAllMarketData_delegate += handler;
			}
			void remove(OnUnSubscribeAllMarketDataDelegate^ handler)
			{
				OnUnSubscribeAllMarketData_delegate -= handler;
			}
			void raise(RspInfoStruct^ rsp)
			{
				if (OnUnSubscribeAllMarketData_delegate)
				{
					OnUnSubscribeAllMarketData_delegate(rsp);
				}
			}}

			event OnSubscribeAllOrderBookDelegate^ OnSubscribeAllOrderBookEvent
			{void add(OnSubscribeAllOrderBookDelegate^ handler)
			{
				OnSubscribeAllOrderBook_delegate += handler;
			}
			void remove(OnSubscribeAllOrderBookDelegate^ handler)
			{
				OnSubscribeAllOrderBook_delegate -= handler;
			}
			void raise(RspInfoStruct^ rsp)
			{
				if (OnSubscribeAllOrderBook_delegate)
				{
					OnSubscribeAllOrderBook_delegate(rsp);
				}
			}}
			event OnUnSubscribeAllOrderBookDelegate^ OnUnSubscribeAllOrderBookEvent
			{void add(OnUnSubscribeAllOrderBookDelegate^ handler)
			{
				OnUnSubscribeAllOrderBook_delegate += handler;
			}
			void remove(OnUnSubscribeAllOrderBookDelegate^ handler)
			{
				OnUnSubscribeAllOrderBook_delegate -= handler;
			}
			void raise(RspInfoStruct^ rsp)
			{
				if (OnUnSubscribeAllOrderBook_delegate)
				{
					OnUnSubscribeAllOrderBook_delegate(rsp);
				}
			}}
			event OnSubscribeAllTickByTickDelegate^ OnSubscribeAllTickByTickEvent
			{void add(OnSubscribeAllTickByTickDelegate^ handler)
			{
				OnSubscribeAllTickByTick_delegate += handler;
			}
			void remove(OnSubscribeAllTickByTickDelegate^ handler)
			{
				OnSubscribeAllTickByTick_delegate -= handler;
			}
			void raise(RspInfoStruct^ rsp)
			{
				if (OnSubscribeAllTickByTick_delegate)
				{
					OnSubscribeAllTickByTick_delegate(rsp);
				}
			}}
			event OnUnSubscribeAllTickByTickDelegate^ OnUnSubscribeAllTickByTickEvent
			{void add(OnUnSubscribeAllTickByTickDelegate^ handler)
			{
				OnUnSubscribeAllTickByTick_delegate += handler;
			}
			void remove(OnUnSubscribeAllTickByTickDelegate^ handler)
			{
				OnUnSubscribeAllTickByTick_delegate -= handler;
			}
			void raise(RspInfoStruct^ rsp)
			{
				if (OnUnSubscribeAllTickByTick_delegate)
				{
					OnUnSubscribeAllTickByTick_delegate(rsp);
				}
			}}

			event OnQueryTickersPriceInfo^ OnQueryTickersPriceInfoEvent{void add(OnQueryTickersPriceInfo^ handler)
			{
				OnQueryTickersPriceInfo_delegate += handler;
			}
			void remove(OnQueryTickersPriceInfo^ handler)
			{
				OnQueryTickersPriceInfo_delegate -= handler;
			}
			void raise(TickerPriceInfo^ ticker_info, RspInfoStruct^ error_info, bool is_last)
			{
				if (OnQueryTickersPriceInfo_delegate)
				{
					OnQueryTickersPriceInfo_delegate(ticker_info, error_info, is_last);
				}
			}}

			

		private:
			//delegates
			OnQuoterDisconnectedDelegate ^ OnDisconnected_delegate;
			OnErrorDelegate^ OnError_delegate;
			OnSubMarketDataDelegate^ OnSubMarketData_delegate;
			OnUnSubMarketDataDelegate^ OnUnSubMarketData_delegate;
			OnDepthMarketDataDelegate^ OnDepthMarketData_delegate;
			OnQueryAllTickersDelegate^ OnQueryAllTickers_delegate;
			
			OnSubOrderBookDelegate^ OnSubOrderBook_delegate;
			OnUnSubOrderBookDelegate^ OnUnSubOrderBook_delegate;
			OnOrderBookDelegate^ OnOrderBook_delegate;
			OnSubTickByTickDelegate^ OnSubTickByTick_delegate;
			OnUnSubTickByTickDelegate^ OnUnSubTickByTick_delegate;
			OnTickByTickDelegate^ OnTickByTick_delegate;
			OnSubscribeAllMarketDataDelegate^ OnSubscribeAllMarketData_delegate;
			OnUnSubscribeAllMarketDataDelegate^ OnUnSubscribeAllMarketData_delegate;
			OnSubscribeAllOrderBookDelegate^ OnSubscribeAllOrderBook_delegate;
			OnUnSubscribeAllOrderBookDelegate^ OnUnSubscribeAllOrderBook_delegate;
			OnSubscribeAllTickByTickDelegate^ OnSubscribeAllTickByTick_delegate;
			OnUnSubscribeAllTickByTickDelegate^ OnUnSubscribeAllTickByTick_delegate;
			OnQueryTickersPriceInfo^ OnQueryTickersPriceInfo_delegate;
		};
	}
}