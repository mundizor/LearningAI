#include "BaseEntity.h";

sf::CircleShape* BaseEntity::GetShape()
{
	return mShape;
}

void BaseEntity::SetShape(sf::CircleShape* _shape)
{
	mShape = _shape;
}
