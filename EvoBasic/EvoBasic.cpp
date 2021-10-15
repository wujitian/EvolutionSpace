// EvoBasic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

typedef enum
{
    AGENT_ACTION_ROCK = 0,
    AGENT_ACTION_PAPER = 1,
    AGENT_ACTION_SCISSOR = 2,
    AGENT_ACTION_MAX
}AGENT_ACTION_TYPE;

class Agent
{
public:
    uint32_t Action();
    uint32_t GetHealth();

private:
    uint32_t health = 10;
};

uint32_t Agent::Action()
{
    return 0;
}

uint32_t Agent::GetHealth()
{
    return this->health;
}

bool Encounter(Agent* pAgent0, Agent* pAgent1)
{
    if (!pAgent0 || !pAgent1)
    {
        cout << "[Error] agent can not null" << endl;
    }

    uint32_t act0 = pAgent0->Action();
    uint32_t act1 = pAgent1->Action();

    if (act0 < AGENT_ACTION_MAX && act1 < AGENT_ACTION_MAX)
    {
        printf("[Error] agent action error.");
        return false;
    }

    if (act0 == AGENT_ACTION_ROCK)
    {
    }
    else if (act0 == AGENT_ACTION_PAPER)
    {
    }
    else
    {
    }
}

int main()
{
    Agent groups[2];

    for (uint32_t i = 0; i < 2; i++)
    {
        std::cout << "Agent " << i << ": " << groups[i].GetHealth() << std::endl;
    }
}