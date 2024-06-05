#pragma once
#include <algorithm>

#include "Math/Vec2/Vec2.h"

struct Rect
{
	Vec2 pos;
	Vec2 size;

	bool IsOverlappingPoint(const Vec2& point) const {
		return point.x >= pos.x && point.x <= pos.x + size.x &&
			point.y >= pos.y && point.y <= pos.y + size.y;
	}

	bool IsOverlappingCircle(const Vec2& point, const float radius) const {
		// 円の中心が矩形の内部にあるかどうかをチェック
		if (IsOverlappingPoint(point)) {
			return true;
		}

		// 矩形の各辺と円の距離をチェック
		float closestX = std::max<float>(pos.x, std::min<float>(point.x, pos.x + size.x));
		float closestY = std::max<float>(pos.y, std::min<float>(point.y, pos.y + size.y));

		// 円の中心と矩形の最近接点との距離を計算
		float distanceX = point.x - closestX;
		float distanceY = point.y - closestY;

		// 距離が半径以下であれば衝突している
		return (distanceX * distanceX + distanceY * distanceY) <= (radius * radius);
	}
};

