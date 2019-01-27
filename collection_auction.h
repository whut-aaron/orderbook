#pragma once
#include<map>
#include "orderbook.h"
class collection_auction
{
public:
	collection_auction();
	~collection_auction();
public:
	uint32_t get_auction_price(uint32_t last_price,orderbook &order_book);
	uint32_t get_auction_volume_from_orders(uint32_t price,const std::map < uint32_t, uint32_t> &orders,bool is_buy);
};

