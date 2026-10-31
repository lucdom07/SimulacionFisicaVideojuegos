#ifndef __RENDER_UTILS_H__
#define __RENDER_UTILS_H__

#include "PxPhysicsAPI.h"
#include "core.hpp"
#include "Vector3D.h"

class RenderItem;
void RegisterRenderItem(const RenderItem* _item);
void DeregisterRenderItem(const RenderItem* _item);

class RenderItem
{
public:
	RenderItem(physx::PxShape* _shape, const physx::PxTransform* _trans, const Vector4& _color) :
		shape(_shape), transform(_trans), actor(NULL), color(_color), references(1)
	{
		shape->acquireReference();
		RegisterRenderItem(this);
	}

	RenderItem(physx::PxShape* _shape, const Vector4& _color) :
		shape(_shape), transform(NULL), actor(NULL), color(_color), references(1)
	{
		shape->acquireReference();
		RegisterRenderItem(this);
	}

	RenderItem(physx::PxShape* _shape, const physx::PxRigidActor* _actor, const Vector4& _color) :
		shape(_shape), transform(NULL), actor(_actor), color(_color), references(1)
	{
		shape->acquireReference();
		RegisterRenderItem(this);
	}

	RenderItem() : shape(NULL), transform(NULL), references(1) {}

	void addReference()
	{
		++references;
	}

	void release()
	{
		--references;
		if (references == 0)
		{
			DeregisterRenderItem(this);
			shape->release();
			delete this;
		}
	}

	Vector3D getDimensions() {
		if (shape->getGeometryType() == physx::PxGeometryType::eSPHERE) {
			float radius = shape->getGeometry().sphere().radius;
			return Vector3D(radius, radius, radius);
		}
		else {
			float width = shape->getGeometry().box().halfExtents.x;
			float height = shape->getGeometry().box().halfExtents.y;
			float depth = shape->getGeometry().box().halfExtents.z;
			return Vector3D(width, height, depth);
		}
	}

	bool checkCollision(RenderItem* other) {
		Vector3D thisDim = getDimensions();
		Vector3D otherDim = other->getDimensions();
		Vector3 thisPos = transform->p;
		Vector3 otherPos = other->transform->p;
		return thisPos.x < otherPos.x + otherDim.x && otherPos.x < thisPos.x + thisDim.x &&
			thisPos.y < otherPos.y + otherDim.y && otherPos.y < thisPos.y + thisDim.y &&
			thisPos.z < otherPos.z + otherDim.z && otherPos.z < thisPos.z + thisDim.z;
	}

public:
	physx::PxShape* shape;
	const physx::PxTransform* transform;
	const physx::PxRigidActor* actor;
	Vector4 color;

	unsigned references;
};

double GetLastTime();
Camera* GetCamera();

physx::PxShape* CreateShape(const physx::PxGeometry& geo, const physx::PxMaterial* mat = nullptr);

#endif