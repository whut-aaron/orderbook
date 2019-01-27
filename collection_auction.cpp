#include "pch.h"
#include "collection_auction.h"
#include<list>
#include<set>
#include<cmath>
collection_auction::collection_auction()
{
}


collection_auction::~collection_auction()
{
}
uint32_t collection_auction::get_auction_price(uint32_t last_close_price,orderbook &order_book)
{
	uint32_t max_volume = 0;
	uint32_t auction_price = 0;

	auto buy_bolume_map = order_book.get_buy_volume();
	auto sell_bolume_map = order_book.get_sell_volume();

	const auto &buy_orders = order_book.get_buy_orders();
	const auto &sell_orders = order_book.get_sell_orders();

	std::set<uint32_t> price_set;
	for (auto it = buy_orders.begin(); it != buy_orders.end(); ++it)
	{
		price_set.insert(it->first);
	}

	for (auto it = sell_orders.begin(); it != sell_orders.end(); ++it)
	{
		price_set.insert(it->first);
	}

	std::list<uint32_t> price_list;
	for (auto price : price_set)
	{
		auto volume = buy_bolume_map[price] < sell_bolume_map[price] ? buy_bolume_map[price] : sell_bolume_map[price];

		if (volume > max_volume)
		{
			max_volume = volume;
			price_list.clear();
			price_list.push_back(price);
		}
		else if(volume == max_volume)
		{
			price_list.push_back(price);
		}
	}

	if (price_list.size() == 1)
	{
		return *price_list.begin();
	}

	if (price_list.size() > 1)
	{
	
		uint32_t auction_price = 0;
		uint32_t dif = UINT32_MAX; 
		for (auto price : price_list)
		{
			if (price - last_close_price < dif)
			{
				dif = std::abs((int32_t)(price - last_close_price));
				auction_price = price;
			}
		}
	}
	
	return auction_price;
}

uint32_t collection_auction::get_auction_volume_from_orders(uint32_t price,const std::map < uint32_t, uint32_t> &orders,bool is_buy)
{
	uint32_t volume = 0;
	for (auto it = orders.begin(); it != orders.end(); ++it)
	{
		if (is_buy && it->first >= price)
		{
			volume += it->second;
		}else if (!is_buy && it->first <= price)
		{
			volume += it->first;
		}
	}

	return volume;
}
