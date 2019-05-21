#include<vcclr.h>
#include"Stdafx.h"
#include"utils.h"
#include"XtpTraderSpi.h"
#include"XtpTraderAdapter.h"
//#include"Delegates.h"

namespace XTP
{
	namespace API
	{
		XtpTraderSpi::XtpTraderSpi(XtpTraderAdapter^ pAdapter)
		{
			m_pAdapter = pAdapter;
		}
		///���ͻ��˵�ĳ�������뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á�
		///@param reason ����ԭ��������������Ӧ
		///@param session_id �ʽ��˻���Ӧ��session_id����¼ʱ�õ�
		///@remark �û���������logout���µĶ��ߣ����ᴥ���˺�����api�����Զ������������߷���ʱ�����û�����ѡ����������������ڴ˺����е���Login���µ�¼��������session_id����ʱ�û��յ������ݸ�����֮ǰ��������
		void XtpTraderSpi::OnDisconnected(uint64_t session_id, int reason)
		{
			m_pAdapter->OnDisconnectedEvent(session_id, reason);
		}

		///����Ӧ��
		///@param error_info ����������Ӧ��������ʱ�ľ���Ĵ������ʹ�����Ϣ,��error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark �˺���ֻ���ڷ�������������ʱ�Ż���ã�һ�������û�����
		void XtpTraderSpi::OnError(XTPRI *error_info)
		{
			m_pAdapter->OnErrorEvent(RspInfoConverter(error_info));
		}

		///����֪ͨ
		///@param order_info ������Ӧ������Ϣ���û�����ͨ��order_info.order_xtp_id����������ͨ��GetClientIDByXTPID() == client_id�������Լ��Ķ�����order_info.qty_left�ֶ��ڶ���Ϊδ�ɽ������ɡ�ȫ�ɡ��ϵ�״̬ʱ����ʾ�˶�����û�гɽ����������ڲ�����ȫ��״̬ʱ����ʾ�˶���������������order_info.order_cancel_xtp_idΪ������Ӧ�ĳ���ID����Ϊ0ʱ��ʾ�˵������ɹ�
		///@param error_info �������ܾ����߷�������ʱ�������ʹ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ÿ�ζ���״̬����ʱ�����ᱻ���ã���Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ�����ߣ��ڶ���δ�ɽ���ȫ���ɽ���ȫ�����������ֳ������Ѿܾ���Щ״̬ʱ������Ӧ�����ڲ��ֳɽ�����������ɶ����ĳɽ��ر�������ȷ�ϡ����е�¼�˴��û��Ŀͻ��˶����յ����û��Ķ�����Ӧ
		void XtpTraderSpi::OnOrderEvent(XTPOrderInfo *order_info, XTPRI *error_info, uint64_t session_id)
		{
			OrderInfoStruct^ order = MNConv<OrderInfoStruct^,XTPOrderInfo>::N2M( order_info);
			m_pAdapter->OnOrderEvent(RspInfoConverter(error_info), order, session_id);
		}

		///�ɽ�֪ͨ
		///@param trade_info �ɽ��ر��ľ�����Ϣ���û�����ͨ��trade_info.order_xtp_id����������ͨ��GetClientIDByXTPID() == client_id�������Լ��Ķ����������Ͻ�����exec_id����Ψһ��ʶһ�ʳɽ���������2�ʳɽ��ر�ӵ����ͬ��exec_id���������Ϊ�˱ʽ����Գɽ��ˡ����������exec_id��Ψһ�ģ���ʱ�޴��жϻ��ơ�report_index+market�ֶο������Ψһ��ʶ��ʾ�ɽ��ر���
		///@remark �����гɽ�������ʱ�򣬻ᱻ���ã���Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ�����ߡ����е�¼�˴��û��Ŀͻ��˶����յ����û��ĳɽ��ر�����ض���Ϊ����״̬����Ҫ�û�ͨ���ɽ��ر��ĳɽ�������ȷ����OnOrderEvent()�������Ͳ���״̬��
		void XtpTraderSpi::OnTradeEvent(XTPTradeReport *trade_info, uint64_t session_id)
		{
			TradeReportStruct^ report = MNConv<TradeReportStruct^, XTPTradeReport>::N2M(trade_info);
			m_pAdapter->OnTradeEvent(report,session_id);
		}

		///����������Ӧ
		///@param cancel_info ����������Ϣ������������order_cancel_xtp_id�ʹ�������order_xtp_id
		///@param error_info �������ܾ����߷�������ʱ�������ʹ�����Ϣ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ�����ߣ���error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ����Ӧֻ���ڳ�����������ʱ���ص�
		void XtpTraderSpi::OnCancelOrderError(XTPOrderCancelInfo *cancel_info, XTPRI *error_info, uint64_t session_id){}

		///�����ѯ������Ӧ
		///@param order_info ��ѯ����һ������
		///@param error_info ��ѯ����ʱ��������ʱ�����صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ����֧�ַ�ʱ�β�ѯ��һ����ѯ������ܶ�Ӧ�����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpTraderSpi::OnQueryOrder(XTPQueryOrderRsp *order_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
		{
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

			m_pAdapter->OnQueryOrderEvent(RspInfoConverter(error_info), order, request_id, is_last, session_id);
		}

		///�����ѯ�ɽ���Ӧ
		///@param trade_info ��ѯ����һ���ɽ��ر�
		///@param error_info ��ѯ�ɽ��ر���������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ����֧�ַ�ʱ�β�ѯ��һ����ѯ������ܶ�Ӧ�����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpTraderSpi::OnQueryTrade(XTPQueryTradeRsp *trade_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
		{
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

			m_pAdapter->OnQueryTradeEvent(RspInfoConverter(error_info), report, request_id, is_last, session_id);
		}

		///�����ѯͶ���ֲ߳���Ӧ
		///@param position ��ѯ����һֻ��Ʊ�ĳֲ����
		///@param error_info ��ѯ�˻��ֲַ�������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark �����û����ܳ��ж����Ʊ��һ����ѯ������ܶ�Ӧ�����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpTraderSpi::OnQueryPosition(XTPQueryStkPositionRsp *position, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id){}

		///�����ѯ�ʽ��˻���Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param asset ��ѯ�����ʽ��˻����
		///@param error_info ��ѯ�ʽ��˻���������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpTraderSpi::OnQueryAsset(XTPQueryAssetRsp *asset, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id){}

		///�����ѯ�ּ�������Ϣ��Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param fund_info ��ѯ���ķּ��������
		///@param error_info ��ѯ�ּ�����������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpTraderSpi::OnQueryStructuredFund(XTPStructuredFundInfo *fund_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id){}

		///�����ѯ�ʽ𻮲�������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param fund_transfer_info ��ѯ�����ʽ��˻����
		///@param error_info ��ѯ�ʽ��˻���������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpTraderSpi::OnQueryFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id){}

		///�ʽ𻮲�֪ͨ
		///@param fund_transfer_info �ʽ𻮲�֪ͨ�ľ�����Ϣ���û�����ͨ��fund_transfer_info.serial_id����������ͨ��GetClientIDByXTPID() == client_id�������Լ��Ķ�����
		///@param error_info �ʽ𻮲��������ܾ����߷�������ʱ�������ʹ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@remark ���ʽ𻮲�������״̬�仯��ʱ�򣬻ᱻ���ã���Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ�����ߡ����е�¼�˴��û��Ŀͻ��˶����յ����û����ʽ𻮲�֪ͨ��
		void XtpTraderSpi::OnFundTransfer(XTPFundTransferNotice *fund_transfer_info, XTPRI *error_info, uint64_t session_id){}

		///�����ѯETF�嵥�ļ�����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param etf_info ��ѯ����ETF�嵥�ļ����
		///@param error_info ��ѯETF�嵥�ļ���������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpTraderSpi::OnQueryETF(XTPQueryETFBaseRsp *etf_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id){}

		///�����ѯETF��Ʊ������Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param etf_component_info ��ѯ����ETF��Լ����سɷֹ���Ϣ
		///@param error_info ��ѯETF��Ʊ����������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpTraderSpi::OnQueryETFBasket(XTPQueryETFComponentRsp *etf_component_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id){}

		///�����ѯ�����¹��깺��Ϣ�б����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param ipo_info ��ѯ���Ľ����¹��깺��һֻ��Ʊ��Ϣ
		///@param error_info ��ѯ�����¹��깺��Ϣ�б�������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpTraderSpi::OnQueryIPOInfoList(XTPQueryIPOTickerRsp *ipo_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id){}

		///�����ѯ�û��¹��깺�����Ϣ����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param quota_info ��ѯ�����û�ĳ���г��Ľ����¹��깺�����Ϣ
		///@param error_info ���ѯ�û��¹��깺�����Ϣ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpTraderSpi::OnQueryIPOQuotaInfo(XTPQueryIPOQuotaRsp *quota_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id){}

		///�����ѯ��Ȩ��Լ����Ӧ����Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		///@param option_info ��ѯ������Ȩ��Լ���
		///@param error_info ��ѯ��Ȩ��Լ��������ʱ���صĴ�����Ϣ����error_infoΪ�գ�����error_info.error_idΪ0ʱ������û�д���
		///@param request_id ����Ϣ��Ӧ������Ӧ������ID
		///@param is_last ����Ϣ��Ӧ�����Ƿ�Ϊrequest_id������������Ӧ�����һ����Ӧ����Ϊ���һ����ʱ��Ϊtrue�����Ϊfalse����ʾ��������������Ϣ��Ӧ
		///@param session_id �ʽ��˻���Ӧ��session_id����¼ʱ�õ�
		///@remark ��Ҫ���ٷ��أ���������������Ϣ������������ʱ���ᴥ������
		void XtpTraderSpi::OnQueryOptionAuctionInfo(XTPQueryOptionAuctionInfoRsp *option_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id)
		{
		}

	}
}