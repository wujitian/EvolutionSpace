// EvoBasic.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Agent.h"
#include "Environment.h"

using namespace std;

std::string GetActionTypeString(EnumAgentActionType type)
{
    std::string result = "";
    switch (type)
    {
    case EnumAgentActionType::AGENT_ACTION_ROCK:
        result = "rock";
        break;
    case EnumAgentActionType::AGENT_ACTION_PAPER:
        result = "paper";
        break;
    case EnumAgentActionType::AGENT_ACTION_SCISSOR:
        result = "scissor";
        break;
    default:
        result = "unknown";
        break;
    }
    return result;
}

bool Encounter(Agent* pAgent0, Agent* pAgent1)
{
    if (!pAgent0 || !pAgent1)
    {
        cout << "[Error] gent can not null" << endl;
        return false;
    }

    if (pAgent0->GetStatus() != EnumAgentStatus::AGENT_STATUS_HEALTHY ||
        pAgent1->GetStatus() != EnumAgentStatus::AGENT_STATUS_HEALTHY)
    {
        return true;
    }

    cout << "-----Encounter start-----" << endl;

    CopyLastActionAgent* pTransAgent0 = (CopyLastActionAgent*)pAgent0;
    SmartAgent* pTransAgent1 = (SmartAgent*)pAgent1;

    pTransAgent0->ReadEnvBeforeAction();
    pTransAgent1->ReadEnvBeforeAction();

    EnumAgentActionType act0 = pTransAgent0->Action();
    EnumAgentActionType act1 = pTransAgent1->Action();

    std::cout << "Agent 0 chose: " << GetActionTypeString(act0) << std::endl;
    std::cout << "Agent 1 chose: " << GetActionTypeString(act1) << std::endl;

    if (act0 >= EnumAgentActionType::AGENT_ACTION_MAX && act1 >= EnumAgentActionType::AGENT_ACTION_MAX)
    {
        printf("[Error] Agent action error.");
        return false;
    }

    int hurt = 1;
    if ((act0 == EnumAgentActionType::AGENT_ACTION_ROCK && act1 == EnumAgentActionType::AGENT_ACTION_PAPER) ||
        (act0 == EnumAgentActionType::AGENT_ACTION_PAPER && act1 == EnumAgentActionType::AGENT_ACTION_SCISSOR) ||
        (act0 == EnumAgentActionType::AGENT_ACTION_SCISSOR && act1 == EnumAgentActionType::AGENT_ACTION_ROCK))
    {
        pTransAgent0->GetHurt(2);
    }
    else if ((act0 == EnumAgentActionType::AGENT_ACTION_ROCK && act1 == EnumAgentActionType::AGENT_ACTION_SCISSOR) ||
        (act0 == EnumAgentActionType::AGENT_ACTION_PAPER && act1 == EnumAgentActionType::AGENT_ACTION_ROCK) ||
        (act0 == EnumAgentActionType::AGENT_ACTION_SCISSOR && act1 == EnumAgentActionType::AGENT_ACTION_PAPER))
    {
        pTransAgent1->GetHurt(2);
    }
    else
    {
        pTransAgent0->GetHurt(hurt);
        pTransAgent1->GetHurt(hurt);
    }

    std::cout << "Agent 0's health after the encounter: " << pTransAgent0->GetHealth() << std::endl;
    std::cout << "Agent 1's health after the encounter: " << pTransAgent1->GetHealth() << std::endl;

    pTransAgent0->ReadEnvAfterAction(act1);
    pTransAgent1->ReadEnvAfterAction(act0);

    cout << "-----Encounter end-----" << endl;

    return true;
}

void GetAllAgentStatus(Agent** pAllAgents, uint32_t num)
{
    if (num == 0)
    {
        return;
    }

    cout << "All agents status:" << endl;
    for (uint32_t i = 0; i < num; ++i)
    {
        uint32_t type = pAllAgents[i]->GetActionType();

        if (pAllAgents[i]->GetStatus() == EnumAgentStatus::AGENT_STATUS_DEAD)
        {
            cout << "Agent " << i << "(" << type << "): dead" << endl;
        }
        else
        {
            cout << "Agent " << i << "(" << type << "):" << pAllAgents[i]->GetHealth() << endl;
        }
    }
}

// 定义猜拳游戏的函数
int game(Agent* pAgent0, Agent* pAgent1)
{
    pAgent0->HealthRevive();
    pAgent1->HealthRevive();

    while (1)
    {
        if (!Encounter(pAgent0, pAgent1))
        {
            cout << "[Error], Encounter error!" << endl;
            return -1;
        }

        if (pAgent0->GetHealth() == 0)
        {
            return 1;   // pAgent1 win
        }
        else if (pAgent1->GetHealth() == 0)
        {
            return 0;   // pAgent0 win
        }
    }
}

int main()
{
    int32_t ret = 0;
    //uint32_t agentNum = 20;
    //Agent *pGroups[20];

    //Environment env;

    /*
    // init
    for (uint32_t i = 0; i < agentNum; ++i)
    {
        if (i < 2)
            pGroups[i] = new Agent(0);
        else if (i < 4)
            pGroups[i] = new Agent(1);
        else if (i < 6)
            pGroups[i] = new Agent(2);
        else
            pGroups[i] = new Agent();   // random
    }

    // make action
    uint32_t roundMax = 6;
    for (uint32_t roundIndex = 0; roundIndex < roundMax; roundIndex++)
    {
        cout << "round: " << roundIndex << endl;
        for (uint32_t i = 0; i < agentNum - 1; i++)
        {
            for (uint32_t j = i + 1; j < agentNum; j++)
            {
                if (!Encounter(pGroups[i], pGroups[j]))
                {
                    cout << "[Error], Encounter error! i = " << i << ", j = " << j << endl;
                    ret = -1;
                    break;
                }
            }
        }

        GetAllAgentStatus(pGroups, agentNum);
        cout << endl;
    }
    */

    // 初始化随机种子
    srand(time(NULL));

    // 创建两个智能体
    //Agent agent0;
    CopyLastActionAgent agent1;
    SmartAgent agent2;

    // 统计两个智能体的获胜局数
    int win0 = 0, win1 = 0;

    // 进行10局游戏
    for (int i = 0; i < 10; i++) {
        // 进行一局游戏
        int result = game(&agent1, &agent2);

        // 根据游戏结果，更新获胜局数
        if (result == 0) {
            win0++;
        }
        else if (result == 1) {
            win1++;
        }
    }

    // 输出获胜局数
    cout << "Agent1 win: " << win0 << " games" << endl;
    cout << "Agent2 win: " << win1 << " games" << endl;

    return ret;
}