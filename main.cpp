#include "pch.h"
#include <iostream>
#include "orderbook.h"
#include "collection_auction.h"
#include<time.h>

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件


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