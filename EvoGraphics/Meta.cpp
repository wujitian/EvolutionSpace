#include "Meta.h"

Meta::Meta(void)
{
	dprintf_i("[Meta] Meta crate.");
}

Meta::~Meta()
{
    dprintf_i("[Meta] Meta destroy.");
}

void Meta::start(void)
{
	dprintf_i("[Meta] Meta start() get in.");
}

void Meta::render(void)
{
	dprintf_i("[Meta] Meta render() get in.");
}

void Meta::shutdown(void)
{
	dprintf_i("[Meta] Meta shutdown() get in.");
}

void Meta::SetMetaTime(double passedTime)
{
	//dprintf_i("[Meta] Set time: %lf", passedTime);
	m_metaPassedTime = passedTime;
}