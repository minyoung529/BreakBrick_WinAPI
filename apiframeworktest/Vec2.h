#pragma once
#include<cassert>
//#include<math.h>
class Vec2
{
public:
	float x;
	float y;
public:
	Vec2();
	~Vec2();
	Vec2(float _x, float _y);
	Vec2(int _x, int _y);
	Vec2(long _x, long _y);
	Vec2(POINT _pt);
	float Length();
	Vec2& Normalize();
	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}
	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator / (Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}
	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}
	Vec2 operator * (UINT _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}
	Vec2 operator * (float _i)
	{
		return Vec2(x * _i, y * _i);
	}
	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}
	void operator -=(Vec2 _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	bool operator ==(Vec2 _vOther)
	{
		return (x == _vOther.x && y == _vOther.y);
	}

	bool operator !=(Vec2 _vOther)
	{
		return (x != _vOther.x || y != _vOther.y);
	}
};

