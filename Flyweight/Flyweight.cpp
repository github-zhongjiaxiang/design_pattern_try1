
#include "Flyweight.h"
#include <string>
#include <vector>
using namespace std;

//享元模式
//举个围棋的例子，围棋的棋盘共有361格，即可放361个棋子。现在要实现一个围棋程序，该怎么办呢？
//首先要考虑的是棋子棋盘的实现，可以定义一个棋子的类，成员变量包括棋子的颜色、形状、位置等信息，
//另外再定义一个棋盘的类，成员变量中有个容器，用于存放棋子的对象。下面给出代码表示：

//棋子的定义，当然棋子的属性除了颜色和位置，还有其他的，这里略去。这两个属性足以说明问题。
//棋子颜色  
namespace Normal{
	enum PieceColor {BLACK, WHITE};  
	//棋子位置  
	struct PiecePos  
	{  
		int x;  
		int y;  
		PiecePos(int a, int b): x(a), y(b) {}  
	};  
	//棋子定义  
	class Piece  
	{  
	protected:  
		PieceColor m_color; //颜色  
		PiecePos m_pos;     //位置  
	public:  
		Piece(PieceColor color, PiecePos pos): m_color(color), m_pos(pos) {}  
		~Piece() {}  
		virtual void Draw() {}  
	};  
	class BlackPiece: public Piece  
	{  
	public:  
		BlackPiece(PieceColor color, PiecePos pos): Piece(color, pos) {}  
		~BlackPiece() {}  
		void Draw() { cout<<"绘制一颗黑棋"<<endl;}  
	};  
	class WhitePiece: public Piece  
	{  
	public:  
		WhitePiece(PieceColor color, PiecePos pos): Piece(color, pos) {}  
		~WhitePiece() {}  
		void Draw() { cout<<"绘制一颗白棋"<<endl;}  
	};
	//棋盘的定义
	class PieceBoard  
	{  
	private:  
		vector<Piece*> m_vecPiece; //棋盘上已有的棋子  
		string m_blackName; //黑方名称  
		string m_whiteName; //白方名称  
	public:  
		PieceBoard(string black, string white): m_blackName(black), m_whiteName(white){}  
		~PieceBoard() { Clear(); }  
		void SetPiece(PieceColor color, PiecePos pos) //一步棋，在棋盘上放一颗棋子  
		{  
			Piece * piece = NULL;  
			if(color == BLACK) //黑方下的  
			{     
				piece = new BlackPiece(color, pos); //获取一颗黑棋  
				cout<<m_blackName<<"在位置("<<pos.x<<','<<pos.y<<")";  
				piece->Draw(); //在棋盘上绘制出棋子  
			}  
			else  
			{     
				piece = new WhitePiece(color, pos);  
				cout<<m_whiteName<<"在位置("<<pos.x<<','<<pos.y<<")";  
				piece->Draw();  
			}  
			m_vecPiece.push_back(piece);  //加入容器中  
		}  
		void Clear() //释放内存  
		{  
			int size = m_vecPiece.size();  
			for(int i = 0; i < size; i++)  
				delete m_vecPiece[i];  
		}  
	};  
	//客户的使用方式如下
	void UsePiece(){
		PieceBoard pieceBoard("A","B");  
		pieceBoard.SetPiece(BLACK, PiecePos(4, 4));  
		pieceBoard.SetPiece(WHITE, PiecePos(4, 16));  
		pieceBoard.SetPiece(BLACK, PiecePos(16, 4));  
		pieceBoard.SetPiece(WHITE, PiecePos(16, 16));  
	}
}
//可以发现，棋盘的容器中存放了已下的棋子，而每个棋子包含棋子的所有属性。
//一盘棋往往需要含上百颗棋子，采用上面这种实现，占用的空间太大了。
//如何改进呢？用享元模式。其定义为：运用共享技术有效地支持大量细粒度的对象。

//在围棋中，棋子就是大量细粒度的对象。
//其属性有内在的，比如颜色、形状等，也有外在的，比如在棋盘上的位置。
//内在的属性是可以共享的，区分在于外在属性。
//因此，可以这样设计，只需定义两个棋子的对象，一颗黑棋和一颗白棋，这两个对象含棋子的内在属性；
//棋子的外在属性，即在棋盘上的位置可以提取出来，存放在单独的容器中。
//相比之前的方案，现在容器中仅仅存放了位置属性，而原来则是棋子对象。
//显然，现在的方案大大减少了对于空间的需求。

//关注PieceBoard 的容器，之前是vector<Piece*> m_vecPiece，现在是vector<PiecePos> m_vecPos。这里是关键。

//棋子的新定义，只包含内在属性：
//棋子颜色
namespace NS_FlyWeightPattern{
	enum PieceColor {BLACK, WHITE};
	//棋子位置
	struct PiecePos
	{
		int x;
		int y;
		PiecePos(int a, int b) : x(a), y(b){}
	};
	//棋子定义
	class Piece{
	protected:
		PieceColor m_color; //颜色
	public:
		Piece(PieceColor color) : m_color(color) {}
		~Piece() {}
		virtual void Draw() {}
	};
	class BlackPiece : public Piece
	{
	public:
		BlackPiece(PieceColor color) : Piece(color) {}
		~BlackPiece() {}
		void Draw() { cout<<"绘制一颗黑棋\n"; }
	};
	class WhitePiece : public Piece
	{
	public:
		WhitePiece(PieceColor color) : Piece(color) {}
		~WhitePiece() {}
		void Draw() { cout<<"绘制一颗白棋\n"; }
	};

	class PieceBoard
	{
	private:
		vector<PiecePos> m_vecPos;
		Piece *m_blackPiece;
		Piece *m_whitePiece;
		string m_blackName;
		string m_whiteName;
	public:
		PieceBoard(string black, string white) : m_blackName(black), m_whiteName(white)
		{
			m_blackPiece = NULL;
			m_whitePiece = NULL;
		}
		~PieceBoard() {delete m_blackPiece; delete m_whitePiece;}
		void SetPiece(PieceColor color, PiecePos pos)
		{
			if(color = BLACK)
			{
				if(m_blackPiece == NULL) // 只有一颗黑棋
					m_blackPiece = new BlackPiece(color);
				cout<<m_blackName<<"在位置("<< pos.x<<','<<pos.y<<")";
				m_blackPiece->Draw();
			}else{
				if(m_whitePiece == NULL) // 只有一颗黑棋
					m_whitePiece = new WhitePiece(color);
				cout<<m_whiteName<<"在位置("<< pos.x<<','<<pos.y<<")";
				m_whitePiece->Draw();
			}
			m_vecPos.push_back(pos);
		}
	};
	//客户的使用方式如下
	void UsePiece(){
		PieceBoard pieceBoard("A","B");  
		pieceBoard.SetPiece(BLACK, PiecePos(4, 4));  
		pieceBoard.SetPiece(WHITE, PiecePos(4, 16));  
		pieceBoard.SetPiece(BLACK, PiecePos(16, 4));  
		pieceBoard.SetPiece(WHITE, PiecePos(16, 16));  
	}
}
//客户的使用方式一样，这里不重复给出，现在给出享元模式的UML图，以围棋为例。
//棋盘中含两个共享的对象，黑棋子和白棋子，所有棋子的外在属性都存放在单独的容器中。

//出处 http://blog.csdn.net/wuzhekai1985
emJRet CFlyweight::Run()
{
	using namespace NS_FlyWeightPattern;
	UsePiece();
	return emJOk;
}
