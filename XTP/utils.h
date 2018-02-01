#pragma once
#include"..\sdk\include\xtp_api_struct.h"
#include"XTP.h"
#include"xtpstruct.h"
#include<string>
#include<memory>
#include<stdlib.h>

using namespace System::Runtime::InteropServices;
namespace XTP {

	namespace API
	{
		/// ���й���,�Զ��ͷ��ַ���ָ���ڴ�
		class  CAutoStrPtr
		{
		public:
			char* m_pChar;
		public:

			CAutoStrPtr(String^ str)
			{
				if (str != nullptr)
				{
					m_pChar = (char*)Marshal::StringToHGlobalAnsi(str).ToPointer();
				}
				else
				{
					m_pChar = nullptr;
				}
			};
			~CAutoStrPtr()
			{
				if (m_pChar != nullptr)
				{
					Marshal::FreeHGlobal(IntPtr(m_pChar));
				}
			};

		};

		///�й���-���й����Զ�ת��
		template<typename M, typename N>
		class  MNConv
		{
		public:
			///Native to Managed
			static M N2M(N* pNative)
			{
				return safe_cast<M>(Marshal::PtrToStructure(IntPtr(pNative), M::typeid));
			};
			////Managed to Native 
			static void M2N(M managed, N* pNative)
			{
				Marshal::StructureToPtr(managed, IntPtr(pNative), true);
			};
			MNConv() {};
			~MNConv() {};
		};

		inline RspInfoStruct^  RspInfoConverter(XTPRspInfoStruct* pRspInfo)
		{
			return safe_cast<RspInfoStruct^>(Marshal::PtrToStructure(IntPtr(pRspInfo), RspInfoStruct::typeid));
		}
	}
}