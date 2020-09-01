#include <d3d11.h>

// XNA math library
//#include <xnamath.h> instead use below
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

// overload printing operation
std::ostream& operator<<(std::ostream& os, DirectX::FXMVECTOR v)
{
	DirectX::XMFLOAT3 dest;
	DirectX::XMStoreFloat3(&dest, v);
	os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ")";
	return os;
}


void DirectXVectorFuncs()
{
	// use XMVECTOR to variables & calculation
	DirectX::XMVECTOR vector = { 1, 2, 3 };

	// use XMFLOAT to class member data
	DirectX::XMFLOAT2 float2 = { 1, 2 };

	// load XMFLOAT to XMVECTOR when calculation
	vector = DirectX::XMLoadFloat2(&float2);
	// Store XMVECTOR to XMFLOAT when store data
	DirectX::XMStoreFloat2(&float2, vector);

	// Use this when we only want to access in certain value
	float x = DirectX::XMVectorGetX(vector); // XMVectorSetX

	// passing parameter - use FXMVECTOR or CXMVECTOR
	/*
	XMINLINE XMMATRIX XMMatrixTransformation2D(				First 3 XMVECTORs - use FXMVECTOR
		FXMVECTOR ScalingOrigin,							After 3 - use CXMVECTOR
		FLOAT ScalingOrientation,
		FXMVECTOR Scaling,
		FXMVECTOR RotationOrigin,
		FLOAT Rotation,
		CXMVECTOR Translation);
		*/

	// constant XMVECTOR - use XMVECTORF32 or XMVECTORU32
	static const DirectX::XMVECTORF32 exampleConst = { 1.f, 1.f, 1.f, 1.f };

	// PIs
	DirectX::XM_PI;
	DirectX::XM_2PI;

	// converting between radians & degrees
	DirectX::XMConvertToRadians(1.f);
	DirectX::XMConvertToDegrees(DirectX::XM_PI);

	// max, min
	DirectX::XMMin(1, 2);

	// vector functions
	DirectX::XMVECTOR vec1 = DirectX::XMVectorZero(); // return zero vector
	DirectX::XMVECTOR vec2 = DirectX::XMVectorSplatOne(); // return {1, 1, 1, 1}
	DirectX::XMVECTOR vec3 = DirectX::XMVectorSet(1.f, 2.f, 3.f, 4.f); // return {1, 2, 3, 4}
	DirectX::XMVECTOR vec4 = DirectX::XMVectorReplicate(1.f); //return {1, 1, 1, 1}
	DirectX::XMVECTOR vec5 = DirectX::XMVectorSplatX(vector); // return {vector.x, vector.x, vector.x, vector.x}

	// other functions - returns XMVECTOR with {result, result, result, result}
	vec1 = DirectX::XMVector3Length(vector); // return length
	vec2 = DirectX::XMVector3LengthSq(vector); // return squared length
	vec3 = DirectX::XMVector3Dot(vec1, vec2); // return dot product
	vec4 = DirectX::XMVector3Cross(vec1, vec2); // return cross
	vec5 = DirectX::XMVector3Normalize(vec1); // return normalized vector
	vec1 = DirectX::XMVector3Orthogonal(vec1); // return vector that orthogonal to vec1
	vec2 = DirectX::XMVector3AngleBetweenVectors(vec1, vec2); // return angle between two vectors
	DirectX::XMVector3ComponentsFromNormal(&vec1, &vec2, vec3, vec4); // returns vec1 - projecting vec3 to vec4
																	  // returns vec2 - perpendicular to vec3, vec4
	bool isEqual = DirectX::XMVector3Equal(vec1, vec2);
	bool isNotEqual = DirectX::XMVector3NotEqual(vec1, vec2);
}

void DirectXMatrixFuncs()
{
	// declaration
	DirectX::XMMATRIX matrix;

	matrix = DirectX::XMMatrixIdentity();	// return identity matrix

	bool isIdentity = DirectX::XMMatrixIsIdentity(matrix);	// return if matrix is identity or not
	
	matrix = DirectX::XMMatrixMultiply(matrix, matrix);	// matrix multiply
	matrix = DirectX::XMMatrixTranspose(matrix);

	DirectX::XMVECTOR vector = DirectX::XMMatrixDeterminant(matrix); //return determinant of the matrix

	matrix = DirectX::XMMatrixInverse(&vector, matrix); // return inverse matrix with vector-(det of matrix), matrix


}

void DirectXTransformations()
{
	DirectX::XMMATRIX matrix = DirectX::XMMatrixScaling(1.f, 1.f, 1.f); // return scaling matrix

	float angle = DirectX::XM_PI;
	matrix = DirectX::XMMatrixRotationX(angle); // clockwise rotation by angle

	DirectX::XMVECTOR axis = { 1.f, 1.f, 1.f };
	matrix = DirectX::XMMatrixRotationAxis(axis, angle);  // clockwise rotation about axis by angle

	matrix = DirectX::XMMatrixTranslation(1.f, 1.f, 1.f);
	matrix = DirectX::XMMatrixTranslationFromVector(axis); // translation by vector amount
	
	DirectX::XMVECTOR vector = DirectX::XMVector3Transform(axis, matrix); // matrix multiplication with vector(axis)

	// NOTE : THESE TWO FUNCTION USES FIXED W VALUE FOR VECTOR
	vector = DirectX::XMVector3TransformCoord(vector, matrix); // vector-matrix product vM with v_w = 1 (point)
	vector = DirectX::XMVector3TransformNormal(vector, matrix); // vector-matrix product vM with v_w = 0 (vector)


}	