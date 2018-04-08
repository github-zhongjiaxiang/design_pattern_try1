
#include "Flyweight.h"
#include <string>
#include <vector>
using namespace std;

//��Ԫģʽ
//�ٸ�Χ������ӣ�Χ������̹���361�񣬼��ɷ�361�����ӡ�����Ҫʵ��һ��Χ����򣬸���ô���أ�
//����Ҫ���ǵ����������̵�ʵ�֣����Զ���һ�����ӵ��࣬��Ա�����������ӵ���ɫ����״��λ�õ���Ϣ��
//�����ٶ���һ�����̵��࣬��Ա�������и����������ڴ�����ӵĶ���������������ʾ��

//���ӵĶ��壬��Ȼ���ӵ����Գ�����ɫ��λ�ã����������ģ�������ȥ����������������˵�����⡣
//������ɫ  
namespace Normal{
	enum PieceColor {BLACK, WHITE};  
	//����λ��  
	struct PiecePos  
	{  
		int x;  
		int y;  
		PiecePos(int a, int b): x(a), y(b) {}  
	};  
	//���Ӷ���  
	class Piece  
	{  
	protected:  
		PieceColor m_color; //��ɫ  
		PiecePos m_pos;     //λ��  
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
		void Draw() { cout<<"����һ�ź���"<<endl;}  
	};  
	class WhitePiece: public Piece  
	{  
	public:  
		WhitePiece(PieceColor color, PiecePos pos): Piece(color, pos) {}  
		~WhitePiece() {}  
		void Draw() { cout<<"����һ�Ű���"<<endl;}  
	};
	//���̵Ķ���
	class PieceBoard  
	{  
	private:  
		vector<Piece*> m_vecPiece; //���������е�����  
		string m_blackName; //�ڷ�����  
		string m_whiteName; //�׷�����  
	public:  
		PieceBoard(string black, string white): m_blackName(black), m_whiteName(white){}  
		~PieceBoard() { Clear(); }  
		void SetPiece(PieceColor color, PiecePos pos) //һ���壬�������Ϸ�һ������  
		{  
			Piece * piece = NULL;  
			if(color == BLACK) //�ڷ��µ�  
			{     
				piece = new BlackPiece(color, pos); //��ȡһ�ź���  
				cout<<m_blackName<<"��λ��("<<pos.x<<','<<pos.y<<")";  
				piece->Draw(); //�������ϻ��Ƴ�����  
			}  
			else  
			{     
				piece = new WhitePiece(color, pos);  
				cout<<m_whiteName<<"��λ��("<<pos.x<<','<<pos.y<<")";  
				piece->Draw();  
			}  
			m_vecPiece.push_back(piece);  //����������  
		}  
		void Clear() //�ͷ��ڴ�  
		{  
			int size = m_vecPiece.size();  
			for(int i = 0; i < size; i++)  
				delete m_vecPiece[i];  
		}  
	};  
	//�ͻ���ʹ�÷�ʽ����
	void UsePiece(){
		PieceBoard pieceBoard("A","B");  
		pieceBoard.SetPiece(BLACK, PiecePos(4, 4));  
		pieceBoard.SetPiece(WHITE, PiecePos(4, 16));  
		pieceBoard.SetPiece(BLACK, PiecePos(16, 4));  
		pieceBoard.SetPiece(WHITE, PiecePos(16, 16));  
	}
}
//���Է��֣����̵������д�������µ����ӣ���ÿ�����Ӱ������ӵ��������ԡ�
//һ����������Ҫ���ϰٿ����ӣ�������������ʵ�֣�ռ�õĿռ�̫���ˡ�
//��θĽ��أ�����Ԫģʽ���䶨��Ϊ�����ù���������Ч��֧�ִ���ϸ���ȵĶ���

//��Χ���У����Ӿ��Ǵ���ϸ���ȵĶ���
//�����������ڵģ�������ɫ����״�ȣ�Ҳ�����ڵģ������������ϵ�λ�á�
//���ڵ������ǿ��Թ����ģ����������������ԡ�
//��ˣ�����������ƣ�ֻ�趨���������ӵĶ���һ�ź����һ�Ű��壬�������������ӵ��������ԣ�
//���ӵ��������ԣ����������ϵ�λ�ÿ�����ȡ����������ڵ����������С�
//���֮ǰ�ķ��������������н��������λ�����ԣ���ԭ���������Ӷ���
//��Ȼ�����ڵķ����������˶��ڿռ������

//��עPieceBoard ��������֮ǰ��vector<Piece*> m_vecPiece��������vector<PiecePos> m_vecPos�������ǹؼ���

//���ӵ��¶��壬ֻ�����������ԣ�
//������ɫ
namespace NS_FlyWeightPattern{
	enum PieceColor {BLACK, WHITE};
	//����λ��
	struct PiecePos
	{
		int x;
		int y;
		PiecePos(int a, int b) : x(a), y(b){}
	};
	//���Ӷ���
	class Piece{
	protected:
		PieceColor m_color; //��ɫ
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
		void Draw() { cout<<"����һ�ź���\n"; }
	};
	class WhitePiece : public Piece
	{
	public:
		WhitePiece(PieceColor color) : Piece(color) {}
		~WhitePiece() {}
		void Draw() { cout<<"����һ�Ű���\n"; }
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
				if(m_blackPiece == NULL) // ֻ��һ�ź���
					m_blackPiece = new BlackPiece(color);
				cout<<m_blackName<<"��λ��("<< pos.x<<','<<pos.y<<")";
				m_blackPiece->Draw();
			}else{
				if(m_whitePiece == NULL) // ֻ��һ�ź���
					m_whitePiece = new WhitePiece(color);
				cout<<m_whiteName<<"��λ��("<< pos.x<<','<<pos.y<<")";
				m_whitePiece->Draw();
			}
			m_vecPos.push_back(pos);
		}
	};
	//�ͻ���ʹ�÷�ʽ����
	void UsePiece(){
		PieceBoard pieceBoard("A","B");  
		pieceBoard.SetPiece(BLACK, PiecePos(4, 4));  
		pieceBoard.SetPiece(WHITE, PiecePos(4, 16));  
		pieceBoard.SetPiece(BLACK, PiecePos(16, 4));  
		pieceBoard.SetPiece(WHITE, PiecePos(16, 16));  
	}
}
//�ͻ���ʹ�÷�ʽһ�������ﲻ�ظ����������ڸ�����Ԫģʽ��UMLͼ����Χ��Ϊ����
//�����к����������Ķ��󣬺����ӺͰ����ӣ��������ӵ��������Զ�����ڵ����������С�

//���� http://blog.csdn.net/wuzhekai1985
emJRet CFlyweight::Run()
{
	using namespace NS_FlyWeightPattern;
	UsePiece();
	return emJOk;
}