// EvoBasic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Agent.h"

using namespace std;

bool Encounter(Agent* pAgent0, Agent* pAgent1)
{
    if (!pAgent0 || !pAgent1)
    {
        cout << "[Error] gent can not null" << endl;
        return false;
    }

    if (pAgent0->GetStatus() != AGENT_STATUS_HEALTHY &&
        pAgent1->GetStatus() != AGENT_STATUS_HEALTHY)
    {
        return true;
    }

    EnumAgentActionType act0 = pAgent0->Action();
    EnumAgentActionType act1 = pAgent1->Action();

    if (act0 >= AGENT_ACTION_MAX && act1 >= AGENT_ACTION_MAX)
    {
        printf("[Error] Agent action error.");
        return false;
    }

    if (act0 == AGENT_ACTION_ROCK)
    {
        if (act1 == AGENT_ACTION_PAPER)
        {
            pAgent0->GetHurt();
        }
        else if (act1 == AGENT_ACTION_SCISSOR)
        {
            pAgent1->GetHurt();
        }
    }
    else if (act0 == AGENT_ACTION_PAPER)
    {
        if (act1 == AGENT_ACTION_SCISSOR)
        {
            pAgent0->GetHurt();
        }
        else if (act1 == AGENT_ACTION_ROCK)
        {
            pAgent1->GetHurt();
        }
    }
    else
    {
        if (act1 == AGENT_ACTION_ROCK)
        {
            pAgent0->GetHurt();
        }
        else if (act1 == AGENT_ACTION_PAPER)
        {
            pAgent1->GetHurt();
        }
    }

    return true;
}

int main()
{
    int32_t ret = 0;
    uint32_t agentNum = 10;
    Agent *pGroups[10];

    // init
    for (uint32_t i = 0; i < agentNum; ++i)
    {
        if (i < 3)
            pGroups[i] = new Agent(0);
        else if (i < 6)
            pGroups[i] = new Agent(1);
        else
            pGroups[i] = new Agent(2);
    }

    for (uint32_t i = 0; i < agentNum - 1; i++)
    {
        for (uint32_t j = i; j < agentNum; j++)
        {
            if (!Encounter(pGroups[i], pGroups[j]))
            {
                cout << "[Error], Encounter error! i = " << i << ", j = " << j << endl;
                ret = -1;
                break;
            }
        }
    }

    cout << "All agents status:" << endl;
    for (uint32_t i = 0; i < agentNum; ++i)
    {
        cout << "Agent " << i << ": " << pGroups[i]->GetHealth() << endl;
    }

    return ret;
}