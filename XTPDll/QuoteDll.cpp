// XTPDll.cpp: ����Ŀ�ļ���
#pragma once
#include "stdafx.h"
#include <msclr/marshal.h>
#include "QuoteDll.h"
#include <functional>
#include "./xtpinclude/xtp_quote_api.h"
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
			delegate void OnSubMarketDataDelegate(RspInfoStruct^, SpecificTickerStruct^,bool);
			delegate void OnUnSubMarketDataDelegate(RspInfoStruct^, SpecificTickerStruct^, bool);
			delegate void OnMarketDataDelegate(MarketDataStruct^);
			delegate void OnQueryAllTickersDelegate(RspInfoStruct^, QuoteStaticInfoStruct^,  bool);
			event OnDisconnectedDelegate^ OnDisconnectedEvent;
			event OnErrorDelegate^ OnErrorEvent;
			event OnSubMarketDataDelegate^ OnSubMarketDataEvent;
			event OnUnSubMarketDataDelegate^ OnUnSubMarketDataEvent;
			event OnMarketDataDelegate ^OnMarketDataEvent;
			event OnQueryAllTickersDelegate ^OnQueryAllTickersEvent;

			void OnDisconnected(int reason) {
				OnDisconnectedEvent(reason);
			}
			void OnError(RspInfoStruct^ resp) {
				OnErrorEvent(resp);
			}
			void OnSubMarketData(RspInfoStruct^ resp, SpecificTickerStruct^ ticker,bool is_last) {
				//if (myEvent != nullptr)
				OnSubMarketDataEvent(resp,ticker,is_last);
			}
			void OnUnSubMarketData(RspInfoStruct^ resp, SpecificTickerStruct^ ticker, bool is_last) {
				OnUnSubMarketDataEvent(resp, ticker, is_last);
			}
			void OnMarketData(MarketDataStruct^ data) {
				OnMarketDataEvent(data);
			}
			void OnQueryAllTickers(RspInfoStruct^ resp, QuoteStaticInfoStruct^ ticker_info,bool is_last) {
				OnQueryAllTickersEvent(resp, ticker_info,is_last);
			};
		private:
			//MyOnSubMarketDataDelegate ^myEvent;
			//Object ^eventLock;
		};
		///ȫ���¼�,��������������Ի�ͨ
		gcroot<QuoteEventSource^> quoteevent_managed = gcnew QuoteEventSource();

		///�����¼����壬��Ϊ����ͨ�ࣨ��Ҫ�̳�QuoteSpi�����������࣬�����޷����ڲ�����delegate
		public class MyQuoteSpi:public QuoteSpi {
		public:
			#pragma region ʵ��QuoteSpi�ص�
			void OnError(XTPRI *error_info) {
				RspInfoStruct^ resInfo = gcnew RspInfoStruct();
				resInfo->error_id = error_info->error_id;
				resInfo->error_msg = gcnew String(error_info->error_msg);
				quoteevent_managed->OnError(resInfo);
				delete resInfo;
			}
			void OnDisconnected(int reason) {
				quoteevent_managed->OnDisconnected(reason);
			}
			void OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) {
				RspInfoStruct^ resInfo = gcnew RspInfoStruct();
				resInfo->error_id = error_info->error_id;
				resInfo->error_msg = gcnew String(error_info->error_msg);
				SpecificTickerStruct^ ticketInfo = gcnew SpecificTickerStruct();
				ticketInfo->exchange_id = ticker->exchange_id;
				ticketInfo->ticker = gcnew String(ticker->ticker);
				quoteevent_managed->OnSubMarketData(resInfo,ticketInfo,is_last);
				delete resInfo;
				delete ticketInfo;
			}
			void OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) {
				RspInfoStruct^ resInfo = gcnew RspInfoStruct();
				resInfo->error_id = error_info->error_id;
				resInfo->error_msg = gcnew String(error_info->error_msg);
				SpecificTickerStruct^ ticketInfo = gcnew SpecificTickerStruct();
				ticketInfo->exchange_id = ticker->exchange_id;
				ticketInfo->ticker = gcnew String(ticker->ticker);
				quoteevent_managed->OnUnSubMarketData(resInfo, ticketInfo, is_last);
				delete resInfo;
				delete ticketInfo;
			}
			void OnMarketData(XTPMD *market_data) {
				#pragma region �յ��г��ɼ�����

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

				#pragma endregion
				quoteevent_managed->OnMarketData(data);
				delete data;
			}
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
		public ref class TXPQuote
		{
		private:
			XTP::API::QuoteApi * pUserApi;
			XTP::API::QuoteSpi* pUserSpi;
			//QuoteSpiManagedClass ^mc;
		public:
			TXPQuote(int client_id , String ^ log_path)  // XTP::API::MyQuoteSpi % spi
			{
				char* log_path_char = (char*)Marshal::StringToHGlobalAnsi(log_path).ToPointer();
				//printf(str2);
				pUserApi = XTP::API::QuoteApi::CreateQuoteApi(client_id, log_path_char);
				//mc = gcnew QuoteSpiManagedClass();
				//pUserSpi = mc->m_Impl;// 
				pUserSpi = new XTP::API::MyQuoteSpi();
				Marshal::FreeHGlobal((IntPtr)log_path_char);
				quoteevent_managed->OnDisconnectedEvent += gcnew XTP::API::QuoteEventSource::OnDisconnectedDelegate(this, &XTP::API::TXPQuote::OnDisconnected);
				quoteevent_managed->OnErrorEvent += gcnew XTP::API::QuoteEventSource::OnErrorDelegate(this, &XTP::API::TXPQuote::OnError);
				quoteevent_managed->OnSubMarketDataEvent += gcnew XTP::API::QuoteEventSource::OnSubMarketDataDelegate(this, &XTP::API::TXPQuote::OnSubMarketData);
				quoteevent_managed->OnUnSubMarketDataEvent += gcnew XTP::API::QuoteEventSource::OnUnSubMarketDataDelegate(this, &XTP::API::TXPQuote::OnUnSubMarketData);
				quoteevent_managed->OnMarketDataEvent += gcnew XTP::API::QuoteEventSource::OnMarketDataDelegate(this, &XTP::API::TXPQuote::OnMarketData);
				quoteevent_managed->OnQueryAllTickersEvent += gcnew XTP::API::QuoteEventSource::OnQueryAllTickersDelegate(this, &XTP::API::TXPQuote::OnQueryAllTickers);
				pUserApi->RegisterSpi(pUserSpi);
			}
			bool IsLogin = false;
			#pragma region ��������

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
			//��������
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
			int Logout() {
				IsLogin = false;
				return pUserApi->Logout();
			}
			#pragma endregion
			#pragma region ������¶�¼�����
			event XTP::API::QuoteEventSource::OnDisconnectedDelegate^ OnDisconnectedEvent;
			event XTP::API::QuoteEventSource::OnErrorDelegate^ OnErrorEvent;
			event XTP::API::QuoteEventSource::OnSubMarketDataDelegate^ OnSubMarketDataEvent;
			event XTP::API::QuoteEventSource::OnUnSubMarketDataDelegate^ OnUnSubMarketDataEvent;
			event XTP::API::QuoteEventSource::OnMarketDataDelegate^ OnMarketDataEvent;
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
			void OnMarketData(MarketDataStruct^ data)
			{
				OnMarketDataEvent(data);
			}
			void OnQueryAllTickers(RspInfoStruct^ resp, QuoteStaticInfoStruct^ ticker_info, bool is_last)
			{
				OnQueryAllTickersEvent(resp, ticker_info, is_last);
			}
			#pragma endregion

		};

	}
}
