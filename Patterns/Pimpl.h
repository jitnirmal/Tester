#include <string>
#include <iostream>
#include <memory>
#include <functional>

class control_pimpl;

class control
{
	std::unique_ptr<control_pimpl> pimpl;
public:
	control() :
		pimpl(std::make_unique<control_pimpl>()){}

	void set_text(std::string text) {
		pimpl->set_text(text);
	}
	void resize(int const w, int const h) {
		pimpl->resize(w, h);
	}
	void show() {
		pimpl->show();
	}
	void hide() {
		pimpl->hide();
	}
};



class control_pimpl
{
	std::string text;
	int width = 0;
	int height = 0;
	bool visible = true;
	void draw()
	{
		std::cout
			<< "control " << std::endl
			<< " visible: " << std::boolalpha << visible
			<< std::noboolalpha << std::endl
			<< " size: " << width << ", " << height << std::endl
			<< " text: " << text << std::endl;
	}
public:
	void set_text(std::string t)
	{
		text = t.data();
		draw();
	}
	void resize(int const w, int const h)
	{
		width = w;
		height = h;
		draw();
	}
	void show()
	{
		visible = true;
		draw();
	}
	void hide()
	{
		visible = false;
		draw();
	}
};

