#include "Animation.h"
#include "utils.h"
#include <numbers>

// global variables
const int sparkArraySize = 100;
Spark sparkArray[sparkArraySize];
int sparkArrayIter = 0;



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


// <------------------------------------independant functions for animations and effects------------------------------------>



bool InitializeSparks()
{
	int tempsize = sizeof(sparkArray) / sizeof(sparkArray[0]);
	for (int i = 0; i < tempsize; i++) {
		Spark spark1;
		sparkArray[i] = spark1;
	}

	return false;
}

Spark* getSparksArray()
{
	return sparkArray;
}

int getSparkArraySize()
{
	return sparkArraySize;
}

bool iterateSparksArray(int numOfSparks, sf::Vector2f pos, float angle, float speed)
{
	for (int i = 0; i < numOfSparks; i++) {
		sparkArrayIter++;
		sparkArrayIter %= sparkArraySize;
		//if (sparkArrayIter >= size)	sparkArrayIter = 0;
		sparkArray[sparkArrayIter].setActive(pos, angle, speed);

	}
	return false;
}

bool playerDeathAnimation(sf::Vector2f pos)
{

	for (int i = 0 , num = 0 ; i < sparkArraySize; i++) {
	//	//getSparksArray()[i];
		if (sparkArray[i].isActive == false) {
			num++;
			sparkArray[i].setActive(pos, randrangefloat(0, 1) * std::numbers::pi * 2, 5 + 3 * randrangefloat(0, 1) );
		}
		if (num >= 40)	break;
	}

	return false;
}

bool enemyDeathAnimation(sf::Vector2f pos)
{
	for (int i = 0, num = 0, num1 = 0; i < sparkArraySize; i++) {

		if (sparkArray[i].isActive == false) {
			num++;
			sparkArray[i].setActive(pos, randrangefloat(0, 1) * std::numbers::pi * 2, 4 + 3 * randrangefloat(0, 1));
		}
		if (num >= 10)	break;
	}

	for (int i = 0, num = 0, num1 = 0; i < sparkArraySize; i++) {
		if (sparkArray[i].isActive == false) {
			num1++;
			sparkArray[i].setActive(pos, std::numbers::pi, 10 + randrangefloat(0, 1)); // left
			sparkArray[i + 1].setActive(pos, 0, 10 + randrangefloat(0, 1)); // left

		}
		if (num1 >= 1) break;
	}

	return false;
}

bool bulletHitsTileAnimation(sf::Vector2f pos, bool flip)
{
	for (int i = 0, num = 0; i < sparkArraySize; i++) {
		if (sparkArray[i].isActive == false) {
			num++;
			//sparkArray[i].setActive(pos, randrangefloat(0, 1) * std::numbers::pi * 2, 3 + 3 * randrangefloat(0, 1)); // have to change this
			sparkArray[i].setActive(pos, randrangefloat(0, 1) - 0.5 + (flip > 0 ? 0 : std::numbers::pi), 3 + 2 * randrangefloat(0, 1));
		}
		if (num >= 3)	break;
	}
	return false;
}


