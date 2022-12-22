#pragma once
class Object;
class Animation;
class Image;
class Animator
{
private:
	Object* m_pOwner;                  // animation 소유 오브젝트
	map<wstring, Animation*> m_mapAni; // 모든 animation
	Animation*				m_pCurAni;  // 현재 재생중인 animation
	bool					m_bRepeat;
	COLORREF				m_tColor;	// 투명 처리할 컬러
	Vec2					m_scale;
public:
	Animator();
	~Animator();
	friend class Object;
public:
	Object* GetObj() {	return m_pOwner; }
public:
	void CreateAnimation(const wstring _strName, Image* _pImage, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount, float _fDuration);
	Animation* FindAnimation(const wstring _strName);
	void Play(const wstring _strName, bool _bRepeat);
	void Update();
	void Render(HDC _dc);

	void SetColor(COLORREF color) { m_tColor = color; }
	void SetScale(Vec2 scale) { m_scale = scale; }
};

