#include "Agent.h"
#include <algorithm>
#include <random>

// class Agent

Agent::Agent() : actionType_(0)
{
    this->actionType_ = rand() % 3;
}

uint32_t Agent::GetHealth()
{
    return this->health_;
}

void Agent::GetHurt(int damage)
{
    this->health_ = max(0, (int)(this->health_ - damage));
    return;
}

EnumAgentStatus Agent::GetStatus()
{
    if (this->health_ > 0)
    {
        return EnumAgentStatus::AGENT_STATUS_HEALTHY;
    }
    else
    {
        return EnumAgentStatus::AGENT_STATUS_DEAD;
    }
}

uint32_t Agent::GetActionType()
{
    return this->actionType_;
}

void Agent::ReadEnvBeforeAction()
{
    // Do something
}

void Agent::ReadEnvAfterAction()
{
    // Do something
}

EnumAgentActionType Agent::Action()
{
    EnumAgentActionType type = EnumAgentActionType::AGENT_ACTION_ROCK;

    if (this->actionType_ == 0)
    {
        type = EnumAgentActionType::AGENT_ACTION_ROCK;
    }
    else if (this->actionType_ == 1)
    {
        type = EnumAgentActionType::AGENT_ACTION_PAPER;
    }
    else if (this->actionType_ == 2)
    {
        type = EnumAgentActionType::AGENT_ACTION_SCISSOR;
    }
    else if (this->actionType_ == 3)
    {
        type = this->ActionStrategyRandom();
    }

    return type;
}

void Agent::HealthRevive()
{
    health_ = 20;
}

EnumAgentActionType Agent::ActionStrategyRandom()
{
    uint32_t randNum = rand() % 3;

    return (EnumAgentActionType)randNum;
}

// class CopyLastActionAgent

void CopyLastActionAgent::SetLastAction(EnumAgentActionType action)
{
    lastAction_ = action;
}

void CopyLastActionAgent::ReadEnvBeforeAction()
{
    // Do something
}

void CopyLastActionAgent::ReadEnvAfterAction(EnumAgentActionType action)
{
    SetLastAction(action);
}

EnumAgentActionType CopyLastActionAgent::Action()
{
    EnumAgentActionType type = EnumAgentActionType::AGENT_ACTION_ROCK;

    if (lastAction_ == EnumAgentActionType::AGENT_ACTION_ROCK)
    {
        type = EnumAgentActionType::AGENT_ACTION_PAPER;
    }
    else if (lastAction_ == EnumAgentActionType::AGENT_ACTION_PAPER)
    {
        type = EnumAgentActionType::AGENT_ACTION_SCISSOR;
    }
    else if (lastAction_ == EnumAgentActionType::AGENT_ACTION_SCISSOR)
    {
        type = EnumAgentActionType::AGENT_ACTION_ROCK;
    }

    return type;
}

// class SmartAgent

SmartAgent::SmartAgent() : Agent()
{
    // 使用 std::random_device 和 std::mt19937 生成随机数
    //std::random_device rd;    // 真随机数
    //std::mt19937 gen(rd());   // 伪随机数
    std::mt19937 gen(4);
    std::uniform_real_distribution<> dis(-0.1, 0.1);

    // 随机生成输入层权重矩阵和隐藏层权重矩阵
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            inputWeights[i][j] = dis(gen);
            hiddenWeights[i][j] = dis(gen);
        }
    }

    // 随机生成 vecComponentLastAction_ 和 vecMyLastAction_ 数组
    std::uniform_int_distribution<> disAction(0, 2);
    for (int i = 0; i < 3; ++i)
    {
        vecComponentLastAction_[i] = static_cast<EnumAgentActionType>(disAction(gen));
        vecMyLastAction_[i] = static_cast<EnumAgentActionType>(disAction(gen));
    }
}

void SmartAgent::SetComponentLastAction(EnumAgentActionType action)
{
    // 将 vecComponentLastAction_ 数组的后两个元素拷贝到前两个元素
    vecComponentLastAction_[0] = vecComponentLastAction_[1];
    vecComponentLastAction_[1] = vecComponentLastAction_[2];

    // 将 action 存储到 vecComponentLastAction_ 数组的最后一个元素
    vecComponentLastAction_[2] = action;
}

void SmartAgent::SetMyLastAction(EnumAgentActionType action)
{
    // 将 vecMyLastAction_ 数组的后两个元素拷贝到前两个元素
    vecMyLastAction_[0] = vecMyLastAction_[1];
    vecMyLastAction_[1] = vecMyLastAction_[2];

    // 将 action 存储到 vecMyLastAction_ 数组的最后一个元素
    vecMyLastAction_[2] = action;

}

void SmartAgent::ReadEnvBeforeAction()
{
    // Do something
}

void SmartAgent::ReadEnvAfterAction(EnumAgentActionType action)
{
    SetComponentLastAction(action);
}

EnumAgentActionType SmartAgent::think()
{
    // 将 EnumAgentActionType 转换为 float 类型的函数
    auto convertToFloat = [](EnumAgentActionType actionType) -> float
    {
        return actionType == EnumAgentActionType::AGENT_ACTION_ROCK ? -1.0
            : actionType == EnumAgentActionType::AGENT_ACTION_PAPER ? 0.0
            : 1.0;
    };

    // 获取对手之前出的动作并将其转换为 mat3 的形式
    vmath::mat3 inputMatrix;
    for (int i = 0; i < 3; i++)
    {
        // 将对手之前出的动作存储在输入数据的第一列
        inputMatrix[i][0] = convertToFloat(vecComponentLastAction_[i]);
        // 将我们之前出的动作存储在输入数据的第二列
        inputMatrix[i][1] = convertToFloat(vecMyLastAction_[i]);
        inputMatrix[i][2] = 0;
    }

    // 使用矩阵相乘的方式模拟神经网络的计算过程
    vmath::mat3 hidden = inputWeights * inputMatrix;
    vmath::mat3 output = hiddenWeights * hidden;

    // 将计算结果转换为 EnumAgentActionType 类型
    EnumAgentActionType action;
    if (output[0][0] > output[1][0] && output[0][0] > output[2][0])
    {
        action = EnumAgentActionType::AGENT_ACTION_ROCK;
    }
    else if (output[1][0] > output[0][0] && output[1][0])
    {
        action = EnumAgentActionType::AGENT_ACTION_PAPER;
    }
    else
    {
        action = EnumAgentActionType::AGENT_ACTION_SCISSOR;
    }

    // 设置当前的我们的action
    SetMyLastAction(action);

    return action;
}