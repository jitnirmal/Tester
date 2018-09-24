#pragma once
#include <memory>
#include <map>
#include <functional>

class Product {
};
class Stock : public Product {};
class Derivative: public Product {};
class Option : public Derivative {};
class Future : public Derivative {};

struct IProductFactory
{
	virtual std::shared_ptr<Product> Create(std::type_info const & type)= 0;
};

using ProductMapType = std::map< std::type_info const *, std::function<std::shared_ptr<Product>()>>;

struct ProductFactory : public IProductFactory
{
	virtual	std::shared_ptr<Product> Create(std::type_info const & type) override
	{
		auto it = _ProductMap.find(&type);
		if (it != _ProductMap.end())
			return it->second();
		return nullptr;
	}
private:
	static ProductMapType _ProductMap;
};

ProductMapType ProductFactory::_ProductMap
{
	{ &typeid(Stock),[]() {return std::make_shared<Stock>(); } },
	{ &typeid(Option), []() {return std::make_shared<Option>(); } },
	{ &typeid(Future), []() {return std::make_shared<Future>(); } }
};