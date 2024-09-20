#include "Animation.h"
#include "utils.h"


Animation::Animation()
{
}

Animation::Animation(std::vector<sf::Texture> images, float img_dur, bool loop)
{
	//for (auto& img : images) {
	//	this->images.push_back(img);
	//}
	this->images = images;

	this->img_duration = img_dur;
	this->loop = loop;
	this->done = false;
	this->frame = 0;

	
}

Animation Animation::getAnimation() // returns a  copy
{
	return Animation(this->images, this->img_duration, this->loop);
}

sf::Texture* Animation::img()
{
	return &images[int(this->frame / this->img_duration)];
}

void Animation::update()
{

	if (this->loop) {
		this->frame = (frame + 1) % int(img_duration * images.size()); // -1 not needed here due to modulus looping the frame
	}
	else {
		this->frame = std::min(this->frame + 1, int(img_duration * images.size() - 1)); // -1 because 1st index is 0
		if (this->frame >= int(img_duration * images.size() - 1))   this->done = true;
	}

}
