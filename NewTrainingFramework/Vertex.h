#pragma once
#include "../Utilities/Math.h"
struct Vertex
{
	Vector3 pos, norm, binorm, tgt, color;
	Vector2 uv, uv2;
	Vertex(const Vertex& vertex)
	{
		this->pos = vertex.pos;
		this->norm = vertex.norm;
		this->binorm = vertex.binorm;
		this->tgt = vertex.tgt;
		this->color = vertex.color;
		this->uv = vertex.uv;
		this->uv2 = vertex.uv2;
	}
	Vertex()
	{

	}
};