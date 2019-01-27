#include "pch.h"
#include <iostream>
#include "orderbook.h"
#include "collection_auction.h"
#include<time.h>

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ������ʾ: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�


int main()
{
	std::cout << "Hello World!\n";
	srand(time(NULL));
	orderbook order_book;
	for (auto i = 0; i < 100; i++)
		order_book.add_order((rand() % 100) + 1, rand() % 100, true);
	for (auto i = 0; i < 100; i++)
		order_book.add_order((rand() % 100) +1, rand() % 100, false);


	const auto &buy_orders = order_book.get_buy_orders();
	const auto &sell_orders = order_book.get_sell_orders();

	collection_auction auction;
	auto auction_price = auction.get_auction_price(0,order_book);
	for (auto it = sell_orders.begin(); it != sell_orders.end(); ++it)
	{
		if (it->first <= auction_price)
		{
			continue;
		}

		std::cout << it->first << " " << it->second << std::endl;
	}

	std::cout << "auction " << auction_price << std::endl;

	for (auto it = buy_orders.rbegin(); it != buy_orders.rend(); ++it)
	{
		if (it->first >= auction_price)
		{
			continue;
		}

		std::cout << it->first << " " << it->second << std::endl;
	}

	getchar();
}