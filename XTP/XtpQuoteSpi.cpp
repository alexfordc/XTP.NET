#include<vcclr.h>
#include"Stdafx.h"
#include"utils.h"
#include"XtpQuoteSpi.h"

namespace XTP
{
	namespace API {
		XtpQuoteSpi::XtpQuoteSpi(XtpQuoteAdapter^ pAdapter)
		{
			m_pAdapter = pAdapter;
		}
		void XtpQuoteSpi::OnError(XTPRI *error_info) {
			m_pAdapter->OnErrorEvent(RspInfoConverter(error_info));
		}
		void XtpQuoteSpi::OnDisconnected(int reason) {
			m_pAdapter->OnDisconnectedEvent(reason);
		}
		void XtpQuoteSpi::OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) {
			SpecificTickerStruct^ ticketInfo =MNConv<SpecificTickerStruct^, XTPST>::N2M(ticker);
			m_pAdapter->OnSubMarketDataEvent(RspInfoConverter(error_info), ticketInfo, is_last);
		}
		void XtpQuoteSpi::OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) {

			SpecificTickerStruct^ ticketInfo = MNConv<SpecificTickerStruct^, XTPST>::N2M(ticker);//  gcnew SpecificTickerStruct();
			m_pAdapter->OnUnSubMarketDataEvent(RspInfoConverter(error_info), ticketInfo, is_last);
		}

		///�������֪ͨ��������һ��һ����
		///@param market_data ��������
		///@param bid1_qty ��һ��������
		///@param bid1_count ��һ���е���Чί�б���
		///@param max_bid1_count ��һ������ί�б���
		///@param ask1_qty ��һ��������
		///@param ask1_count ��һ���е���Чί�б���
		///@param max_ask1_count ��һ������ί�б���
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpQuoteSpi::OnDepthMarketData(XTPMD *market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count)
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
			
			m_pAdapter->OnDepthMarketDataEvent(data, nullptr, 0, 0, nullptr, 0, 0);
			delete data;
		}
		
		void XtpQuoteSpi::OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last) {
			QuoteStaticInfoStruct^ data = gcnew QuoteStaticInfoStruct();
			RspInfoStruct^ resInfo = gcnew RspInfoStruct();
			if (error_info == nullptr || error_info->error_id == 0) {
				resInfo->error_id = 0;
				resInfo->error_msg = "";
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
			}
			else {
				resInfo->error_id = error_info->error_id;
				resInfo->error_msg = gcnew String(error_info->error_msg);
			}
			m_pAdapter->OnQueryAllTickersEvent(resInfo, data, is_last);
			
			delete data;
		}
				
		///�������鶩����Ӧ��
		///@param ticker ��ϸ�ĺ�Լ�������
		///@param error_info ���ĺ�Լ��������ʱ�Ĵ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param is_last �Ƿ�˴ζ��ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ÿ�����ĵĺ�Լ����Ӧһ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpQuoteSpi::OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
		{}

		///�˶����鶩����Ӧ��
		///@param ticker ��ϸ�ĺ�Լȡ���������
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param is_last �Ƿ�˴�ȡ�����ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ÿ��ȡ�����ĵĺ�Լ����Ӧһ��ȡ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpQuoteSpi::OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
		{}

		///���鶩����֪ͨ
		///@param order_book ���鶩�������ݣ���Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpQuoteSpi::OnOrderBook(XTPOB *order_book)
		{}

		///�����������Ӧ��
		///@param ticker ��ϸ�ĺ�Լ�������
		///@param error_info ���ĺ�Լ��������ʱ�Ĵ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param is_last �Ƿ�˴ζ��ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ÿ�����ĵĺ�Լ����Ӧһ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpQuoteSpi::OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
		{}

		///�˶��������Ӧ��
		///@param ticker ��ϸ�ĺ�Լȡ���������
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param is_last �Ƿ�˴�ȡ�����ĵ����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ÿ��ȡ�����ĵĺ�Լ����Ӧһ��ȡ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpQuoteSpi::OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
		{}

		///�������֪ͨ
		///@param tbt_data ����������ݣ��������ί�к���ʳɽ�����Ϊ���ýṹ�壬��Ҫ����type�����������ί�л�����ʳɽ�����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpQuoteSpi::OnTickByTick(XTPTBT *tbt_data)
		{}

		///����ȫ�г�������Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		void XtpQuoteSpi::OnSubscribeAllMarketData(XTPRI *error_info)
		{}

		///�˶�ȫ�г�������Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		void XtpQuoteSpi::OnUnSubscribeAllMarketData(XTPRI *error_info)
		{}

		///����ȫ�г������鶩����Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		void XtpQuoteSpi::OnSubscribeAllOrderBook(XTPRI *error_info)
		{}

		///�˶�ȫ�г������鶩����Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		void XtpQuoteSpi::OnUnSubscribeAllOrderBook(XTPRI *error_info)
		{}

		///����ȫ�г����������Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		void XtpQuoteSpi::OnSubscribeAllTickByTick(XTPRI *error_info)
		{}

		///�˶�ȫ�г����������Ӧ��
		///@param error_info ȡ�����ĺ�Լʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ��Ҫ���ٷ���
		void XtpQuoteSpi::OnUnSubscribeAllTickByTick(XTPRI *error_info)
		{
			
		}
		
		///��ѯ��Լ�����¼۸���ϢӦ��
		///@param ticker_info ��Լ�����¼۸���Ϣ
		///@param error_info ��ѯ��Լ�����¼۸���Ϣʱ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param is_last �Ƿ�˴β�ѯ�����һ��Ӧ�𣬵�Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		void XtpQuoteSpi::OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI *error_info, bool is_last)
		{}
	}
}