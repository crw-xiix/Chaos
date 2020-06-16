#pragma once

class Animation
{
private:

public:
	virtual ~Animation() = default;

	virtual void Start() = 0;
};

class AnimationArrow : public Animation
{
private:
public:
};