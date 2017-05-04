// XTPDll.h
#pragma once
#include "basicDll.h"

using namespace System;

namespace XTP {
	namespace API {

		/// <summary>
		/// XTP_EXCHANGE_TYPE �ǽ���������
		/// </summary>
		public enum class EXCHANGE_TYPE
		{
			XTP_EXCHANGE_SH = 1,	///<��֤
			XTP_EXCHANGE_SZ,		///<��֤
			XTP_EXCHANGE_MAX	///<�����ڵĽ���������
		};

		///����
		public ref struct MarketDataStruct
		{
			// ����
			///����������
			int exchange_id;
			///��Լ���루��������������Ϣ��
			String^	ticker;

			// ��Ʊ�ȼ۸�
			///���¼�
			double	last_price;
			///������
			double	pre_close_price;
			///����
			double	open_price;
			///��߼�
			double	high_price;
			///��ͼ�
			double	low_price;
			///������
			double	close_price;

			// �ڻ�������
			///��ֲ�����Ŀǰδ��д��
			double	pre_open_interest;
			///�ֲ�����Ŀǰδ��д��
			double	open_interest;
			///�ϴν���ۣ�Ŀǰδ��д��
			double	pre_settlement_price;
			///���ν���ۣ�Ŀǰδ��д��
			double	settlement_price;

			///��ͣ��ۣ�Ŀǰδ��д��
			double	upper_limit_price;
			///��ͣ��ۣ�Ŀǰδ��д��
			double	lower_limit_price;
			///����ʵ�ȣ�Ŀǰδ��д��
			double	pre_delta;
			///����ʵ�ȣ�Ŀǰδ��д��
			double	curr_delta;

			/// ʱ����
			Int64 data_time;

			// ��������
			///����
			Int64	qty;
			///�ɽ����
			double	turnover;
			///���վ���
			double	avg_price;

			// ������
			///ʮ�������
			array<double>^ bid;
			///ʮ��������
			array<double>^	ask;
			///ʮ��������
			array<Int64>^	bid_qty;
			///ʮ��������
			array<Int64>^	ask_qty;

			// ltsû�а��������ݣ�Ŀǰδ��д��
			///�ɽ�����
			Int64 trades_count;
			///��ǰ����״̬˵��
			String^ ticker_status;
			///ί����������
			Int64 total_bid_qty;
			///ί����������
			Int64 total_ask_qty;
			///��Ȩƽ��ί��۸�
			double ma_bid_price;
			///��Ȩƽ��ί���۸�
			double ma_ask_price;
			///ծȯ��Ȩƽ��ί��۸�
			double ma_bond_bid_price;
			///ծȯ��Ȩƽ��ί���۸�
			double ma_bond_ask_price;
			///ծȯ����������
			double yield_to_maturity;
			///ETF��ֵ��ֵ
			double iopv;
			///ETF�깺����
			Int32 etf_buy_count;
			///ETF��ر���
			Int32 etf_sell_count;
			///ETF�깺����
			double etf_buy_qty;
			///ETF�깺���
			double etf_buy_money;
			///ETF�������
			double etf_sell_qty;
			///ETF��ؽ��
			double etf_sell_money;
			///Ȩִ֤�е�������
			double total_warrant_exec_qty;
			///Ȩ֤��ͣ�۸�Ԫ��
			double warrant_lower_price;
			///Ȩ֤��ͣ�۸�Ԫ��
			double warrant_upper_price;
			///���볷������
			Int32 cancel_buy_count;
			///������������
			Int32 cancel_sell_count;
			///���볷������
			double cancel_buy_qty;
			///������������
			double cancel_sell_qty;
			///���볷�����
			double cancel_buy_money;
			///�����������
			double cancel_sell_money;
			///�����ܱ���
			Int64 total_buy_count;
			///�����ܱ���
			Int64 total_sell_count;
			///����ί�гɽ����ȴ�ʱ��
			Int32 duration_after_buy;
			///����ί�гɽ����ȴ�ʱ��
			Int32 duration_after_sell;
			///��ί�м�λ��
			Int32 num_bid_orders;
			///����ί�м�λ��
			Int32 num_ask_orders;
			///�ɽ�ʱ�䣨UA3113��
			Int32 exec_time;
			///���б�־��UA103/UA104��
			String^ is_market_closed;
			///��Լ�ֲ�����UA103��
			double total_position;
			///��ӯ��1��UA103��
			double pe_ratio1;
			///��ӯ��2��UA103��
			double pe_ratio2;
		} ;

		public ref struct QuoteStaticInfoStruct {
			///����������
			int exchange_id;
			///��Լ���루��������������Ϣ���������ո���'\0'��β
			String^ ticker;
			/// ��Լ����
			String^ ticker_name;
			/// ��Լ����
			int ticker_type;
			///������
			double  pre_close_price;
			///��ͣ���
			double  upper_limit_price;
			///��ͣ���
			double  lower_limit_price;
			///��С�䶯��λ
			double  price_tick;
			/// ��Լ��С������(��)
			Int32  buy_qty_unit;
			/// ��Լ��С������(��)
			Int32 sell_qty_unit;
		};
	}
}