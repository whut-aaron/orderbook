// orderbook.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include "orderbook.h"
#include<unordered_map>
#include<unordered_set>


orderbook::orderbook()
{
}


orderbook::~orderbook()
{
}

void orderbook::add_order(uint32_t price, uint32_t volume ,bool is_buy)
{
	is_buy ? buy_orders_[price] += volume : sell_orders_[price] += volume;
}
std::unordered_map<uint32_t, uint32_t> orderbook::get_buy_volume()
{
	std::unordered_map<uint32_t, uint32_t> buy_auction_volume;
	uint32_t last_total_volume = 0;
	for (auto it = buy_orders_.begin(); it != buy_orders_.end(); ++it)
	{
		buy_auction_volume[it->first] = it->second + last_total_volume;
		last_total_volume += it->second;
	}

	return std::move(buy_auction_volume);
}

std::unordered_map<uint32_t, uint32_t> orderbook::get_sell_volume()
{
	std::map<uint32_t, uint32_t> sell_auction_volume;
	std::map<uint32_t, uint32_t>::iterator last_it = sell_orders_.end();
	uint32_t last_total_volume = 0;
	for (auto it = sell_orders_.begin(); it != sell_orders_.end(); ++it)
	{
		sell_auction_volume[it->first] = it->second + last_total_volume;
		last_total_volume += it->second;
	}

	return std::move(sell_auction_volume);

}
