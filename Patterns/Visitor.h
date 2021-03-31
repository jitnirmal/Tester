#pragma once
#include <vector>


/// <summary>
/// This pattern is useful when public APIs need to support plug-in operations. 
/// Clients can then perform their intended operations on a class (with the visiting class) without modifying the source.
/// </summary>
class IVisitable;

class IVisitor
{
public:
	IVisitor();
	virtual ~IVisitor();

	virtual void 
	
	
	(IVisitable&) = 0;

};

class IVisitable
{
public:
	IVisitable();
	virtual ~IVisitable();

	void accept(IVisitor& visitor)
	{
		visitor.visit(*this);
	}
};



class OrderMsg : public IVisitable
{
public:
	char MsgType;
	
};


class RVDeserializer : IVisitor
{
	void publishToGUI()
	{
		OrderMsg msg;
		msg.accept(*this);
	}

	virtual void visit(IVisitable& visitable)
	{
		OrderMsg& msg = static_cast<OrderMsg&>(visitable);
		switch (msg.MsgType)
		{
		case 'A':
			// deserializeOrderCreateMsg(static_cast<OrderCreateMsg&>(msg));
			break;
		case 'B':
			//deserializeOrderAmendMsg(static_cast<OrderAmendMsg&>(msg));
			break;
		case 'C':
			//deserializeOrderCancelMsg(static_cast<OrderCancelMsg&>(msg));
			break;
		}
	}
};


#pragma once
#include <iostream>
#include <memory>
#include <cassert>
#include <chrono>

namespace assignment {
	namespace ctvs {

		static constexpr double PI = 3.14;

		/// <summary>
		/// CompileTime Visitor
		/// As opposed to classic Visitor pattern, using double dispatch at run-time—this
		///  implementation uses compile time C++ language feature to provide the facility 
		/// making it much faster at run time and does not have cyclic dependencies issue.
		/// </summary>
		class Shape {
		public:
			Shape() = default;
			virtual ~Shape() = default;
			explicit Shape(const std::string& name) noexcept : _name(name) {}
			inline const std::string& name() const noexcept { return _name; }

			/// <summary>
			/// template accept function required in base class.
			/// </summary>
			template <typename Visitable, typename Visitor>
			static void accept(Visitable& p, Visitor& v) noexcept
			{
				v.visit(p);
			}
		private:
			std::string _name;
		};

		class Circle : public Shape {
		public:
			explicit Circle(double radius) noexcept : _radius(radius) {}
			double GetRadius() const noexcept { return _radius; }
		private:
			double _radius{ 0.0 };
		};

		class Triangle : public Shape {
		public:
			Triangle() = default;
			Triangle(double base, double height) noexcept : _base(base), _height(height) {}
			inline double GetBase() const noexcept { return _base; }
			inline double GetHeight() const noexcept { return _height; }
		private:
			double _base{ 0.0 };
			double _height{ 0.0 };
		};

		class Rectangle : public Shape {
		public:
			Rectangle() = default;
			Rectangle(double length, double breadth) noexcept : _length(length), _breadth(breadth) {}
			inline double GetLength() const noexcept { return _length; }
			inline double GetBreadth() const noexcept { return _breadth; }
		private:
			double _length{ 0.0 };
			double _breadth{ 0.0 };
		};

		class AreaVisitor {
		public:
			void visit(Circle& c) {
				_circleArea = PI * c.GetRadius();
			}
			void visit(Triangle& t) {
				_triangleArea = t.GetBase() * t.GetHeight() * 0.5;
			}
			void visit(Rectangle& r) {
				_rectangleArea = r.GetBreadth() * r.GetLength();
			}
			inline double GetCircleArea() const noexcept { return _circleArea; }
			inline double GetTriangleArea() const noexcept { return _triangleArea; }
			inline double GetRectangleArea() const noexcept { return _rectangleArea; }
		private:
			double _circleArea{ 0.0 };
			double _triangleArea{ 0.0 };
			double _rectangleArea{ 0.0 };
		};

		auto test_ctvs()
		{
			constexpr double radius{ 3.2 };
			Circle c(radius);

			constexpr double base{ 4.0 };
			constexpr double height{ 5.5 };
			Triangle t(base, height);

			constexpr double length{ 3.2 };
			constexpr double breadth{ 4.1 };
			Rectangle r(length, breadth);

			AreaVisitor av;

			constexpr int COUNT{ 10000 };
			auto start = std::chrono::steady_clock::now();
			for (int i = 0; i < COUNT; ++i) {
				Shape::accept(c, av);
				Shape::accept(t, av);
				Shape::accept(r, av);
			}
			auto end = std::chrono::steady_clock::now();
			return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / COUNT;
		}



	} // ctvs
} // assignment

int main()
{
	std::cout << assignment::ctvs::test_ctvs() << " : time";
}