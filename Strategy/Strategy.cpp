
#include "Strategy.h"

using namespace std;
//策略模式是指定义一系列的算法，把它们一个个封装起来，并且使它们可相互替换。
//本模式使得算法可独立于使用它的客户而变化。
//也就是说这些算法所完成的功能一样，对外的接口一样，只是各自实现上存在差异。
//用策略模式来封装算法，效果比较好。下面以高速缓存（Cache）的替换算法为例，实现策略模式。
//
//什么是Cache的替换算法呢？
//简单解释一下， 当发生Cache缺失时，Cache控制器必须选择Cache中的一行，并用欲获得的数据来替换它。
//所采用的选择策略就是Cache的替换算法。

//抽象接口
class ReplaceAlgorithm
{
public:
	virtual void Replace() = 0;
};
//三种具体的替换算法
class LRU_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
	void Replace() { cout<<"Least Recently Used replace algorithm"<<endl; }
};
class FIFO_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
	void Replace() { cout<<"First in First out replace algorithm"<<endl; }
};
class Random_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
	void Replace() { cout<<"Random replace algorithm"<<endl; }
};
//接着给出Cache的定义，这里很关键，Cache的实现方式直接影响了客户的使用方式，其关键在于如何指定替换算法。

//方式一：直接通过参数指定，传入一个特定算法的指针。
namespace ByParam_Strategy
{
	class Cache
	{
	private:
		ReplaceAlgorithm * m_ra;
	public:
		Cache(ReplaceAlgorithm* ra) { m_ra = ra;}
		~Cache(){delete m_ra;}
		void Replace(){ m_ra->Replace(); }
	};
}
 //如果用这种方式，客户就需要知道这些算法的具体定义。只能以下面这种方式使用，可以看到暴露了太多的细节。
 //方式二：也是直接通过参数指定，只不过不是传入指针，而是一个标签。
	 //这样客户只要知道算法的相应标签即可，而不需要知道算法的具体定义。
namespace ByEnumParam_Strategy
{
	enum RA{ LRU, FIFO, RANDOM};
	class Cache
	{
	private:
		ReplaceAlgorithm* m_ra;
	public:
		Cache(enum RA ra){
			if(ra == LRU)
				m_ra = new LRU_ReplaceAlgorithm();
			else if(ra == FIFO)
				m_ra = new FIFO_ReplaceAlgorithm();
			else if(ra == RANDOM)
				m_ra = new Random_ReplaceAlgorithm();
			else
				m_ra = NULL;
		};
		~Cache(){delete m_ra;}
		void Replace(){ m_ra->Replace();}
	};
}
//相比方式一，这种方式用起来方便多了。
//其实这种方式将简单工厂模式与策略模式结合在一起，算法的定义使用了策略模式，
//而Cache的定义其实使用了简单工厂模式。

//上面两种方式，构造函数都需要形参。构造函数是否可以不用参数呢？下面给出第三种实现方式。
//方式三：利用模板实现。算法通过模板的实参指定。
//当然了，还是使用了参数，只不过不是构造函数的参数。
//在策略模式中，参数的传递难以避免，客户必须指定某种算法。
namespace Template_Strategy
{
	template<class RA>
	class Cache
	{
	private:
		RA m_ra;
	public:
		Cache(){}
		~Cache() {}
		void Replace(){ m_ra.Replace();}
	};
}
//出处 http://blog.csdn.net/wuzhekai1985

emJRet CStrategy::Run()
{
	ByParam_Strategy::Cache cache1(new FIFO_ReplaceAlgorithm());
	cache1.Replace();
	ByEnumParam_Strategy::Cache cache2(ByEnumParam_Strategy::LRU);
	cache2.Replace();
	Template_Strategy::Cache<Random_ReplaceAlgorithm> cache3; //模板实参
	cache3.Replace();
	return emJOk;
}
