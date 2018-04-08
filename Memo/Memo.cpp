
#include "Memo.h"
#include <string>
#include <vector>
using namespace std;

//备忘录模式：在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。
//这样以后就可将该对象恢复到原先保存的状态[DP]。
//举个简单的例子，我们玩游戏时都会保存进度，所保存的进度以文件的形式存在。
//这样下次就可以继续玩，而不用从头开始。
//这里的进度其实就是游戏的内部状态，而这里的文件相当于是在游戏之外保存状态。
//这样，下次就可以从文件中读入保存的进度，从而恢复到原来的状态。这就是备忘录模式。

//给出备忘录模式的UML图，以保存游戏的进度为例。

//Memento类定义了内部的状态，而Caretake类是一个保存进度的管理者，GameRole类是游戏角色类。
//可以看到GameRole的对象依赖于Memento对象，而与Caretake对象无关。下面给出一个简单的是实现。

//需保存的信息
class Memento
{
public:
	int m_vitality; //生命值
	int m_attack;		//进攻值
	int m_defense;	//防守值
public:
	Memento(int vitality, int attack, int defense) :
			m_vitality(vitality), m_attack(attack), m_defense(defense){}
	Memento& operator=(const Memento &memento)
	{
		m_vitality = memento.m_vitality;
		m_attack = memento.m_attack;
		m_defense = memento.m_defense;
		return *this;
	}
};
//游戏角色
class GameRole
{
private:
	int m_vitality;
	int m_attack;
	int m_defense;
public:
	GameRole() : m_vitality(100), m_attack(100),m_defense(100){}
	Memento Save() //保存进度，只与Memento对象交互，并不牵涉到Caretake
	{
		Memento memento(m_vitality, m_attack, m_defense);
		return memento;
	}
	void Load(Memento memento) //载入进度，只与Memento对象交互，并不牵涉到 Caretake
	{
		m_vitality = memento.m_vitality;
		m_attack = memento.m_attack;
		m_defense = memento.m_defense;
	}
	void Show() { cout<<"vitality : "<<m_vitality<<",attack: "<<m_attack<<",defense: "<<m_defense<<endl;}
	void Attack() {m_vitality -=10; m_attack -=10; m_defense -=10;}
};
//保存的进度库
class Caretake
{
public:
	Caretake() {}
	void Save(Memento memento) { m_vecMemento.push_back(memento); }
	Memento Load(int state) { return m_vecMemento[state]; }
private:
	vector<Memento> m_vecMemento;
};

//出处 http://blog.csdn.net/wuzhekai1985
emJRet CMemo::Run()
{
	Caretake caretake;
	GameRole role;
	role.Show();
	caretake.Save(role.Save()); 
	role.Attack();
	role.Show();
	role.Load(caretake.Load(0));
	role.Show();
	return emJOk;
}
