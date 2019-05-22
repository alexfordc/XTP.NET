#pragma once
#include "stdafx.h"
#include <msclr/marshal.h>
#include "xtpstruct.h"
#include "utils.h"
#include <functional>
#include "XtpTraderSpi.h"
#include"../sdk/include/xtp_trader_api.h"
using namespace msclr::interop;
using namespace System;
using namespace System::Runtime::InteropServices;

namespace XTP
{
	namespace API
	{
		XtpTraderAdapter::XtpTraderAdapter(int client_id, String^ account_key, String ^ log_path, TE_RESUME_TYPE resume_type)
		{
			
			pTdApi = XTP::API::TraderApi::CreateTraderApi(client_id, CAutoStrPtr(log_path).m_pChar);
			pTdApi->SubscribePublicTopic((XTP_TE_RESUME_TYPE)resume_type);
			pTdApi->SetSoftwareVersion("1.1.16.9");

			char* account_key_char = (char*)Marshal::StringToHGlobalAnsi(account_key).ToPointer();
			pTdApi->SetSoftwareKey(account_key_char);
			Marshal::FreeHGlobal((IntPtr)account_key_char);

			pTdSpi = new XtpTraderSpi(this);
			
			pTdApi->RegisterSpi(pTdSpi);
		}
		XtpTraderAdapter::~XtpTraderAdapter()
		{
			//
		}
		UInt64 XtpTraderAdapter::Login(String ^ ip, int port, String ^ investor_id, String ^ password, PROTOCOL_TYPE protocal_type) {
			char* investor_id_char = (char*)Marshal::StringToHGlobalAnsi(investor_id).ToPointer();
			char* password_char = (char*)Marshal::StringToHGlobalAnsi(password).ToPointer();
			char* ip_char = (char*)Marshal::StringToHGlobalAnsi(ip).ToPointer();
			uint64_t loginResult = pTdApi->Login(ip_char, port, investor_id_char, password_char, (XTP_PROTOCOL_TYPE)protocal_type);//XTP_PROTOCOL_TCP
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
		UInt64 XtpTraderAdapter::GetClientIDByXTPID(UInt64 order_xtp_id) {
			return pTdApi->GetClientIDByXTPID(order_xtp_id);
		}
		///ͨ��������xtpϵͳ�е�ID��ȡ����ʽ��˻���
		///@return �����ʽ��˻���
		///@param order_xtp_id ������xtpϵͳ�е�ID
		///@remark ֻ���ʽ��˻���¼�ɹ���,���ܵõ���ȷ����Ϣ
		String^ XtpTraderAdapter::GetAccountByXTPID(UInt64 order_xtp_id) {
			return gcnew String(pTdApi->GetAccountByXTPID(order_xtp_id));
		}
		void XtpTraderAdapter::SubscribePublicTopic(TE_RESUME_TYPE resume_type) {
			pTdApi->SubscribePublicTopic((XTP_TE_RESUME_TYPE)resume_type);
		}

		void XtpTraderAdapter::SetHeartBeatInterval(UInt32 interval)
		{
			pTdApi->SetHeartBeatInterval(interval);
		}

		String^ XtpTraderAdapter::GetTradingDay() {
			return  gcnew String(pTdApi->GetTradingDay());
		}
		//��ȡAPI�汾��
		String^ XtpTraderAdapter::GetApiVersion() {
			return  gcnew String(pTdApi->GetApiVersion());
		}
		///��ȡAPI��ϵͳ����
		RspInfoStruct^ XtpTraderAdapter::GetApiLastError() {
			XTPRI* error_info = pTdApi->GetApiLastError();
			RspInfoStruct^ resInfo = gcnew RspInfoStruct();
			resInfo->error_id = error_info->error_id;
			resInfo->error_msg = gcnew String(error_info->error_msg);
			return resInfo;
		}
		///�ǳ�����
		///@return �ǳ��Ƿ�ɹ�����0����ʾ�ǳ��ɹ�����-1����ʾ�ǳ�ʧ��
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		int XtpTraderAdapter::Logout(UInt64 session_id) {
			IsLogin = false;
			return pTdApi->Logout(session_id);
		}
		UInt64 XtpTraderAdapter::InsertOrder(OrderInsertInfo ^order, UInt64 session_id) {
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
			return pTdApi->InsertOrder(order_info, session_id);
		}
		///������������
		///@return ������XTPϵͳ�е�ID,���Ϊ��0����ʾ��������ʧ�ܣ���ʱ�û����Ե���GetApiLastError()����ȡ������룬�ǡ�0����ʾ�������ͳɹ����û���Ҫ��¼�·��ص�order_cancel_xtp_id������֤һ����������Ψһ����ͬ�Ľ����ղ���֤Ψһ��
		///@param order_xtp_id ��Ҫ������ί�е���XTPϵͳ�е�ID
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		///@remark ��������ɹ������ڱ�����Ӧ����OnOrderEvent()�ﷵ��ԭ����������ȫ������Ϣ��������ɹ�������OnCancelOrderError()��Ӧ�����з��ش���ԭ��
		UInt64 XtpTraderAdapter::CancelOrder(UInt64 order_xtp_id, UInt64 session_id) {
			return pTdApi->CancelOrder(order_xtp_id, session_id);
		}
		///���ݱ���ID�����ѯ����
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param order_xtp_id ��Ҫ��ѯ�ı�����xtpϵͳ�е�ID����InsertOrder()�ɹ�ʱ���ص�order_xtp_id
		///@param session_id �ʽ��˻���Ӧ��session_id����¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		int XtpTraderAdapter::QueryOrderByXTPID(UInt64 order_xtp_id, UInt64 session_id, int request_id) {
			return pTdApi->QueryOrderByXTPID(order_xtp_id, session_id, request_id);
		}
		///�����ѯ����
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param query_param ��Ҫ��ѯ�Ķ������ɸѡ���������к�Լ�������Ϊ�գ���Ĭ�����д��ڵĺ�Լ���룬�����Ϊ�գ��벻���ո񣬲���'\0'��β��������ʼʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰ������0�㣬����ʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰʱ��
		///@param session_id �ʽ��˻���Ӧ��session_id����¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		///@remark �÷���֧�ַ�ʱ�β�ѯ�������Ʊ����Ϊ�գ���Ĭ�ϲ�ѯʱ����ڵ����б����������ѯʱ��������и���Ʊ������صı������˺�����ѯ���Ľ�����ܶ�Ӧ�����ѯ�����Ӧ
		int XtpTraderAdapter::QueryOrders(QueryOrderReq ^query_param, UInt64 session_id, int request_id) {
			XTPQueryOrderReq *query = new XTPQueryOrderReq();
			IntPtr ticker = Marshal::StringToHGlobalAnsi(query_param->ticker);
			strcpy(query->ticker, static_cast<char*>(ticker.ToPointer()));
			Marshal::FreeHGlobal(ticker);
			query->begin_time = query_param->begin_time;
			query->end_time = query_param->end_time;
			return pTdApi->QueryOrders(query, session_id, request_id);
		}
		///����ί�б�������ѯ��سɽ�
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param order_xtp_id ��Ҫ��ѯ��ί�б�ţ���InsertOrder()�ɹ�ʱ���ص�order_xtp_id
		///@param session_id �ʽ��˻���Ӧ��session_id����¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		///@remark �˺�����ѯ���Ľ�����ܶ�Ӧ�����ѯ�����Ӧ
		int XtpTraderAdapter::QueryTradesByXTPID(UInt64 order_xtp_id, UInt64 session_id, int request_id) {
			return pTdApi->QueryTradesByXTPID(order_xtp_id, session_id, request_id);
		}
		///�����ѯ�ѳɽ�
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param query_param ��Ҫ��ѯ�ĳɽ��ر�ɸѡ���������к�Լ�������Ϊ�գ���Ĭ�����д��ڵĺ�Լ���룬�����Ϊ�գ��벻���ո񣬲���'\0'��β��������ʼʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰ������0�㣬����ʱ���ʽΪYYYYMMDDHHMMSSsss��Ϊ0��Ĭ�ϵ�ǰʱ��
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		///@remark �÷���֧�ַ�ʱ�β�ѯ�������Ʊ����Ϊ�գ���Ĭ�ϲ�ѯʱ����ڵ����гɽ��ر��������ѯʱ��������и���Ʊ������صĳɽ��ر����˺�����ѯ���Ľ�����ܶ�Ӧ�����ѯ�����Ӧ
		int XtpTraderAdapter::QueryTrades(QueryTraderReq ^query_param, UInt64 session_id, int request_id) {
			XTPQueryTraderReq *query = new XTPQueryTraderReq();
			IntPtr ticker = Marshal::StringToHGlobalAnsi(query_param->ticker);
			strcpy(query->ticker, static_cast<char*>(ticker.ToPointer()));
			Marshal::FreeHGlobal(ticker);
			query->begin_time = query_param->begin_time;
			query->end_time = query_param->end_time;
			return pTdApi->QueryTrades(query, session_id, request_id);
		}
		///�����ѯͶ���ֲ߳�
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param ticker ��Ҫ��ѯ�ĳֲֺ�Լ���룬����Ϊ�գ������Ϊ�գ��벻���ո񣬲���'\0'��β
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		///@remark �÷�������û��ṩ�˺�Լ���룬����ѯ�˺�Լ�ĳֲ���Ϣ�������Լ����Ϊ�գ���Ĭ�ϲ�ѯ���гֲ���Ϣ
		int XtpTraderAdapter::QueryPosition(String^ ticker, UInt64 session_id, int request_id) {
			char* ticker_char = (char*)Marshal::StringToHGlobalAnsi(ticker).ToPointer();
			int result = pTdApi->QueryPosition(ticker_char, session_id, request_id);
			Marshal::FreeHGlobal((IntPtr)ticker_char);
			return result;
		}
		///�����ѯ�ʲ�
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		int XtpTraderAdapter::QueryAsset(UInt64 session_id, int request_id) {
			return pTdApi->QueryAsset(session_id, request_id);
		}

		///�����ѯ�ּ�����
			///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
			///@param query_param ��Ҫ��ѯ�ķּ�����ɸѡ����������ĸ����������Ϊ�գ���Ĭ�����д��ڵ�ĸ���������Ϊ�գ��벻���ո񣬲���'\0'��β�����н����г�����Ϊ��
			///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
			///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
			///@remark �˺�����ѯ���Ľ�����ܶ�Ӧ�����ѯ�����Ӧ
		int XtpTraderAdapter::QueryStructuredFund(QueryStructuredFundInfoReq^  query_param, UInt64 session_id, int request_id)
		{
			XTPQueryStructuredFundInfoReq native;
			MNConv<QueryStructuredFundInfoReq^, XTPQueryStructuredFundInfoReq>::M2N(query_param, &native);
			return pTdApi->QueryStructuredFund(&native, session_id, request_id);
		}

		///�ʽ𻮲�����
		///@return �ʽ𻮲�������XTPϵͳ�е�ID,���Ϊ��0����ʾ��Ϣ����ʧ�ܣ���ʱ�û����Ե���GetApiLastError()����ȡ������룬�ǡ�0����ʾ��Ϣ���ͳɹ����û���Ҫ��¼�·��ص�serial_id������֤һ����������Ψһ����ͬ�Ľ����ղ���֤Ψһ��
		///@param fund_transfer �ʽ𻮲���������Ϣ
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		///@remark �˺���֧��һ�������Ľڵ�֮����ʽ𻮲���ע���ʽ𻮲��ķ���
		UInt64  XtpTraderAdapter::FundTransfer(FundTransferReq^ fund_transfer, UInt64 session_id)
		{
			XTPFundTransferReq native;
			MNConv<FundTransferReq^, XTPFundTransferReq>::M2N(fund_transfer, &native);
			return pTdApi->FundTransfer(&native, session_id);
		}

		///�����ѯ�ʽ𻮲�
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param query_param ��Ҫ��ѯ���ʽ𻮲�����ɸѡ����������serial_id����Ϊ0����Ĭ�������ʽ𻮲������������Ϊ0���������ض����ʽ𻮲�����
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		int XtpTraderAdapter::QueryFundTransfer(QueryFundTransferLogReq^ query_param, UInt64 session_id, int request_id)
		{
			XTPQueryFundTransferLogReq native;
			MNConv<QueryFundTransferLogReq^, XTPQueryFundTransferLogReq>::M2N(query_param, &native);
			return pTdApi->QueryFundTransfer(&native, session_id, request_id);
		}

		///�����ѯETF�嵥�ļ�
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param query_param ��Ҫ��ѯ��ETF�嵥�ļ���ɸѡ���������к�Լ�������Ϊ�գ���Ĭ�����д��ڵ�ETF��Լ���룬market�ֶ�Ҳ����Ϊ��ʼֵ����Ĭ�������г���ETF��Լ
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		int XtpTraderAdapter::QueryETF(QueryETFBaseReq^ query_param, UInt64 session_id, int request_id)
		{
			XTPQueryETFBaseReq native;
			MNConv<QueryETFBaseReq^, XTPQueryETFBaseReq>::M2N(query_param, &native);
			return pTdApi->QueryETF(&native, session_id, request_id);
		}

		///�����ѯETF��Ʊ��
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param query_param ��Ҫ��ѯ��Ʊ���ĵ�ETF��Լ�����к�Լ���벻����Ϊ�գ�market�ֶ�Ҳ����ָ��
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		int XtpTraderAdapter::QueryETFTickerBasket(QueryETFComponentReq^ query_param, UInt64 session_id, int request_id)
		{
			XTPQueryETFComponentReq native;
			MNConv<QueryETFComponentReq^, XTPQueryETFComponentReq>::M2N(query_param, &native);
			return pTdApi->QueryETFTickerBasket(&native, session_id, request_id);
		}

		///�����ѯ�����¹��깺��Ϣ�б�
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		int XtpTraderAdapter::QueryIPOInfoList(UInt64 session_id, int request_id)
		{
			return pTdApi->QueryIPOInfoList(session_id, request_id);
		}

		///�����ѯ�û��¹��깺�����Ϣ
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		int XtpTraderAdapter::QueryIPOQuotaInfo(UInt64 session_id, int request_id)
		{
			return pTdApi->QueryIPOQuotaInfo( session_id, request_id);
		}

		///�����ѯ��Ȩ��Լ
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ�ɹ����ǡ�0����ʾ������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@param query_param ��Ҫ��ѯ����Ȩ��Լ��ɸѡ����������ΪNULL��ΪNULL��ʾ��ѯ���е���Ȩ��Լ��
		///@param session_id �ʽ��˻���Ӧ��session_id,��¼ʱ�õ�
		///@param request_id �����û���λ��ѯ��Ӧ��ID�����û��Զ���
		int XtpTraderAdapter::QueryOptionAuctionInfo(QueryOptionAuctionInfoReq^ query_param, UInt64 session_id, int request_id)
		{
			XTPQueryOptionAuctionInfoReq native;
			MNConv<QueryOptionAuctionInfoReq^, XTPQueryOptionAuctionInfoReq>::M2N(query_param, &native);
			return pTdApi->QueryOptionAuctionInfo(&native, session_id,request_id);
		}
	}
}