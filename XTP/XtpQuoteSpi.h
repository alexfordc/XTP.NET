#pragma once

#include<vcclr.h>
#include"utils.h"
#include"XtpQuoteAdapter.h"

namespace XTP
{
	namespace API {
		class XtpQuoteSpi :public QuoteSpi
		{
		private:
			gcroot<XtpQuoteAdapter^> m_pAdapter;
		public:
			XtpQuoteSpi(XtpQuoteAdapter^ pAdapter);
		public:
			///���ͻ����������̨ͨ�����ӶϿ�ʱ���÷��������á�
			///@param reason ����ԭ��������������Ӧ
			///@remark api�����Զ������������߷���ʱ�����û�����ѡ����������������ڴ˺����е���Login���µ�¼��ע���û����µ�¼����Ҫ���¶�������
			virtual void OnDisconnected(int reason) ;


			///����Ӧ��
			///@param error_info ����������Ӧ��������ʱ�ľ���Ĵ������ʹ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark �˺���ֻ���ڷ�������������ʱ�Ż���ã�һ�������û�����
			virtual void OnError(XTPRI *error_info) ;

			///��������Ӧ��
			///@param ticker ��ϸ�ĺ�Լ�������
			///@param error_info ���ĺ�Լ��������ʱ�Ĵ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴ζ��ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ÿ�����ĵĺ�Լ����Ӧһ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			virtual void OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) ;

			///�˶�����Ӧ��
			///@param ticker ��ϸ�ĺ�Լȡ���������
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴�ȡ�����ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ÿ��ȡ�����ĵĺ�Լ����Ӧһ��ȡ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			virtual void OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) ;

			///�������֪ͨ��������һ��һ����
			///@param market_data ��������
			///@param bid1_qty ��һ��������
			///@param bid1_count ��һ���е���Чί�б���
			///@param max_bid1_count ��һ������ί�б���
			///@param ask1_qty ��һ��������
			///@param ask1_count ��һ���е���Чί�б���
			///@param max_ask1_count ��һ������ί�б���
			///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			virtual void OnDepthMarketData(XTPMD *market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count) ;

			///�������鶩����Ӧ��
			///@param ticker ��ϸ�ĺ�Լ�������
			///@param error_info ���ĺ�Լ��������ʱ�Ĵ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴ζ��ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ÿ�����ĵĺ�Լ����Ӧһ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			virtual void OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last) ;

			///�˶����鶩����Ӧ��
			///@param ticker ��ϸ�ĺ�Լȡ���������
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴�ȡ�����ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ÿ��ȡ�����ĵĺ�Լ����Ӧһ��ȡ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			virtual void OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last) ;

			///���鶩����֪ͨ
			///@param order_book ���鶩�������ݣ���Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			virtual void OnOrderBook(XTPOB *order_book) ;

			///�����������Ӧ��
			///@param ticker ��ϸ�ĺ�Լ�������
			///@param error_info ���ĺ�Լ��������ʱ�Ĵ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴ζ��ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ÿ�����ĵĺ�Լ����Ӧһ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			virtual void OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last) ;

			///�˶��������Ӧ��
			///@param ticker ��ϸ�ĺ�Լȡ���������
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴�ȡ�����ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			///@remark ÿ��ȡ�����ĵĺ�Լ����Ӧһ��ȡ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			virtual void OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last) ;

			///�������֪ͨ
			///@param tbt_data ����������ݣ��������ί�к���ʳɽ�����Ϊ���ýṹ�壬��Ҫ����type�����������ί�л�����ʳɽ�����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
			virtual void OnTickByTick(XTPTBT *tbt_data) ;

			///����ȫ�г�������Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			virtual void OnSubscribeAllMarketData(XTPRI *error_info) ;

			///�˶�ȫ�г�������Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			virtual void OnUnSubscribeAllMarketData(XTPRI *error_info) ;

			///����ȫ�г������鶩����Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			virtual void OnSubscribeAllOrderBook(XTPRI *error_info) ;

			///�˶�ȫ�г������鶩����Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			virtual void OnUnSubscribeAllOrderBook(XTPRI *error_info) ;

			///����ȫ�г����������Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			virtual void OnSubscribeAllTickByTick(XTPRI *error_info) ;

			///�˶�ȫ�г����������Ӧ��
			///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@remark ��Ҫ���ٷ���
			virtual void OnUnSubscribeAllTickByTick(XTPRI *error_info) ;


			///��ѯ�ɽ��׺�Լ��Ӧ��
			///@param ticker_info �ɽ��׺�Լ��Ϣ
			///@param error_info ��ѯ�ɽ��׺�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴β�ѯ�ɽ��׺�Լ�����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			virtual void OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last) ;

			///��ѯ��Լ�����¼۸���ϢӦ��
			///@param ticker_info ��Լ�����¼۸���Ϣ
			///@param error_info ��ѯ��Լ�����¼۸���Ϣʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
			///@param is_last �Ƿ�˴β�ѯ�����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
			virtual void OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI *error_info, bool is_last) ;
		
		};
	}
}