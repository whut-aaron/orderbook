#pragma once
#include<unordered_map>
#include<map>

class orderbook
{
public:
	orderbook();
	~orderbook();
public:
	void add_order(uint32_t price, uint32_t volume,bool is_buy);
	const std::map<uint32_t, uint32_t,std::less<uint32_t>> &get_buy_orders() { return buy_orders_; }
	const std::map<uint32_t, uint32_t,std::greater<uint32_t>> &get_sell_orders() { return sell_orders_; }

	std::unordered_map<uint32_t, uint32_t> get_buy_volume();
	std::unordered_map<uint32_t, uint32_t> get_sell_volume();
private:
	std::map<uint32_t, uint32_t,std::less<uint32_t> > buy_orders_;
	std::map<uint32_t, uint32_t,std::greater<uint32_t> > sell_orders_;
};

