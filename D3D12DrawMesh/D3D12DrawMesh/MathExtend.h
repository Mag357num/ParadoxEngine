#pragma once
#include "stdafx.h"

#include <glm.hpp>
#include <ext/vector_float3.hpp>
#include <ext/matrix_float4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/euler_angles.hpp>
#include <gtx/transform.hpp>

using FVector2 = glm::vec2;
using FVector = glm::vec3;
using FVector4 = glm::vec4;
using FMatrix = glm::mat4;
using FQuat = glm::tquat<float>;

struct FTransform
{
	FVector Scale;
	FQuat Quat;
	FVector Translation;
};

float Atan2(const float& Y, const float& X);

FVector4 GetBufferSizeAndInvSize(FVector2 Param);