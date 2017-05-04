#pragma once
///���õĽṹ
using namespace System;

namespace XTP {
	namespace API {

		/// <summary>
		/// XTP_PROTOCOL_TYPE ��һ��ͨѶ����Э�鷽ʽ
		/// </summary>
		public enum class PROTOCOL_TYPE
		{
			XTP_PROTOCOL_TCP = 1,	///<����TCP��ʽ����
			XTP_PROTOCOL_UDP		///<����UDP��ʽ����
		};

		public ref struct RspInfoStruct
		{
			///�������
			int	error_id;
			///������Ϣ
			String^	error_msg;
		};

		///ָ���ĺ�Լ
		public ref struct SpecificTickerStruct
		{
			///����������
			int exchange_id;
			///��Լ���루��������������Ϣ������"600000  "
			String^	ticker;
		};


	}
}