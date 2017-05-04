#pragma once
#include "stdafx.h"
#include <msclr/marshal.h>
#include "TraderDll.h"
#include <functional>
#include "./xtpinclude/xtp_trader_api.h"
//#include <vcclr.h>
//#include <atlstr.h>
using namespace msclr::interop;
using namespace System;
using namespace System::Runtime::InteropServices;
//using namespace std::placeholders; // for `_1`

namespace XTP {
	namespace API {

		///�м佻���¼���������ͨ������
		public ref class TraderEventSource
		{
		public:
			///�����¼��ͻص�����,���õĴ����������¼�Դͷ���������ת������C#��¶����

			delegate void OnDisconnectedDelegate(UInt64, int);
			delegate void OnErrorDelegate(RspInfoStruct^);
			delegate void OnOrderDelegate(RspInfoStruct^, OrderInfoStruct^);
			delegate void OnQueryOrderDelegate(RspInfoStruct^, OrderInfoStruct^, int, bool);
			delegate void OnOrderCancelDelegate(RspInfoStruct^, OrderCancelInfoStruct^);
			delegate void OnTradeDelegate(TradeReportStruct^);
			delegate void OnQueryTradeDelegate(RspInfoStruct^, TradeReportStruct^, int, bool);
			delegate void OnQueryAssetDelegate(RspInfoStruct^, QueryAssetRspStruct^, int, bool);
			delegate void OnQueryPositionDelegate(RspInfoStruct^, QueryStkPositionStruct^, int, bool);
			event OnDisconnectedDelegate^ OnDisconnectedEvent;
			event OnErrorDelegate^ OnErrorEvent;
			event OnOrderDelegate^ OnOrderEvent;
			event OnQueryOrderDelegate^ OnQueryOrderEvent;
			event OnOrderCancelDelegate^ OnOrderCancelEvent;
			event OnTradeDelegate^ OnTradeEvent;
			event OnQueryTradeDelegate^ OnQueryTradeEvent;
			event OnQueryAssetDelegate^ OnQueryAssetEvent;
			event OnQueryPositionDelegate ^OnQueryPositionEvent;
			void OnDisconnected(UInt64 session_id, int reason) {
				OnDisconnectedEvent(session_id, reason);
			}
			void OnError(RspInfoStruct^ resp) {
				OnErrorEvent(resp);
			}
			void OnOrder(RspInfoStruct^ resp, OrderInfoStruct^ order) {
				OnOrderEvent(resp, order);
			}
			void OnQueryOrder(RspInfoStruct^ resp, OrderInfoStruct^ order, int request_id, bool is_last) {
				OnQueryOrderEvent(resp, order, request_id, is_last);
			}
			void OnOrderCancel(RspInfoStruct^ resp, OrderCancelInfoStruct^ cancel) {
				OnOrderCancelEvent(resp, cancel);
			}
			void OnTrade(TradeReportStruct ^ report) {
				OnTradeEvent(report);
			}
			void OnQueryTrade(RspInfoStruct^ resp, TradeReportStruct^ report, int request_id, bool is_last) {
				OnQueryTradeEvent(resp, report, request_id, is_last);
			}
			void OnQueryPosition(RspInfoStruct^ resp, QueryStkPositionStruct^ report, int request_id, bool is_last) {
				OnQueryPositionEvent(resp, report, request_id, is_last);
			}
			void OnQueryAsset(RspInfoStruct ^ resp, QueryAssetRspStruct ^ asset, int request_id, bool is_last) {
				OnQueryAssetEvent(resp, asset, request_id, is_last);
			}

		private:
			//MyOnSubMarketDataDelegate ^myEvent;
			//Object ^eventLock;
		};

		///ȫ���¼�,��������������Ի�ͨ
		gcroot<TraderEventSource^> traderevent_managed = gcnew TraderEventSource();

		///�����¼����壬��Ϊ����ͨ�ࣨ��Ҫ�̳�TraderSpi�����������࣬�����޷����ڲ�����delegate
		public class MyTraderSpi :public TraderSpi {
		public:
			//MyQuoteSpi() {}
			//MyQuoteSpi(EventSource^ managed) : m_managed(managed) {}
			#pragma region ���÷���
			///��ȡ���÷���������״̬
			RspInfoStruct^ GetRspInfoStruct(XTPRI* error_info) {
				RspInfoStruct^ resInfo = gcnew RspInfoStruct();
				resInfo->error_id = error_info->error_id;
				resInfo->error_msg = gcnew String(error_info->error_msg);
				return resInfo;
			}
			///�����¼����õĲ�ѯ���׷���
			TradeReportStruct^ GetTradeReportStruct(XTPQueryTradeRsp* trade_info) {
				TradeReportStruct^ report = gcnew TradeReportStruct();
				///XTPϵͳ����ID
				report->order_xtp_id = trade_info->order_xtp_id;
				///�������ã�С��1000000
				report->order_client_id = trade_info->order_client_id;
				///��Լ����
				report->ticker = gcnew String(trade_info->ticker);
				///�����г�
				report->market = (MARKET_TYPE)trade_info->market;
				///������
				report->local_order_id = trade_info->local_order_id;
				///�ɽ���ţ����Ψһ���Ͻ���ÿ�ʽ���Ψһ
				report->exec_id = gcnew String(trade_info->exec_id);
				///�۸�
				report->price = trade_info->price;
				///����
				report->quantity = trade_info->quantity;
				///�ɽ�ʱ��
				report->trade_time = trade_info->trade_time;
				///�ɽ����
				report->trade_amount = trade_info->trade_amount;
				///�ɽ���� --�ر���¼�ţ�ÿ��������Ψһ
				report->report_index = trade_info->report_index;
				///������� --����������
				report->order_exch_id = gcnew String(trade_info->order_exch_id);
				///�ɽ�����  --�ɽ��ر��е�ִ������
				report->trade_type = (TTradeTypeType)trade_info->trade_type;
				///��������
				report->side = (SIDE_TYPE)trade_info->side;
				///����������Ա���� 
				report->branch_pbu = gcnew String(trade_info->branch_pbu);
				return report;
			}

			//�����¼����õĲ�ѯ��������
			OrderInfoStruct^ GetOrderInfoStruct(XTPOrderInfo *order_info) {
				OrderInfoStruct^ order = gcnew OrderInfoStruct();
				///XTPϵͳ����ID
				order->order_xtp_id = order_info->order_xtp_id;
				///�������ã��û��Զ��壬С��1000000
				order->order_client_id = order_info->order_client_id;
				///�����������ã��û��Զ��壬С��1000000
				order->order_cancel_client_id = order_info->order_cancel_client_id;
				///������XTPϵͳ�е�id
				order->order_cancel_xtp_id = order_info->order_cancel_xtp_id;
				///��Լ����
				order->ticker = gcnew String(order_info->ticker);
				///�����г�
				order->market = (MARKET_TYPE)order_info->market;
				///�۸�
				order->price = order_info->price;
				///����
				order->quantity = order_info->quantity;
				///�����۸�����
				order->price_type = (PRICE_TYPE)order_info->price_type;
				///��������
				order->side = (SIDE_TYPE)order_info->side;
				///��ɽ�����
				order->qty_traded = order_info->qty_traded;
				///ʣ���������������ɹ�ʱ����ʾ��������
				order->qty_left = order_info->qty_left;
				///ί��ʱ��
				order->insert_time = order_info->insert_time;
				///����޸�ʱ��
				order->update_time = order_info->update_time;
				///����ʱ��
				order->cancel_time = order_info->cancel_time;
				///�ɽ����
				order->trade_amount = order_info->trade_amount;
				///���ر������ OMS���ɵĵ���
				order->order_local_id = gcnew String(order_info->order_local_id);
				///����״̬
				order->order_status = (ORDER_STATUS_TYPE)order_info->order_status;
				///�����ύ״̬
				order->order_submit_status = (ORDER_SUBMIT_STATUS_TYPE)order_info->order_submit_status;
				///��������
				order->order_type = (TOrderTypeType)(order_info->order_type);
				//order->order_type = gcnew String((char*)order_info->order_type);
				return order;
			}
			#pragma endregion
			#pragma region ʵ��TraderSpi�ص�

			void OnError(XTPRI *error_info) {
				traderevent_managed->OnError(GetRspInfoStruct(error_info));
			}
			void OnDisconnected(UInt64 session_id,int reason) {
				traderevent_managed->OnDisconnected(session_id,reason);
			}
			///����֪ͨ
			///@param order_info ������Ӧ������Ϣ���û�����ͨ��order_info.order_xtp_id����������ͨ��GetClientIDByXTPID() == client_id�������Լ��Ķ�����order_info.qty_left�ֶ��ڶ���Ϊδ�ɽ������ɡ�ȫ�ɡ��ϵ�״̬ʱ����ʾ�˶�����û�гɽ����������ڲ�����ȫ��״̬ʱ����ʾ�˶���������������order_info.order_cancel_xtp_idΪ������Ӧ�ĳ���ID����Ϊ0ʱ��ʾ�˵������ɹ�
			///@param error_info �������ܾ����߷�������ʱ�������ʹ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ÿ�ζ���״̬����ʱ�����ᱻ���ã���Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ�����ߣ��ڶ���δ�ɽ���ȫ���ɽ���ȫ�����������ֳ������Ѿܾ���Щ״̬ʱ������Ӧ�����ڲ��ֳɽ�����������ɶ����ĳɽ��ر�������ȷ��
			void OnOrderEvent(XTPOrderInfo *order_info, XTPRI *error_info) {
				traderevent_managed->OnOrder(GetRspInfoStruct(error_info), GetOrderInfoStruct(order_info));
			};
			///�ɽ�֪ͨ
			///@param trade_info �ɽ��ر��ľ�����Ϣ���û�����ͨ��trade_info.order_xtp_id����������ͨ��GetClientIDByXTPID() == client_id�������Լ��Ķ����������Ͻ�����exec_id����Ψһ��ʶһ�ʳɽ���������2�ʳɽ��ر�ӵ����ͬ��exec_id���������Ϊ�˱ʽ����Գɽ��ˡ����������exec_id��Ψһ�ģ���ʱ�޴��жϻ��ơ�eport_index+market�ֶο������Ψһ��ʶ��ʾ�ɽ��ر���
			///@remark �����гɽ�������ʱ�򣬻ᱻ���ã���Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ�����ߡ�
			void OnTradeEvent(XTPTradeReport *trade_info) {
				traderevent_managed->OnTrade(GetTradeReportStruct(trade_info));
			};
			///����������Ӧ
			///@param cancel_info ����������Ϣ������������order_cancel_xtp_id�ʹ�������order_xtp_id
			///@param error_info �������ܾ����߷�������ʱ�������ʹ�����Ϣ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ�����ߣ���error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ����Ӧֻ���ڳ�����������ʱ���ص�
			void OnCancelOrderError(XTPOrderCancelInfo *cancel_info, XTPRI *error_info) {
				OrderCancelInfoStruct^ cancel = gcnew OrderCancelInfoStruct();
				cancel->order_cancel_xtp_id = cancel_info->order_cancel_xtp_id;
				cancel->order_xtp_id = cancel_info->order_xtp_id;
				traderevent_managed->OnOrderCancel(GetRspInfoStruct(error_info), cancel);
			};

			///�����ѯ������Ӧ
			///@param order_info ��ѯ���ı���
			///@param error_info ��ѯ����ʱ��������ʱ�����صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param request_id ����Ϣ��Ӧ������Ӧ������ID
			///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ����֧�ַ�ʱ�β�ѯ��һ����ѯ������ܶ�Ӧ�����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			void OnQueryOrder(XTPQueryOrderRsp *order_info, XTPRI *error_info, int request_id, bool is_last) {
				traderevent_managed->OnQueryOrder(GetRspInfoStruct(error_info), GetOrderInfoStruct(order_info), request_id, is_last);
			};

			///�����ѯ�ɽ���Ӧ
			///@param trade_info ��ѯ���ĳɽ��ر�
			///@param error_info ��ѯ�ɽ��ر���������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param request_id ����Ϣ��Ӧ������Ӧ������ID
			///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ����֧�ַ�ʱ�β�ѯ��һ����ѯ������ܶ�Ӧ�����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			void OnQueryTrade(XTPQueryTradeRsp *trade_info, XTPRI *error_info, int request_id, bool is_last) {
				traderevent_managed->OnQueryTrade(GetRspInfoStruct(error_info), GetTradeReportStruct(trade_info),request_id,is_last);
			};

			///�����ѯͶ���ֲ߳���Ӧ
			///@param position ��ѯ���ĳֲ����
			///@param error_info ��ѯ�˻��ֲַ�������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param request_id ����Ϣ��Ӧ������Ӧ������ID
			///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark �����û����ܳ��ж����Ʊ��һ����ѯ������ܶ�Ӧ�����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			void OnQueryPosition(XTPQueryStkPositionRsp *position, XTPRI *error_info, int request_id, bool is_last) {
				QueryStkPositionStruct^ posi = gcnew QueryStkPositionStruct();
				///֤ȯ����
				posi->ticker = gcnew String(position->ticker);
				///֤ȯ����
				posi->ticker_name = gcnew String(position->ticker_name, 0, sizeof(position->ticker_name), System::Text::Encoding::UTF8);
				///�����г�
				posi->market = (MARKET_TYPE)position->market;
				///��ǰ�ֲ�
				posi->total_qty = position->total_qty;
				///���ùɷ���
				posi->sellable_qty = position->sellable_qty;
				///�ֲֳɱ�
				posi->avg_price = position->avg_price;
				///����ӯ��
				posi->unrealized_pnl = position->unrealized_pnl;
				traderevent_managed->OnQueryPosition(GetRspInfoStruct(error_info), posi, request_id, is_last);
			};

			///�����ѯ�ʽ��˻���Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			///@param asset ��ѯ�����ʽ��˻����
			///@param error_info ��ѯ�ʽ��˻���������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param request_id ����Ϣ��Ӧ������Ӧ������ID
			///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			void OnQueryAsset(XTPQueryAssetRsp *asset, XTPRI *error_info, int request_id, bool is_last) {
				QueryAssetRspStruct ^ query_asset = gcnew QueryAssetRspStruct();
				query_asset->total_asset = asset->total_asset;
				query_asset->buying_power = asset->buying_power;
				query_asset->security_asset = asset->security_asset;
				query_asset->fund_buy_amount = asset->fund_buy_amount;
				query_asset->fund_buy_fee = asset->fund_buy_fee;
				query_asset->fund_sell_amount = asset->fund_sell_amount;
				query_asset->fund_sell_fee = asset->fund_sell_fee;
				query_asset->withholding_amount = asset->withholding_amount;
				traderevent_managed->OnQueryAsset(GetRspInfoStruct(error_info), query_asset, request_id, is_last);
			};

			#pragma endregion
		};

		///��¶��C#�������� 
		public ref class TXPTrader
		{
		private:
			XTP::API::TraderApi * pUserApi;
			XTP::API::TraderSpi* pUserSpi;
		public:
			TXPTrader(int client_id, String^ account_key, String ^ log_path, TE_RESUME_TYPE resume_type) 
			{
				char* log_path_char = (char*)Marshal::StringToHGlobalAnsi(log_path).ToPointer();
				pUserApi = XTP::API::TraderApi::CreateTraderApi(client_id, log_path_char);
				pUserApi->SubscribePublicTopic((XTP_TE_RESUME_TYPE)resume_type);
				pUserApi->SetSoftwareVersion("1.1.6.2");

				char* account_key_char = (char*)Marshal::StringToHGlobalAnsi(account_key).ToPointer();
				pUserApi->SetSoftwareKey(account_key_char);
				Marshal::FreeHGlobal((IntPtr)account_key_char);

				pUserSpi = new XTP::API::MyTraderSpi();
				Marshal::FreeHGlobal((IntPtr)log_path_char);
				//pUserApi->RegisterSpi(&spi); // ע���¼���
				traderevent_managed->OnDisconnectedEvent += gcnew XTP::API::TraderEventSource::OnDisconnectedDelegate(this, &XTP::API::TXPTrader::OnDisconnected);
				traderevent_managed->OnErrorEvent += gcnew XTP::API::TraderEventSource::OnErrorDelegate(this, &XTP::API::TXPTrader::OnError);
				traderevent_managed->OnQueryAssetEvent += gcnew XTP::API::TraderEventSource::OnQueryAssetDelegate(this, &XTP::API::TXPTrader::OnQueryAsset);
				traderevent_managed->OnTradeEvent += gcnew XTP::API::TraderEventSource::OnTradeDelegate(this, &XTP::API::TXPTrader::OnTrade);
				traderevent_managed->OnOrderEvent += gcnew XTP::API::TraderEventSource::OnOrderDelegate(this, &XTP::API::TXPTrader::OnOrder);
				traderevent_managed->OnOrderCancelEvent += gcnew XTP::API::TraderEventSource::OnOrderCancelDelegate(this, &XTP::API::TXPTrader::OnOrderCancel);
				traderevent_managed->OnQueryOrderEvent += gcnew XTP::API::TraderEventSource::OnQueryOrderDelegate(this, &XTP::API::TXPTrader::OnQueryOrder);
				traderevent_managed->OnQueryTradeEvent += gcnew XTP::API::TraderEventSource::OnQueryTradeDelegate(this, &XTP::API::TXPTrader::OnQueryTrade);
				traderevent_managed->OnQueryPositionEvent += gcnew XTP::API::TraderEventSource::OnQueryPositionDelegate(this, &XTP::API::TXPTrader::OnQueryPosition);
				
				pUserApi->RegisterSpi(pUserSpi);
			}
			bool IsLogin = false;
			#pragma region ��������

			UInt64 Login(String ^ ip, int port, String ^ investor_id, String ^ password, PROTOCOL_TYPE protocal_type) {
				char* investor_id_char = (char*)Marshal::StringToHGlobalAnsi(investor_id).ToPointer();
				char* password_char = (char*)Marshal::StringToHGlobalAnsi(password).ToPointer();
				char* ip_char = (char*)Marshal::StringToHGlobalAnsi(ip).ToPointer();
				uint64_t loginResult = pUserApi->Login(ip_char, port, investor_id_char, password_char, (XTP_PROTOCOL_TYPE)protocal_type);//XTP_PROTOCOL_TCP
				Marshal::FreeHGlobal((IntPtr)investor_id_char);
				Marshal::FreeHGlobal((IntPtr)password_char);
				Marshal::FreeHGlobal((IntPtr)ip_char);
				if (loginResult > 0) {
					IsLogin = true;
				}
				return loginResult;
			}
			///ͨ��������xtpϵͳ�е�ID��ȡ�µ��Ŀͻ���id
			///@return ���ؿͻ���id�������ô˷��������Լ��µĶ���
			///@param order_xtp_id ������xtpϵͳ�е�ID
			///@remark ����ϵͳ����ͬһ�û��ڲ�ͬ�ͻ����ϵ�¼������ÿ���ͻ���ͨ����ͬ��client_id��������
			UInt64 GetClientIDByXTPID(UInt64 order_xtp_id) {
				return pUserApi->GetClientIDByXTPID(order_xtp_id);
			}
			///ͨ��������xtpϵͳ�е�ID��ȡ����ʽ��˻���
			///@return �����ʽ��˻���
			///@param order_xtp_id ������xtpϵͳ�е�ID
			///@remark ֻ���ʽ��˻���¼�ɹ���,���ܵõ���ȷ����Ϣ
			String^ GetAccountByXTPID(UInt64 order_xtp_id) {
				return gcnew String(pUserApi->GetAccountByXTPID(order_xtp_id));
			}
			void SubscribePublicTopic(TE_RESUME_TYPE resume_type) {
				pUserApi->SubscribePublicTopic((XTP_TE_RESUME_TYPE)resume_type);
			}
			String^ GetTradingDay() {
				return  gcnew String(pUserApi->GetTradingDay());
			}
			//��ȡAPI�汾��
			String^ GetApiVersion() {
				return  gcnew String(pUserApi->GetApiVersion());
			}
			///��ȡAPI��ϵͳ����
			RspInfoStruct^ GetApiLastError() {
				XTPRI* error_info = pUserApi->GetApiLastError();
				RspInfoStruct^ resInfo = gcnew RspInfoStruct();
				resInfo->error_id = error_info->error_id;
				resInfo->error_msg = gcnew String(error_info->error_msg);
				return resInfo;
			}
			///�ǳ�����
			///@return �ǳ��Ƿ�ɹ�����0����ʾ�ǳ��ɹ�����-1����ʾ�ǳ�ʧ��
			///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
			int Logout(UInt64 session_id) {
				IsLogin = false;
				return pUserApi->Logout(session_id);
			}
			UInt64 InsertOrder(XTPOrderInsert ^order, UInt64 session_id) {
				XTPOrderInsertInfo *order_info = new XTPOrderInsertInfo();
				order_info->order_xtp_id = order->order_xtp_id;
				order_info->order_client_id = order->order_client_id;
				order_info->market = (XTP_MARKET_TYPE)order->market;
				order_info->price = order->price;
				order_info->stop_price = order->stop_price;
				order_info->quantity = order->quantity;
				order_info->price_type = (XTP_PRICE_TYPE)order->price_type;
				order_info->side = (XTP_SIDE_TYPE)order->side;
				IntPtr ticker = Marshal::StringToHGlobalAnsi(order->ticker);
				strcpy(order_info->ticker, static_cast<char*>(ticker.ToPointer()));
				static_cast<char*>(ticker.ToPointer());
				Marshal::FreeHGlobal(ticker);
				return pUserApi->InsertOrder(order_info,session_id);
			}
			///������������
			///@return ������XTPϵͳ�е�ID,���Ϊ��0����ʾ��������ʧ�ܣ���ʱ�û����Ե���GetApiLastError()����ȡ������룬�ǡ�0����ʾ�������ͳɹ����û���Ҫ��¼�·��ص�order_cancel_xtp_id������֤һ����������Ψһ����ͬ�Ľ����ղ���֤Ψһ��
			///@param order_xtp_id ��Ҫ������ί�е���XTPϵͳ�е�ID
			///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
			///@remark ��������ɹ������ڱ�����Ӧ����OnOrderEvent()�ﷵ��ԭ����������ȫ������Ϣ��������ɹ�������OnCancelOrderError()��Ӧ�����з��ش���ԭ��
			UInt64 CancelOrder(UInt64 order_xtp_id, UInt64 session_id) {
				return pUserApi->CancelOrder(order_xtp_id, session_id);
			}
			///���ݱ���ID�����ѯ����
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param order_xtp_id ��Ҫ��ѯ�ı�����xtpϵͳ�е�ID����InsertOrder()�ɹ�ʱ���ص�order_xtp_id
			///@param session_id �ʽ��˻���Ӧ��session_id����¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			int QueryOrderByXTPID(UInt64 order_xtp_id, UInt64 session_id, int request_id) {
				return pUserApi->QueryOrderByXTPID(order_xtp_id, session_id, request_id);
			}
			///�����ѯ����
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param query_param ��Ҫ��ѯ�Ķ������ɸѡ���������к�Լ�������Ϊ�գ���Ĭ�����д��ڵĺ�Լ���룬�����Ϊ�գ��벻���ո񣬲���'\0'��β��������ʼʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰ������0�㣬����ʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰʱ��
			///@param session_id �ʽ��˻���Ӧ��session_id����¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			///@remark �÷���֧�ַ�ʱ�β�ѯ�������Ʊ����Ϊ�գ���Ĭ�ϲ�ѯʱ����ڵ����б����������ѯʱ��������и���Ʊ������صı������˺�����ѯ���Ľ�����ܶ�Ӧ�����ѯ�����Ӧ
			int QueryOrders(XTPQueryOrder ^query_param, UInt64 session_id, int request_id) {
				XTPQueryOrderReq *query = new XTPQueryOrderReq();
				IntPtr ticker = Marshal::StringToHGlobalAnsi(query_param->ticker);
				strcpy(query->ticker, static_cast<char*>(ticker.ToPointer()));
				Marshal::FreeHGlobal(ticker);
				query->begin_time = query_param->begin_time;
				query->end_time = query_param->end_time;
				return pUserApi->QueryOrders(query, session_id, request_id);
			}
			///����ί�б�������ѯ��سɽ�
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param order_xtp_id ��Ҫ��ѯ��ί�б�ţ���InsertOrder()�ɹ�ʱ���ص�order_xtp_id
			///@param session_id �ʽ��˻���Ӧ��session_id����¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			///@remark �˺�����ѯ���Ľ�����ܶ�Ӧ�����ѯ�����Ӧ
			int QueryTradesByXTPID(UInt64 order_xtp_id, UInt64 session_id, int request_id) {
				return pUserApi->QueryTradesByXTPID(order_xtp_id, session_id, request_id);
			}
			///�����ѯ�ѳɽ�
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param query_param ��Ҫ��ѯ�ĳɽ��ر�ɸѡ���������к�Լ�������Ϊ�գ���Ĭ�����д��ڵĺ�Լ���룬�����Ϊ�գ��벻���ո񣬲���'\0'��β��������ʼʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰ������0�㣬����ʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰʱ��
			///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			///@remark �÷���֧�ַ�ʱ�β�ѯ�������Ʊ����Ϊ�գ���Ĭ�ϲ�ѯʱ����ڵ����гɽ��ر��������ѯʱ��������и���Ʊ������صĳɽ��ر����˺�����ѯ���Ľ�����ܶ�Ӧ�����ѯ�����Ӧ
			int QueryTrades(XTPQueryTrader ^query_param, UInt64 session_id, int request_id) {
				XTPQueryTraderReq *query = new XTPQueryTraderReq();
				IntPtr ticker = Marshal::StringToHGlobalAnsi(query_param->ticker);
				strcpy(query->ticker, static_cast<char*>(ticker.ToPointer()));
				Marshal::FreeHGlobal(ticker);
				query->begin_time = query_param->begin_time;
				query->end_time = query_param->end_time;
				return pUserApi->QueryTrades(query, session_id, request_id);
			}
			///�����ѯͶ���ֲ߳�
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param ticker ��Ҫ��ѯ�ĳֲֺ�Լ���룬����Ϊ�գ������Ϊ�գ��벻���ո񣬲���'\0'��β
			///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			///@remark �÷�������û��ṩ�˺�Լ���룬����ѯ�˺�Լ�ĳֲ���Ϣ�������Լ����Ϊ�գ���Ĭ�ϲ�ѯ���гֲ���Ϣ
			int QueryPosition(String^ ticker, UInt64 session_id, int request_id) {
				char* ticker_char = (char*)Marshal::StringToHGlobalAnsi(ticker).ToPointer();
				int result =  pUserApi->QueryPosition(ticker_char, session_id, request_id);
				Marshal::FreeHGlobal((IntPtr)ticker_char);
				return result;
			}
			///�����ѯ�ʲ�
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			int QueryAsset(UInt64 session_id, int request_id) {
				return pUserApi->QueryAsset(session_id, request_id);
			}

			#pragma endregion

			#pragma region �¼�����

			event XTP::API::TraderEventSource::OnDisconnectedDelegate^ OnDisconnectedEvent;
			event XTP::API::TraderEventSource::OnErrorDelegate^ OnErrorEvent;
			event XTP::API::TraderEventSource::OnQueryAssetDelegate^ OnQueryAssetEvent;
			event XTP::API::TraderEventSource::OnTradeDelegate^ OnTradeEvent;
			event XTP::API::TraderEventSource::OnQueryTradeDelegate^ OnQueryTradeEvent;
			event XTP::API::TraderEventSource::OnOrderDelegate^ OnOrderEvent;
			event XTP::API::TraderEventSource::OnQueryOrderDelegate^ OnQueryOrderEvent;
			event XTP::API::TraderEventSource::OnOrderCancelDelegate^ OnOrderCancelEvent;
			event XTP::API::TraderEventSource::OnQueryPositionDelegate^ OnQueryPositionEvent;
			
			#pragma endregion

		protected:
			#pragma region �¼�����


			void OnDisconnected(UInt64 session_id,int reason)
			{
				IsLogin = false;
				OnDisconnectedEvent(session_id,reason);
			}
			void OnError(RspInfoStruct^ resp)
			{
				OnErrorEvent(resp);
			}
			void OnQueryAsset(RspInfoStruct ^ resp, QueryAssetRspStruct ^ asset, int request_id, bool is_last) {
				OnQueryAssetEvent(resp, asset, request_id, is_last);
			}
			void OnOrder(RspInfoStruct^ resp, OrderInfoStruct^ order) {
				OnOrderEvent(resp, order);
			}
			void OnQueryOrder(RspInfoStruct^ resp, OrderInfoStruct^ order, int request_id, bool is_last) {
				OnQueryOrderEvent(resp, order, request_id, is_last);
			}
			void OnOrderCancel(RspInfoStruct^ resp, OrderCancelInfoStruct^ cancel) {
				OnOrderCancelEvent(resp, cancel);
			}
			void OnTrade(TradeReportStruct ^ report) {
				OnTradeEvent(report);
			}
			void OnQueryTrade(RspInfoStruct^ resp, TradeReportStruct^ report, int request_id, bool is_last) {
				OnQueryTradeEvent(resp, report, request_id, is_last);
			}
			void OnQueryPosition(RspInfoStruct^ resp, QueryStkPositionStruct^ report, int request_id, bool is_last) {
				OnQueryPositionEvent(resp, report, request_id, is_last);
			}
			#pragma endregion
		};

	}
}