// 5_Flyweight - 167
#include <iostream>
#include <string>
#include <map>
#include "helper.h"
class Image
{
	std::string image_url;
	Image(std::string url) : image_url(url)
	{
		std::cout << url << " Downloading..." << std::endl;
	}
public:
	
	void Draw() { std::cout << "Draw " << image_url << std::endl; }

	friend class ImageFactory; // ImageFactory 에서는 Image의 private member 접근가능
};

// Image 객체를 생성/관리 하는 클래스를 별도로 만들어본다.
class ImageFactory
{
	//싱글톤 코드를 만드는 매크로!
	MAKE_SINGLETON(ImageFactory)
	std::map<std::string, Image*> image_map;
public:
	Image* Create(std::string url)
	{
		Image* img = image_map[url];
		if (img == nullptr) {
			img = new Image(url);
			image_map[url] = img;
		}
		return img;
	}
};

int main()
{
	ImageFactory& factory = ImageFactory::getInstance();

	Image* img1 = factory.Create("www.naver.com/a.png");
	img1->Draw();

	Image* img2 = factory.Create("www.naver.com/a.png");
	img2->Draw();

}



