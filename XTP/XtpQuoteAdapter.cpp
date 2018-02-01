// XTPDll.cpp: ����Ŀ�ļ���
#pragma once
#include "stdafx.h"
#include <msclr/marshal.h>
#include "xtpstruct.h"
#include "utils.h"
#include <functional>
#include"XtpQuoteAdapter.h"
#include"XtpQuoteSpi.h"
#include "..\sdk\include\xtp_quote_api.h"

using namespace msclr::interop;
using namespace System;
using namespace System::Runtime::InteropServices;

namespace XTP {
	namespace API {
		
		///����QuoteApi
		///@param client_id ���������룩��������ͬһ�û��Ĳ�ͬ�ͻ��ˣ����û��Զ���
		///@param log_path ���������룩����������Ϣ�ļ���Ŀ¼�����趨һ���п�дȨ�޵���ʵ���ڵ�·��
		///@param log_level ��־�������
		///@remark ���һ���˻���Ҫ�ڶ���ͻ��˵�¼����ʹ�ò�ͬ��client_id��ϵͳ����һ���˻�ͬʱ��¼����ͻ��ˣ����Ƕ���ͬһ�˻�����ͬ��client_idֻ�ܱ���һ��session���ӣ�����ĵ�¼��ǰһ��session�����ڼ䣬�޷�����
		XtpQuoteAdapter::XtpQuoteAdapter(int client_id, String ^ log_path, LOG_LEVEL log_level)
		{
			pUserApi = XTP::API::QuoteApi::CreateQuoteApi(client_id, CAutoStrPtr(log_path).m_pChar, (XTP_LOG_LEVEL)log_level);

			pUserSpi = new XtpQuoteSpi(this);
		
			pUserApi->RegisterSpi(pUserSpi);
		}
		XtpQuoteAdapter::~XtpQuoteAdapter(void)
		{

		}

		///�û���¼����
		///@return ��¼�Ƿ�ɹ�����0����ʾ��¼�ɹ�����-1����ʾ���ӷ�����������ʱ�û����Ե���GetApiLastError()����ȡ������룬��-2����ʾ�Ѵ������ӣ��������ظ���¼�������Ҫ����������logout����-3����ʾ�����д���
		///@param ip ������ip��ַ�����ơ�127.0.0.1��
		///@param port �������˿ں�
		///@param user ��½�û���
		///@param password ��½����
		///@param sock_type ��1������TCP����2������UDP
		///@remark �˺���Ϊͬ������ʽ������Ҫ�첽�ȴ���¼�ɹ������������ؼ��ɽ��к�����������apiֻ����һ������
		int XtpQuoteAdapter::Login(String ^ ip, int port, String ^ investor_id, String ^ password, PROTOCOL_TYPE protocal_type) {
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

		String^ XtpQuoteAdapter::GetTradingDay() {
			return  gcnew String(pUserApi->GetTradingDay());
		}
		//��ȡAPI�汾��
		String^ XtpQuoteAdapter::GetApiVersion() {
			return  gcnew String(pUserApi->GetApiVersion());
		}
		///��ȡAPI��ϵͳ����
		RspInfoStruct^ XtpQuoteAdapter::GetApiLastError() {
			XTPRI* error_info = pUserApi->GetApiLastError();
			RspInfoStruct^ resInfo = gcnew RspInfoStruct();
			resInfo->error_id = error_info->error_id;
			resInfo->error_msg = gcnew String(error_info->error_msg);
			return resInfo;
		}
		//��ѯ���й�Ʊ����
		int XtpQuoteAdapter::QueryAllTickers(EXCHANGE_TYPE exchange) {
			return pUserApi->QueryAllTickers((XTP_EXCHANGE_TYPE)exchange);
		}
		
		///�ǳ�����
		///@return �ǳ��Ƿ�ɹ�����0����ʾ�ǳ��ɹ����ǡ�0����ʾ�ǳ�������ʱ�û����Ե���GetApiLastError()����ȡ�������
		///@remark �˺���Ϊͬ������ʽ������Ҫ�첽�ȴ��ǳ������������ؼ��ɽ��к�������
		int XtpQuoteAdapter::Logout() {
			IsLogin = false;
			return pUserApi->Logout();
		}
		
		///���ò���UDP��ʽ����ʱ�Ľ��ջ�������С
		///@remark ��Ҫ��Login֮ǰ���ã�Ĭ�ϴ�С����С���þ�Ϊ64MB���˻����С��λΪMB��������2�Ĵη���������128MB������128��
		void XtpQuoteAdapter::SetUDPBufferSize(UInt32 buff_size)
		{
			pUserApi->SetUDPBufferSize(buff_size);
		}

		///�����������ʱ��������λΪ��
		///@param interval �������ʱ��������λΪ��
		///@remark �˺���������Login֮ǰ����
		void XtpQuoteAdapter::SetHeartBeatInterval(UInt32 interval)
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
		int XtpQuoteAdapter::SubscribeMarketData(array<String^>^ ticker, EXCHANGE_TYPE exchange, bool is_subscribe) {
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

		///����/�˶����鶩������
		///@return ����/�˶����鶩�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
		///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո� 
		///@param exchage_id ����������
		///@param is_subscribe �Ƿ��Ƕ���
		///@remark ����һ���Զ���ͬһ֤ȯ�������Ķ����Լ�������û���Ϊ����������Ҫ���µ�¼���������������Ҫ���¶�������(�ݲ�֧��)
		int XtpQuoteAdapter::SubscribeOrderBook(array<String^>^ ticker, EXCHANGE_TYPE exchage_id, bool is_subscribe)
		{///@param count Ҫ����/�˶����鶩�����ĺ�Լ����

			int count = ticker->Length;
			char** chTicker = new char*[count];
			for (int i = 0; i < count; ++i)
			{
				chTicker[i] =  CAutoStrPtr::CAutoStrPtr(ticker[i]).m_pChar;
			}
			int result = 0;
			if (is_subscribe)
			{
				result = pUserApi->SubscribeOrderBook(chTicker, count, (XTP_EXCHANGE_TYPE)exchage_id);
			}
			else
			{
				result = pUserApi->UnSubscribeOrderBook(chTicker, count, (XTP_EXCHANGE_TYPE)exchage_id);
			}
			delete[] chTicker;
			return result;
		}

		///����/�˶�������顣
		///@return ����/�˶��������ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
		///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո�  
		///@param exchage_id ����������
		///@param  is_subscribe �Ƿ��Ƕ���
		///@remark ����һ���Զ���ͬһ֤ȯ�������Ķ����Լ�������û���Ϊ����������Ҫ���µ�¼���������������Ҫ���¶�������(�ݲ�֧��)
		int XtpQuoteAdapter::SubscribeTickByTick(array<String^>^ ticker, EXCHANGE_TYPE exchage_id, bool is_subscribe)
		{
			int count = ticker->Length;
			char** chTicker = new char*[count];
			for (int i = 0; i < count; ++i)
			{
				chTicker[i] =  CAutoStrPtr::CAutoStrPtr(ticker[i]).m_pChar;
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

		///����/�˶�ȫ�г�������
		///@return ����/�˶�ȫ�г�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
		///@param  is_subscribe �Ƿ��Ƕ���
		///@remark ��Ҫ��ȫ�г��˶�����ӿ�����ʹ��
		int XtpQuoteAdapter::SubscribeAllMarketData(bool is_subscribe)
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

		///����/�˶�ȫ�г������鶩����
		///@return ����/�˶�ȫ�г����鶩�����ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
		///@param  is_subscribe �Ƿ��Ƕ���
		///@remark ��Ҫ��ȫ�г��˶����鶩�����ӿ�����ʹ��
		int XtpQuoteAdapter::SubscribeAllOrderBook(bool is_subscribe)
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
		
		///����/�˶�ȫ�г����������
		///@return ����/�˶�ȫ�г��������ӿڵ����Ƿ�ɹ�����0����ʾ�ӿڵ��óɹ����ǡ�0����ʾ�ӿڵ��ó���
		///@param  is_subscribe �Ƿ��Ƕ���
		///@remark ��Ҫ��ȫ�г��˶��������ӿ�����ʹ��
		int XtpQuoteAdapter::SubscribeAllTickByTick(bool is_subscribe)
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
				
		///��ȡ��Լ�����¼۸���Ϣ
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ��ѯ�ɹ����ǡ�0����ʾ��ѯ���ɹ�
		///@param ticker ��ԼID���飬ע���Լ���������'\0'��β���������ո�  
		///@param exchage_id ����������
		int XtpQuoteAdapter::QueryTickersPriceInfo(array<String^>^ ticker, EXCHANGE_TYPE exchage_id)
		{
			int count = ticker->Length;
			char** chTicker = new char*[count];
			for (int i = 0; i < count; ++i)
			{
				chTicker[i] =  CAutoStrPtr::CAutoStrPtr(ticker[i]).m_pChar;
			}
			int result = pUserApi->QueryTickersPriceInfo(chTicker, count, (XTP_EXCHANGE_TYPE)exchage_id);
			delete[] chTicker;
			return result;
		}

		///��ȡ���к�Լ�����¼۸���Ϣ
		///@return ��ѯ�Ƿ�ɹ�����0����ʾ��ѯ�ɹ����ǡ�0����ʾ��ѯ���ɹ�
		int XtpQuoteAdapter::QueryAllTickersPriceInfo()
		{
			return pUserApi->QueryAllTickersPriceInfo();
		}
	}
}
