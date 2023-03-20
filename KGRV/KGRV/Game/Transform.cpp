#include "Transform.h"
using namespace std;

DirectX::XMMATRIX Transform::GlobalPosMatrix()
{
	DirectX::XMMATRIX globalMatrix = DirectX::XMMatrixIdentity()
		* DirectX::XMMatrixScaling(scale.x, scale.y, scale.z)
		* DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z)
		* DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	return globalMatrix;
}

void Transform::SetParent(Transform* newParent, bool saveLocalPosition)
{
	if (newParent == this) {
		return;
	}
	auto lastGlobalPos = GlobalPosition();
	auto lastGlobalRot = GlobalRotation();
	if (parent != nullptr) {
		parent->RemoveChild(this);
	}
	parent = newParent;
	parent->AddChild(this);
	if (!saveLocalPosition) {
		SetGlobalPos(lastGlobalPos);
		SetGlobalRotation(lastGlobalRot);
	}
}

void Transform::UpdateValues()
{
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	this->forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	this->up = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, vecRotationMatrix);

}
DirectX::XMMATRIX Transform::LocalToGlobalMatrix()
{
	auto curMatrix = GetLocalToParentMatrix();
	auto curParent = parent;

	while (curParent != nullptr)
	{
		curMatrix *= curParent->GetLocalToParentMatrix();
		curParent = curParent->parent;
	}

	return curMatrix;
}
DirectX::XMMATRIX Transform::GlobalToLocalMatrix()
{
	std::vector<Transform*> parents;

	auto curParent = parent;
	if (curParent != nullptr) parents.push_back(curParent);

	while (curParent != nullptr)
	{
		curParent = curParent->parent;
		if (curParent != nullptr) parents.push_back(curParent);
	}
	auto curMatrix = XMMatrixIdentity();
	for (int i = parents.size() - 1; i >= 0; --i)
	{
		curMatrix *= XMMatrixInverse(nullptr, parents[i]->GetLocalToParentMatrix());
	}
	curMatrix *= XMMatrixInverse(nullptr, GetLocalToParentMatrix());
	return curMatrix;

}
void Transform::RemoveChild(Transform* child)
{
	vector<Transform*>::iterator position = std::find(children.begin(), children.end(), child);
	if (position != children.end())
		children.erase(position);
}
void Transform::AddChild(Transform* child)
{
	children.push_back(child);
}
void Transform::LookAt(XMFLOAT3 target)
{
	auto curPos = position;
	XMFLOAT3 lookVector = { curPos.x - target.x, curPos.y - target.y, curPos.z - target.z };
	if (lookVector.x == 0 && lookVector.y == 0 && lookVector.z == 0)
		return;
	float pitch = 0.0f;
	float yaw = 0.0f;
	if (lookVector.y != 0.0f)
	{
		const float distance = sqrt(lookVector.x * lookVector.x + lookVector.z * lookVector.z);
		pitch = atan(lookVector.y / distance);
	}
	if (lookVector.x != 0.0f)
	{
		yaw = atan(lookVector.x / lookVector.z);
	}
	if (lookVector.z > 0)
		yaw += XM_PI;
	rotation.x = pitch;
	rotation.y = yaw;
	rotation.z = 0.0f;

}


DirectX::XMMATRIX Transform::LocalToGlobalRotationMatrix()
{
	auto curMatrix = XMMatrixRotationRollPitchYawFromVector(rotation);
	auto curParent = parent;

	while (curParent != nullptr)
	{
		curMatrix *= XMMatrixRotationRollPitchYawFromVector(curParent->rotation);
		curParent = curParent->parent;
	}

	return curMatrix;
}

XMMATRIX Transform::GlobalToLocalRotationMatrix()
{

	std::vector<Transform*> parents;

	auto curParent = parent;
	if (curParent != nullptr) parents.push_back(curParent);

	while (curParent != nullptr)
	{
		curParent = curParent->parent;
		if (curParent != nullptr) parents.push_back(curParent);
	}

	auto curMatrix = XMMatrixRotationRollPitchYaw(0, 0, 0);
	for (int i = parents.size() - 1; i >= 0; --i)
	{
		curMatrix *= XMMatrixInverse(nullptr, XMMatrixRotationRollPitchYawFromVector(parents[i]->rotation));
	}
	curMatrix *= XMMatrixInverse(nullptr, XMMatrixRotationRollPitchYawFromVector(rotation));


	return curMatrix;
}