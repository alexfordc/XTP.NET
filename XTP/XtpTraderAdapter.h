#pragma once
#include"utils.h"
#include"../sdk/include/xtp_trader_api.h"
#include"Delegates.h"

namespace XTP
{
	namespace API {
		class XtpTraderSpi;
	}
}
namespace XTP
{
	namespace API
	{
		public ref class XtpTraderAdapter
		{
		private:
			~XtpTraderAdapter(void);
		private:
			TraderApi * pTdApi;

			XtpTraderSpi* pTdSpi;
		public:
			bool IsLogin = false;
		public:
			XtpTraderAdapter(int client_id, String^ account_key, String ^ log_path, TE_RESUME_TYPE resume_type);

		public:
			UInt64 Login(String ^ ip, int port, String ^ investor_id, String ^ password, PROTOCOL_TYPE protocal_type);

			///ͨ��������xtpϵͳ�е�ID��ȡ�µ��Ŀͻ���id
			///@return ���ؿͻ���id�������ô˷��������Լ��µĶ���
			///@param order_xtp_id ������xtpϵͳ�е�ID
			///@remark ����ϵͳ����ͬһ�û��ڲ�ͬ�ͻ����ϵ�¼������ÿ���ͻ���ͨ����ͬ��client_id��������
			UInt64 GetClientIDByXTPID(UInt64 order_xtp_id);

			///ͨ��������xtpϵͳ�е�ID��ȡ����ʽ��˻���
			///@return �����ʽ��˻���
			///@param order_xtp_id ������xtpϵͳ�е�ID
			///@remark ֻ���ʽ��˻���¼�ɹ���,���ܵõ���ȷ����Ϣ
			String^ GetAccountByXTPID(UInt64 order_xtp_id);

			void SubscribePublicTopic(TE_RESUME_TYPE resume_type);

			///�����������ʱ��������λΪ��
			///@param interval �������ʱ��������λΪ��
			///@remark �˺���������Login֮ǰ����
			void SetHeartBeatInterval(UInt32 interval);

			String^ GetTradingDay();

			//��ȡAPI�汾��
			String^ GetApiVersion();
			///��ȡAPI��ϵͳ����
			RspInfoStruct^ GetApiLastError();

			///�ǳ�����
			///@return �ǳ��Ƿ�ɹ�����0����ʾ�ǳ��ɹ�����-1����ʾ�ǳ�ʧ��
			///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
			int Logout(UInt64 session_id);

			UInt64 InsertOrder(OrderInsertInfo ^order, UInt64 session_id);

			///������������
			///@return ������XTPϵͳ�е�ID,���Ϊ��0����ʾ��������ʧ�ܣ���ʱ�û����Ե���GetApiLastError()����ȡ������룬�ǡ�0����ʾ�������ͳɹ����û���Ҫ��¼�·��ص�order_cancel_xtp_id������֤һ����������Ψһ����ͬ�Ľ����ղ���֤Ψһ��
			///@param order_xtp_id ��Ҫ������ί�е���XTPϵͳ�е�ID
			///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
			///@remark ��������ɹ������ڱ�����Ӧ����OnOrderEvent()�ﷵ��ԭ����������ȫ������Ϣ��������ɹ�������OnCancelOrderError()��Ӧ�����з��ش���ԭ��
			UInt64 CancelOrder(UInt64 order_xtp_id, UInt64 session_id);

			///���ݱ���ID�����ѯ����
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param order_xtp_id ��Ҫ��ѯ�ı�����xtpϵͳ�е�ID����InsertOrder()�ɹ�ʱ���ص�order_xtp_id
			///@param session_id �ʽ��˻���Ӧ��session_id����¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			int QueryOrderByXTPID(UInt64 order_xtp_id, UInt64 session_id, int request_id);

			///�����ѯ����
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param query_param ��Ҫ��ѯ�Ķ������ɸѡ���������к�Լ�������Ϊ�գ���Ĭ�����д��ڵĺ�Լ���룬�����Ϊ�գ��벻���ո񣬲���'\0'��β��������ʼʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰ������0�㣬����ʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰʱ��
			///@param session_id �ʽ��˻���Ӧ��session_id����¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			///@remark �÷���֧�ַ�ʱ�β�ѯ�������Ʊ����Ϊ�գ���Ĭ�ϲ�ѯʱ����ڵ����б����������ѯʱ��������и���Ʊ������صı������˺�����ѯ���Ľ�����ܶ�Ӧ�����ѯ�����Ӧ
			int QueryOrders(QueryOrderReq ^query_param, UInt64 session_id, int request_id);

			///����ί�б�������ѯ��سɽ�
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param order_xtp_id ��Ҫ��ѯ��ί�б�ţ���InsertOrder()�ɹ�ʱ���ص�order_xtp_id
			///@param session_id �ʽ��˻���Ӧ��session_id����¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			///@remark �˺�����ѯ���Ľ�����ܶ�Ӧ�����ѯ�����Ӧ
			int QueryTradesByXTPID(UInt64 order_xtp_id, UInt64 session_id, int request_id);

			///�����ѯ�ѳɽ�
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param query_param ��Ҫ��ѯ�ĳɽ��ر�ɸѡ���������к�Լ�������Ϊ�գ���Ĭ�����д��ڵĺ�Լ���룬�����Ϊ�գ��벻���ո񣬲���'\0'��β��������ʼʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰ������0�㣬����ʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰʱ��
			///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			///@remark �÷���֧�ַ�ʱ�β�ѯ�������Ʊ����Ϊ�գ���Ĭ�ϲ�ѯʱ����ڵ����гɽ��ر��������ѯʱ��������и���Ʊ������صĳɽ��ر����˺�����ѯ���Ľ�����ܶ�Ӧ�����ѯ�����Ӧ
			int QueryTrades(QueryTraderReq ^query_param, UInt64 session_id, int request_id);

			///�����ѯͶ���ֲ߳�
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param ticker ��Ҫ��ѯ�ĳֲֺ�Լ���룬����Ϊ�գ������Ϊ�գ��벻���ո񣬲���'\0'��β
			///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			///@remark �÷�������û��ṩ�˺�Լ���룬����ѯ�˺�Լ�ĳֲ���Ϣ�������Լ����Ϊ�գ���Ĭ�ϲ�ѯ���гֲ���Ϣ
			int QueryPosition(String^ ticker, UInt64 session_id, int request_id);

			///�����ѯ�ʲ�
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			int QueryAsset(UInt64 session_id, int request_id);

		public:
			//events//
			event OnTraderDisconnectedDelegate^ OnDisconnectedEvent
			{
				void add(OnTraderDisconnectedDelegate^ hanlder)
				{
					OnDisconnected_delegate += hanlder;
				}
				void remove(OnTraderDisconnectedDelegate^ hanlder)
				{
					OnDisconnected_delegate -= hanlder;
				}
				void raise(UInt64 session_id, Int32 reason)
				{
					if (OnDisconnected_delegate)
					{
						OnDisconnected_delegate(session_id, reason);
					}
				}
			}
			event OnErrorDelegate^ OnErrorEvent
			{
				void add(OnErrorDelegate^ hanlder)
				{
					OnError_delegate += hanlder;
				}
				void remove(OnErrorDelegate^ hanlder)
				{
					OnError_delegate -= hanlder;
				}
				void raise(RspInfoStruct^ rsp)
				{
					if (OnError_delegate)
					{
						OnError_delegate(rsp);
					}
				}
			}
			event OnOrderDelegate^ OnOrderEvent
			{
				void add(OnOrderDelegate^ hanlder)
				{
					OnOrder_delegate += hanlder;
				}
				void remove(OnOrderDelegate^ hanlder)
				{
					OnOrder_delegate -= hanlder;
				}
				void raise(RspInfoStruct^ rsp, OrderInfoStruct^ order, UInt64 session_id)
				{
					if (OnOrder_delegate)
					{
						OnOrder_delegate(rsp, order, session_id);
					}
				}
			}
			event OnQueryOrderDelegate^ OnQueryOrderEvent
			{
				void add(OnQueryOrderDelegate^ hanlder)
				{
					OnQueryOrder_delegate += hanlder;
				}
				void remove(OnQueryOrderDelegate^ hanlder)
				{
					OnQueryOrder_delegate -= hanlder;
				}
				void raise(RspInfoStruct^ rsp, OrderInfoStruct^ order, int request_id, bool is_last, UInt64 session_id)
				{
					if (OnQueryOrder_delegate)
					{
						OnQueryOrder_delegate(rsp, order, request_id, is_last, session_id);
					}
				}
			}
			event OnOrderCancelDelegate^ OnOrderCancelEvent
			{
				void add(OnOrderCancelDelegate^ hanlder)
				{
					OnOrderCancel_delegate += hanlder;
				}
				void remove(OnOrderCancelDelegate^ hanlder)
				{
					OnOrderCancel_delegate -= hanlder;
				}
				void raise(RspInfoStruct^ rsp, OrderCancelInfoStruct^ order_cancel, UInt64 session_id)
				{
					if (OnOrderCancel_delegate)
					{
						OnOrderCancel_delegate(rsp, order_cancel, session_id);
					}
				}
			}
			event OnTradeDelegate^ OnTradeEvent
			{
				void add(OnTradeDelegate^ hanlder)
				{
					OnTrade_delegate += hanlder;
				}
				void remove(OnTradeDelegate^ hanlder)
				{
					OnTrade_delegate -= hanlder;
				}
				void raise(TradeReportStruct^ trade_report, UInt64 session_id)
				{
					if (OnTrade_delegate)
					{
						OnTrade_delegate(trade_report, session_id);
					}
				}
			}
			event OnQueryTradeDelegate^ OnQueryTradeEvent
			{
				void add(OnQueryTradeDelegate^ hanlder)
				{
					OnQueryTrade_delegate += hanlder;
				}
				void remove(OnQueryTradeDelegate^ hanlder)
				{
					OnQueryTrade_delegate -= hanlder;
				}
				void raise(RspInfoStruct^ rsp, TradeReportStruct^ trade_report, int request_id, bool is_last, UInt64 session_id)
				{
					if (OnQueryTrade_delegate)
					{
						OnQueryTrade_delegate(rsp, trade_report, request_id, is_last, session_id);
					}
				}
			}
			event OnQueryAssetDelegate^ OnQueryAssetEvent
			{
				void add(OnQueryAssetDelegate^ hanlder)
				{
					OnQueryAsset_delegate += hanlder;
				}
				void remove(OnQueryAssetDelegate^ hanlder)
				{
					OnQueryAsset_delegate -= hanlder;
				}
				void raise( QueryAssetRspStruct^ asset, RspInfoStruct^ rsp, int request_id, bool is_last, UInt64 session_id)
				{
					if (OnQueryAsset_delegate)
					{
						OnQueryAsset_delegate(asset, rsp,  request_id, is_last, session_id);
					}
				}
			}
			event OnQueryPositionDelegate ^OnQueryPositionEvent
			{
				void add(OnQueryPositionDelegate^ hanlder)
				{
					OnQueryPosition_delegate += hanlder;
				}
				void remove(OnQueryPositionDelegate^ hanlder)
				{
					OnQueryPosition_delegate -= hanlder;
				}
				void raise( QueryStkPositionStruct^ pos, RspInfoStruct^ rsp, int request_id, bool is_last, UInt64 session_id)
				{
					if (OnQueryPosition_delegate)
					{
						OnQueryPosition_delegate(pos, rsp, request_id, is_last, session_id);
					}
				}
			}
		private:
			//delegates
			OnTraderDisconnectedDelegate ^ OnDisconnected_delegate;
			OnErrorDelegate^ OnError_delegate;
			OnOrderDelegate^ OnOrder_delegate;
			OnQueryOrderDelegate^ OnQueryOrder_delegate;
			OnOrderCancelDelegate^ OnOrderCancel_delegate;
			OnTradeDelegate^ OnTrade_delegate;
			OnQueryTradeDelegate^ OnQueryTrade_delegate;
			OnQueryAssetDelegate^ OnQueryAsset_delegate;
			OnQueryPositionDelegate ^OnQueryPosition_delegate;
		};
	}
}