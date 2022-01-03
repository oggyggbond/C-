#include<iostream>
using namespace std;
#include<string>

// khai b�o c?u tr�c 1 c�i node
struct NODE
{
	string data;
	NODE* pNext;
};

// ================================================== C?U TR�C STACK ======================================================

// khai b�o c?u tr�c STACK
struct STACK
{
	NODE* pTop;
};

// h�m kh?i t?o node
NODE* KhoiTaoNode(string x)
{
	NODE* p = new NODE;
	if (p == NULL)
	{
		cout << "\nKhong du bo nho de cap phat";
		return NULL;
	}
	p->data = x;
	p->pNext = NULL;
	return p;
}

// h�m ki?m tra xem stack c� r?ng kh�ng
bool IsEmpty(STACK s)
{
	if (s.pTop == NULL)
	{
		return true; // stack r?ng
	}
	return false; // stack ?ang c� ph?n t?
}
// h�m th�m node p v�o ??u danh s�ch 
bool Push(STACK& s, NODE* p)
{
	// stack r?ng
	if (IsEmpty(s) == true)
	{
		s.pTop = p;
	}
	else
	{
		p->pNext = s.pTop;
		s.pTop = p;
	}
	return true;
}

// h�m l?y ph?n t? ra kh?i stack <=> l?y ph?n t? ??u stack ra v� x�a n� ?i
bool Pop(STACK& s, string& x)
{
	if (IsEmpty(s) == true)
	{
		return false;
	}
	else
	{
		NODE* k = s.pTop;
		x = s.pTop->data; // gi? l?i d? li?u b�n trong ph?n t? ??u stack 
		s.pTop = s.pTop->pNext;
		delete k;
	}
	return true;
}

// h�m l?y ph?n t? ??u stack ra ?? xem
bool Top(STACK s, string& x)
{
	if (IsEmpty(s) == true)
	{
		return false;
	}
	x = s.pTop->data;
	return true;
}

// h�m gi?i ph�ng v�ng nh?
void Giai_Phong_STACK(STACK& s)
{
	NODE* k = s.pTop;
	while (s.pTop != NULL)
	{
		s.pTop = s.pTop->pNext;
		delete k;
		k = s.pTop;
	}
}

// ========================================= C?U TR�C QUEUE =======================================================
// khai b�o c?u tr�c QUEUE
struct QUEUE
{
	NODE* pTop;
};

// h�m ki?m tra xem QUEUE c� r?ng kh�ng
bool IsEmpty(QUEUE q)
{
	if (q.pTop == NULL)
	{
		return true; // QUEUE r?ng
	}
	return false; // QUEUE ?ang c� ph?n t?
}
// h�m th�m node p v�o cu?i danh s�ch 
bool Push(QUEUE& q, NODE* p)
{
	// QUEUE r?ng
	if (IsEmpty(q) == true)
	{
		q.pTop = p;
	}
	else
	{
		for (NODE* k = q.pTop; k != NULL; k = k->pNext)
		{
			if (k->pNext == NULL)
			{
				k->pNext = p;
				break;
			}
		}
	}
	return true;
}

// h�m l?y ph?n t? ra kh?i QUEUE <=> l?y ph?n t? ??u QUEUE ra v� x�a n� ?i
bool Pop(QUEUE& q, string& x)
{
	if (IsEmpty(q) == true)
	{
		return false;
	}
	else
	{
		NODE* k = q.pTop;
		x = q.pTop->data; // gi? l?i d? li?u b�n trong ph?n t? ??u stQUEUEack 
		q.pTop = q.pTop->pNext;
		delete k;
	}
	return true;
}

// h�m l?y ph?n t? ??u QUEUE ra ?? xem
bool Top(QUEUE q, string& x)
{
	if (IsEmpty(q) == true)
	{
		return false;
	}
	x = q.pTop->data;
	return true;
}

// h�m gi?i ph�ng v�ng nh?
void Giai_Phong_QUEUE(QUEUE& q)
{
	NODE* k = q.pTop;
	while (q.pTop != NULL)
	{
		q.pTop = q.pTop->pNext;
		delete k;
		k = q.pTop;
	}
}

// h�m x? l� chuy?n bi?u th?c trung t? sang h?u t?
void TrungTo_HauTo(STACK& s, QUEUE& q, string trungto)
{
	// duy?t qua t?ng ph?n t? trong bi?u th?c trungto
	for (int i = 0; i < trungto.length(); i++)
	{

		// n?u ph?n t? ?ang x�t l� to�n h?ng...
		if (trungto[i] >= '0' && trungto[i] <= '9')
		{
			// ...push v�o trong QUEUE
			string str;
			str.push_back(trungto[i]); // ??y k� t? v�o cu?i chu?i str
			NODE* x = KhoiTaoNode(str);
			Push(q, x); // th�m node x v�o queue
		}
		else if (trungto[i] == '(') // n?u ph?n t? ?ang x�t l� d?u m? ngo?c (...
		{
			// ...push v�o trong STACK
			string str;
			str.push_back(trungto[i]); // ??y k� t? v�o cu?i chu?i str
			NODE* x = KhoiTaoNode(str);
			Push(s, x); // th�m node x v�o stack
		}
		else if (trungto[i] == ')') // n?u ph?n t? ?ang x�t l� d?u ?�ng ngo?c )...
		{
			// duy?t qua t?ng ph?n trong stack
			while (IsEmpty(s) == false)
			{
				string str;
				Pop(s, str);
				if (str[0] == '(')
				{
					// ...g?p k� t? m? ngo?c th� d?ng
					break;
				}
				else
				{
					// ...push v�o trong QUEUE
					NODE* x = KhoiTaoNode(str);
					Push(q, x); // th�m node x v�o QUEUE
				}
			}
		}
		else if (trungto[i] == '+' || trungto[i] == '-' || trungto[i] == '*' || trungto[i] == '/')
		{
			//... n?u stack r?ng
			if (IsEmpty(s) == true)
			{
				// ...push v�o trong STACK
				string str;
				str.push_back(trungto[i]); // ??y k� t? v�o cu?i chu?i str
				NODE* x = KhoiTaoNode(str);
				Push(s, x); // th�m node x v�o stack
			}
			else //...stack kh�ng r?ng <=> c� ph?n t?
			{
				string str;
				Top(s, str); // l?y ph?n t? ??u STACK ra ki?m tra
				//...ph?n t? ??u STACK l� to�n t? th�...
				if (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/')
				{
					// ...ph?n t? ??u stack l� + v� -
					if (str[0] == '+' || str[0] == '-')
					{
						// ..ph?n t? ?ang x�t l� * v� /
						if (trungto[i] == '*' || trungto[i] == '/')
						{
							// ===> ?? ?u ti�n c?a ph?n t? ??u STACK(str[0]) < ph?n t? ?ang x�t X(trungto[i])
							// ...push v�o trong STACK
							string str_1;
							str_1.push_back(trungto[i]); // ??y k� t? v�o cu?i chu?i str
							NODE* x = KhoiTaoNode(str_1);
							Push(s, x); // th�m node x v�o stack
						}
						else
						{
							if (trungto[i] == '+' || trungto[i] == '-')
							{
								while (IsEmpty(s) == false)
								{
									// ...n?u ph?n t? ??u STACK(str[0]) = X(trungto[i]) 
									
									// ===> ?? ?u ti�n c?a ph?n t? ??u STACK(str[0]) >= ph?n t? ?ang x�t X(trungto[i])
											// ...l?y ph?n t? ??u STACK push v�o trong QUEUE
									string str_1;
									str_1.push_back(str[0]); // ??y k� t? v�o cu?i chu?i str
									NODE* x = KhoiTaoNode(str_1);
									Push(q, x); // th�m node x v�o QUEUE

									Pop(s, str); // l?y ph?n t? ??u STACK ra ki?m tra
									// ..ph?n t? ??u STACK kh�ng ph?i l� to�n t? th� d?ng
									if (str[0] != '+' || str[0] != '-' || str[0] != '*' || str[0] != '/')
									{
										break; // d?ng l?i kh�ng l?y n?a
									}
								}

								// ...push X v�o trong STACK
								string str_1;
								str_1.push_back(trungto[i]); // ??y k� t? v�o cu?i chu?i str
								NODE* x = KhoiTaoNode(str_1);
								Push(s, x); // th�m node x v�o stack
							}
						}
					}
					else // ...ph?n t? ??u stack l� * v� / >= X
					{
						// ..stack r?ng th� d?ng		
						while (IsEmpty(s) == false)
						{
							// ...n?u ph?n t? ??u STACK(str[0]) >= X(trungto[i]) 
							if (str[0] == '*' || str[0] == '/')
							{
								// ===> ?? ?u ti�n c?a ph?n t? ??u STACK(str[0]) >= ph?n t? ?ang x�t X(trungto[i])
									// ...l?y ph?n t? ??u STACK push v�o trong QUEUE
								string str_1;
								str_1.push_back(str[0]); // ??y k� t? v�o cu?i chu?i str
								NODE* x = KhoiTaoNode(str_1);
								Push(q, x); // th�m node x v�o QUEUE

								Pop(s, str); // l?y ph?n t? ??u STACK ra ki?m tra
								// ..ph?n t? ??u STACK kh�ng ph?i l� to�n t? th� d?ng
								if (str[0] != '+' || str[0] != '-' || str[0] != '*' || str[0] != '/')
								{
									break; // d?ng l?i kh�ng l?y n?a
								}
							}
						}

						// ...push X v�o trong STACK
						string str_1;
						str_1.push_back(trungto[i]); // ??y k� t? v�o cu?i chu?i str
						NODE* x = KhoiTaoNode(str_1);
						Push(s, x); // th�m node x v�o stack
					}
				}
				else //...ph?n t? ??u STACK kh�ng ph?i l� to�n t? th�
				{
					// ...push v�o trong STACK
					string str_1;
					str_1.push_back(trungto[i]); // ??y k� t? v�o cu?i chu?i str
					NODE* x = KhoiTaoNode(str_1);
					Push(s, x); // th�m node x v�o stack
				}
			}
		}
	}

	// ...trong stack c�n ph?n t? n�o th� push h?t sang QUEUE
	while (IsEmpty(s) == false)
	{
		string str;
		Pop(s, str);
		NODE* x = KhoiTaoNode(str);
		Push(q, x); // th�m node x v�o QUEUE
	}
}

// xu?t bi?u th?c trung t?
void Xuat_BIEU_THUC_TRUNG_TO(QUEUE& q)
{
	while (IsEmpty(q) == false)
	{
		string str;
		Pop(q, str);
		cout << str;
	}
}

int main()
{
	STACK s;
	s.pTop = NULL; // kh?i t?o stack r?ng
	QUEUE q;
	q.pTop = NULL;

	string trungto = "8/2+5-((8-4)*2)+8/2";
	// 8 2 / 5 + 8 4 - 2 * - 8 2 / +
	TrungTo_HauTo(s, q, trungto);
	cout << "\n\n\t\t BIEU THUC TRUNG TO NHAN DUOC LA: ";
	Xuat_BIEU_THUC_TRUNG_TO(q);

	Giai_Phong_STACK(s); // gi?i ph�ng stack
	Giai_Phong_QUEUE(q); // gi?i ph�ng queue
	system("pause");
	return 0;
}