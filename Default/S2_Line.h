
enum LINELR_ID { LINE_LR_LEFT, LINE_LR_RIGHT, LINE_LR_END };
enum LINEID { LINE_DOWN, LINE_UP, LINE_LEFT, LINE_RIGHT, LINE_LD, LINE_LU, LINE_RD, LINE_RU, LINE_END };
typedef struct tagPoint
{
	float		fX;
	float		fY;

	tagPoint(void) { ZeroMemory(this, sizeof(tagPoint)); }
	tagPoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

typedef struct tagLineInfo
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;
	LINEID	line_id;
	tagLineInfo(void) { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOINT& tLeft, LINEPOINT& tRight, LINEID _line_id) : tLPoint(tLeft), tRPoint(tRight), line_id(_line_id) {}
}LINEINFO;

#pragma once
class CS2_Line
{
public:
	//CLine();
	//CLine(const LINE& tLine);
	CS2_Line(LINEPOINT& tLeft, LINEPOINT& tRight, LINEID lineID);
	CS2_Line(LINEINFO& _LineInfo);
	virtual ~CS2_Line();

public:
	LINEINFO*		Get_Line(void) { return &m_tLineInfo; }

public:
	void		Render(HDC hDC);
	void		Release(void);

private:
	LINEINFO	m_tLineInfo;
};

