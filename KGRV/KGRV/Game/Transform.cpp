#include "Transform.h"

DirectX::XMMATRIX Transform::GlobalPosMatrix()
{
	DirectX::XMMATRIX globalMatrix = DirectX::XMMatrixIdentity()
		* DirectX::XMMatrixScaling(scale.x, scale.y, scale.z)
		* DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z)
		* DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	return globalMatrix;
}

void Transform::UpdateValues()
{
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	this->forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	this->up = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, vecRotationMatrix);

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