// XTPDll.cpp: ����Ŀ�ļ���
#pragma once
#include "stdafx.h"
#include <msclr/marshal.h>
#include "xtpstruct.h"
#include "utils.h"
#include <functional>
#include "..\sdk\include\xtp_quote_api.h"
using namespace msclr::interop;
using namespace System;
using namespace System::Runtime::InteropServices;

namespace XTP {
	namespace API {

		///�м������¼���������ͨ������
		public ref class QuoteEventSource
		{
		public:
			///�����¼��ͻص�����.���õĴ����������¼�Դͷ���������ת������C#��¶����

			delegate void OnDisconnectedDelegate(int);
			delegate void OnErrorDelegate(RspInfoStruct^);
			delegate void OnSubMarketDataDelegate(RspInfoStruct^, SpecificTickerStruct^, bool);
			delegate void OnUnSubMarketDataDelegate(RspInfoStruct^, SpecificTickerStruct^, bool);
			/*virtual void OnDepthMarketData(XTPMD *market_data, 
			int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, 
			int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count) {};
			*/
			delegate void OnDepthMarketDataDelegate(MarketDataStruct^,array<Int64>^,Int32,Int32,array<Int64>^,Int32,Int32);
			delegate void OnQueryAllTickersDelegate(RspInfoStruct^, QuoteStaticInfoStruct^, bool);
			event OnDisconnectedDelegate^ OnDisconnectedEvent;
			event OnErrorDelegate^ OnErrorEvent;
			event OnSubMarketDataDelegate^ OnSubMarketDataEvent;
			event OnUnSubMarketDataDelegate^ OnUnSubMarketDataEvent;
			event OnDepthMarketDataDelegate^ OnDepthMarketDataEvent;
			event OnQueryAllTickersDelegate ^OnQueryAllTickersEvent;

			void OnDisconnected(int reason) {
				OnDisconnectedEvent(reason);
			}
			void OnError(RspInfoStruct^ resp) {
				OnErrorEvent(resp);
			}
			void OnSubMarketData(RspInfoStruct^ resp, SpecificTickerStruct^ ticker, bool is_last) {
				//if (myEvent != nullptr)
				OnSubMarketDataEvent(resp, ticker, is_last);
			}
			void OnUnSubMarketData(RspInfoStruct^ resp, SpecificTickerStruct^ ticker, bool is_last) {
				OnUnSubMarketDataEvent(resp, ticker, is_last);
			}
			
			void OnDepthMarketData(MarketDataStruct^ md, array<Int64>^ bid1Qtys, Int32 bid1Count, Int32 bid1MaxCount, array<Int64>^ ask1Qtys, Int32 ask1Count, Int32 ask1MaxCount) {
				OnDepthMarketDataEvent(md, bid1Qtys, bid1Count, bid1MaxCount, ask1Qtys, ask1Count, ask1MaxCount);
			}
			void OnQueryAllTickers(RspInfoStruct^ resp, QuoteStaticInfoStruct^ ticker_info, bool is_last) {
				OnQueryAllTickersEvent(resp, ticker_info, is_last);
			};
		private:
			//MyOnSubMarketDataDelegate ^myEvent;
			//Object ^eventLock;
		};
		///ȫ���¼�,��������������Ի�ͨ
		gcroot<QuoteEventSource^> quoteevent_managed = gcnew QuoteEventSource();

		///�����¼����壬��Ϊ����ͨ�ࣨ��Ҫ�̳�QuoteSpi�����������࣬�����޷����ڲ�����delegate
		public class XtpQuoteSpi :public QuoteSpi {
		public:
			#pragma region ʵ��QuoteSpi�ص�
			void OnError(XTPRI *error_info) {
				quoteevent_managed->OnError(Native::RspInfoConverter(error_info));
			}
			void OnDisconnected(int reason) {
				quoteevent_managed->OnDisconnected(reason);
			}
			void OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) {
				SpecificTickerStruct^ ticketInfo =Native::MNConv<SpecificTickerStruct^,XTPST>::N2M(ticker);
				quoteevent_managed->OnSubMarketData(Native::RspInfoConverter(error_info), ticketInfo, is_last);
			}
			void OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) {
				
				SpecificTickerStruct^ ticketInfo = Native::MNConv<SpecificTickerStruct^,XTPST>::N2M(ticker);//  gcnew SpecificTickerStruct();
				
				quoteevent_managed->OnUnSubMarketData(Native::RspInfoConverter(error_info), ticketInfo, is_last);
			}
			#pragma region �յ��г��ɼ�����
			

			///�������֪ͨ��������һ��һ����
			///@param market_data ��������
			///@param bid1_qty ��һ��������
			///@param bid1_count ��һ���е���Чί�б���
			///@param max_bid1_count ��һ������ί�б���
			///@param ask1_qty ��һ��������
			///@param ask1_count ��һ���е���Чί�б���
			///@param max_ask1_count ��һ������ί�б���
			///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			void OnDepthMarketData(XTPMD *market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count)
			{
				// �յ��г��ɼ�����

				MarketDataStruct^ data = gcnew MarketDataStruct();
				// ����
				///����������
				data->exchange_id = market_data->exchange_id;
				///��Լ���루��������������Ϣ��
				data->ticker = gcnew String(market_data->ticker);
				// ��Ʊ�ȼ۸�
				///���¼�
				data->last_price = market_data->last_price;
				///������
				data->pre_close_price = market_data->pre_close_price;
				///����
				data->open_price = market_data->open_price;
				///��߼�
				data->high_price = market_data->high_price;
				///��ͼ�
				data->low_price = market_data->low_price;
				///������
				data->close_price = market_data->close_price;

				// �ڻ�������
				///��ֲ�����Ŀǰδ��д��
				data->pre_open_interest = market_data->pre_open_interest;
				///�ֲ�����Ŀǰδ��д��
				data->open_interest = market_data->open_interest;
				///�ϴν���ۣ�Ŀǰδ��д��
				data->pre_settlement_price = market_data->pre_settlement_price;
				///���ν���ۣ�Ŀǰδ��д��
				data->settlement_price = market_data->settlement_price;

				///��ͣ��ۣ�Ŀǰδ��д��
				data->upper_limit_price = market_data->upper_limit_price;
				///��ͣ��ۣ�Ŀǰδ��д��
				data->lower_limit_price = market_data->lower_limit_price;
				///����ʵ�ȣ�Ŀǰδ��д��
				data->pre_delta = market_data->pre_delta;
				///����ʵ�ȣ�Ŀǰδ��д��
				data->curr_delta = market_data->curr_delta;

				/// ʱ����
				data->data_time = market_data->data_time;

				// ��������
				///����
				data->qty = market_data->qty;
				///�ɽ����
				data->turnover = market_data->turnover;
				///���վ���
				data->avg_price = market_data->avg_price;

				// ������
				///ʮ�������
				array<double>^ bid = gcnew array<double>(sizeof(market_data->bid));
				for (int i = 0; i < sizeof(market_data->bid); i++) {
					bid[i] = market_data->bid[i];
				}
				data->bid = bid;
				///ʮ��������
				array<double>^	ask = gcnew array<double>(sizeof(market_data->ask));
				for (int i = 0; i < sizeof(market_data->ask); i++) {
					ask[i] = market_data->ask[i];
				}
				data->ask = ask;
				///ʮ��������
				array<int64_t>^	bid_qty = gcnew array<int64_t>(sizeof(market_data->bid_qty));
				for (int i = 0; i < sizeof(market_data->bid_qty); i++) {
					bid_qty[i] = market_data->bid_qty[i];
				}
				data->bid_qty = bid_qty;
				///ʮ��������
				array<int64_t>^	ask_qty = gcnew array<int64_t>(sizeof(market_data->ask_qty));
				for (int i = 0; i < sizeof(market_data->ask_qty); i++) {
					ask_qty[i] = market_data->ask_qty[i];
				}
				data->ask_qty = ask_qty;

				// ltsû�а��������ݣ�Ŀǰδ��д��
				///�ɽ�����
				data->trades_count = market_data->trades_count;
				///��ǰ����״̬˵��
				data->ticker_status = gcnew String(market_data->ticker_status);
				///ί����������
				data->total_bid_qty = market_data->total_bid_qty;
				///ί����������
				data->total_ask_qty = market_data->total_ask_qty;
				///��Ȩƽ��ί��۸�
				data->ma_bid_price = market_data->ma_bid_price;
				///��Ȩƽ��ί���۸�
				data->ma_ask_price = market_data->ma_ask_price;
				///ծȯ��Ȩƽ��ί��۸�
				data->ma_bond_bid_price = market_data->ma_bond_bid_price;
				///ծȯ��Ȩƽ��ί���۸�
				data->ma_bond_ask_price = market_data->ma_bond_ask_price;
				///ծȯ����������
				data->yield_to_maturity = market_data->yield_to_maturity;
				///ETF��ֵ��ֵ
				data->iopv = market_data->iopv;
				///ETF�깺����
				data->etf_buy_count = market_data->etf_buy_count;
				///ETF��ر���
				data->etf_sell_count = market_data->etf_sell_count;
				///ETF�깺����
				data->etf_buy_qty = market_data->etf_buy_qty;
				///ETF�깺���
				data->etf_buy_money = market_data->etf_buy_money;
				///ETF�������
				data->etf_sell_qty = market_data->etf_sell_qty;
				///ETF��ؽ��
				data->etf_sell_money = market_data->etf_sell_money;
				///Ȩִ֤�е�������
				data->total_warrant_exec_qty = market_data->total_warrant_exec_qty;
				///Ȩ֤��ͣ�۸�Ԫ��
				data->warrant_lower_price = market_data->warrant_lower_price;
				///Ȩ֤��ͣ�۸�Ԫ��
				data->warrant_upper_price = market_data->warrant_upper_price;
				///���볷������
				data->cancel_buy_count = market_data->cancel_buy_count;
				///������������
				data->cancel_sell_count = market_data->cancel_sell_count;
				///���볷������
				data->cancel_buy_qty = market_data->cancel_buy_qty;
				///������������
				data->cancel_sell_qty = market_data->cancel_sell_qty;
				///���볷�����
				data->cancel_buy_money = market_data->cancel_buy_money;
				///�����������
				data->cancel_sell_money = market_data->cancel_sell_money;
				///�����ܱ���
				data->total_buy_count = market_data->total_buy_count;
				///�����ܱ���
				data->total_sell_count = market_data->total_sell_count;
				///����ί�гɽ����ȴ�ʱ��
				data->duration_after_buy = market_data->duration_after_buy;
				///����ί�гɽ����ȴ�ʱ��
				data->duration_after_sell = market_data->duration_after_sell;
				///��ί�м�λ��
				data->num_bid_orders = market_data->num_bid_orders;
				///����ί�м�λ��
				data->num_ask_orders = market_data->num_ask_orders;
				///�ɽ�ʱ�䣨UA3113��
				data->exec_time = market_data->exec_time;
				///���б�־��UA103/UA104��
				data->is_market_closed = gcnew String(market_data->is_market_closed);
				///��Լ�ֲ�����UA103��
				data->total_position = market_data->total_position;
				///��ӯ��1��UA103��
				data->pe_ratio1 = market_data->pe_ratio1;
				///��ӯ��2��UA103��
				data->pe_ratio2 = market_data->pe_ratio2;

				quoteevent_managed->OnDepthMarketData(data, nullptr, 0, 0, nullptr, 0, 0);
				delete data;
			}

			#pragma endregion
			void OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last) {
				QuoteStaticInfoStruct^ data = gcnew QuoteStaticInfoStruct();
				RspInfoStruct^ resInfo = gcnew RspInfoStruct();
				if (error_info == nullptr || error_info->error_id == 0) {
					resInfo->error_id = 0;
					resInfo->error_msg = "";
				#pragma region �յ���ѯ��Ʊ��������
					// �յ��г��ɼ�����
					// ����
					///����������
					data->exchange_id = ticker_info->exchange_id;
					///��Լ���루��������������Ϣ��
					data->ticker = gcnew String(ticker_info->ticker);
					/// ��Լ����
					data->ticker_name = gcnew String(ticker_info->ticker_name, 0, sizeof(ticker_info->ticker_name), System::Text::Encoding::UTF8);
					/// ��Լ����
					data->ticker_type = ticker_info->ticker_type;
					///������
					data->pre_close_price = ticker_info->pre_close_price;
					///��ͣ���
					data->upper_limit_price = ticker_info->upper_limit_price;
					///��ͣ���
					data->lower_limit_price = ticker_info->lower_limit_price;
					///��С�䶯��λ
					data->price_tick = ticker_info->price_tick;
					/// ��Լ��С������(��)
					data->buy_qty_unit = ticker_info->buy_qty_unit;
					/// ��Լ��С������(��)
					data->sell_qty_unit = ticker_info->sell_qty_unit;
				#pragma endregion
				}
				else {
					resInfo->error_id = error_info->error_id;
					resInfo->error_msg = gcnew String(error_info->error_msg);
				}
				quoteevent_managed->OnQueryAllTickers(resInfo, data, is_last);
				delete data;
			}
			#pragma endregion
		};


		///��¶��C#�������� 
		public ref class XtpQuote
		{
		private:
			XTP::API::QuoteApi * pUserApi;
			XTP::API::QuoteSpi* pUserSpi;
			//QuoteSpiManagedClass ^mc;
		public:
			///����QuoteApi
			///@param client_id ���������룩��������ͬһ�û��Ĳ�ͬ�ͻ��ˣ����û��Զ���
			///@param log_path ���������룩����������Ϣ�ļ���Ŀ¼�����趨һ���п�дȨ�޵���ʵ���ڵ�·��
			///@param log_level ��־�������
			///@remark ���һ���˻���Ҫ�ڶ���ͻ��˵�¼����ʹ�ò�ͬ��client_id��ϵͳ����һ���˻�ͬʱ��¼����ͻ��ˣ����Ƕ���ͬһ�˻�����ͬ��client_idֻ�ܱ���һ��session���ӣ�����ĵ�¼��ǰһ��session�����ڼ䣬�޷�����
			XtpQuote(int client_id, String ^ log_path,LOG_LEVEL log_level) 
			{
				char* log_path_char = (char*)Marshal::StringToHGlobalAnsi(log_path).ToPointer();
				//printf(str2);
				pUserApi = XTP::API::QuoteApi::CreateQuoteApi(client_id, log_path_char,(XTP_LOG_LEVEL)log_level);
				//mc = gcnew QuoteSpiManagedClass();
				//pUserSpi = mc->m_Impl;// 
				pUserSpi = new XTP::API::XtpQuoteSpi();
				Marshal::FreeHGlobal((IntPtr)log_path_char);
				quoteevent_managed->OnDisconnectedEvent += gcnew XTP::API::QuoteEventSource::OnDisconnectedDelegate(this, &XTP::API::XtpQuote::OnDisconnected);
				quoteevent_managed->OnErrorEvent += gcnew XTP::API::QuoteEventSource::OnErrorDelegate(this, &XTP::API::XtpQuote::OnError);
				quoteevent_managed->OnSubMarketDataEvent += gcnew XTP::API::QuoteEventSource::OnSubMarketDataDelegate(this, &XTP::API::XtpQuote::OnSubMarketData);
				quoteevent_managed->OnUnSubMarketDataEvent += gcnew XTP::API::QuoteEventSource::OnUnSubMarketDataDelegate(this, &XTP::API::XtpQuote::OnUnSubMarketData);
				quoteevent_managed->OnDepthMarketDataEvent += gcnew XTP::API::QuoteEventSource::OnDepthMarketDataDelegate(this, &XTP::API::XtpQuote::OnDepthMarketData);
				quoteevent_managed->OnQueryAllTickersEvent += gcnew XTP::API::QuoteEventSource::OnQueryAllTickersDelegate(this, &XTP::API::XtpQuote::OnQueryAllTickers);
				pUserApi->RegisterSpi(pUserSpi);
			}
			
			bool IsLogin = false;
			
			#pragma region ��������
			///�û���¼����
			///@return ��¼�Ƿ�ɹ�����0����ʾ��¼�ɹ�����-1����ʾ���ӷ�����������ʱ�û����Ե���GetApiLastError()����ȡ������룬��-2����ʾ�Ѵ������ӣ��������ظ���¼�������Ҫ����������logout����-3����ʾ�����д���
			///@param ip ������ip��ַ�����ơ�127.0.0.1��
			///@param port �������˿ں�
			///@param user ��½�û���
			///@param password ��½����
			///@param sock_type ��1������TCP����2������UDP
			///@remark �˺���Ϊͬ������ʽ������Ҫ�첽�ȴ���¼�ɹ������������ؼ��ɽ��к�����������apiֻ����һ������
			int Login(String ^ ip, int port, String ^ investor_id, String ^ password, PROTOCOL_TYPE protocal_type) {
				char* investor_id_char = (char*)Marshal::StringToHGlobalAnsi(investor_id).ToPointer();
				char* password_char = (char*)Marshal::StringToHGlobalAnsi(password).ToPointer();
				char* ip_char = (char*)Marshal::StringToHGlobalAnsi(ip).ToPointer();
				int loginResult = pUserApi->Login(ip_char, port, investor_id_char, password_char, (XTP_PROTOCOL_TYPE)protocal_type);//XTP_PROTOCOL_TCP
				Marshal::FreeHGlobal((IntPtr)investor_id_char);
				Marshal::FreeHGlobal((IntPtr)password_char);
				Marshal::FreeHGlobal((IntPtr)ip_char);
				if (loginResult == 0) {
					IsLogin = true;
				}
				return loginResult;
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
			//��ѯ���й�Ʊ����
			int QueryAllTickers(EXCHANGE_TYPE exchange) {
				return pUserApi->QueryAllTickers((XTP_EXCHANGE_TYPE)exchange);
			}
			///�ǳ�����
			///@return �ǳ��Ƿ�ɹ�����0����ʾ�ǳ��ɹ����ǡ�0����ʾ�ǳ�������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@remark �˺���Ϊͬ������ʽ������Ҫ�첽�ȴ��ǳ������������ؼ��ɽ��к�������
			int Logout() {
				IsLogin = false;
				return pUserApi->Logout();
			}


			///���ò���UDP��ʽ����ʱ�Ľ��ջ�������С
			///@remark ��Ҫ��Login֮ǰ���ã�Ĭ�ϴ�С����С���þ�Ϊ64MB���˻����С��λΪMB��������2�Ĵη���������128MB������128��
			void SetUDPBufferSize(UInt32 buff_size)
			{
				pUserApi->SetUDPBufferSize(buff_size);
			}

			///�����������ʱ��������λΪ��
			///@param interval �������ʱ��������λΪ��
			///@remark �˺���������Login֮ǰ����
			void SetHeartBeatInterval(UInt32 interval)
			{
				pUserApi->SetHeartBeatInterval(interval);
			}

			///����/�˶����顣
			///@return ���Ľӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո� 
			///@param count Ҫ����/�˶�����ĺ�Լ����
			///@param exchage_id ����������
			///@param is_subscribe �Ƿ��Ƕ���
			///@remark ����һ���Զ���ͬһ֤ȯ�������Ķ����Լ�������û���Ϊ����������Ҫ���µ�¼���������������Ҫ���¶�������
			int SubscribeMarketData(array<String^>^ ticker, EXCHANGE_TYPE exchange, bool is_subscribe) {
				//marshal_context ^ context = gcnew marshal_context();
				char** tokensAsAnsi = new char*[ticker->Length];
				for (int i = 0; i < ticker->Length; i++)
				{
					//IntPtr p = Marshal::StringToHGlobalAnsi(ticker[i]);
					//tokensAsAnsi[i] = static_cast<char*>(p.ToPointer());
					//Marshal::FreeHGlobal(p);
					tokensAsAnsi[i] = static_cast<char*>(Marshal::StringToHGlobalAnsi(ticker[i]).ToPointer());
					//const char* str4 = context->marshal_as<const char*>(ticker[i]);
					//tokensAsAnsi[i] = str4;
				}
				// The marshalled results are freed when context goes out of scope
				int result = 0;
				if (is_subscribe) {
					result = pUserApi->SubscribeMarketData(tokensAsAnsi, ticker->Length, (XTP_EXCHANGE_TYPE)exchange);//���Ĺ�Ʊ����
				}
				else {
					result = pUserApi->UnSubscribeMarketData(tokensAsAnsi, ticker->Length, XTP_EXCHANGE_TYPE(exchange));//ȡ�����Ĺ�Ʊ����
				}
				delete[] tokensAsAnsi;    // Please note you must use delete[] here!
										  //delete context;
				return result;
			}
			
			///�˶����顣
			///@return ȡ�����Ľӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո�  
			
			///@param exchage_id ����������
			///@remark ����һ����ȡ������ͬһ֤ȯ�������Ķ����Լ����Ҫ�붩������ӿ�����ʹ��
			int UnSubscribeMarketData(array<String^>^ ticker, EXCHANGE_TYPE exchage_id)
			{
				///@param count Ҫ����/�˶�����ĺ�Լ����
				int count = ticker->Length;
				char** chTicker = new char*[count];
				for (int i = 0; i < count; ++i)
				{
					chTicker[i] = Native::CAutoStrPtr::CAutoStrPtr(ticker[i]).m_pChar;
				}
				int result = 0;
				result = pUserApi->UnSubscribeMarketData(chTicker, count, (XTP_EXCHANGE_TYPE)exchage_id);
				delete[] chTicker;
				return result;
			}

			///����/�˶����鶩������
			///@return ����/�˶����鶩�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո� 
			///@param exchage_id ����������
			///@param is_subscribe �Ƿ��Ƕ���
			///@remark ����һ���Զ���ͬһ֤ȯ�������Ķ����Լ�������û���Ϊ����������Ҫ���µ�¼���������������Ҫ���¶�������(�ݲ�֧��)
			int SubscribeOrderBook(array<String^>^ ticker, EXCHANGE_TYPE exchage_id,bool is_subscribe)
			{///@param count Ҫ����/�˶����鶩�����ĺ�Լ����
			
				int count = ticker->Length;
				char** chTicker = new char*[count];
				for (int i = 0; i < count; ++i)
				{
					chTicker[i] = Native::CAutoStrPtr::CAutoStrPtr(ticker[i]).m_pChar;
				}
				int result = 0;
				if (is_subscribe)
				{
					result= pUserApi->SubscribeOrderBook(chTicker, count, (XTP_EXCHANGE_TYPE)exchage_id);
				}
				else
				{
					result = pUserApi->UnSubscribeOrderBook(chTicker, count, (XTP_EXCHANGE_TYPE)exchage_id);
				}
				delete[] chTicker;
				return result;
			}

			///�˶����鶩������
			///@return ȡ���������鶩�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո�  
			///@param count Ҫ����/�˶����鶩�����ĺ�Լ����
			///@param exchage_id ����������
			///@remark ����һ����ȡ������ͬһ֤ȯ�������Ķ����Լ����Ҫ�붩�����鶩�����ӿ�����ʹ��
		/*	int UnSubscribeOrderBook(array<String^>^ ticker, int count, EXCHANGE_TYPE exchage_id)
			{
				return 0;
			}*/

			///����/�˶�������顣
			///@return ����/�˶��������ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո�  
			///@param exchage_id ����������
			///@param  is_subscribe �Ƿ��Ƕ���
			///@remark ����һ���Զ���ͬһ֤ȯ�������Ķ����Լ�������û���Ϊ����������Ҫ���µ�¼���������������Ҫ���¶�������(�ݲ�֧��)
			int SubscribeTickByTick(array<String^>^ ticker, EXCHANGE_TYPE exchage_id,bool is_subscribe)
			{
				int count = ticker->Length;
				char** chTicker = new char*[count];
				for (int i = 0; i < count; ++i)
				{
					chTicker[i] = Native::CAutoStrPtr::CAutoStrPtr(ticker[i]).m_pChar;
				}
				int result = 0;
				if (is_subscribe)
				{
					result = pUserApi->SubscribeTickByTick(chTicker, count, (XTP_EXCHANGE_TYPE)exchage_id);
				}
				else
				{
					result = pUserApi->UnSubscribeTickByTick(chTicker, count, (XTP_EXCHANGE_TYPE)exchage_id);
				}
				delete[] chTicker;
				return result;
			}

			///�˶�������顣
			///@return ȡ�������������ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո�  
			///@param count Ҫ����/�˶����鶩�����ĺ�Լ����
			///@param exchage_id ����������
			///@remark ����һ����ȡ������ͬһ֤ȯ�������Ķ����Լ����Ҫ�붩���������ӿ�����ʹ��
			/*int UnSubscribeTickByTick(array<String^>^ ticker, int count, EXCHANGE_TYPE exchage_id)
			{
				return 0;
			}*/

			///����/�˶�ȫ�г�������
			///@return ����/�˶�ȫ�г�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param  is_subscribe �Ƿ��Ƕ���
			///@remark ��Ҫ��ȫ�г��˶�����ӿ�����ʹ��
			int SubscribeAllMarketData(bool is_subscribe)
			{
				if (is_subscribe)
				{
					return pUserApi->SubscribeAllMarketData();
				}
				else
				{
					return pUserApi->UnSubscribeAllMarketData();
				}
			}

			///�˶�ȫ�г�������
			///@return �˶�ȫ�г�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@remark ��Ҫ�붩��ȫ�г�����ӿ�����ʹ��
			/*int UnSubscribeAllMarketData()
			{
				return pUserApi->UnSubscribeAllMarketData();
			}*/

			///����/�˶�ȫ�г������鶩����
			///@return ����/�˶�ȫ�г����鶩�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param  is_subscribe �Ƿ��Ƕ���
			///@remark ��Ҫ��ȫ�г��˶����鶩�����ӿ�����ʹ��
			int SubscribeAllOrderBook(bool is_subscribe)
			{
				if (is_subscribe)
				{
					return pUserApi->SubscribeAllOrderBook();
				}
				else
				{
					return pUserApi->UnSubscribeAllOrderBook();
				}
			}

			///�˶�ȫ�г������鶩����
			///@return �˶�ȫ�г����鶩�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@remark ��Ҫ�붩��ȫ�г����鶩�����ӿ�����ʹ��
	/*		int UnSubscribeAllOrderBook()
			{
				return 0;
			}*/

			///����/�˶�ȫ�г����������
			///@return ����/�˶�ȫ�г��������ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@param  is_subscribe �Ƿ��Ƕ���
			///@remark ��Ҫ��ȫ�г��˶��������ӿ�����ʹ��
			int SubscribeAllTickByTick(bool is_subscribe)
			{
				if (is_subscribe)
				{
					return pUserApi->SubscribeAllTickByTick();
				}
				else
				{
					return pUserApi->UnSubscribeAllTickByTick();
				}
			}

			///�˶�ȫ�г����������
			///@return �˶�ȫ�г��������ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
			///@remark ��Ҫ�붩��ȫ�г��������ӿ�����ʹ��
			/*int UnSubscribeAllTickByTick()
			{
				return 0;
			}*/
			
			///��ȡ��Լ�����¼۸���Ϣ
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ��ѯ�ɹ����ǡ�0����ʾ��ѯ���ɹ�
			///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո�  
			///@param exchage_id ����������
			int QueryTickersPriceInfo(array<String^>^ ticker, EXCHANGE_TYPE exchage_id)
			{
				int count = ticker->Length;
				char** chTicker = new char*[count];
				for (int i = 0; i < count; ++i)
				{
					chTicker[i] = Native::CAutoStrPtr::CAutoStrPtr(ticker[i]).m_pChar;
				}
				int result = pUserApi->QueryTickersPriceInfo(chTicker,count,(XTP_EXCHANGE_TYPE)exchage_id);
				delete[] chTicker;
				return result;
			}

			///��ȡ���к�Լ�����¼۸���Ϣ
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ��ѯ�ɹ����ǡ�0����ʾ��ѯ���ɹ�
			int QueryAllTickersPriceInfo()
			{
				return pUserApi->QueryAllTickersPriceInfo();
			}

			#pragma endregion
		#pragma region ������¶�¼�����
			event XTP::API::QuoteEventSource::OnDisconnectedDelegate^ OnDisconnectedEvent;
			event XTP::API::QuoteEventSource::OnErrorDelegate^ OnErrorEvent;
			event XTP::API::QuoteEventSource::OnSubMarketDataDelegate^ OnSubMarketDataEvent;
			event XTP::API::QuoteEventSource::OnUnSubMarketDataDelegate^ OnUnSubMarketDataEvent;
			event XTP::API::QuoteEventSource::OnDepthMarketDataDelegate^ OnDepthMarketDataEvent;
			event XTP::API::QuoteEventSource::OnQueryAllTickersDelegate^ OnQueryAllTickersEvent;
		#pragma endregion

		protected:
		#pragma region �¼�����

			void OnDisconnected(int reason)
			{
				IsLogin = false;
				OnDisconnectedEvent(reason);
			}
			void OnError(RspInfoStruct^ resp)
			{
				OnErrorEvent(resp);
			}
			void OnSubMarketData(RspInfoStruct^ resp, SpecificTickerStruct^ ticker, bool is_last)
			{
				OnSubMarketDataEvent(resp, ticker, is_last);
			}
			void OnUnSubMarketData(RspInfoStruct^ resp, SpecificTickerStruct^ ticker, bool is_last)
			{
				OnUnSubMarketDataEvent(resp, ticker, is_last);
			}

			void OnDepthMarketData(MarketDataStruct^ md, array<Int64>^ bid1Qtys, Int32 bid1Count, Int32 bid1MaxCount, array<Int64>^ ask1Qtys, Int32 ask1Count, Int32 ask1MaxCount) {
				OnDepthMarketDataEvent(md, bid1Qtys, bid1Count, bid1MaxCount, ask1Qtys, ask1Count, ask1MaxCount);
			}
			void OnQueryAllTickers(RspInfoStruct^ resp, QuoteStaticInfoStruct^ ticker_info, bool is_last)
			{
				OnQueryAllTickersEvent(resp, ticker_info, is_last);
			}
			
			///�������鶩����Ӧ��
			///@param ticker ��ϸ�ĺ�Լ�������
			///@param error_info ���ĺ�Լ��������ʱ�Ĵ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴ζ��ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ÿ�����ĵĺ�Լ����Ӧһ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			void OnSubOrderBook(SpecificTickerStruct^ ticker, RspInfoStruct^ error_info, bool is_last) 
			{

			}

			///�˶����鶩����Ӧ��
			///@param ticker ��ϸ�ĺ�Լȡ���������
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴�ȡ�����ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ÿ��ȡ�����ĵĺ�Լ����Ӧһ��ȡ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			void OnUnSubOrderBook(SpecificTickerStruct^ ticker, RspInfoStruct^ error_info, bool is_last) 
			{
			}

			///���鶩����֪ͨ
			///@param order_book ���鶩�������ݣ���Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			virtual void OnOrderBook(XTPOB *order_book) {};

			///�����������Ӧ��
			///@param ticker ��ϸ�ĺ�Լ�������
			///@param error_info ���ĺ�Լ��������ʱ�Ĵ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴ζ��ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ÿ�����ĵĺ�Լ����Ӧһ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			virtual void OnSubTickByTick(SpecificTickerStruct^ ticker, RspInfoStruct^ error_info, bool is_last) 
			{
			}

			///�˶��������Ӧ��
			///@param ticker ��ϸ�ĺ�Լȡ���������
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴�ȡ�����ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ÿ��ȡ�����ĵĺ�Լ����Ӧһ��ȡ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			void OnUnSubTickByTick(SpecificTickerStruct^ ticker, RspInfoStruct^ error_info, bool is_last) 
			{}

			///�������֪ͨ
			///@param tbt_data ����������ݣ��������ί�к���ʳɽ�����Ϊ���ýṹ�壬��Ҫ����type�����������ί�л�����ʳɽ�����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			void OnTickByTick(XTPTBT *tbt_data) 
			{}

			///����ȫ�г�������Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			void OnSubscribeAllMarketData(RspInfoStruct^ error_info) 
			{}

			///�˶�ȫ�г�������Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			void OnUnSubscribeAllMarketData(RspInfoStruct^ error_info) {}

			///����ȫ�г������鶩����Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			void OnSubscribeAllOrderBook(RspInfoStruct^ error_info) {}

			///�˶�ȫ�г������鶩����Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			void OnUnSubscribeAllOrderBook(RspInfoStruct^ error_info) {}

			///����ȫ�г����������Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			void OnSubscribeAllTickByTick(RspInfoStruct^ error_info) {}

			///�˶�ȫ�г����������Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			void OnUnSubscribeAllTickByTick(RspInfoStruct^ error_info) {}


			///��ѯ�ɽ��׺�Լ��Ӧ��
			///@param ticker_info �ɽ��׺�Լ��Ϣ
			///@param error_info ��ѯ�ɽ��׺�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴β�ѯ�ɽ��׺�Լ�����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			void OnQueryAllTickers(XTPQSI* ticker_info, RspInfoStruct^ error_info, bool is_last) 
			{}

			///��ѯ��Լ�����¼۸���ϢӦ��
			///@param ticker_info ��Լ�����¼۸���Ϣ
			///@param error_info ��ѯ��Լ�����¼۸���Ϣʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴β�ѯ�����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			void OnQueryTickersPriceInfo(XTPTPI* ticker_info, RspInfoStruct^ error_info, bool is_last) 
			{}

		#pragma endregion

		};

	}
}
